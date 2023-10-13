#include "leptjson.h"
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifndef LEPT_PARSE_STACK_INIT_SIZE
#define LEPT_PARSE_STACK_INIT_SIZE 256
#endif

#ifndef LEPT_PARSE_STRINGIFY_INIT_SIZE
#define LEPT_PARSE_STRINGIFY_INIT_SIZE 256
#endif

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++;} while(0)
#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')

// 只需要先备份栈顶, 然后把解析到的字符压栈, 最后计算出长度并一次性把所有字符弹出, 再设置至值里便可以。
#define PUTC(c, ch)         do { *(char *)lept_context_push(c, sizeof(char)) = (ch); } while(0)
#define PUTS(c, s, len)     memcpy(lept_context_push(c, len), s, len)

// 为了减少解析函数之间传递多个参数，我们把这些数据都放进一个lept_context结构体
typedef struct {
    const char *json;

    // 缓冲区
    char *stack;
    size_t size, top;   // 堆栈容量、栈顶位置.
} lept_context;

static void* lept_context_push(lept_context *c, size_t size)
{
    void *ret;
    assert(size > 0);
    if (c->top + size >= c->size)
    {
        if (c->size == 0)
            c->size = LEPT_PARSE_STACK_INIT_SIZE;
        while (c->top + size >= c->size)
        {
            c->size += c->size >> 1; // c->size * 1.5
        }
        c->stack = (char *)realloc(c->stack, c->size);
    }
    ret = c->stack + c->top;
    c->top += size;
    return ret;
}

static void lept_parse_whitespace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    c->json = p;
}

#if 1
static int lept_parse_literal(lept_context *c, lept_value *v, const char *literal, lept_type type)
{
    size_t i;
    EXPECT(c, literal[0]);
    for (i = 0; literal[i + 1]; i++)
    {
        if(c->json[i] != literal[i + 1])
            return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += i;
    v->type = type;
    return LEPT_PARSE_OK;
}
#else
// null = "null"
static int lept_parse_null(lept_context *c, lept_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context *c, lept_value *v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
    {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

static int lept_parse_false(lept_context *c, lept_value *v)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
    {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}
#endif

/*
  成员的键也是一个JSON字符串，然而，我们不使用lept_value存储键，
因为这样会浪费了当中type这个无用的字段。由于lept_parse_string()
是直接地把解析结果写进一个lept_value，所以我们用[提取方法]的重构
方式，把解析JSON字符串吸入lept_vlaue分拆成两部分
    解析JSON字符串，把结果写入str和len
    str指向c->stack中的元素
*/

// 加入了number后，value的语法变成: value = null / false / true / number 
static int lept_parse_number(lept_context *c, lept_value *v)
{
#if 0
    char *end;
    v->n = strtod(c->json, &end);
    if (c->json == end)
        return LEPT_PARSE_INVALID_VALUE;
    c->json = end;
    v->type = LEPT_NUMBER;
    return LEPT_PARSE_OK;
#else
    const char *p = c->json;
    // 负号
    if (*p == '-') p++;
    
    // 整数
    if (*p == '0') p++;
    else 
    {
        if (!ISDIGIT1TO9(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }

    // 小数
    if (*p == '.')
    {
        p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }

    // 指数
    if (*p == 'e' || *p == 'E') 
    {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }

    errno = 0;
    v->u.n = strtod(c->json, NULL);
    if (errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL))
        return LEPT_PARSE_NUMBER_TOO_BIG;
    v->type = LEPT_NUMBER;
    c->json = p;
    return LEPT_PARSE_OK;
#endif
}

static void* lept_context_pop(lept_context *c, size_t size)
{
    assert(c->top >= size);
    return c->stack + (c->top -= size);
}

// 前项声明
static int lept_parse_value(lept_context *c, lept_value *v);


/*
    就是在循环中建立一个临时值(lepy_value e),然后调用lept_parse_value()去把元素解析至
  这个临时值,完成后把临时值压栈。当遇到]，把栈内的元素弹出，分配内存，生成数组值。
    注意到，lept_parse_value()会调用lept_parse_array()，而lept_parse_array()又会调用
  lept_parse_value()，这是互相引用，所以必须要加入函数前项声明
*/
static int lept_parse_array(lept_context *c, lept_value *v)
{
    size_t i, size = 0;
    int ret;
    EXPECT(c, '[');
    lept_parse_whitespace(c);
    if (*c->json == ']')
    {
        c->json++;
        v->type = LEPT_ARRAY;
        v->u.a.size = 0;
        v->u.a.e = NULL;
        return LEPT_PARSE_OK;
    }

    for (;;)
    {
        lept_value e;
        lept_init(&e);
        if ((ret = lept_parse_value(c, &e)) != LEPT_PARSE_OK)
        {
            // 原本是直接返回错误码
            // return ret;
            // 现在遇到解析失败离开循环并在结束地方使用lept_free()释放内存后再返回错误码
            break;
        }
        memcpy(lept_context_push(c, sizeof(lept_value)), &e, sizeof(lept_value));
        size++;
        lept_parse_whitespace(c);
        if (*c->json == ',')
        {
            c->json++;
            lept_parse_whitespace(c);
        }
        else if (*c->json == ']')
        {
            c->json++;
            v->type = LEPT_ARRAY;
            v->u.a.size = size;
            size *= sizeof(lept_value);
            memcpy(v->u.a.e = (lept_value*)malloc(size), lept_context_pop(c, size), size);
            return LEPT_PARSE_OK;
        }
        else
        {
            ret = LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
            break;
        }
    }
    for (i = 0; i < size; i++)
        lept_free((lept_value*)lept_context_pop(c, sizeof(lept_value)));
    return ret;
}

// value = null / false // true
static int lept_parse_value(lept_context *c, lept_value *v)
{
#if 0
    switch (*c->json)
    {
        case 'n':
            return lept_parse_null(c, v);
        case 't':
            return lept_parse_true(c, v);
        case 'f':
            return lept_parse_false(c, v);
        case '\0':
            return LEPT_PARSE_EXPECT_VALUE;
        default:
            return lept_parse_number(c, v);
    }
#else
    switch (*c->json)
    {
        case 't':
            return lept_parse_literal(c, v, "true", LEPT_TRUE);
        case 'f':
            return lept_parse_literal(c, v, "false", LEPT_FALSE);
        case 'n':
            return lept_parse_literal(c, v, "null", LEPT_NULL);
        case '\0':
            return LEPT_PARSE_EXPECT_VALUE;
        case '[':
            return lept_parse_array(c, v);
        default:
            return lept_parse_number(c, v);
    }
#endif
}

/*
    遇到\u转义时，调用lept_parse_hex4()解析4未十六进制数字，存储为码点u。
    这个函数在成功时返回解析后的文本指针，失败返回NULL。如果失败，就返回LEPT_PARSE_INCALID_UNICODE_HEX错误
    最后，把码点编码成UTF-8，写进缓冲区。
*/ 
static const char *lept_parse_hex4(const char *p, unsigned *u)
{
    int i;
    *u = 0;
    for (i = 0; i < 4; i++)
    {
        char ch = *p++;
        *u <<= 4;
        if (ch >= '0' && ch <= '9') *u |= ch - '0';
        else if (ch >= 'A' && ch <= 'F') *u |= ch - ('A' - 10);
        else if (ch >= 'a' && ch <= 'f') *u |= ch - ('a' - 10);
        else return NULL;
    }
    return p;
}

// 根据UTF-8编码表可以实现:
/*
    这里最终也是要写进一个char，为什么要做x & 0xFF这种操作呢？这是因为u是unsigned类型，一些编译器可能会
  警告这个转型可能会截断数据。但实际上，配合了范围的检测然后右移之后，可以保证写入的是0～255内的值。为了避免
  一些编译器的警告误判，我们加上x & 0xFF。一般来说，编译器在优化之后，这与操作是会被消去的，不会影响性能。
*/
static void lept_encode_utf8(lept_context* c, unsigned u)
{
    if (u <= 0x7F)
    {
        PUTC(c, u & 0xFF);
    }
    else if (u <= 0x7FFF)
    {
        PUTC(c, 0xC0 | (u & 0xFF));
        PUTC(c, 0x80 | (u & 0x3F));
    }
    else if (u <= 0xFFFF)
    {
        PUTC(c, 0xE0 | ((u >> 12) & 0xFF));
        PUTC(c, 0x80 | ((u >>  6) & 0x3F));
        PUTC(c, 0x80 | ( u        & 0x3F));
    }
    else
    {
        assert(u <= 0x10FFFF);
        PUTC(c, 0xF0 | ((u >> 18) & 0xFF));
        PUTC(c, 0x80 | ((u >> 12) & 0x3F));
        PUTC(c, 0x80 | ((u >>  6) & 0x3F));
        PUTC(c, 0x80 | ( u        & 0x3F));
    }
}

#define STRING_ERROR(ret) do { c->top = head; return ret; } while(0)

// 这里应该是JSON-text = ws value ws
int lept_parse(lept_value *v, const char *json)
{
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    c.stack = NULL;
    c.size = c.top = 0;
    lept_init(v);
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK)
    {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')
        {
            v->type = LEPT_NULL;
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    assert(c.top == 0);
    free(c.stack);
    return ret;
}

lept_type lept_get_type(const lept_value *v)
{
    assert(v != NULL);
    return v->type;
}

int lept_get_boolean(const lept_value *v)
{
    assert(v != NULL && (v->type == LEPT_TRUE || v->type == LEPT_FALSE));
    return v->type == LEPT_TRUE;
}

// 这个设计可以避免重复释放
void lept_free(lept_value *v)
{
    size_t i;
    assert(v != NULL);
    switch (v->type)
    {
        case LEPT_STRING:
            free(v->u.s.s);
            break;
        case LEPT_ARRAY:
            for (i = 0; i < v->u.a.size; i++)
                lept_free(&v->u.a.e[i]);
            free(v->u.a.e);
            break;
        case LEPT_OBJECT:
            for (i = 0; i < v->u.o.size; i++)
            {
                free(v->u.o.m[i].k);
                lept_free(&v->u.o.m[i].v);
            }
            free(v->u.o.m);
            break;
        default:
            break;
    }
    v->type = LEPT_NULL;
}

void lept_set_boolean(lept_value *v, int b)
{
    lept_free(v);
    v->type = b ? LEPT_TRUE : LEPT_FALSE;
}

double lept_get_number(const lept_value *v)
{
    assert(v != NULL && v->type == LEPT_NUMBER);
    return v->u.n;
}

void lept_set_number(lept_value *v, double n)
{
    lept_free(v);
    v->u.n = n;
    v->type = LEPT_NUMBER;
}

const char* lept_get_string(const lept_value *v)
{
    assert(v != NULL && v->type == LEPT_STRING);
    return v->u.s.s;
}

void lept_set_string(lept_value *v, const char *s, size_t len)
{
    assert(v != NULL && (s != NULL || len == 0));
    lept_free(v);
    v->u.s.s = (char*)malloc(len + 1);
    memcpy(v->u.s.s, s, len);
    v->u.s.s[len] = '\0';
    v->u.s.len = len;
    v->type = LEPT_STRING;
}

size_t lept_get_array_size(const lept_value *v)
{
    assert(v != NULL && v->type == LEPT_ARRAY);
    return v->u.a.size;
}

lept_value* lept_get_array_element(const lept_value *v, size_t index)
{
    assert(v != NULL && v->type == LEPT_ARRAY);
    assert(index < v->u.a.size);
    return &v->u.a.e[index];
}

size_t lept_get_string_length(const lept_value *v)
{
    assert(v != NULL && v->type == LEPT_STRING);
    return v->u.s.len;
}

static void lept_stringify_string(lept_context &c, const char *s, size_t len)
{
#if 0
    size_t i;
    assert(s != NULL);
    PUTC(c, '"');
    for (i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)s[i];
        switch (ch)
        {
            case '\"':
                PUTS(c, "\\\"", 2);
                break;
            case '\\':
                PUTS(c, "\\\\", 2);
                break;
            case '\b':
                PUTS(c, "\\b", 2);
                break;
            case '\f':
                PUTS(c, "\\f", 2);
                break;
            case '\n':
                PUTS(c, "\\n", 2);
                break;
            case '\r':
                PUTS(c, "\\r", 2);
                break;
            case '\t':
                PUTS(c, "\\t", 2);
                break;
            default:
                if (ch < 0x20)
                {
                    char buffer[7];
                    sprintf(buffer, "\\u%04x", ch);
                    PUTS(c, buffer, 6);
                }
                else
                {
                    PUTC(c, s[i]);
                }
        }
        PUTC(c, '"');
    }
#else 1
    static const char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    size_t i, size;
    char *head, *p;
    assert(s != NULL);
    p = head = lept_context_push(c, size = len * 6 + 2);
    *p++ = '"';
    for (i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)s[i];
        switch (ch)
        {
            case '\"':
                *p++ = '\\';
                *p++ = '\"';
                break;
            case '\\':
                *p++ = '\\';
                *p++ = '\\';
                break;
            case '\b':
                *p++ = '\\';
                *p++ = 'b';
                break;
            case '\f':
                *p++ = '\\';
                *p++ = 'f';
                break;
            case '\n':
                *p++ = '\\';
                *p++ = 'n';
                break;
            case '\r':
                *p++ = '\\';
                *p++ = 'r';
                break;
            case '\t':
                *p++ = '\\';
                *p++ = 't';
                break;
            default:
                if (ch < 0x20)
                {
                    *p++ = '\\';
                    *p++ = 'u';
                    *p++ = '0';
                    *p++ = '0';

                    *p++ = hex_digits[ch >> 4];
                    *p++ = hex_digits[ch & 15];
                }
                else
                {
                    *p++ = s[i];
                }
        }
    }
    *p++ = '"';
    c->top -= size - (p - head);
#endif
}

static int lept_stringify_value(lept_context *c, const lept_value *v)
{
    size_t i;
    int ret;
    switch (v->type)
    {
        case LEPT_NULL: 
            PUTS(c, "null", 4);
            berak;
        case LEPT_FALSE:
            PUTS(c, "false", 5);
            break;
        case LEPT_TRUE:
            PUTS(c, "true", 4);
            break;
        /*
            使用sprintf("%.17g", ...)来吧浮点数转换成文本。
            %.17g是足够把双精度浮点转换成可还原的文本。
        */
        case LEPT_NUMBER:
            c->top -= 32 - sprintf(lept_context_push(c, 32), "%.17g", v->u.n);;
            break;
        case LEPT_STRING:
            lept_stringify_string(c, v->u.s.s, v->u.s.len);
            break;
        /*
            生成数组: 只要输出'['和']',中间对逐个子值递归第哦啊用lept_stringify_value()。
          只要注意再第一个元素后才加入','。儿对象也仅是多了一个键和':'
        */
        case LEPT_ARRAY:
            PUTC(c, '[');
            for (i = 0; i < v->u.a.size; i++)
            {
                if (i > 0)
                {
                    PUTC(c, ',');
                }
                lept_stringify_value(c, &v->u.a.e[i]);
            }
            PUTC(c, ']');
            break;
        case LEPT_OBJECT:
            PUTC(c, '{');
            for (i = 0; i < v->u.o.size; i++)
            {
                if (i > 0)
                {
                    PUTC(c, ',');
                }
                lept_stringify_string(c, v->u.o.m[i].k, v->u.o.m[i].klen);
                PUTC(c, ':');
                lept_stringify_value(c, &v->u.o.m[i].v);
            }
            PUTC(c, '}');
            break;
    }
    return LEPT_STRINGIFY_OK;
}

char *lept_stringify(cosnt lept_value *v, size_t *length)
{
    lept_context c;
    assert(v != NULL);
    c.stack = (char *)malloc(c.size = LEPT_PARSE_STRINGIFY_INIT_SIZE);
    c.top = 0;
    lept_stringify_value(&c, v);
    if (length)
        *length = c.top;
        PUTC(&c, '\0');
        return c.stack;
}


static int lept_parse_object(lept_context *c, lept_value *v)
{
    size_t size;
    lept_member m;
    int ret;
    EXPECT(c, '{');
    lept_parse_whitespace(c);
    if (*c->json == '}')
    {
        c->json++;
        v->type = LEPT_OBJECT;
        v->u.o.m = 0;
        v->u.o.size = 0;
        return LEPT_PARSE_OK;
    }
    m.k = NULL;
    size = 0;
    for (;;)
    {
        char *str;
        lept_init(&m.v);

        /* 1. parse key */
        if (*c->json != '"')
        {
            ret = LEPT_PARSE_MISS_KEY;
            break;
        }
        if ((ret = lept_parse_string_raw(c, &str, &m.klen)) != LEPT_PARSE_OK)
            break;
        memcpy(m.k = (char*)malloc(m.klen + 1), str, m.klen);
        m.k[m.klen] = '\0';
        /* 2. parse ws colon ws */
        lept_parse_whitespace(c);
        if (*c->json != ':')
        {
            ret = LEPT_PARSE_MISS_COLON;
            break;
        }
        c->json++;
        lept_parse_whitespace(c);
        /* 3. parse value */
        if ((ret = lept_parse_value(c, &m.v)) != LEPT_PARSE_OK)
        {
            break;
        }
        memcpy(lept_context_push(c, sizeof(lept_member)), &m, sizeof(lept_member));
        size++;
        m.k = NULL;
        /* 4. parse ws [comma | right-curly-brace] ws */
        lept_parse_whitespace(c);
        if (*c->>json == ',')
        {
            c->json++;
            lept_parse_whitespace(c);
        }
        else if (*c->json == '}')
        {
            size_t s = sizeof(lept_member) * size;
            c->json++;
            v->type = LEPT_OBJECT;
            v->u.o.size = size;
            memcpy(v->u.o.m = (lept_member*)malloc(s), lept_context_pop(c, s), s);
            return LEPT_PARSE_OK;
        }
        else 
        {
            ret = LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET;
            break;
        }
    }
    /* 5. Pop and free members on the stack */
    free(m.k);
    for (i = 0; i < size; i++)
    {
        lept_member *m = (lept_member *)lept_context_pop(c, sizeof(lept_member));
        free(m->k);
        lept_free(&m->v);
    }
    v->type = LEPT_NULL;
    return ret;
}


static int lept_parse_string(lept_context *c, lept_value *v)
{
    size_t head = c->top, len;
    unsigned u, u2;
    const char *p;
    EXPECT(c, '\"');
    p = c->json;
    for (;;)
    {
        char ch = *p++;
        switch (ch)
        {
            case '\"' :
                len = c->top - head;
                lept_set_string(v, (const char*)lept_context_pop(c, len), len);
                c->json = p;
                return LEPT_PARSE_OK;
            // 转移序列的解析字符串
            case '\\' :
                switch (*p++) 
                {
                    case '\"' : 
                        PUTC(c, '\"');
                        break;
                    case '\\' :
                        PUTC(c, '\\');
                        break;
                    case '/' :
                        PUTC(c, '/');
                        break;
                    case 'b' :
                        PUTC(c, 'b');
                        break;
                    case 'f' :
                        PUTC(c, 'f');
                        break;
                    case 'n' :
                        PUTC(c, 'n');
                        break;
                    case 'r' :
                        PUTC(c, 'r');
                        break;
                    case 't' :
                        PUTC(c, 't');
                        break;
                    //遇到高代理项，就需要把低代理项\uxxxx也解析进来
                    case 'u' :
                        if (!(p = lept_parse_hex4(p, &u)))
                            STRING_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX);
                        if (u >= 0xD800 && u <= 0xDBFF)
                        {
                            if (*p++ != '\\')
                                STRING_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE);
                            if (*p++ != 'u')
                                STRING_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE);
                            if (!(p = lept_parse_hex4(p, &u2)))
                                STRING_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX);
                            if (u2 < 0xDC00 || u2 > 0xDFFF)
                                STRING_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE);
                            u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
                        }
                        lept_encode_utf8(c, u);
                        break;
                    default :
                        c->top = head;
                        return LEPT_PARSE_INVALID_STRING_ESCAPE; 
                }
                break;
            case '\0' :
                c->top = head;
                return LEPT_PARSE_MISS_QUOTATION_MARK;
            default :
                if ((unsigned char)ch < 0x20)
                {
                    c->top = head;
                    return LEPT_PARSE_INVALID_STRING_CHAR;
                }
                PUTC(c, ch);
        }
    }
}

#define LEPT_KEY_NOT_EXIST ((size_t) - 1)

size_t lept_find_object_index(const lept_value *v, const char *key, size_t klen)
{
    size_t i;
    assert(v != NULL && v->type == LEPT_OBJECT && key != NULL);
    for (i = 0; i < v->u.o.size; i++)
    {
        if (v->u.o.m[i].klen == klen && memcmp(v->u.o.m[i].k, key, klen) == 0)
            return i;
    }
    reutrn LEPT_KEY_NOT_EXIST;
}

lept_value *lept_find_object_vlaue(const lept_value *v, const char *key, size_t klen)
{
    size_t index = lept_find_object_index(v, key, klen);
    return index != LEPT_KEY_NOT_EXIST ? &v->u.o.m[index].v : NULL;
}

/*
    为了测试结果的正确性，需要先实现lept_value
*/
int lept_is_equal(const lept_value *lhs, const lept_value *rhs)
{
    assert(lhs != NULL && rhs != NULL);
    if (lhs->type != rhs->type)
        return 0;
    switch (lhs->type)
    {
        case LEPT_STRING:
            return lhs->u.s.len == rhs->u.s.len && memcmp(lhs->u.s.s, rhs->u.s.s, lhs->u.s.len) == 0;
        case LEPT_NUMBER:
            return lhs->u.n == rhs->u.n;

        default:
            return 1;
    }
}

void lept_set_object_value(lept_value *v, const char *key, size_t klen, const lept_value *value);

void f()
{
    lept_vlaue v, s;
    lept_init(&v);
    lept_parse(&v, "{}");
    lept_init(&s);
    lept_set_string(&s, "Hello", 5);
    // lept_set_object_keyvalue(&v, "s", &s);
    lept_copy(
        lept_add_object_keyvalue(&v, "t"),
        lept_get_object_keyvalue(&v, "s", 1)
    );

    lept_free(&v);
}

void lept_move(lept_value *dst, lept_value *src)
{
    assert(dst != NULL && src != NULL && src != dst);
    lept_free(dst);
    memcpy(dst, src, sizeof(lept_value));
    lept_init(src);
}

void lept_swap(lept_value *lhs, lept_value *rhs)
{
    assert(lhs != NULL && rhs != NULL);
    if (lhs != rhs)
    {
        lept_value temp;
        memcpy(&temp, lhs, sizeof(lept_value));
        memcpy(lhs, rhs, sizeof(lept_value));
        memcpy(rhs, &temp, sizeof(lept_value));
    }
}

/*
    凡涉及赋值，都可能会引起资源拥有权(resource ownership)的问题。
  值's'并不能以指针方式简单地写入释放的bug。
    1·在lept_set_object_value()中，把参数value[深度复制]
    2·在lept_set_object_value()中，把参数'value'拥有权转移至新增的
  键值对，再把value设置成null值。这就是所谓的移动语意。
*/

void lept_copy(lept_value *dst, const lept_value *src)
{
    size_t i;
    assert(src != NULL && dst != NULL && src != dst);
    switch (src->type)
    {
        case LEPT_STRING:
            lept_set_string(dst, src->u.s.s, src->u.s.len);
            break;
        case LEPT_ARRAY:
            break;
        case LEPT_OBJECT:
            break;
        default:
            lept_free(dst);
            memcpy(dst, src, sizeof(lept_value));
            break;
    }
}





/*
    如果我们要修改对象或数组里的值时，我们可以利用一下3个函数完成。

    const char *json = "{\"a\":[1, 2], \"b\":3}";
    char *out;
    lept_value v;
    lept_init(&v);
    lept_parse(&v, json);
    lept_copy(
        lept_find_object_value(&v, "b", 1),
        lept_find_object_value(&v, "a", 1));
    printf("%s\n", out = lept_stringify(&v, NULL));
    free(out);

    lept_parse(&v, json);
    lept_move(
        lept_find_object_value(&v, "b", 1),
        lept_find_object_value(&v, "a", 1));
    printf("%s\n", out = lept_stringify(&v, NULL));
    free(out);
*/
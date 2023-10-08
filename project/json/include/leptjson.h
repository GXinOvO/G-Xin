#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> // size_t

// JSON中6中数据类型
typedef enum
{
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

// JSON作为一个属性结构，每个都需要一个节点表示
/*
    这样的话，我们需要把之前的v->n改成v->u.n。而要访问字符串的数据，则要使用v->u.s.s和v->u.s.len。
    但其实C11新增来匿名struct/union语法, 就可以采用v->n、v->s、v->len来作访问。
*/
typedef struct {
#if 0
    char *s;
    size_t len;
    double n;
#else
    union {
        struct { 
            char *s;
            size_t len;
        } s;
        double n;
    } u;
#endif
    lept_type type;
} lept_value;

enum 
{
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG,
    LEPT_PARSE_MISS_QUOTATION_MARK,
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    LEPT_PARSE_INVALID_STRING_CHAR,
    LEPT_PARSE_INVALID_UNICODE_HEX,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE
};

// 解析JSON
int lept_parse(lept_value *v, const char *json);

// 访问结果
lept_type lept_get_type(const lept_value *v);

double lept_get_number(const lept_value *v);

#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

void lept_free(lept_value *v);

#define lept_set_null(v) lept_free(v)

// 由于字符串的长度不是固定的, 我们要动态分配内存
void lept_set_string(lept_value *v, const char *s, size_t len);

int lept_get_boolean(const lept_value *v);

void lept_set_boolean(lept_value *v, int b);

double lept_get_number(const lept_value *v);

void lept_set_number(lept_value *v, double n);

const char* lept_get_string(const lept_value *v);

size_t lept_get_string_length(const lept_value *v);

#endif
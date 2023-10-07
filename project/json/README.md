1. JSON语法子集
    JSON-text = ws value ws
    ws = *(%x20 / %x09 / %x0A / %x0D)
    value = null / false / true
    null = "null"
    false = "false"
    true = "true"
  
  当中%xhh表示以16进制表示的字符, / 是多选一, *是零或多个, ()用于分组
  第一行: JSON文本由3部分组成，首先是空白(whitespace), 接着是一个值, 最后是空白
  第二行: 所谓空白, 是由零或多个空格符、制表符、换行符、回车符所组成
  第三行: 我们显示的值只可以是null、false或true，他们分别由对应的字面值
  我们的解析器应能判断输入是否一个合法的JSON。如果输入的JSON不符合这个语法，我们要产生对应的错误码，方便使用者追查问题

  在这个JSON语法子集中，我们定义3中错误码:
    ·若一个JSON只含有空白, 传回LEPT_PARSE_EXPECT_VALUE
    ·若一个值以后, 在空白之后还有其他字符, 传回LEPT_PARSE_ROOT_NOT_SINGULAR
    ·若值不是那三种字面值，传回LEPT_PARSE_INVALID_VALUE

  leptjson是一个手写的递归下降解析器。由于JSON语法特别简单，我们不需要写分词器，只需检测下一个字符，便可以知道他是哪种类型的值，然后调用相关的分析函数。对于完整的JSON语法，跳过空白后，只需检测当前字符:
    · n -> null
    · t -> true
    · f -> false
    · " -> string
    · 0-9/- -> number
    · [ -> array
    · { -> object
  所以，我们可以按照JSON语法一节的EBNF简单翻译成解析函数 

2. JSON数字语法
    number = [ "-" ] int [ frac ] [ exp ]
    int = "0" / digit1-9 *digit
    frac = "." 1*digit
    exp = ("e" / "E") ["-" / "+"] 1*digit

  number是以十进制表示, 它主要由4部分顺序组成: 负号、整数、小数、指数。只有整数是必须部分。注意和直觉可能不同的是，正号是不合法的。
  整数部分如果是0开始, 只能是单个0; 而由1-9开始的话,可以加任意数量的数字(0-9)。也就是说, 0123不是一个合法的JSON数字。
  小数部分比较直观, 就是小数点后是一或多个数字(0-9)
  JSON可使用科学记数法，指数部分由大写E或小写e开始, 然后可有正负号, 之后是一或多个数字(0-9).

3. 数字表示方式
  从JSON数字的语法, 我们可能直观地会认为它应该表示位一个浮点数(floating point number), 因为它带有小数和指数部分。然而, 我怕标准中并没有限制数字的范围或精度。为简单起见, leptjson选择以双精度浮点数(C中的double类型)来存储JSON数字。

4. 十进制转换至二进制
  我们需要把十进制的数字转换成二进制的double。这并不是容易的事情。为了简单起见, leptjson将使用标准库strtod()来进行转换。strtod()可转换JSON所要求的格式, 但问题是, 一些JSON不容许的格式, strtod()也可转换, 所以我们需要自行做格式校验。

  
5. JSON的字符串语法和C语言很相似，都是以双引号把字符扩起来，如"Hello"。但字符串采用了双引号作分隔，那么怎样可以在字符串中插入一个双引号?
  把a"b写成"a"b"肯定不行，都不知道那里是字符串的结束了。因此，我们需要引入转义字符(escape character), C语言和JSON都使用 \ (反斜线)作为转义字符, 那么"在字符串中就表示为 \" , a"b的JSON字符串则写成"a\"b"。如以下的字符串语法所示, JSON共支持9种转义序列:
  string = quotation-mark *char quotation-mark
  char = unescaped /
    escape (
      %x22 /        ; "     quotation mark    U+0022
      %x5C /        ; \     reverse solidus   U+005C
      %x2F /        ; /     solidus           U+002F
      %x62 /        ; b     backspace         U+0008
      %x66 /        ; f     form feed         U+000C
      %x6E /        ; n     line feed         U+000A
      %x72 /        ; r     carriage return   U+000D
      %x74 /        ; t     tab               U+0009
      %x75 4HEXDIG ); uXXXX                   U+XXXX
  escape = %x5C
  quotation-mark = %x22 ; "
  unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
  简单翻译一下，JSON字符串是由前后两个双引号夹着零至多个字符。

  之中空缺的%x22是双引号, %x5C是单斜线。而不合法的字符是%x00至%x1F，需要简单地在defalut里处理(lept_parse_string)
  其中char带不带符号，是实现定义的.如果编译器定义char为带符号的话，(unsigned char)ch >= 0x80的字符，都会变成负数，并产生LEPT_PARSE_INVALID_STRING_CHAR错误。我们现时还没有测试ASCII以外的字符，所以有没有转型至不带符号都不影响

6. 字符串表示
  在C语言中, 字符串一般表示为空结尾字符串(null-terminated string)， 即以空字符('\0')代表字符串的结束。然而，JSON字符串是允许含有空字符的, 例如这个JSON "Hello\u0000World"就是单个字符串, 解析后为11个字符。如果纯粹使用空结尾字符串来表示JSON解析后的结果,就没法处理空字符。

7. 缓冲区与堆栈
  解析字符串(以及之后的数组、对象)时, 需要把解析的结果先储存在一个临时的缓冲区，最后再用lept_set_string把缓冲区的结果设进值之中。在完成解析一个字符串之后，这个缓冲区的大小是不能预知的.因此，可以采用动态数组,即数组空间不足时，能自动扩展。

  因此, 可以分配内存来储存解析后的字符，以及记录字符的数目(即字符串长度)。由于大部分C程序都假设字符串是空结尾字符串, 我们还是在最后加上一个空字符, 那么不需处理\u0000这种字符的应用可以简单地把它当作是空结尾字符串。
  
8. Linux下的内存泄漏检测方法
  valgrind --leak-check=full ./leptjson_test

9. Unicode
  ASCII, 一种7-bit字符编码系统，在计算机中以一个字节存储一个字符。然而，它仅适合美国英语, 甚至一些英语中常用的标点符号、重音符号都不能表示，无法表示各国语言，特别是中日韩语等表意文字。
  在Unicode出现之前，各地区制定了不同的编码系统,如中文主要用GB 2312和大五码、日文主要用JIS等。
  之后指定了Unicode，收录135中语言共128237个字符。
  每个字符映射至一个整数码点，码点范围是0~0x10FFFF，码点又通常记作U+XXXX，当中XXXX为16进位数字。
  UTF-8的编码单元是8位的字节，成为最流行格式是因为:
    ·它采用字节为编码单元, 不会有字节序的问题
    ·每个ASCII字符只需一个字节去储存
    ·如果程序猿来是以字节方式储存字符，理论上不需要特别改动就能处理UTF-8的数据

注:
  1. strtod():
    会扫描参数nptr字符串，跳过前面的空格字符，直到遇上数字或 正负符号才开始做转换，到出现非数字或字符串结束时('\0')才结束转换，并将结果返回。

需求:
  由于UTF-8的普及性，大部分的JSON也通常会以UTF-8存储。我们的JSON库也会只支持UTF-8.
  C标准库没有关于Unicode的处理共轭能(C++11有),我们会实现JSON库所需的字符编码处理功能。
  对于非转义(unescaped)的字符，只要他们不少于32(0~31是不合法的编码单元), 我们可以直接复制到结果。假设输入是以合法UTF-8编码
  而对于JSON字符串中的\uXXXX是以16进制表示码点U+0000至U+FFFF, 我们需要:
    1·解析4位十六进制整数为码点
    2·由于字符串是以UTF-8存储, 我们要把这个码点编码称UTF-8.
  但4位的16进制数字只能表示0至0xFFFF，但之前我们说的码点是从0至0x10FFFF,那怎么能表示多出来的码点？
  其实, U+0000至0xFFFF这组Unicode字符称为基本多这种平面，还有另外16个平面。那么BMP之外的字符，JSON会使用代理对(surrogate pair)表示\uXXXX \uYYYY。在BMP中, 保留了2048个代理码点。如果第一个码点是U+D800至U+DBFF，我们便知道他的代码对的高代理项(high surrogate)，之后应该伴随一个U+DC00至U+DFFF的低代理项(low surrogate)。然后，我们用下列公式把代理对(H,L)变成成真实的码点:
  codepoint = 0x10000 + (H - 0xD800) x 0x400 + (L - 0xDC00)
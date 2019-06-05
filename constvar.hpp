#ifndef _CONSTVAR_H
#define _CONSTVAR_H
#endif

#include <map>
#include <string>
#include <vector>
#include <fstream>
#define REGISTERS       6
//#define TOKENANALYZER            1
//#define syntaxanalyzer           2
#define DEBUG                    3
#define StartSyntaxAnalysis      4
//#define StartTokenAnalysis       5
//#define preprocessor             6
//#define StartPreProcess          7

#define SYN_AUTO			0 // auto
#define SYN_BREAK			1 //break
#define SYN_CASE			2 //case
#define SYN_CHAR            3 //char
#define SYN_CONST			4 //const
#define SYN_CONTINUE		5 //continue
#define SYN_DEFAULT			6 //default
#define SYN_DO				7 //do
#define SYN_WHILE			8 //while
#define SYN_FOR				9 //for
#define SYN_SWITCH			10 //switch
#define SYN_ELSE			11 //else
#define SYN_ENUM			12 //enum
#define SYN_EXTERN			13 //extern
#define SYN_GOTO			14 //goto
#define SYN_IF				15 //if
#define SYN_REGISTER		16 //register
#define SYN_RETURN			17 //return
#define SYN_SIZEOF			18 //sizeof
#define SYN_STATIC			19 //static
#define SYN_STRUCT			20 //struct
#define SYN_TYPEDEF			21 //typedef
#define SYN_UNION			22 //union
#define SYN_VOLATILE		23 //volatile
#define SYN_VOID			24 //void
#define SYN_TRUE			25 //TRUE
#define SYN_FALSE			26 //FALSE
#define SYN_FLOAT			27 //flaot
#define SYN_DOUBLE			29 //double
#define SYN_INT				30 //int
#define SYN_LONG			31 //long
#define SYN_SIGNED			32 //signed
#define SYN_UNSIGNED        107// unsigned
#define SYN_SHORT			33 //short
#define SYN_BOOL			87 //bool
#define SYN_MACRO_IF		34 //#if
#define SYN_MACRO_IFNDEF	35 //#ifndef
#define SYN_MACRO_ELIF		36 //#elif
#define SYN_MACRO_ENDIF		37 //#endif
#define SYN_MACRO_ELSE		38 //#else
#define SYN_MACRO_INCLUDE	39 //#include
#define SYN_MACRO_DEFINE	40 //#define
#define SYN_MACRO_UNDEF		41 //#undef
#define SYN_MACRO_IFDEF     106// #ifdef
#define SYN_LINE			42 //#line
#define SYN_ERROR			43 //#error
#define SYN_PRAGMA			44 //pragma
#define SYN_PAREN_L			45 //(
#define SYN_PAREN_R			46 //)
#define SYN_BRACE_L			47 //{
#define SYN_BRACE_R			48 //}
#define SYN_SQU_BRACE_L		49 //[
#define SYN_SQU_BRACE_R		50//]
#define SYN_LT				51 //<
#define SYN_GT				52 //>
#define SYN_LE				53 //<=
#define SYN_GE				54//>=
#define SYN_EQ				55//==
#define SYN_ADD				56 //+
#define SYN_SUB				57  //-
#define SYN_MOD				58 //%
#define SYN_MODEQ			59//%=
#define SYN_AE				60 //+=
#define SYN_SE				61//-=
#define SYN_ME				62 //*=
#define SYN_DE				63 ///=
#define SYN_INC				64//++
#define SYN_DEC				65//--
#define SYN_POINTER			66//->
#define SYN_NOTEQ			67//!=
#define SYN_CHOOSE			68//?
#define SYN_AND				69 //&&
#define SYN_OR				70 //||
#define SYN_NOT				71 //!
#define SYN_SET				72 //=
#define SYN_MUL				73 //*
#define SYN_DIV				74 ///
#define SYN_COMMA			75 //,
#define SYN_SEMIC			76 //;
#define SYN_BIT_XOREQ		77//^=
#define SYN_BIT_OR			78 //|
#define SYN_BIT_NOT			79//~
#define SYN_BIT_AND			80//&
#define SYN_BIT_XOR			81//^
#define SYN_BIT_ANDEQ		82//&=
#define SYN_BIT_SHL			83 //<<
#define SYN_BIT_SHLEQ		84 //<<=
#define SYN_BIT_SHREQ		85 // >>=
#define SYN_BIT_SHR			86 //>>
#define SYN_BIT_NOTEQ       87//~=
#define SYN_BIT_OREQ        89//|=
#define SYN_DOT             90 //.
#define SYN_POST            91 //##
#define SYN_SHARP           92 //#
#define SYN_COLON           93 //:
#define SYN_TRIDOTS         94 //...
#define SYN_QUES            95 //?
#define SYN_DOTMUL          96 //.*
#define SYN_KEYWORD         98 //keyword
#define SYN_NUMBER          99 // number
#define SYN_SCOPE           100//::
#define SYN_POINTERMUL      102 //->*
#define SYN_STRING          103 //string
#define SYN_NUMBER_LONG     104
#define SYN_NUMBER_DOUBLE   105
#define SYN_TEXT            111
#define SYN_TYPEDEFNAME     108
#define SYN_FUNCTION        109 //函数
#define SYN_TYPENAME        110
#define SYN_NULL            111
// ID STATE
#define ID_FUN				1
#define ID_CHAR				2
#define ID_SHORT			4
#define ID_SIGNEDINT        5
#define ID_UNSIGNEDINT      6
#define ID_INT				7
#define ID_FLOAT			8
#define ID_DOUBLE			9
#define ID_SIGNED			10
#define ID_POINTER			11
#define ID_SIGNEDLONG       12
#define ID_LONG				13
#define ID_UNSIGNEDLONG     14
#define ID_BOOLEN			15
#define ID_SELFDEFINE       16


#define char_mask       0x1
#define short_mask      0x2
#define int_mask        0x4
#define long_mask       0x8
#define double_mask     0x10
#define string_mask     0x20
#define signed_mask     0x40
#define unsigned_mask   0x80
#define struct_mask     0x100
#define union_mask      0x200
#define enum_mask       0x400
#define selfdefine_mask  0x800
#define pointer_mask    0x1000
#define float_mask      0x2000
#define array_mask      0x4000
#define static_mask     0x8000
#define const_mask      0x10000
#define volatile_mask   0x20000

#define STATIC          1
#define AUTO            2
#define REGISTER        3
#define EXTERN          4
#define TYPEDEF         5

// DEFINE STATE
#define ERROR               -1

std::map<std::string,int> KeyWordMap={
    {"auto",SYN_AUTO},          {"break",SYN_BREAK},          {"case",SYN_CASE},        {"const",SYN_CONST},    {"char",SYN_CHAR},
    {"continue",SYN_CONTINUE},  {"default",SYN_DEFAULT},      {"do",SYN_DO},            {"while",SYN_WHILE},    {"for",SYN_FOR},      
    {"switch",SYN_SWITCH},      {"else",SYN_ELSE},            {"enum",SYN_ENUM},        {"extern",SYN_EXTERN},  {"goto",SYN_GOTO},    
    {"if",SYN_IF},              {"register",SYN_REGISTER},    {"return",SYN_RETURN},    {"sizeof",SYN_SIZEOF},  {"static",SYN_STATIC},  
    {"struct",SYN_STRUCT},      {"typedef",SYN_TYPEDEF},      {"union",SYN_UNION},      {"volatile",SYN_VOLATILE},{"void",SYN_VOID},    
    {"true",SYN_TRUE},          {"false",SYN_FALSE},          {"float",SYN_FLOAT},      {"double",SYN_DOUBLE},  {"int",SYN_INT},     
    {"long",SYN_LONG},          {"signed",SYN_SIGNED},  {"unsigned",SYN_UNSIGNED},      {"short",SYN_SHORT},      {"bool",SYN_BOOL},      {"#if",SYN_MACRO_IF},     
    {"#ifndef",SYN_MACRO_IFNDEF},     {"#elif",SYN_MACRO_ELIF},   {"#else",SYN_MACRO_ELSE},   {"#include",SYN_MACRO_INCLUDE},{"#endif",SYN_MACRO_ENDIF},
    {"#define",SYN_MACRO_DEFINE}, {"#undef",SYN_MACRO_UNDEF}, {"#line",SYN_LINE},{"#ifdef",SYN_MACRO_IFDEF } ,      {"#error",SYN_ERROR},   {"#pragma",SYN_PRAGMA},
    {"<",SYN_LT},{">",SYN_GT},{"<=",SYN_LE},{">=",SYN_GE},{"==",SYN_EQ},{"+",SYN_ADD},{"-",SYN_SUB},{"(",SYN_PAREN_L},{")",SYN_PAREN_R},
    {"[",SYN_SQU_BRACE_L},{"]",SYN_SQU_BRACE_R},{"{",SYN_BRACE_L},{"}",SYN_BRACE_R},{"%",SYN_MOD},{"%=",SYN_MODEQ},{"+=",SYN_AE},{"-=",SYN_SE},{"*=",SYN_ME},
    {"/=",SYN_DE},{"++",SYN_INC},{"--",SYN_DEC},{"->",SYN_POINTER},{"!=",SYN_NOTEQ},{"?",SYN_QUES},{"&&",SYN_AND},{"||",SYN_OR},{"!",SYN_NOT},{"=",SYN_SET},
    {"/",SYN_DIV},{",",SYN_COMMA},{";",SYN_SEMIC},{"^=",SYN_BIT_XOREQ},{"|",SYN_BIT_OR},{"~",SYN_BIT_NOT},{"&",SYN_BIT_AND},{"^",SYN_BIT_XOR},{"&=",SYN_BIT_ANDEQ},
    {"<<",SYN_BIT_SHL},{"<<=",SYN_BIT_SHLEQ},{">>",SYN_BIT_SHR},{">>=",SYN_BIT_SHREQ},{"|=",SYN_BIT_OREQ},{".",SYN_DOT},{"##",SYN_POST},{"#",SYN_SHARP},{":",SYN_COLON},
    {"...",SYN_TRIDOTS},{"::",SYN_SCOPE},
    };


union IntgerNumber{
    short ShortNumber;
    unsigned short UnSignedShortNumber;

    int   IntNumber;
    unsigned int UnSignedIntNumber;

    long  LongNumber;
    unsigned long UnSignedLongNumber;
};

union FloatPointNumber{
    float FloatNumber;
    double DoubleNumber;
    long double LongDoubleNumber;
};

union RealNumber{
    union IntgerNumber intgerNumber;
    union FloatPointNumber floatNumber;
    
};

union Number{
    union RealNumber realNumber;
};

struct ArrayInfo{
    long Dimension;
    std::vector<int> dims;
};

struct TokenValue{
    long value_type;
    std::string StringValue;
    union Number number;
    std::string value_address;
    struct ArrayInfo arrayinfo;
};

struct TOKEN{
    int TokenType;
    struct TokenValue tokenValue;
};


unsigned int LineNumber = 1;

std::string text;
std::string PreProcesstext;
bool SwitchForMacro = false;

std::map<std::string,bool> IncludeFile;

struct textPart{
    long MacroType;  // 1 general ,2 macro function
    std::vector<std::string> arguments;
    std::string textpart;
};

std::map<std::string, struct textPart> MacroValue;
std::ofstream midfile;


struct ValueInfo{
    bool isSetValue;
    long value_type;  /* 1 integer,2 float point number,3 charactor, 4 string,5 short, 6 signed,7 unsigned, 8 struct,9 struct ,
    10 enum, -1 selfdefined*/
    std::string type_name;
    long limit_type; /* 0 NONE,1 const,2 volaltile*/
    long store_type; /* 0 NONE,1 static,2 auto,3 register,4 extern,5 typedef*/
    long sub_statement_type;
    std::string struct_name;
    std::string value_name;
    std::vector<struct TokenValue> block_value;
    std::vector<struct TokenValue> struct_body;
    struct TokenValue value;
};



struct ValueAliasName{
    long store_type;
    long limit_type; /* 0 NONE, 1 const,2 volatile */
    long value_type;
    long sub_statement_type;
    struct ArrayInfo arrayinfo;
    std::string struct_name;
    std::string alias;
};

struct ArgumentsType{
    long type;
    std::string argument_name;
};

struct FunctionInfo{
    std::string function_name;
    std::vector<struct ArgumentsType> args_type;
    long     store_type;
    long     limit_type;
    long     return_type;
};


std::vector<struct ValueInfo> GlobalValue;
struct ValueInfo valueinfo;
struct ValueAliasName aliasname;
std::vector<struct TokenValue> structlabellist;

long store_type = 0,limit_type = 0,statement_type;
std::string id_name = "",function_name = "",struct_name="",address_value,type_name = "";
std::vector<struct TokenValue> struct_info;
std::vector<struct TokenValue> struct_body;
struct TokenValue id_primary;

std::vector<struct ValueAliasName> ValueAlais;
std::vector<struct FunctionInfo> FuncInfo;
struct FunctionInfo func_info;
struct ArgumentsType args_type;

bool GlobalScopeValue = true;
bool InStruct = false;
bool InPreProcess = true;
bool StructDefineList = false;
int list_init = 0;
std::map<std::string,std::vector<std::string>> ReadOnlyData;

std::ofstream assemble_file;
bool RunTimeTrans = false;

bool FunctionRegion = false;

struct LocalValue{
 /* 0 function ,1 嵌套作用域*/
    std::string function_name;
    std::vector<struct ValueInfo> value_info;
};

std::map<std::string,struct LocalValue>  localvalue;
struct LocalValue local_value;

std::map<std::string,struct LocalValue> Anonymous_domain;
struct LocalValue anonymous_domain_value;
int domain_number = 0;
int InAnonymousDomain = 0;

std::map<std::string /* value_name*/ ,int /* offset */> value_offset;
std::map<std::string,std::string> read_only_offset;
std::map<std::string,bool> RegisterBitMap = {
    {"rax",false},{"rbx",false},{"rcx",false},{"rdx",false},{"rsi",false},{"rdi",false},
    {"xmm0",false},{"xmm1",false},{"xmm2",false},{"xmm3",false},{"xmm4",false},{"xmm5",false},{"xmm6",false},{"xmm7",false},
};

std::map<std::string,bool> GeneralRigisterMap ={
    {"rax",false},{"rbx",false},{"rcx",false},{"rdx",false},{"rsi",false},{"rdi",false},  
};

bool BuildCode = false;

struct Value{
    int value_type;
    long sub_statement_type;
    std::string value_name;
    long value_integer;
    double value_float;
    std::string const_char;
    std::string value_address;
    int Type; /* 1 integer ;2 addresss*/
};

long array_count =  0;
struct double_label{
    std::string label;
    int type;
};
std::map<std::string,std::map<double,struct double_label>> func_double_label;
long double_label_counter = 0;
long TotalElement;
bool FirstBlock = true;
long array_offset = 0;

bool InIdList = false;

bool GlobalScope = true;

long RunTimeLine = 0;

long sub_statement_type = 0;

bool initial_list = false;

bool InRegister = false; /* Value in %(r/e)ax */

std::map<std::string /* char */,long /* ascii code */> ASCIITable{
    {"'\0'",0x00},{"'\n'",0xa},{"'\r'",0xd},{"'\v'",0xb},{"'\a'",0x7},{"'\b'",0x8},
    {"'\f'",0xc},{"'\''",0x27},{"'\"'",0x22},{"'\\'",0x5c},{"'\?'",0x3f},{"' '",32},
    {"'!'",33},{"'#'",35},{"'$'",36},{"'%'",37},{"'&'",38},/*{"','",39},*/
    {"'('",40},{"')'",41},{"'*'",42},{"'+'",43},{"','",44},{"'-'",45},
    {"'.'",46},{"'/'",47},{"'0'",48},{"'1'",49},{"'2'",50},{"'3'",51},
    {"'4'",52},{"'5'",53},{"'6'",54},{"'7'",55},{"'8'",56},{"'9'",57},
    {"':'",58},{"';'",59},{"'<'",60},{"'='",61},{"'>'",62},{"'?'",63},
    {"'@'",64},{"'A'",65},{"'B'",66},{"'C'",67},{"'D'",68},{"'E'",69},
    {"'F'",70},{"'G'",71},{"'H'",72},{"'I'",73},{"'J'",74},{"'K'",75},
    {"'L'",76},{"'M'",77},{"'N'",78},{"'O'",79},{"'P'",82},{"'Q'",81},
    {"'R'",82},{"'S'",83},{"'T'",84},{"'U'",85},{"'V'",86},{"'W'",87},
    {"'X'",88},{"'Y'",89},{"'Z'",90},{"'['",91},/*{"'/'",92},*/{"']'",93},
    {"'^'",94},{"'_'",95},{"'`'",96},{"'a'",97},{"'b'",98},{"'c'",99},
    {"'d'",100},{"'e'",101},{"'f'",102},{"'g'",103},{"'h'",104},{"'i'",105},
    {"'j'",106},{"'k'",107},{"'l'",108},{"'m'",109},{"'n'",110},{"'o'",111},
    {"'p'",112},{"'q'",113},{"'r'",114},{"'s'",115},{"'t'",116},{"'u'",117},
    {"'v'",118},{"'w'",119},{"'x'",120},{"'y'",121},{"'z'",122},{"'{'",123},
    {"'|'",124},{"'}'",125},{"'~'",126},
};
#ifndef _TOKENANALYZER_H
#define _TOKENANALYZER_H
#endif

#include <iostream>
#include <string>
#include "./constvar.hpp"

using namespace std;
#define NOT_BLANCK(c)   ((c != '\t') || (c != '\f') || (c != '\v') || (c != '\0') || ( c!= ' '))
#define BLANCK(c)       (!NOT_BLANCK(c))
#define NOT_NEWLINE(c)  (c != '\n')
#define NEWLINE(c)      (!NOT_NEWLINE(c))
#define IsDights(c)     ((c >= '0') && (c <= '9'))  
#define OneToNine(c)    ((c >= '1') && (c <= '9'))
#define ZeroToSeven(c)  ((c >= '0') && (c <= '7'))
#define FloatPost(c)    (c == 'f' || c == 'F' || c == 'l' || c == 'L')
#define LETTER_(c)      ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
#define HexDights(c)    (IsDights(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
#define IsSpecial(c)    ((c == '\'') || (c == '\"') || (c == '?') || (c == '\\') || (c == 'a') || \
                         (c == 'b') || (c == 'f') || (c == 'n') || (c == 'r') || (c == 't') || (c == 'v'))

#define AppendCharToString(c)   {\
                                    TokenString.push_back(CurrentChar);\
                                    TokenLength++;\
                                }

#define NEXT(first,second)  do{ \
                                AppendCharToString(CurrentChar)\
                                CurrentChar = ReadAChar();\
                                if(CurrentChar == first || CurrentChar == second){\
                                    AppendCharToString(CurrentChar)\
                                }\
                                else\
                                    SeekFileHandler(-1L);\
                                return SYN_NUMBER;  \
                        }while(0);

#define NEXT_U(symbol)  do{\
                            AppendCharToString(CurrentChar)\
                            CurrentChar = ReadAChar();\
                            if(CurrentChar == symbol)\
                                NEXT('u','U')\
                            else if(CurrentChar == 'u' || CurrentChar == 'U'){\
                                AppendCharToString(CurrentChar)\
                                return SYN_NUMBER;\
                            }\
                            else\
                            {\
                                SeekFileHandler(-1L);\
                                return SYN_NUMBER;\
                            }\
                        }while(0);

#define ReadACharUntilNotHex(CurrentChar)   for(CurrentChar = ReadAChar();HexDights(CurrentChar);CurrentChar = ReadAChar()){ \
                                                if(CurrentChar == 0){ \
                                                    exit(0);\
                                                }\
                                                AppendCharToString(CurrentChar)\
                                            }

#define ReadACharUntilNotDight(CurrentChar) for(CurrentChar = ReadAChar();IsDights(CurrentChar);CurrentChar = ReadAChar()){\
                                                if(CurrentChar == 0){\
                                                    exit(0);\
                                                }\
                                                AppendCharToString(CurrentChar)\
                                            }  
                                        
#define ReadACharUntilNotOtc(CurrentChar)   for(CurrentChar = ReadAChar();ZeroToSeven(CurrentChar);CurrentChar = ReadAChar()){\
                                                if(CurrentChar == 0){\
                                                    exit(0);\
                                                }\
                                                AppendCharToString(CurrentChar)\
                                            }

static bool FileStart = true;
static bool HeadFile = false;
class TokenAnalyzer{
public:
    TokenAnalyzer()=default;
    void SetFileName(const std::string FileName);
    TOKEN NextToken(void);
    int IsADecimal(void);
    int IsOtcimal(void);
    int IsHeximal(void);
    int IsDecFloat(void);
    int IsHexFloat(void);
    int IsStringOrChar(void);
    inline void RenewLex(void);
    int ContinueRead(void);
    int NextRead(void);
    void ChangeStringToNumber(TOKEN &token);

//  Real Number Change
   inline signed String2Signed(void);
   inline short String2Short(void);
   inline unsigned short String2UnSignedShort(void);
   inline int String2Int(void);
   inline signed int String2SignedInt(void);
   inline unsigned int String2UnSignedInt(void);
   inline long String2Long(void);
   inline signed long String2SignedLong(void);
   inline unsigned long String2UnSignedLong(void);
   inline float String2Float(void);
   inline double String2Double(void);

    void SeekFileHandler(long offset);
    char ReadAChar(void);
    inline bool isEOF(void);
    inline int tokenLength(void);
    inline std::string tokenString(void);
    inline bool &getPreProcessStatus(void);
    inline bool &getGlobalStatus(void);
    int Processor(void);
    int FoundKeyWord(void);
    void CloseFile(void);
    ~TokenAnalyzer();
private:
    std::ifstream FileHandler;
    int TokenLength;
    char PreChar;
    bool PreProcess_ = false;
    bool Global_ = true;
    std::string TokenString;
};

TokenAnalyzer::~TokenAnalyzer(){
    //Nothing to do
}

void TokenAnalyzer::CloseFile(void){
    FileHandler.close();
}

void TokenAnalyzer::SetFileName(const std::string FileName){
    FileHandler.open(FileName,std::ios_base::in);
    if(!FileHandler.is_open())
    {
        std::cout << "No Such File or Direcotry!" << std::endl;
        exit(0);
    }
}

inline bool &TokenAnalyzer::getGlobalStatus(void){
    return Global_;
}
inline bool &TokenAnalyzer::getPreProcessStatus(void){
    return PreProcess_;
}
inline bool TokenAnalyzer::isEOF(void){
    return (FileHandler.eof()) ? 1:0;
}


inline int TokenAnalyzer::tokenLength(void){
    return TokenLength;
}
inline std::string TokenAnalyzer::tokenString(void){
    return TokenString;
}

int TokenAnalyzer::IsHeximal(void){
    char CurrentChar;
    ReadACharUntilNotHex(CurrentChar)
    switch(CurrentChar){
        case 'U':
        case 'u':
            CurrentChar = ReadAChar();
            switch(CurrentChar){
                case 'l':
                        NEXT('l','l');
                case 'L':
                        NEXT('L','L');
            }
            SeekFileHandler(-1L);
            return SYN_NUMBER;
        case 'l':
            NEXT_U('l');
        case 'L':
            NEXT_U('L');
        default:
            SeekFileHandler(-1L);
            return SYN_NUMBER;
    }
}

int TokenAnalyzer::NextRead(void){
    char CurrentChar;
    for(CurrentChar = ReadAChar();CurrentChar && CurrentChar != '\'' && CurrentChar != '\\' && CurrentChar != '\n' ;CurrentChar = ReadAChar()){
        AppendCharToString(CurrentChar)
    }
    if(CurrentChar == '\''){
        AppendCharToString(CurrentChar)
        return SYN_STRING;
    }
    else if(CurrentChar == '\\'){
        AppendCharToString(CurrentChar)
        return ContinueRead();
    }
    else if(CurrentChar == '\n'){
        while((CurrentChar = ReadAChar()) == '\n');
        if(CurrentChar == '\\'){
            AppendCharToString(CurrentChar)
            return ContinueRead();
        }
        else if(CurrentChar == '\'' || CurrentChar == '\"'){
            AppendCharToString(CurrentChar)
            return SYN_NUMBER;
        }
        else if(FileHandler.eof()){
#if defined(TOKENANALYZER)
            std::cout << "Meet File End!" << std::endl;
#endif
            return ERROR;
        }
        else{
            return NextRead();
        }
    }
    return ERROR;
}

int TokenAnalyzer::ContinueRead(void){
    char CurrentChar;
    CurrentChar = ReadAChar();
    if(IsSpecial(CurrentChar)){
        AppendCharToString(CurrentChar)
        CurrentChar = ReadAChar();
        if(CurrentChar == '\'' || CurrentChar == '\"'){
            AppendCharToString(CurrentChar)
            return SYN_STRING;
        }
        else{
            AppendCharToString(CurrentChar)
            return IsStringOrChar();
        }
    }
    else if(ZeroToSeven(CurrentChar)){
        AppendCharToString(CurrentChar)
        ReadACharUntilNotOtc(CurrentChar)
        SeekFileHandler(-1L);
        return NextRead();
    }
    else{
        AppendCharToString(CurrentChar)
        switch (CurrentChar)
        {
            case 'x':   
                ReadACharUntilNotHex(CurrentChar)
                SeekFileHandler(-1L);
                return NextRead();
            case 'U':
            case 'u':
                ReadACharUntilNotHex(CurrentChar)
                SeekFileHandler(-1L);
                return NextRead();
            default:
                std::cout << "Lex:Symbol Error!" << CurrentChar << std::endl;
                exit(1);
        }
    }
}
int TokenAnalyzer::IsStringOrChar(void){
    char CurrentChar;
    CurrentChar = ReadAChar();
    if(CurrentChar == '\\'){
        AppendCharToString(CurrentChar)
        return ContinueRead();
    }
    else if(CurrentChar != '\'' && CurrentChar != '\\' && CurrentChar != '\n' && CurrentChar != '\"'){
        AppendCharToString(CurrentChar)
        char TempChar = CurrentChar;
        CurrentChar = ReadAChar();
        if(CurrentChar != '\'' && CurrentChar != '\\' && CurrentChar != '\n' && CurrentChar != '\"'){
            AppendCharToString(CurrentChar)
            return IsStringOrChar();
        }
        else if(CurrentChar == '\'' || CurrentChar == '\"' ){
            AppendCharToString(CurrentChar)
            return SYN_STRING;
        }
        else{
/*            std::cout << "Symbol Error!---" << CurrentChar << std::endl;
            exit(1);*/
            AppendCharToString(CurrentChar)
            return ContinueRead();
        }
    }
    else if(CurrentChar == '\"' || CurrentChar == '\''){
        AppendCharToString(CurrentChar)
        return SYN_STRING;
    }
    else{
        std::cout << "Lex:Symbol Error!" << CurrentChar << std::endl;
        exit(1);
    }
}
int TokenAnalyzer::IsDecFloat(void){
    char CurrentChar;
    ReadACharUntilNotDight(CurrentChar)
    switch (CurrentChar)
    {
        case '.':
            AppendCharToString(CurrentChar)
            ReadACharUntilNotDight(CurrentChar)
            if(FloatPost(CurrentChar)){
                AppendCharToString(CurrentChar)
                goto postfloat;
            }
            else if(CurrentChar == 'e' || CurrentChar == 'E')
                ;
            else{
                SeekFileHandler(-1L);
                return SYN_NUMBER;
            }
        case 'e':
        case 'E':
            AppendCharToString(CurrentChar)
            CurrentChar = ReadAChar();
            AppendCharToString(CurrentChar)
            switch(CurrentChar){
                case '+':
                case '-':
                    ReadACharUntilNotDight(CurrentChar)
            }
            if(IsDights(CurrentChar))
                ReadACharUntilNotDight(CurrentChar)
            if(FloatPost(CurrentChar)){
                AppendCharToString(CurrentChar)
                return SYN_NUMBER;
            }
            else{
                SeekFileHandler(-1L);
                return SYN_NUMBER;
            }
postfloat:
        case 'f':
        case 'F':
        case 'L':
        case 'l':
            AppendCharToString(CurrentChar)
            return SYN_NUMBER;
        default:
            SeekFileHandler(-1L);
            return SYN_NUMBER;
    }
}

int TokenAnalyzer::IsOtcimal(void){
    char CurrentChar;
    ReadACharUntilNotOtc(CurrentChar)
    switch(CurrentChar){
        case 'u':
        case 'U':
                AppendCharToString(CurrentChar)
                CurrentChar = ReadAChar();
                switch(CurrentChar){
                    case 'l':
                        NEXT('l','l');
                    case 'L':
                        NEXT('L','L');
                    default:
                        SeekFileHandler(-1L);
                        return SYN_NUMBER;
                }
        case 'l':
                NEXT_U('l')
        case 'L':
                NEXT_U('L')
        default:
            SeekFileHandler(-1L);
            return SYN_NUMBER;
    }
}

int TokenAnalyzer::IsADecimal(void){
    char CurrentChar;
    ReadACharUntilNotDight(CurrentChar)
    switch(CurrentChar){
        case '.':
            AppendCharToString(CurrentChar)
            return IsDecFloat();
        case 'u':
        case 'U':
                AppendCharToString(CurrentChar)
                CurrentChar = ReadAChar();
                switch(CurrentChar){
                    case 'l':
                        NEXT('l','l');
                    case 'L':
                        NEXT('L','L');
                    default:
                        SeekFileHandler(-1L);
                        return SYN_NUMBER;
                }
        case 'l':
                NEXT_U('l')
        case 'L':
                NEXT_U('L')
        default:
            SeekFileHandler(-1L);
            return SYN_NUMBER;
    }
}

int TokenAnalyzer::IsHexFloat(void){
    char CurrentChar;
    ReadACharUntilNotHex(CurrentChar)
    switch(CurrentChar){
        case '.':
            AppendCharToString(CurrentChar)
            ReadACharUntilNotHex(CurrentChar)
            if(CurrentChar == 'p' || CurrentChar == 'P')
                ; // Nothing to do
            else{
                std::cout <<"Lex:Symbol Error!" << CurrentChar << std::endl;
                exit(1);
            }
        case 'p':
        case 'P':
                AppendCharToString(CurrentChar)
                ReadACharUntilNotDight(CurrentChar)
                if(CurrentChar == '+' || CurrentChar == '-'){
                    ReadACharUntilNotDight(CurrentChar)
                    if(FloatPost(CurrentChar)){
                        AppendCharToString(CurrentChar)
                        return SYN_KEYWORD;
                    }
                    else{
                        SeekFileHandler(-1L);
                        return SYN_KEYWORD;
                    }
                }
                if(FloatPost(CurrentChar)){
                    AppendCharToString(CurrentChar)
                    return SYN_KEYWORD;
                }
                else {
                    SeekFileHandler(-1L);
                    return SYN_KEYWORD;
                }
        default:
            std::cout << "Lex:Symbol Error!" << CurrentChar << std::endl;
            exit(1);
    }
}


void TokenAnalyzer::SeekFileHandler(long offset){
    if(FileHandler){
        FileHandler.seekg(offset,std::ios::cur);
        if(PreProcess_){
            PreProcesstext.pop_back();
        }
        if(Global_){ 
            text.pop_back();
        }
    }
    else{
#if defined(TOKENANALYZER)
        std::cout << "Meet File End!" << std::endl;
#endif 
        return;
    }
    return ;
}

char TokenAnalyzer::ReadAChar(void){
    char TempChar;
    TempChar = FileHandler.get();

    if(PreProcess_){
        PreProcesstext.push_back(TempChar);
    }
    if(Global_){     
        text.push_back(TempChar);
    }

    return TempChar;
}

int TokenAnalyzer::Processor(void){
        char CurrentChar;
        if(FileHandler.eof()){
            return ERROR;
        }
        for(CurrentChar = ReadAChar();CurrentChar ;CurrentChar = ReadAChar()){
        //  Is Blanck ?
            switch(CurrentChar){
                case '\t':
                case '\f':
                case '\v':
                case ' ':
                case '\n':
                    do{
                        if(CurrentChar == '\n'){
#if defined(syntaxanalyzer)
                            std::cout <<  "No."<< LineNumber  << std::endl;
#endif
                            LineNumber++;
                        }
                        CurrentChar = ReadAChar();
                    }while(!NOT_BLANCK(CurrentChar));
                    if(!FileHandler.eof()){
                        SeekFileHandler(-1L);
                        continue;
                    }
                    else{
#if defined(TOKENANALYZER)
                        std::cout << "Meet File End!" << std::endl;
#endif 
                        return(0);
                    }
                default:
                    break;
            }

        // Is Calculatoer ?
            switch(CurrentChar){
                case '+':{
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_AE;
                        case '+':
                            AppendCharToString(CurrentChar)
                            return SYN_INC;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_ADD;
                    }
                }
                case '-':{
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_SE;
                        case '-':
                            AppendCharToString(CurrentChar)
                            return SYN_DEC;
                        case '>':
                            AppendCharToString(CurrentChar)
                            CurrentChar = ReadAChar();
                            switch(CurrentChar){
                                case '*':
                                    AppendCharToString(CurrentChar)
                                    return SYN_POINTERMUL;
                                default:
                                    SeekFileHandler(-1L);
                                    return SYN_POINTER;
                            }
                        default:
                            SeekFileHandler(-1L);
                            return SYN_SUB;
                    }
                }
                case '*':{
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_ME;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_MUL;
                    }
                }
                case '/':{
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_DE;
                        case '/':
                            do{
                                CurrentChar = ReadAChar();
                                if(FileHandler.eof())
                                    break;
                            }while(NOT_NEWLINE(CurrentChar));
                            if(!FileHandler.eof()){
                                TokenString.pop_back();
                                TokenLength--;
                                //SeekFileHandler(-1L);
                                continue;
                            }
                            else{
#if defined(TOKENANALYZER)
                                std::cout << "Meet File End!" << std::endl;
#endif
                                return(0);
                            }
                        case '*':
                            char tempchar;
                            while (!isEOF() && ((tempchar = ReadAChar())!='/' ||  CurrentChar != '*')){
						        if(CurrentChar == '\n'){
                                    LineNumber++;
                                }
                                CurrentChar = tempchar;
                            }
                            TokenString.pop_back();
                            TokenLength--;
                            continue;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_DIV;
                    }
                }
                case '%':{
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_MODEQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_MOD;
                    }
                }
            }

        // Is Bit Operatoer
            switch(CurrentChar){
                case '&':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '&':
                            AppendCharToString(CurrentChar)
                            return SYN_AND;
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_BIT_ANDEQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_BIT_AND;
                    }
                case '|':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '|':
                            AppendCharToString(CurrentChar)
                            return SYN_OR;
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_BIT_OREQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_BIT_OR;
                    }
                case '^':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_BIT_XOREQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_BIT_XOR;
                    }
                case '~':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_BIT_NOTEQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_BIT_NOT;
                    }
                case '!':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_NOTEQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_NOT;
                    }
            }

        // Is Relation Operator
            switch(CurrentChar){
                case '>':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '>':
                            AppendCharToString(CurrentChar)
                            CurrentChar = ReadAChar();
                            if(CurrentChar == '='){
                                AppendCharToString(CurrentChar)
                                return SYN_BIT_SHREQ;
                            }
                            SeekFileHandler(-1L);
                            return SYN_BIT_SHR;
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_GE;
                        default:
                            SeekFileHandler(-1L);
                            HeadFile = false;
                            return SYN_GT;
                    }
                case '<':  
                    TokenString.push_back(CurrentChar);
                    TokenLength++;
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '<':
                            TokenString.push_back(CurrentChar);
                            TokenLength++;
                            CurrentChar = ReadAChar();
                            if(CurrentChar == '='){
                                TokenString.push_back(CurrentChar);
                                TokenLength++;
                                return SYN_BIT_SHLEQ;
                            }
                            SeekFileHandler(-1L);
                            return SYN_BIT_SHL;
                        case '=':
                            TokenString.push_back(CurrentChar);
                            TokenLength++;
                            return SYN_LE;
                        default:
                            SeekFileHandler(-1L);
                            HeadFile = true;
                            return SYN_LT;
                    }
                case '=':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '=':
                            AppendCharToString(CurrentChar)
                            return SYN_EQ;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_SET;
                    }
            }

        // Is Misc
            switch(CurrentChar){
                case '#':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    if(CurrentChar == '#')
                        return SYN_POST;
                    else if(LETTER_(CurrentChar)){
                        AppendCharToString(CurrentChar)
                        do{
                            CurrentChar = ReadAChar();
                            if(LETTER_(CurrentChar) || IsDights(CurrentChar)){
                                AppendCharToString(CurrentChar)
                            }
                            else{
                                SeekFileHandler(-1L);
                                return SYN_KEYWORD;
                            }
                        }while(1);
                    }
                    else
                    {
                        SeekFileHandler(-1L);
                        return SYN_SHARP;
                    }
                case '\\':
                    if(PreProcess_){
                        continue;
                    }
                    else
                    {
                        break;
                    }
                case ';':
                    AppendCharToString(CurrentChar)
                    return SYN_SEMIC;
                case '[':
                    AppendCharToString(CurrentChar)
                    return SYN_SQU_BRACE_L;
                case ']':
                    AppendCharToString(CurrentChar)
                    return SYN_SQU_BRACE_R;
                case '{':
                    AppendCharToString(CurrentChar)
                    return SYN_BRACE_L;
                case '}':
                    AppendCharToString(CurrentChar)
                    return SYN_BRACE_R;
                case '?':
                    AppendCharToString(CurrentChar)
                    return SYN_QUES;
                case ',':
                    AppendCharToString(CurrentChar)
                    return SYN_COMMA;
                case '(':
                    AppendCharToString(CurrentChar)
                    return SYN_PAREN_L;
                case ')':
                    AppendCharToString(CurrentChar)
                    return SYN_PAREN_R;
                case ':':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case ':':
                            AppendCharToString(CurrentChar)
                            return SYN_SCOPE;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_COLON;
                    }
                case '.':
                    AppendCharToString(CurrentChar)
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '.':
                            AppendCharToString(CurrentChar)
                            CurrentChar = ReadAChar();
                            if(CurrentChar == '.'){
                                AppendCharToString(CurrentChar)
                                return SYN_TRIDOTS;
                            }
                            else{
                                    std::cout << "No Sunch Token: " << TokenString << std::endl;
                            }
                        case '*':
                            return SYN_DOTMUL;
                        default:
                            SeekFileHandler(-1L);
                            return SYN_DOT;
                    }
            }

        // Is ID ?
            if(LETTER_(CurrentChar)){
                AppendCharToString(CurrentChar)
                if(CurrentChar == 'L' || CurrentChar == 'U'){
                    char TempChar = CurrentChar;
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '\"':
                        case '\'':
                            AppendCharToString(CurrentChar)
                            return IsStringOrChar();
                        default:
                            CurrentChar = TempChar;  // CurrentChar == 'L' || 'U'
                            SeekFileHandler(-1L);
                    }
                }
                else if(CurrentChar == 'u'){
                    char TempChar = CurrentChar;
                    CurrentChar = ReadAChar();
                    switch(CurrentChar){
                        case '\'':
                        case '\"':
                            TokenString.push_back(CurrentChar);
                            TokenLength++;
                            return IsStringOrChar();
                        case '8':{
                            char _TempChar = CurrentChar;
                            CurrentChar = ReadAChar();
                            switch(CurrentChar){
                                case '\'':
                                case '\"':
                                    TokenString.push_back(_TempChar);
                                    TokenString.push_back(CurrentChar);
                                    TokenLength+=2;
                                    return IsStringOrChar();
                                default:
                                    SeekFileHandler(-1L);
                                    CurrentChar = _TempChar; // CurrentChar == '8'
                            }
                            break;
                        }
                        default:
                            SeekFileHandler(-1L);
                            CurrentChar = TempChar; // CurrentChar == 'u'
                    }
                }
                do{
                    CurrentChar = ReadAChar();
                    if(LETTER_(CurrentChar) || IsDights(CurrentChar) || CurrentChar == '.' || CurrentChar == '/' || CurrentChar == '-'){
                        if(CurrentChar == '.' || CurrentChar == '/' || CurrentChar == '-')
                            if(HeadFile){
                                AppendCharToString(CurrentChar)
                            }else
                            {
                                SeekFileHandler(-1L);
                                break;
                            }
                        else{
                            AppendCharToString(CurrentChar)
                        }
                    }
                    else
                    {
                        SeekFileHandler(-1L);
                        break;
                    }
                    
                }while(1);
                if(HeadFile){
                    if(TokenString.find("-") != TokenString.npos || TokenString.find(".") != TokenString.npos || TokenString.find("/") != TokenString.npos){
                        HeadFile = false;
                        return SYN_TEXT;
                    }
                }
                if(CurrentChar == '('){
                    return SYN_FUNCTION;
                }
                return SYN_KEYWORD;
            }
            else if(IsDights(CurrentChar)){
                AppendCharToString(CurrentChar)
                char TempChar ;
                int Count = 0;
                switch(CurrentChar){
                    case '0':
                        CurrentChar = ReadAChar();
                        if(CurrentChar == 'x' || CurrentChar == 'X'){
                            AppendCharToString(CurrentChar)
                            CurrentChar = ReadAChar();
                            Count++;
                            do{
                                if(!HexDights(CurrentChar))
                                    break;
                                else{
                                    CurrentChar = ReadAChar();
                                    Count++;
                                }
                            }while(1);
                            Count = 0 - Count;
                            SeekFileHandler(Count);
                            if(CurrentChar == '.' || CurrentChar == 'P' || CurrentChar == 'p'){
                                return IsHexFloat();
                            }
                            else if(CurrentChar == 'u' || CurrentChar == 'U' || CurrentChar == 'l' ||
                                        CurrentChar == 'L' ){
                                            return IsHeximal();
                            }
                            else
                            {
                                return IsHeximal();
                            }
                            
                        }
                        else if(ZeroToSeven(CurrentChar)){
                            AppendCharToString(CurrentChar)
                            switch(CurrentChar){
                                case '.':
                                    AppendCharToString(CurrentChar)
                                    return IsDecFloat();
                                case '0':
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':
                                case '6':
                                case '7':
                                    do{
                                        if(!IsDights(CurrentChar))
                                            break;
                                        else
                                        {
                                            CurrentChar = ReadAChar();
                                            Count++;
                                        }
                                    }while(1);
                                    Count = 0 - Count;
                                    SeekFileHandler(Count);
                                    if(CurrentChar == '.'){
                                        return IsDecFloat();
                                    }
                                    else if(CurrentChar == 'u' || CurrentChar == 'U' ||
                                                CurrentChar == 'l'  || CurrentChar == 'L'){

                                            return IsOtcimal();
                                    }
                                    else
                                    {
                                        break;
                                    }
                                    
                                case '8':
                                case '9':
                                case 'u':
                                case 'U':
                                case 'l':
                                case 'L':
                                    return IsOtcimal();
                            }
                        }
                        if(IsDights(CurrentChar)){
                            AppendCharToString(CurrentChar)
                            return IsDecFloat();
                        }
                        if(CurrentChar == '.'){
                            AppendCharToString(CurrentChar)
                            return IsDecFloat();
                        }
                        SeekFileHandler(-1);
                        return SYN_NUMBER;
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        return IsADecimal();
                    default:break;
                }
            }
            else if(CurrentChar == '\'' || CurrentChar == '\"'){
                    AppendCharToString(CurrentChar)
                    return IsStringOrChar();
            }
            break;
        }
        return ERROR;
}
void TokenAnalyzer::ChangeStringToNumber(TOKEN &token){
    if(TokenString.find('.') != std::string::npos){
        token.tokenValue.number.realNumber.floatNumber.DoubleNumber = String2Double();
        token.TokenType = SYN_NUMBER_DOUBLE;
    }
    else{
        token.tokenValue.number.realNumber.intgerNumber.LongNumber = String2Long();
        token.TokenType = SYN_NUMBER_LONG;
    }
    return ;
}

TOKEN TokenAnalyzer::NextToken(void){
    TOKEN token;
    int KeywordType;
    TokenLength = 0;
    TokenString = "";
    token.TokenType = Processor();
    if(FileHandler.eof()){
        return token;
    }
    switch(token.TokenType){
        case SYN_KEYWORD:
            if(KeyWordMap.count(TokenString)){
                token.TokenType = KeyWordMap[TokenString];
            }
            break;
        case SYN_NUMBER:
            ChangeStringToNumber(token);
        default:break;
    }
    token.tokenValue.StringValue = TokenString;


#if defined(TOKENANALYZER)
    std::cout << "LEX: " << token.tokenValue.StringValue << ": ";
    switch(token.TokenType){
        case SYN_NUMBER_DOUBLE:
            std::cout << token.tokenValue.number.realNumber.floatNumber.DoubleNumber << std::endl;
            break;
        case SYN_NUMBER_LONG:
            std::cout << token.tokenValue.number.realNumber.intgerNumber.LongNumber << std::endl;
            break;
        default:
            std::cout << token.TokenType << std::endl;
    }
#endif

    return token;
}



inline int TokenAnalyzer::FoundKeyWord(void){
    return KeyWordMap[TokenString];
}


inline signed TokenAnalyzer::String2Signed(void){
    return static_cast<signed>(atoi(TokenString.c_str()));
}

inline short TokenAnalyzer::String2Short(void){
    return static_cast<short>(atoi(TokenString.c_str()));
}

inline unsigned short TokenAnalyzer::String2UnSignedShort(void){
    return static_cast<unsigned short>(atoi(TokenString.c_str()));
}

inline int TokenAnalyzer::String2Int(void){
    return atoi(TokenString.c_str());
}

inline signed int TokenAnalyzer::String2SignedInt(void){
    return static_cast<signed int>(atoi(TokenString.c_str()));
}

inline unsigned int TokenAnalyzer::String2UnSignedInt(void){
    return static_cast<unsigned int>(atoi(TokenString.c_str()));
}

inline long TokenAnalyzer::String2Long(void){
    return atol(TokenString.c_str());
}

inline signed long TokenAnalyzer::String2SignedLong(void){
    return atol(TokenString.c_str());
}

inline unsigned long TokenAnalyzer::String2UnSignedLong(void){
    return (unsigned long)atol(TokenString.c_str());
}

inline float TokenAnalyzer::String2Float(void){
    return std::stof(TokenString.c_str());
}

inline double TokenAnalyzer::String2Double(void){
    return std::stod(TokenString.c_str());
}
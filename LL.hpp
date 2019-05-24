#ifndef _SYNTAXANALYZER_H
#define _SYNTAXANALYZER_H
#endif

#include "TokenAnalyzer.hpp"
#include "BuildObjectCode.hpp"

#define process_id_or_function_statement    do{\
                                                int type = CurrentTokenType;\
                                                while(isType(CurrentTokenType))\
                                                    Type();\
                                                if(type == SYN_STRUCT || type == SYN_UNION){\
                                                    StructOrUnion();\
                                                    break;\
                                                }\
                                                if(CurrentTokenType == SYN_KEYWORD){\
                                                    StatementID();\
                                                }\
                                                else if(CurrentTokenType == SYN_FUNCTION){\
                                                    StatementFunction();\
                                                    return;\
                                                }\
                                            }while(0);

#define Error(Notice,ErrorCode) do{\
                                    std::cout << Notice << std::endl;\
                                    exit(ErrorCode);\
                                }while(0);

std::string alias_name;
class SyntaxAnalyzer{
public:
    SyntaxAnalyzer();
    SyntaxAnalyzer(const std::string FileName);
    ~SyntaxAnalyzer();
    

    void BuildAST(void);
    void Statement(void);                           // 声明
    void StoreTypeSymbol(void);                     // 存储类型符
    void LimitTypeSymbol(void);                     // 类型限制符
    void Type(void);                                // 类型
    void IdList(void);                              // Id表
    void Primary(int tokenvalue);                   // 初始值
    void PrimaryList(void);                         // 初始化列表
    void PList(void);                               // 列表
    void Pointer(void);                             // 指针
    void ArgumentList(void);                        // 参数列表
    void Argument(void);                            // 参数
    void ArgumentType(void);                        // 参数类型
    void Brace(void);                               // 方括号
    long ConstExpress(void);                        // 常量表达式
    void CompoundSentence(void);                    // 复合语句
    void StructList(void);                          // 结构表
    void Struct(void);                              // 结构
    void UnionList(void);                           // 枚举表 
    void Union(void);                               // 枚举
    void Express(void);                             // 表达式
    void Express1(void);                            // 表达式
    void AssignmentExpress(void);                   // 赋值表达式
    void AssignmentOperator(void);                  // 赋值擦作符
    void ConditionExpress(void);                    // 
    void LogicOrExpress(void);
    void LogicOrExpress1(void);
    void LogicAndExpress(void);
    void LogicAndExpress1(void);
    void BitOrExpress(void);
    void BitOrExpress1(void);
    void BitXorExpress(void);
    void BitXorExpress1(void);
    void BitAndExpress(void);
    void BitAndExpress1(void);
    void EqualClassExpress(void);
    void EqualClassExpress1(void);
    void RelationExpress(void);
    void RelationExpress1(void);
    void ShiftExpress(void);
    void ShiftExpress1(void);
    void AddClassExpress(void);
    void AddClassExpress1(void);
    void MulClassExpress(void);
    void MulClassExpress1(void);
    void ForceTranExpress(void);
    void UnaryExpress(void);
    void PostfixExpress(void);
    void PostfixExpress1(void);
    void PrimaryExpress(void);
    void ArgumentExpress(void);
    void ArgumentExpress1(void);
    void ControlInstruction(void);
    void PreProcessorConditionInstruction(void);
    void LabelList(void);
    bool isControlInstruction(int tokenvalue);
    void Constant(void);
    void RealArgument(void);
    void Args(void);
    void StatementFunction(void);
    void StatementID(void);
    void StructOrUnion(void);
    void BuildSymbolTable(void);
    inline bool isEOF(void);                        // 判断函数
    void Match(int type);                           // 获取函数
    std::string getTokenString(void);               // 获取token的字符传
    inline int getTokenCoding(void);                // 获取token的编码
    bool isType(int tokenvalue);                    // 是否是type
    void BackAToken(void);                          // 后退一个Token
private:
    TokenAnalyzer tokenAnalyzer;
    TOKEN token;
    int CurrentTokenType;
    bool _PreProcess = true;
    std::string TokenString;
};

SyntaxAnalyzer::SyntaxAnalyzer(){
    /*
        Nothing to do
     */
}

SyntaxAnalyzer::~SyntaxAnalyzer(){
    /*
        Nothing to do
    */
}
SyntaxAnalyzer::SyntaxAnalyzer(const std::string FileName){
    tokenAnalyzer.SetFileName(FileName);
    if(tokenAnalyzer.isEOF()){
        std::cout << "Not Such file or directory!" << std::endl;
        exit(1);
    }
}

static bool isStoreTypeSymbol(int tokenvalue){
    switch(tokenvalue){
        case SYN_EXTERN:
        case SYN_STATIC:
        case SYN_AUTO:
        case SYN_REGISTER:
        case SYN_TYPEDEF:
            return true;
        default:    
            return false;
    }
}

static bool isLimitTypeSymbol(int tokenvalue){
    switch (tokenvalue)
    {
        case SYN_CONST:
        case SYN_VOLATILE:
            return true;
        default:
            return false;
    }
}

static bool isValueAlias(const std::string &alias){
    auto alias_begin = ValueAlais.cbegin();
    while(alias_begin != ValueAlais.cend()){
        if(alias_begin->alias == alias)
            return true;
        alias_begin++;
    }
    return false;
}

bool SyntaxAnalyzer::isType(int tokenvalue){
    switch(tokenvalue){
        case SYN_VOID:
        case SYN_INT:
        case SYN_CHAR:
        case SYN_LONG:
        case SYN_SHORT:
        case SYN_FLOAT:
        case SYN_DOUBLE:
        case SYN_SIGNED:
        case SYN_UNSIGNED:
        case SYN_STRUCT:
        case SYN_UNION:
        case SYN_ENUM:
//        case SYN_KEYWORD:
            return true;
        case SYN_KEYWORD:
            return isValueAlias(getTokenString());
        case SYN_MUL:
            //Pointer();
            return true;
        default:
            return false;
    }
}

bool SyntaxAnalyzer::isControlInstruction(int tokenvalue){
    switch(tokenvalue){
        case SYN_MACRO_DEFINE:
        case SYN_LINE:
        case SYN_MACRO_INCLUDE:
        case SYN_MACRO_UNDEF:
        case SYN_ERROR:
        case SYN_PRAGMA:
        case SYN_SHARP:
        case SYN_MACRO_IF:
        case SYN_MACRO_IFDEF:
        case SYN_MACRO_IFNDEF:
            return true;
        default:
            return false;
    }
}
void SyntaxAnalyzer::BuildAST(void){
    Match(-2);
    while(!isEOF()){
        Statement();
    }
    return;
}

void SyntaxAnalyzer::StructOrUnion(void){
    int type = CurrentTokenType;
    if(CurrentTokenType == SYN_KEYWORD){
        id_name = getTokenString();
        Match(SYN_KEYWORD);
    }
    if(CurrentTokenType == SYN_BRACE_L){
        Match(SYN_BRACE_L);
        if(type == SYN_STRUCT)
            StructList();
        else
            UnionList();
        Match(SYN_BRACE_R);
    }
    if(CurrentTokenType == SYN_KEYWORD)
        Match(SYN_KEYWORD);
    if(CurrentTokenType == SYN_SET){
        Match(SYN_SET);
        Primary(CurrentTokenType);
    }
    return;
}

void SyntaxAnalyzer::StatementID(void){
    id_name = getTokenString();
    Match(SYN_KEYWORD);
    if(CurrentTokenType == SYN_SET){
#if defined(syntaxanalyzer)
    std::cout << "StatementID-> id[=Primary] IdList;" << std::endl;
#endif
        Match(SYN_SET);
        Primary(CurrentTokenType);
        IdList();
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_COLON){
#if defined(syntaxanalyzer)
    std::cout << "StatementID-> id[:ConstExpress] IdList;" << std::endl;
#endif
        Match(SYN_COLON);
        ConstExpress();
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_SQU_BRACE_L){
#if defined(syntaxanalyzer)
    std::cout << "StatementArray-> id[ ConstExpress ] Brace[=Primary];" << std::endl;
#endif
        statement_type |= array_mask;
        id_primary.arrayinfo.Dimension = 1;
        Match(SYN_SQU_BRACE_L);
        id_primary.arrayinfo.dims.push_back(ConstExpress());
        Match(SYN_SQU_BRACE_R);
        Brace();
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
        }
        Match(SYN_SEMIC);
    }
    else{
        IdList();
        Match(SYN_SEMIC);
    }
    return;
}

void SyntaxAnalyzer::StatementFunction(void){
#if defined(syntaxanalyzer)
    std::cout << "StatementFunction-> function(ArgumentList)(;|{Statement}) " << std::endl;
#endif
    Match(SYN_FUNCTION);
    Match(SYN_PAREN_L);
    ArgumentList();
    Match(SYN_PAREN_R);
    if(CurrentTokenType == SYN_SEMIC){
        return; //Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_BRACE_L){
        CompoundSentence();
    }
    return;
}

// 判断文件是否已经读取完毕
inline bool SyntaxAnalyzer::isEOF(void){
    return (tokenAnalyzer.isEOF()) ? true : false;
}

// 获取Token的字符串
std::string SyntaxAnalyzer::getTokenString(void){
    return tokenAnalyzer.tokenString();
}

// 获取Token的编码
inline int SyntaxAnalyzer::getTokenCoding(void){
    return KeyWordMap[getTokenString()];
}

void SyntaxAnalyzer::BackAToken(void){
    int offset = tokenAnalyzer.tokenLength();
    offset = 0 - offset;
    tokenAnalyzer.SeekFileHandler(offset);
    return;
}

void SyntaxAnalyzer::Match(int type){
    char TempChar; 
    if(type == token.TokenType){
        token = tokenAnalyzer.NextToken();
        if(token.TokenType == SYN_KEYWORD){
            TempChar = tokenAnalyzer.ReadAChar();
            if(TempChar == '('){
                token.TokenType = SYN_FUNCTION;
            }
            tokenAnalyzer.SeekFileHandler(-1);
        }
        CurrentTokenType = token.TokenType;
        return ;
    }
    else if(type == -2){
        token = tokenAnalyzer.NextToken();
        CurrentTokenType = token.TokenType;
        return ;
    }
    else{
        std::cout <<  " No Match symbol: " << token.TokenType << std::endl;
        exit(1);
    }
}

// Value define
void SyntaxAnalyzer::Statement(void){

    if(isStoreTypeSymbol(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> [StoreTypeSymbol] [ LimitTypeSymbol ] Type  process_id_or_function_statement;" << token.tokenValue.StringValue << std::endl;
#endif
        StoreTypeSymbol();
        if(isLimitTypeSymbol(CurrentTokenType)){
            LimitTypeSymbol();
        }
        process_id_or_function_statement
    }
    else if(isLimitTypeSymbol(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> [ LimitTypeSymbol ] Type process_id_or_function_statement;" << std::endl;
#endif
        LimitTypeSymbol();
        process_id_or_function_statement
    }
    else if(isType(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> Type  process_id_or_function_statement;" << std::endl;
#endif
        process_id_or_function_statement
    }
    else if(CurrentTokenType == SYN_SEMIC){
#if defined(syntaxanalyzer)
    std::cout << "Statement->;" << std::endl;
#endif
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_IF){
#if defined(syntaxanalzyer)
    std::cout << "Statement-> if(Express) Statement [else Statement]" << std::endl;
#endif
        Match(SYN_IF);
        Match(SYN_PAREN_L);
        Express();
        Match(SYN_PAREN_R);
        Statement();
        if(CurrentTokenType == SYN_ELSE){
            Match(SYN_ELSE);
            Statement();
        }
    }
    else if(CurrentTokenType == SYN_SWITCH){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> switch(Express) Statement" << std::endl;
#endif  
        Match(SYN_SWITCH);
        Match(SYN_PAREN_L);
        Express();
        Match(SYN_PAREN_R);
        Statement();
    }
    else if(CurrentTokenType == SYN_CASE){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> case ConstExpress:Statement" << std::endl;
#endif
        Match(SYN_CASE);
        ConstExpress();
        Match(SYN_COLON);
        Statement();
    }
    else if(CurrentTokenType == SYN_DEFAULT){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> default:Statement" << std::endl;
#endif
        Match(SYN_DEFAULT);
        Match(SYN_COLON);
        Statement();
    }
    else if(CurrentTokenType == SYN_WHILE){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> While(Express) Statement" << std::endl;
#endif
        Match(SYN_WHILE);
        Match(SYN_PAREN_L);
        Express();
        Match(SYN_PAREN_R);
        Statement();
    }
    else if(CurrentTokenType == SYN_DO){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> do Statement while(Express);" << std::endl;
#endif
        Match(SYN_DO);
        Statement();
        Match(SYN_WHILE);
        Express();
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_FOR){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> for([Express];[Express];[Express]) Statement" << std::endl;
#endif
        Match(SYN_FOR);
        Match(SYN_PAREN_L);
        if(CurrentTokenType != SYN_SEMIC){
            Express();
        }
        Match(SYN_SEMIC);
        if(CurrentTokenType != SYN_SEMIC)
            Express();
        Match(SYN_SEMIC);
        if(CurrentTokenType != SYN_SEMIC)
            Express();
        Match(SYN_PAREN_R);
        Statement();
    }
    else if(CurrentTokenType == SYN_GOTO){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> goto id;" << std::endl;
#endif
        Match(SYN_GOTO);
        Match(SYN_KEYWORD);
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_CONTINUE){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> continue;" << std::endl;
#endif
        Match(SYN_CONTINUE);
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_BREAK){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> break;" << std::endl;
#endif
        Match(SYN_BREAK);
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_RETURN){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> return [Express] ;" << std::endl;
#endif
        Match(SYN_RETURN);
        if(CurrentTokenType != SYN_SEMIC)
            Express();
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_BRACE_L){
#if defined(syntaxanalyzer)
    std::cout << "Statement->CompoundSentence" << std::endl;
#endif
        CompoundSentence();
    }
    else if(isControlInstruction(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Statement-> ControlInstruction" << std::endl;
#endif  
        ControlInstruction();
    }
    else if(CurrentTokenType == SYN_MACRO_ELIF || CurrentTokenType == SYN_MACRO_ELSE || CurrentTokenType == SYN_MACRO_ENDIF){
        PreProcessorConditionInstruction();
        return;
    }
    else{
        Express();
        Match(SYN_SEMIC);
    }
    return;
}

void SyntaxAnalyzer::StoreTypeSymbol(void){
#if defined(syntaxanalyzer)
    std::cout << "StoreTypeSymbol-> " << getTokenString() << std::endl; 
#endif
    int code = getTokenCoding();
    switch (code)
    {
        case SYN_AUTO:
            store_type = AUTO;//2
            break;
        case SYN_STATIC:
            store_type = STATIC;//1
            break;
        case SYN_REGISTER:
            store_type = REGISTER;//3
            break;
        case SYN_EXTERN:
            store_type = EXTERN;//4
            break;
        case SYN_TYPEDEF:
            store_type = TYPEDEF;
            break;
    }
    Match(code);
    return;
}

void SyntaxAnalyzer::LimitTypeSymbol(void){
#if defined(syntaxanalyzer)
    std::cout << "LimitTypeSymbol-> " << getTokenString() << std::endl;
#endif
    if(getTokenCoding() == SYN_CONST){
        limit_type = 1;
    }
    else{
        limit_type = 2;
    }
    Match(getTokenCoding());
    return;
}

static std::vector<struct ValueAliasName>::const_iterator getAlias(const std::string alias){
    auto alias_begin = ValueAlais.cbegin();
    while(alias_begin != ValueAlais.cend()){
        if(alias_begin->alias == alias)
            break;
        alias_begin++;
    }
    return alias_begin;
}

void SyntaxAnalyzer::Type(void){
#if defined(syntaxanalyzer)
    std::cout << "Type-> " << getTokenString()  << std::endl;
#endif

    if(KeyWordMap.count(getTokenString())){
        int code = getTokenCoding();
        switch (code)
        {   
            case SYN_SHORT:
                statement_type |= short_mask;
                break;
            case SYN_INT:
                statement_type |= int_mask;
                break;
            case SYN_SIGNED:
                statement_type |= signed_mask;
                break;
            case SYN_UNSIGNED: 
                statement_type |= unsigned_mask;
                break;
            case SYN_LONG:
                statement_type |= long_mask;
                break;
            case SYN_CHAR:
                statement_type |= char_mask;
                break;
            case SYN_FLOAT:
                statement_type |= float_mask;
                break;
            case SYN_DOUBLE:
                statement_type |= double_mask;
                break;
            case SYN_STRING:
                statement_type |= string_mask;
                break;
            case SYN_STRUCT:
                statement_type |= struct_mask;
                break;
            case SYN_UNION:
                statement_type |= union_mask;
                break;
            case SYN_ENUM: 
                statement_type |= enum_mask;
                break;
            case SYN_MUL:
                statement_type |= pointer_mask;
                Pointer();
                break;
        }
        Match(code);
    }
    else if(CurrentTokenType == SYN_MUL){
        Pointer();
    }
    else if(CurrentTokenType == SYN_KEYWORD){
        
        alias_name = getTokenString();
        if(getAlias(alias_name) != ValueAlais.cend()){
            statement_type |= seldefine_mask;
            Match(SYN_KEYWORD);
        }
    }
    return;
}

void SyntaxAnalyzer::Primary(int tokenvalue){
    switch(tokenvalue){
        case SYN_NUMBER_DOUBLE:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> double_num "<< token.tokenValue.StringValue << std::endl;
#endif
            id_primary.number.realNumber.floatNumber.DoubleNumber = token.tokenValue.number.realNumber.floatNumber.DoubleNumber;
            Match(SYN_NUMBER_DOUBLE);
            return;
        case SYN_NUMBER_LONG:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> long_num " << token.tokenValue.StringValue << " " << token.TokenType << std::endl;
#endif
            id_primary.number.realNumber.intgerNumber.LongNumber = token.tokenValue.number.realNumber.intgerNumber.LongNumber;
            Match(SYN_NUMBER_LONG);
            return;
        case SYN_STRING:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> "<< token.tokenValue.StringValue  << std::endl;
#endif
            id_primary.StringValue = token.tokenValue.StringValue;
            Match(SYN_STRING);
            return;
        case SYN_KEYWORD:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> id "<< token.tokenValue.StringValue << std::endl;
#endif
            CopyToNewId(getTokenString(),id_primary);
            Match(SYN_KEYWORD);
            return;
        case SYN_BRACE_L:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> {PrimaryList [,]}" << std::endl;
#endif
            Match(SYN_BRACE_L);
            PrimaryList();
            if(CurrentTokenType == SYN_COMMA){
                Match(SYN_COMMA);
            }
            Match(SYN_BRACE_R);
            return;
    }
}

void SyntaxAnalyzer::PrimaryList(void){
#if defined(syntaxanalyzer)
    std::cout << "PrimaryList-> Primary PList" << std::endl;
#endif
    InStruct = true;
    Primary(CurrentTokenType);
    PList();
    InStruct = false;
    return;
}

void SyntaxAnalyzer::PList(void){
    if(GlobalScopeValue && InStruct)
        struct_info.push_back(id_primary);
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "PList-> ,Primary PList" << std::endl;
#endif
        Match(SYN_COMMA);
        Primary(CurrentTokenType);
        PList();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "PList->" << std::endl;
#endif
    }
    return;
}

static void ResetGlobalvalue(void){
    store_type = 0;
    limit_type = 0;
    statement_type = 0;
    id_name = "";
    function_name = "";
    id_primary.arrayinfo.Dimension = 0;
    id_primary.arrayinfo.dims.erase(id_primary.arrayinfo.dims.cbegin(),id_primary.arrayinfo.dims.cend());
    id_primary.StringValue = "";
    id_primary.number.realNumber.floatNumber.DoubleNumber = 0;
    id_primary.number.realNumber.intgerNumber.LongNumber = 0;
}

static void ResetAlias(void){
    alias_name = "";
    ResetGlobalvalue();
    return;
}

void SyntaxAnalyzer::BuildSymbolTable(void){
    if(GlobalScopeValue && store_type != TYPEDEF){
        if(statement_type & seldefine_mask){
            auto alias = getAlias(alias_name);
            if(alias != ValueAlais.cend()){
                valueinfo.store_type = alias->store_type;
                valueinfo.limit_type = alias->limit_type;
                valueinfo.value_type = alias->value_type;
                CopyValue(alias->value_type,id_primary,valueinfo)
            }
        }
        else{
            valueinfo.store_type = store_type;
            valueinfo.limit_type = limit_type;
            valueinfo.value_type = statement_type;
            if(statement_type & array_mask){
                valueinfo.value.arrayinfo.Dimension = id_primary.arrayinfo.Dimension;
                valueinfo.value.arrayinfo.dims = id_primary.arrayinfo.dims;             
            }
            else {
                CopyValue(statement_type,id_primary,valueinfo)
            }

        }
        valueinfo.value_name = id_name;
        GlobalValue.push_back(valueinfo);
    }
    else if(GlobalScopeValue && store_type == TYPEDEF){
        aliasname.limit_type = limit_type;
        aliasname.value_type = statement_type;
        aliasname.alias = id_name;
        ValueAlais.push_back(aliasname);
    }

    return ;
}

void SyntaxAnalyzer::IdList(void){
    BuildSymbolTable();
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "IdList-> , id[=Primary] IdList" << std::endl;
#endif
        
        Match(SYN_COMMA);
        id_name = getTokenString();
        Match(SYN_KEYWORD);
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
        }
        IdList();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "IdList->" << std::endl;
#endif
        ResetGlobalvalue();
    }
    ResetGlobalvalue(); 
    return;
}
//
// 指针
void SyntaxAnalyzer::Pointer(void){
    statement_type |= pointer_mask;
    if(CurrentTokenType == SYN_MUL){
#if defined(syntaxanalyzer)
    std::cout << "Pointer-> * [LimitTypeSymbol] Pointer" << std::endl;
#endif  
        Match(SYN_MUL);
        if(isLimitTypeSymbol(CurrentTokenType))
            LimitTypeSymbol();
        Pointer();
    }
    else
    {
#if defined(syntaxanalyzer)
    std::cout << "Pointer->" << std::endl;
#endif
    }
    
}

void SyntaxAnalyzer::ArgumentList(void){
    if(CurrentTokenType == SYN_PAREN_R){
#if defined(syntaxanalyzer)
    std::cout << "ArgumentList->" << std::endl;
#endif
        return;
    }
    else {
#if defined(syntaxanalyzer)
    std::cout << "ArgumentList->ArgumentType Argument" << std::endl;
#endif
        ArgumentType();
        Argument();
    }
    return;
}

void SyntaxAnalyzer::Argument(void){
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "Argument-> , ArgumentType Argument" << std::endl;
#endif
        Match(SYN_COMMA);
        ArgumentType();
        Argument();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "Argument-> " << std::endl;
#endif  
        ;
    }
    return;
}

void SyntaxAnalyzer::ArgumentType(void){

    if(CurrentTokenType == SYN_TRIDOTS){
#if defined(sytaxanalyzer)
    std::cout << "ArgumentType-> ..." << std::endl;
#endif
        Match(SYN_TRIDOTS);
        return;        
    }
    if(isLimitTypeSymbol(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "ArgumentType-> [LimitTypeSymbol] Type [ id[=Primary] ] " << std::endl;
#endif
        LimitTypeSymbol();
    }
    while(isType(CurrentTokenType))
        Type();
    if(CurrentTokenType == SYN_KEYWORD){
#if defined(syntaxanalyzer)
    std::cout << "id-> " << token.tokenValue.StringValue << std::endl;
#endif
        if(CurrentTokenType == SYN_NULL)
        {
            Match(SYN_NULL);
            return;
        }
        Match(SYN_KEYWORD);
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
        }
    }
    return;
}

void SyntaxAnalyzer::CompoundSentence(void){
#if defined(syntaxanalyzer)
    std::cout << "CompoundSentence-> {S}" << std::endl;
#endif
    Match(SYN_BRACE_L);
    while(CurrentTokenType != SYN_BRACE_R)
        Statement();
    Match(SYN_BRACE_R);
    return;
}

void SyntaxAnalyzer::Brace(void){
    
    if(CurrentTokenType == SYN_SQU_BRACE_L){
#if defined(syntaxanalyzer)
    std::cout << "Brace-> [ConstExpress] Brace" << std::endl;
#endif
        id_primary.arrayinfo.Dimension++;
        Match(SYN_SQU_BRACE_L);
        id_primary.arrayinfo.dims.push_back(ConstExpress());
        Match(SYN_SQU_BRACE_R);
        Brace();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "Brace-> " << std::endl;
#endif        
        ;
    }
    BuildSymbolTable();
    ResetGlobalvalue();
    return;
}

long SyntaxAnalyzer::ConstExpress(void){
    long number_value;
    switch(CurrentTokenType){
        case SYN_NUMBER_LONG:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> Num_long" << std::endl;
#endif
            number_value = std::stol(getTokenString().c_str()); 
            Match(SYN_NUMBER_LONG);
            return number_value;
        case SYN_NUMBER_DOUBLE:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> Num_double" << std::endl;
#endif
            Match(SYN_NUMBER_DOUBLE);
            return 0;
        case SYN_STRING:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> string" << std::endl;
#endif
            Match(SYN_STRING);
            return 0;
        case SYN_KEYWORD:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> id" << std::endl;
#endif
            /* Check value Table */
            Match(SYN_KEYWORD);
            return 0;
        case SYN_FUNCTION:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress->  Functon" << std::endl;
#endif
            Match(SYN_FUNCTION);
            return 0;
        default:
            return 0;
            Error("Symbol Error!",1)
    }
    return 0;
}

void SyntaxAnalyzer::StructList(void){
#if defined(syntaxanalyzer)
    std::cout << "StructList-> Statement" << std::endl;
#endif
    while(CurrentTokenType != SYN_BRACE_R)
        Statement();
    return;
}

void SyntaxAnalyzer::UnionList(void){
#if defined(syntaxanalyzer)
    std::cout << "id[=Primary] Union" << std::endl;
#endif
    Match(SYN_KEYWORD);
    if(CurrentTokenType == SYN_SET){
        Match(SYN_SET);
        Primary(CurrentTokenType);
    }
    Union();
    return;
}

void SyntaxAnalyzer::Union(void){

    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "Union-> , id[=Primary] Union" << std::endl;
#endif
        Match(SYN_COMMA);
        Match(SYN_KEYWORD);
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
        }
        Union();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "Union-> " << std::endl;
#endif
        ;
    }
    return;
}

//
// ==============================================================================
void SyntaxAnalyzer::Express(void){
#if defined(syntaxanalyzer)
    std::cout << "Express-> AssignmentExpress Express1" << std::endl;
#endif
    AssignmentExpress();
    Express1();
    return;
}

void SyntaxAnalyzer::Express1(void){
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "Express1-> , AssignmentExpress Express1" << std::endl;
#endif
        Match(SYN_COMMA);
        AssignmentExpress();
        Express1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "Express1->" << std::endl;
#endif
        ;
    }
    return;
}

static bool isUnaryExpress(int tokentype){
    switch (tokentype)
    {
        case SYN_INC:
        case SYN_DEC:
        case SYN_BIT_AND:
        case SYN_MUL:
        case SYN_ADD:
        case SYN_SUB:
        case SYN_BIT_NOT:
        case SYN_NOT:
        case SYN_SIZEOF:
        case SYN_KEYWORD:
        case SYN_STRING:
        case SYN_NUMBER_DOUBLE:
        case SYN_NUMBER_LONG:
        case SYN_PAREN_L:
            return true;
        default:
            return false;       
    }
}
void SyntaxAnalyzer::AssignmentExpress(void){
    if(isUnaryExpress(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "AssignmentExpress-> UnaryExpress AssignmentOperator AssignmentExpress" << std::endl;
#endif
        UnaryExpress();
        AssignmentOperator();
        AssignmentExpress();
    }
    else {
#if defined(syntaxanalyzer)
    std::cout << "AssignmentExpress-> ConditionExpress" << std::endl;
#endif
        ConditionExpress();
    }
    return;
}

void SyntaxAnalyzer::AssignmentOperator(void){
    switch(CurrentTokenType){
        case SYN_SET:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> = " << std::endl;
#endif
        Match(getTokenCoding());
        break;

        case SYN_ME:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator->  *= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_DE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> /= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_MODEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> %= " << std::endl;
#endif
        case SYN_AE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> += " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_SE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> -= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_BIT_SHLEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> <<= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_BIT_SHREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> >>= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_BIT_ANDEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator->  &= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_BIT_XOREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> ^= " << std::endl;
#endif
        Match(getTokenCoding());
        break;
        case SYN_BIT_OREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> |=" << std::endl;
#endif
        Match(getTokenCoding());
        break;
        default:
            return;
    }
}
void SyntaxAnalyzer::ConditionExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "ConditionExpres-> LogicOrExpress [ ? Express:ConditionExpress]" << std::endl;
#endif
    LogicOrExpress();
    if(CurrentTokenType == SYN_QUES){
        Match(SYN_QUES);
        Express();
        Match(SYN_COLON);
        ConditionExpress();
    }
    return;
}

void SyntaxAnalyzer::LogicOrExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "LogicOrExpress-> LogicAndExpress LogicOrExpress1" << std::endl;
#endif
    LogicAndExpress();
    LogicOrExpress1();
    return;
}

void SyntaxAnalyzer::LogicOrExpress1(void){
    if(CurrentTokenType == SYN_OR){
#if defined(syntaxanalyzer)
    std::cout << "LogicOrExpress1-> || LogicAndExpress LogicOrExpress1" << std::endl;
#endif
        Match(SYN_OR);
        LogicAndExpress();
        LogicOrExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "LogicOrExpress1->" << std::endl;
#endif  
        ;
    }
    return;
}

void SyntaxAnalyzer::LogicAndExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "LogicAndExpress-> BitOrExpress LogicAndExpress1" << std::endl;
#endif
    BitOrExpress();
    LogicAndExpress1();
    return;
}

void SyntaxAnalyzer::LogicAndExpress1(void){
    if(CurrentTokenType == SYN_AND){
#if  defined(syntaxanalyzer)
    std::cout << "LogicAndExpress1-> && BitExpress LogicAndExpress1" << std::endl;
#endif
        Match(SYN_AND);
        BitOrExpress();
        LogicAndExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "LogicAndExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::BitOrExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitOrExpress->BitXorExpress BitOrExpress1" << std::endl;
#endif
    BitXorExpress();
    BitOrExpress1();
}

void SyntaxAnalyzer::BitOrExpress1(void){
    if(CurrentTokenType == SYN_BIT_OR){
#if defined(syntaxanalyzer)
    std::cout << "BitOrExpress1-> | BitXorExpress BitOrExpress1" << std::endl;
#endif
        Match(SYN_BIT_OR);
        BitXorExpress();
        BitOrExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "BitOrExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::BitXorExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitXorExpress-> BitAndExpress BitXorExpress1" << std::endl;
#endif
    BitAndExpress();
    BitXorExpress1();
}

void SyntaxAnalyzer::BitXorExpress1(void){
    if(CurrentTokenType ==  SYN_BIT_XOR){
#if defined(syntaxanalyzer)
    std::cout << "BitXorExpress1-> ^ BitAndExpress BitXorExpress1" << std::endl;
#endif
        Match(SYN_BIT_XOR);
        BitAndExpress();
        BitXorExpress1();
    }
    else
    {
#if defined(syntaxanalyzer)
    std::cout << "BitXorExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::BitAndExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitAndExpress-> EqualClassExpress BitAndExpress1" << std::endl;
#endif
    EqualClassExpress();
    BitAndExpress1();
}

void SyntaxAnalyzer::BitAndExpress1(void){
    if(CurrentTokenType == SYN_BIT_AND){
#if defined(syntaxanalyzer)
    std::cout << "BitAndExpress1-> & EqualClassExpress BitAndExpres1" << std::endl;
#endif
        Match(SYN_BIT_AND);
        EqualClassExpress();
        BitAndExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "BitAndExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::EqualClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "EqualClassExpress-> RelationExpress EqualClassExpress1" << std::endl;
#endif  
    RelationExpress();
    EqualClassExpress1();
}

void SyntaxAnalyzer::EqualClassExpress1(void){
    if(CurrentTokenType == SYN_NOTEQ || CurrentTokenType == SYN_EQ){
#if defined(syntaxanalyzer)
    std::cout << "EqualClassExpress1->(== | !=) RelationExpress EqualClassExpress1" << std::endl;
#endif
        std::cout << token.tokenValue.StringValue << std::endl;
        Match(getTokenCoding());
        RelationExpress();
        EqualClassExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "EqualClassExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::RelationExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "RelationExpress-> ShiftExpress RelationExpress1" << std::endl;
#endif  
    ShiftExpress();
    RelationExpress1();
}

void SyntaxAnalyzer::RelationExpress1(void){
    if(CurrentTokenType  == SYN_GT || CurrentTokenType == SYN_GE || CurrentTokenType == SYN_LT || CurrentTokenType == SYN_LE){
#if defined(syntaxanalyzer)
    std::cout << "RelationExpress1-> (<|>|<=|>=) ShiftExpress RelationExpress1" << std::endl;
#endif        
        Match(getTokenCoding());
        ShiftExpress();
        RelationExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "RelationExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::ShiftExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "ShiftExpress-> AddClassExpress ShiftExpress" << std::endl;
#endif
    AddClassExpress();
    ShiftExpress1();
}

void SyntaxAnalyzer::ShiftExpress1(void){
    if(CurrentTokenType == SYN_BIT_SHL || CurrentTokenType == SYN_BIT_SHR){
#if defined(syntaxanalyzer)
    std::cout << "ShiftExpress1-> (<<|>>) AddClassExpress ShiftExpress1" << std::endl;
#endif
        Match(getTokenCoding());
        AddClassExpress();
        ShiftExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "ShiftExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::AddClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "AddClassExpress-> MulClassExpress AddClassExpress1" << std::endl;
#endif
    MulClassExpress();
    AddClassExpress1();
}

void SyntaxAnalyzer::AddClassExpress1(void){
    if(CurrentTokenType == SYN_ADD || CurrentTokenType == SYN_SUB){
#if defined(syntaxanalyzer)
    std::cout << "AddClassExpress1-> (+|-) MulClassExpress AddClassExpress1" << std::endl;
#endif
        Match(getTokenCoding());
        MulClassExpress();
        AddClassExpress1();
    }
    else{
#if defined(syntaxanalzyer)
    std::cout << "AddClassExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::MulClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "MulClassExpress-> ForeceTranExpress MulClassExpress1" << std::endl;
#endif
    ForceTranExpress();
    MulClassExpress1();
}

void SyntaxAnalyzer::MulClassExpress1(void){
    if(CurrentTokenType == SYN_MUL  || CurrentTokenType == SYN_DIV || CurrentTokenType == SYN_MOD){
#if defined(syntaxanalyzer)
    std::cout << "(*|/|%) ForeceTranExpress MulClassExpress1" << std::endl;
#endif
        if(CurrentTokenType != SYN_MUL)
            Match(getTokenCoding());
        else
        {
            Match(SYN_MUL);
        }
        
        ForceTranExpress();
        MulClassExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "MulClassExpress1->" << std::endl;
#endif
        ;
    }
    return;
}

void SyntaxAnalyzer::ForceTranExpress(void){
    if(CurrentTokenType == SYN_PAREN_L){
#if defined(syntaxanalyzer)
    std::cout << "ForceTranExpress-> (Type) ForceTranExpress" << std::endl;
#endif
        Match(SYN_PAREN_L);
        Type();
        Match(SYN_PAREN_R);
        ForceTranExpress();
    }
    else if(isType(CurrentTokenType)){
        Type();
        ForceTranExpress();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "ForceTranExpress-> UnaryExpress" << std::endl;
#endif
        UnaryExpress();
    }
    return;
}

static bool isUnaryOperator(int tokentype){
    switch(tokentype){
        case SYN_BIT_AND:
        case SYN_MUL:
        case SYN_ADD:
        case SYN_SUB:
        case SYN_BIT_NOT:
        case SYN_NOT:
        case SYN_FUNCTION:
            return true;
        default:
            return false;
    }

}

static bool isConstantExpress(int tokentype){
    switch (tokentype)
    {
        case SYN_KEYWORD:
        case SYN_NUMBER_DOUBLE:
        case SYN_NUMBER_LONG:
        case SYN_STRING:
            return true;
        default:
            return false;
    }
}
void SyntaxAnalyzer::Args(void){
            if(CurrentTokenType == SYN_KEYWORD){
#if defined(syntaxanalyzer)
    std::cout << "Args-> id" << token.tokenValue.StringValue << std::endl;
#endif
                Match(SYN_KEYWORD);
            }
            else if( CurrentTokenType == SYN_PAREN_R || CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "Args-> " << std::endl;
#endif
                ;
            }
            else if(isConstantExpress(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Args-> ConstExpress" << " " << token.tokenValue.StringValue << std::endl;
#endif  
                switch (CurrentTokenType)
                {
                    case SYN_STRING:
                        Match(SYN_STRING);
                        break;
                    case SYN_NUMBER_DOUBLE:
                        Match(SYN_NUMBER_DOUBLE);
                        break;
                    case SYN_NUMBER_LONG:
                        Match(SYN_NUMBER_LONG);
                        break;
                }
            }
            else if(isType(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Args-> Type [id[=Primary]] " << std::endl;
#endif
                Type();
                if(CurrentTokenType == SYN_KEYWORD)
                {
                    Match(SYN_KEYWORD);
                    if(CurrentTokenType == SYN_SET){
                        Match(SYN_SET);
                        Primary(CurrentTokenType);
                    }
                }
            }
            else if(isUnaryExpress(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "Args-> UnaryExpress" << std::endl;
#endif
                UnaryExpress();
            }
}

void SyntaxAnalyzer::UnaryExpress(void){
    if(CurrentTokenType == SYN_INC || CurrentTokenType == SYN_DEC){
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> (++|--) UnaryExpress" << std::endl;
#endif
        Match(getTokenCoding());
        UnaryExpress();
    }
    else if(isUnaryOperator(CurrentTokenType)){
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> UnaryOperator ForceTranExpress" << std::endl;
#endif
        if(CurrentTokenType == SYN_MUL)
            Match(SYN_MUL);
        else if(CurrentTokenType == SYN_FUNCTION){
            Match(SYN_FUNCTION);
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> function(Args)  RealArgument)" << std::endl;
#endif
            Match(SYN_PAREN_L);
            Args();
            RealArgument();
            Match(SYN_PAREN_R);
        }
        else
            Match(getTokenCoding());
        ForceTranExpress();
    }
    else if(CurrentTokenType == SYN_SIZEOF){
        Match(SYN_SIZEOF);
        if(CurrentTokenType == SYN_PAREN_L){
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> sizeof(type)" << std::endl;
#endif
            Match(SYN_PAREN_L);
            Type();
            Match(SYN_PAREN_R);
        }
        else{
#if defined(syntaxanalyzer)
    std:;cout << "UnaryExpress-> sizeof UnaryExpress" << std::endl;
#endif
            UnaryExpress();
        }
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> PostfixExpress" << std::endl;
#endif
        PostfixExpress();
    }
    return;
}

void SyntaxAnalyzer::PostfixExpress(void){
    PrimaryExpress();
    PostfixExpress1();
}

void SyntaxAnalyzer::PostfixExpress1(void){
    switch(CurrentTokenType){
        case SYN_SQU_BRACE_L:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1-> [Express] PostfixExpress1 " << std::endl;
#endif
            Match(SYN_SQU_BRACE_L);
            Express();
            Match(SYN_SQU_BRACE_R);
            PostfixExpress1();
            break;
        case SYN_PAREN_L:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1->  ([ArgumentExpress])  PostfixExpress1 " << std::endl;
#endif
            Match(SYN_PAREN_L);
            if(CurrentTokenType == SYN_PAREN_R){
                ;
            }
            else{
                ArgumentExpress();
            }
            Match(SYN_PAREN_R);
            PostfixExpress1();
            break;
        case SYN_DOT:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1-> .id PostfixExpress1 " << std::endl;
#endif
            Match(SYN_DOT);
            Match(SYN_KEYWORD);
            PostfixExpress1();
            break;
        case SYN_INC:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1->  ++ PostfixExpress1 " << std::endl;
#endif
            Match(SYN_INC);
            PostfixExpress1();
            break;
        case SYN_DEC:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1->  -- PostfixExpress1 " << std::endl;
#endif
            Match(SYN_DEC);
            PostfixExpress1();
            break;
        case SYN_POINTER:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1-> ->id  PostfixExpress1 " << std::endl;
#endif
            Match(SYN_POINTER);
            Match(SYN_KEYWORD);
            PostfixExpress1();
            break;
        default:
#if defined(syntaxanalyzer)
    std::cout << "PostfixExpress1->" << std::endl;
#endif  
        return;
    }
}

void SyntaxAnalyzer::PrimaryExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "PrimaryExpress-> Id | ConstExpress | (Express)" << std::endl;
#endif
    if(CurrentTokenType == SYN_KEYWORD){
#if defined(syntaxanalyzer)
    std::cout << "id-> " << token.tokenValue.StringValue << std::endl;
#endif
        Match(SYN_KEYWORD);
    }
    else if(CurrentTokenType == SYN_NUMBER_DOUBLE){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        Match(SYN_NUMBER_DOUBLE);
    }
    else if(CurrentTokenType == SYN_NUMBER_LONG){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        Match(SYN_NUMBER_LONG);
    }
    else if(CurrentTokenType == SYN_STRING){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        Match(SYN_STRING);
    }
    else if(CurrentTokenType == SYN_PAREN_L){
        Match(SYN_PAREN_L);
        Express();
        Match(SYN_PAREN_R);
    }
    return;
}

void SyntaxAnalyzer::ArgumentExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "ArgumentExpress-> AssignmentExpress ArgumentExpress1" << std::endl;
#endif
    AssignmentExpress();
    ArgumentExpress1();
}

void SyntaxAnalyzer::ArgumentExpress1(void){
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "ArgumentExpress1-> , ArgumentExpress ArgumentExpress1" << std::endl;
#endif
        Match(SYN_COMMA);
        ArgumentExpress();
        ArgumentExpress1();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "ArgumentExpress1-> " << std::endl;
#endif
        ;
    }
}

void SyntaxAnalyzer::RealArgument(void){
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "RealArgument-> , Args RealArgument" << std::endl;
#endif
        Match(SYN_COMMA);
        Args();
        RealArgument();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "RealArgument->" << std::endl;
#endif        
        ;
    }
    return;
}

// =================================================================
// 预处理

void SyntaxAnalyzer::Constant(void){
    ;
}

bool isLabelList(int tokenvalue){
    return true;
}
void SyntaxAnalyzer::ControlInstruction(void){
    InPreProcess = true;
    switch(CurrentTokenType){
        case SYN_MACRO_DEFINE:
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#define id[([idlist])] labellist" << std::endl;
#endif
            Match(SYN_MACRO_DEFINE);
            if(CurrentTokenType == SYN_KEYWORD)
                Match(SYN_KEYWORD);
            else {
                Match(SYN_FUNCTION);
            }
            if(CurrentTokenType == SYN_PAREN_L){
                Match(SYN_PAREN_L);
                if(CurrentTokenType == SYN_PAREN_R){
                    ;
                }
                else if(CurrentTokenType == SYN_KEYWORD){
                    Match(SYN_KEYWORD);
                    IdList();
                }
                Match(SYN_PAREN_R);
            }
            Express();
            break;
        case SYN_MACRO_UNDEF:
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#undef id" << std::endl;
#endif
            Match(SYN_MACRO_UNDEF);
            Match(SYN_KEYWORD);
            break;
        case SYN_MACRO_INCLUDE:
            Match(SYN_MACRO_INCLUDE);
            _PreProcess = true;
            if(CurrentTokenType == SYN_STRING){
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#include string" << std::endl;
#endif
                Match(SYN_STRING);
                _PreProcess = true;
            }
            else if(CurrentTokenType == SYN_LT){
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#include <Text>" << std::endl;
#endif      
                Match(SYN_LT);
                Match(SYN_TEXT);
                Match(SYN_GT);
                _PreProcess = true;
            }
            else{
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#include LabelList" << std::endl;
#endif
                LabelList();
                _PreProcess = true;
            }
            break;
        case SYN_LINE:
            Match(SYN_LINE);
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#line Constant [string]" << std::endl;
#endif
            Constant();
            if(CurrentTokenType == SYN_STRING){
                Match(SYN_STRING);
            }
            break;
        case SYN_ERROR:
            Match(SYN_ERROR);
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#error [LabelList]" << std::endl;
#endif
            if(isLabelList(CurrentTokenType)){
                LabelList();
            }
            break;
        case SYN_PRAGMA:
            Match(SYN_PRAGMA);
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#pragma [LabelList]" << std::endl;
#endif            
            if(isLabelList(CurrentTokenType)){
                LabelList();
            }
            break;
        case SYN_SHARP:
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->#" << std::endl;
#endif
            Match(SYN_SHARP);
            break;
        default:
#if defined(syntaxanalyzer)
    std::cout << "ControlInstruction->PreProcessorConditionInstruction" << std::endl;
#endif
            PreProcessorConditionInstruction();
    }
}

void SyntaxAnalyzer::PreProcessorConditionInstruction(void){
    switch(CurrentTokenType){
        case SYN_MACRO_IF:
#if defined(syntaxanalyzer)
    std::cout << "PreProcessorConditionInstruction->#if Express" << std::endl;
#endif
            Match(SYN_MACRO_IF);
            Express();
            break;
        case SYN_MACRO_IFDEF:
#if defined(syntaxanalyzer)
    std::cout << "PreProcessorConditionInstruction->#ifdef ConstExpress" << std::endl;
#endif
            Match(SYN_MACRO_IFDEF);
            ConstExpress();
            
            break;
        case SYN_MACRO_IFNDEF:
#if defined(syntaxanalyzer)
    std::cout << "PreProcessorConditionInstruction->#ifndef ConstExpress" << std::endl;
#endif
            Match(SYN_MACRO_IFNDEF);
            ConstExpress();
            break;
        case SYN_MACRO_ENDIF:
            Match(SYN_MACRO_ENDIF);
            InPreProcess = false;
            return;
    }
    while(CurrentTokenType != SYN_MACRO_ELIF && CurrentTokenType != SYN_MACRO_ELSE && CurrentTokenType != SYN_MACRO_ENDIF){
        Statement();
    }
    while(CurrentTokenType == SYN_MACRO_ELIF){
#if defined(syntaxanalyzer)
        std::cout << "PreProcessorConditionInstruction->#elif ConstExpress" << std::endl; 
#endif
        Match(SYN_MACRO_ELIF);
        Express();
        while(CurrentTokenType != SYN_MACRO_ENDIF && CurrentTokenType != SYN_MACRO_ELSE)
            Statement();
    }
    if(CurrentTokenType == SYN_MACRO_ELSE){
#if defined(syntaxanalyzer)
        std::cout << "PreProcessorConditionInstruction->#else" << std::endl; 
#endif
        Match(SYN_MACRO_ELSE);
        while(CurrentTokenType != SYN_MACRO_ENDIF)
            Statement();
    }

    Match(SYN_MACRO_ENDIF);
    InPreProcess = false;
    return;
}

void SyntaxAnalyzer::LabelList(void){
    ;
}

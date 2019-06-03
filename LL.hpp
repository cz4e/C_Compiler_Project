#ifndef _SYNTAXANALYZER_H
#define _SYNTAXANALYZER_H
#endif

#include "TokenAnalyzer.hpp"
#include "BuildObjectCode.hpp"
#define AMD64_SIZE      16
#define process_id_or_function_statement    do{\
                                                int type = CurrentTokenType;\
                                                while(isType(CurrentTokenType))\
                                                    Type();\
                                                if(type == SYN_STRUCT || type == SYN_UNION){\
                                                    if(type == SYN_STRUCT){\
                                                        struct_or_union = 1;\
                                                    }\
                                                    else{\
                                                        struct_or_union = 2;\
                                                    }\
                                                    StructOrUnion();\
                                                    break;\
                                                }\
                                                else if(type == SYN_ENUM){\
                                                    if(CurrentTokenType == SYN_BRACE_L){\
                                                        Match(SYN_BRACE_L);\
                                                        EnumList();\
                                                        Match(SYN_BRACE_R);\
                                                        if(CurrentTokenType == SYN_KEYWORD){\
                                                            struct_name = getTokenString();\
                                                            Match(SYN_KEYWORD);\
                                                            BuildSymbolTable();\
                                                            ResetAlias();\
                                                        }\
                                                        Match(SYN_SEMIC);\
                                                    }\
                                                }\
                                                if(CurrentTokenType == SYN_KEYWORD){\
                                                    StatementID();\
                                                }\
                                                else if(CurrentTokenType == SYN_FUNCTION){\
                                                    if(store_type == STATIC){\
                                                        func_info.store_type = static_mask;\
                                                    }\
                                                    func_info.limit_type = limit_type;\
                                                    func_info.return_type = statement_type;\
                                                    statement_type = 0;\
                                                    StatementFunction();\
                                                    FuncInfo.push_back(func_info);\
                                                    ResetFuncDefine();\
                                                    return;\
                                                }\
                                            }while(0);

#define Error(Notice,ErrorCode) do{\
                                    std::cout << Notice << std::endl;\
                                    exit(ErrorCode);\
                                }while(0);

#define CalculateBytes(_type,isoffset)   do{\
                                            long this_scope_bytes = 0;\
                                            if(isoffset){\
                                                if(value_offset.find(iter_begin.value_name) != value_offset.end()){\
                                                    ;\
                                                }\
                                                else{\
                                                    value_offset.insert(std::pair<std::string,int>(iter_begin.value_name,TotalBytes));\
                                                }\
                                            }\
                                            if(iter_begin.value_type & pointer_mask){\
                                                if(iter_begin.value_type & array_mask){\
                                                    long Count = 1;\
                                                    for(auto dims_ : iter_begin.value.arrayinfo.dims){\
                                                            Count *= dims_;\
                                                    }\
                                                    if(!isoffset){\
                                                        TotalBytes += sizeof(_type *) * Count;\
                                                    }\
                                                    else\
                                                        this_scope_bytes += sizeof(_type *) * Count;\
                                                }\
                                                else {\
                                                    if(!isoffset){\
                                                        TotalBytes += sizeof(_type*);\
                                                    }\
                                                    else{\
                                                        this_scope_bytes += sizeof(_type*);\
                                                    }\
                                                }\
                                            }\
                                            else if(iter_begin.value_type & array_mask){\
                                                long Count = 1;\
                                                for(auto dims_ : iter_begin.value.arrayinfo.dims){\
                                                        Count *= dims_;\
                                                }\
                                                if(!isoffset){\
                                                    TotalBytes += sizeof(_type) * Count;\
                                                }\
                                                else\
                                                    this_scope_bytes += sizeof(_type) * Count;\
                                            }\
                                            else{\
                                                if(!isoffset){\
                                                    TotalBytes += sizeof(_type);\
                                                }\
                                                else\
                                                    this_scope_bytes += sizeof(_type);\
                                            }\
                                            if(isoffset){\
                                                TotalBytes -= this_scope_bytes;\
                                            }\
                                }while(0);

#define CalculatAllBytes(_name,isoffset)      do{\
                                                for(auto iter_begin:_name[func_info.function_name].value_info){\
                                                    if(     iter_begin.value_type & char_mask){\
                                                        CalculateBytes(char,isoffset)\
                                                    }\
                                                    else if(iter_begin.value_type & short_mask){\
                                                        CalculateBytes(short,isoffset)\
                                                    }\
                                                    else if(iter_begin.value_type & int_mask){\
                                                        CalculateBytes(int,isoffset)\
                                                    }\
                                                    else if(iter_begin.value_type & long_mask){\
                                                        CalculateBytes(long,isoffset)\
                                                    }\
                                                    else if(iter_begin.value_type & float_mask){\
                                                        CalculateBytes(float,isoffset)\
                                                    }\
                                                    else if(iter_begin.value_type & double_mask){\
                                                        CalculateBytes(double,isoffset)\
                                                    }\
                                                }\
                                            }while(0);

static std::string WhichXmmFree(void){
    std::string xmm = "xmm";
    for(int index = 0;index <=7 ;index++){
        if(!RegisterBitMap[xmm + std::to_string(index)]){
           // RegisterBitMap[xmm + std::to_string(index)] = true;
            return "%" + xmm + std::to_string(index);
        }
    }
    return "";
}







std::string alias_name;
int struct_or_union;
static void ResetGlobalvalue(void){

    store_type = 0;
    limit_type = 0;
    statement_type = 0;
    struct_name = "";
    id_name = "";
    if(!FunctionRegion){
        function_name = "";
    }
    address_value = "";
    id_primary.arrayinfo.Dimension = 0;
    id_primary.arrayinfo.dims.erase(id_primary.arrayinfo.dims.cbegin(),id_primary.arrayinfo.dims.cend());
    id_primary.StringValue = "";
    id_primary.number.realNumber.floatNumber.DoubleNumber = 0.0;
    id_primary.number.realNumber.floatNumber.FloatNumber = 0.0;
    id_primary.number.realNumber.intgerNumber.LongNumber = 0;
    id_primary.value_type = 0;
    id_primary.value_address = "";
    struct_info.erase(struct_info.cbegin(),struct_info.cend());
    struct_body.erase(struct_body.cbegin(),struct_body.cend());

    valueinfo.isSetValue = false;
    valueinfo.value.arrayinfo.Dimension = 0;
    valueinfo.value.arrayinfo.dims.erase(valueinfo.value.arrayinfo.dims.cbegin(),valueinfo.value.arrayinfo.dims.cend());
    valueinfo.value.StringValue = "";
    valueinfo.value.number.realNumber.floatNumber.DoubleNumber = 0;
    valueinfo.value.number.realNumber.intgerNumber.LongNumber = 0;
    valueinfo.block_value.erase(valueinfo.block_value.cbegin(),valueinfo.block_value.cend());
    valueinfo.struct_body.erase(valueinfo.struct_body.cbegin(),valueinfo.struct_body.cend());
    valueinfo.value_type = 0;

    local_value.function_name = "";
    local_value.value_info.erase(local_value.value_info.cbegin(),local_value.value_info.cend());
    anonymous_domain_value.value_info.erase(anonymous_domain_value.value_info.cbegin(),anonymous_domain_value.value_info.cend());
}

static void ResetAlias(void){
    if(!BuildCode){
        alias_name = "";
        ResetGlobalvalue();
    }
    return;
}

static void ResetFuncDefine(void){
    if(!FunctionRegion){
        func_info.function_name = "";
        func_info.args_type.erase(func_info.args_type.cbegin(),func_info.args_type.cend());
        func_info.return_type = 0;
    }
}

static void getOffset(std::string & offset_str,std::string value_name){
    for(auto iter:Anonymous_domain[func_info.function_name].value_info){
        if(iter.value_name == value_name){
            offset_str =   "-" + std::to_string(value_offset[value_name]) + "(%rbp)";
            return;
        }
    }
    for(auto iter:localvalue[func_info.function_name].value_info){
        if(iter.value_name == value_name){
            offset_str =   "-" + std::to_string(value_offset[value_name]) + "(%rbp)";
            return;
        }
    }
    for(auto iter:GlobalValue){
        if(iter.value_name == value_name){
            offset_str = value_name + "(%rip)";
            return;
        }
    }

}

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
    struct Value Primary(int tokenvalue);                   // 初始值
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
    struct Value Express(void);                             // 表达式
    void Express1(void);                            // 表达式
    struct Value AssignmentExpress(void);                   // 赋值表达式
    int AssignmentOperator(void);                  // 赋值擦作符
    struct Value ConditionExpress(void);                    // 
    struct Value LogicOrExpress(void);
    void LogicOrExpress1(void);
    struct Value LogicAndExpress(void);
    void LogicAndExpress1(void);
    struct Value BitOrExpress(void);
    void BitOrExpress1(void);
    struct Value BitXorExpress(void);
    void BitXorExpress1(void);
    struct Value BitAndExpress(void);
    void BitAndExpress1(void);
    struct Value EqualClassExpress(void);
    void EqualClassExpress1(void);
    struct Value RelationExpress(void);
    void RelationExpress1(void);
    struct Value ShiftExpress(void);
    void ShiftExpress1(void);
    struct Value AddClassExpress(void);
    void AddClassExpress1(void);
    struct Value MulClassExpress(void);
    void MulClassExpress1(void);
    struct Value ForceTranExpress(void);
    struct Value UnaryExpress(void);
    struct Value PostfixExpress(void);
    void PostfixExpress1(void);
    struct Value PrimaryExpress(void);
    void ArgumentExpress(void);
    void ArgumentExpress1(void);
    void ControlInstruction(void);
    void PreProcessorConditionInstruction(void);
    void LabelList(void);
    bool isControlInstruction(int tokenvalue);
    void Constant(void);
    void RealArgument(void);
    void Args(void);
    void ArrayArgus(void);
    void StatementFunction(void);
    void StatementID(void);
    void StructOrUnion(void);
    void EnumList(void);
    void BuildSymbolTable(void);
    inline bool isEOF(void);                        // 判断函数
    void Match(int type);                           // 获取函数
    std::string getTokenString(void);               // 获取token的字符传
    inline int getTokenCoding(void);                // 获取token的编码
    bool isType(int tokenvalue);                    // 是否是type
    void BackAToken(void);                          // 后退一个Token
    void setFileName(const std::string filename);
    void ReOpenFile(const std::string filename);
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

void SyntaxAnalyzer::ReOpenFile(const std::string filename){
    tokenAnalyzer.CloseFile();
    setFileName(filename);
}

void SyntaxAnalyzer::setFileName(const std::string filename){
    tokenAnalyzer.SetFileName(filename);
    if(tokenAnalyzer.isEOF()){
        std::cout << "Not Such file or directory!" << std::endl;
        exit(1);
    }
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
    valueinfo.isSetValue = false;
    while(!isEOF()){
        Statement();
    }
    return;
}

void SyntaxAnalyzer::StructOrUnion(void){

    if(CurrentTokenType == SYN_KEYWORD){
        struct_name = getTokenString();
        Match(SYN_KEYWORD);
    }
    if(CurrentTokenType == SYN_BRACE_L){
        Match(SYN_BRACE_L);
        if(struct_or_union == 1)
            StructList();
        else
            UnionList();
        Match(SYN_BRACE_R);
    }

    if(CurrentTokenType == SYN_KEYWORD){
       id_name = getTokenString();
        Match(SYN_KEYWORD);
    }
    if(CurrentTokenType == SYN_SET){
        Match(SYN_SET);
        Primary(CurrentTokenType);
    }
    BuildSymbolTable();
    ResetAlias();
    return;
}

static std::string WhichRegisterFree(void){
    for(auto iter:GeneralRigisterMap){
        if(!iter.second && iter.first[0] != 'x'){
            return "%" + iter.first ;
        }
    }
    return "";
}

static void ClearBit(long & bitmap){
    if(bitmap & char_mask){
        bitmap &= ~short_mask;
        bitmap &= ~int_mask;
        bitmap &= ~long_mask;
        bitmap &= ~float_mask;
        bitmap &= ~double_mask;
    }
    else if(bitmap & short_mask){
        bitmap &= ~char_mask;
        bitmap &= ~int_mask;
        bitmap &= ~long_mask;
        bitmap &= ~float_mask;
        bitmap &= ~double_mask;
    }
    else if(bitmap & int_mask){
        bitmap &= ~char_mask;
        bitmap &= ~short_mask;
        bitmap &= ~long_mask;
        bitmap &= ~float_mask;
        bitmap &= ~double_mask;
    }
    else if(bitmap & long_mask){
        bitmap &= ~char_mask;
        bitmap &= ~short_mask;
        bitmap &= ~int_mask;
        bitmap &= ~float_mask;
        bitmap &= ~double_mask;
    }
    else if(bitmap & float_mask){
        bitmap &= ~char_mask;
        bitmap &= ~short_mask;
        bitmap &= ~int_mask;
        bitmap &= ~long_mask;
        bitmap &= ~double_mask;
    }
    else if(bitmap & double_mask){
        bitmap &= ~char_mask;
        bitmap &= ~short_mask;
        bitmap &= ~int_mask;
        bitmap &= ~long_mask;
        bitmap &= ~float_mask;
    }
}
void SyntaxAnalyzer::StatementID(void){

    id_name = getTokenString();
    Match(SYN_KEYWORD);
    if(CurrentTokenType == SYN_SET){
#if defined(syntaxanalyzer)
    std::cout << "StatementID-> id[=Primary] IdList;" << std::endl;
#endif
        Match(SYN_SET);
        struct Value value_ = Primary(CurrentTokenType);
        IdList();
        Match(SYN_SEMIC);
        
        if(RunTimeTrans && FunctionRegion ){
            long offset = value_offset[id_name];
            if(value_.value_type == SYN_KEYWORD){
                std::string register_ = WhichRegisterFree();
                std::string XmmRegister = WhichXmmFree() ;
                std::string dest_offset_str,src_offset_str;
                getOffset(src_offset_str,value_.value_name);
                getOffset(dest_offset_str,id_name);
                if(statement_type & short_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovw\t" << src_offset_str << "," << register_ << std::endl;
                        assemble_file << "\tmovw\t" << register_ << "," << dest_offset_str << std::endl;
                    }   
                }
                else if(statement_type & int_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovl\t" << src_offset_str << "," << register_ << std::endl;
                        assemble_file << "\tmovl\t" << register_ << "," << dest_offset_str << std::endl;
                    }   
                }
                else if(statement_type & long_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovl\t" << src_offset_str << "," << register_ << std::endl;
                        assemble_file << "\tmovl\t" << register_ << "," << dest_offset_str << std::endl;
                    }   
                }
                else if(statement_type & long_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovq\t" << src_offset_str << "," << register_ << std::endl;
                        assemble_file << "\tmovq\t" << register_ << "," << dest_offset_str << std::endl;
                    }   
                }
                else if(statement_type & float_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovss\t" << src_offset_str << "," << XmmRegister << std::endl;
                        assemble_file << "\tmovss\t" <<  XmmRegister << "," << dest_offset_str << std::endl;
                    }   
                }
                else if(statement_type & double_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){;}
                    else{
                        assemble_file << "\tmovsd\t" << src_offset_str << "," << XmmRegister << std::endl;
                        assemble_file << "\tmovsd\t" <<  XmmRegister << "," << dest_offset_str << std::endl;
                    }   
                }
            }
            else if(value_.value_type & char_mask){
                if(statement_type & pointer_mask){
                    assemble_file << "\tleaq\t" << read_only_offset[value_.const_char] << "(%rip),%rax" << std::endl;
                    assemble_file << "\tmovq\t" << "%rax" << ",-" << offset << "(%rbp)" << std::endl;
                }
                else if(statement_type & array_mask){
                    ;
                }
                else{
                    assemble_file << "\tmovb\t" << "$" << (long)(value_.const_char[1]) << ",-" << offset << "(%rbp)" << std::endl;
                }
            }
            else if(value_.value_type & short_mask){
                if(statement_type & array_mask){
                    ;
                }
                else if(statement_type & pointer_mask){
                    std::string register_ = WhichRegisterFree();
                    int _offset = value_offset[value_.value_address];
                    if(_offset){
                        assemble_file << "\tleaq\t" << "-" << _offset << "(%rbp)" << "," << register_ << std::endl;
                        assemble_file << "\tmovw\t" << register_ << ",-" << offset << "(%rbp)" << std::endl;
                    }
                }
                else
                    assemble_file << "\tmovw\t$" << value_.value_integer << ",-" << offset << "(%rbp)" << std::endl;
            }
            else if(value_.value_type & int_mask){
                if(statement_type & array_mask){
                    assemble_file << "\tmovl\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                    array_offset += sizeof(int);
                }
                else if(statement_type & pointer_mask){
                    std::string register_ = WhichRegisterFree();
                    int _offset = value_offset[value_.value_address];
                    if(_offset){
                        assemble_file << "\tleaq\t" << "-" << _offset << "(%rbp)" << "," << register_ << std::endl;
                        assemble_file << "\tmovl\t" << register_ << ",-" << offset << "(%rbp)" << std::endl;
                    }
                }
                else
                    assemble_file << "\tmovl\t$" << value_.value_integer << ",-" << offset << "(%rbp)" << std::endl;
            }
            else if(value_.value_type & long_mask){
                if(statement_type & array_mask){
                    assemble_file << "\tmovq\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                    array_offset += sizeof(long);
                }
                else if(statement_type & pointer_mask){
                    std::string register_ = WhichRegisterFree();
                    int _offset = value_offset[value_.value_address];
                    if(_offset){
                        assemble_file << "\tleaq\t" << "-" << _offset << "(%rbp)" << "," << register_ << std::endl;
                        assemble_file << "\tmovq\t" << register_ << ",-" << offset << "(%rbp)" << std::endl;
                    }
                }
                else
                    assemble_file << "\tmovq\t$" << value_.value_integer << ",-" << offset << "(%rbp)" << std::endl; 
            }
            else if(value_.value_type & float_mask){
                if(statement_type & array_mask){;}
                else if(statement_type & pointer_mask){;}
                else{
                    std::string label = func_double_label[func_info.function_name][value_.value_float].label;
                    label = label+ "(%rip)";
                    std::string XmmRegister = WhichXmmFree();
                    assemble_file << "\tmovss\t" << label << "," << XmmRegister << std::endl;
                    assemble_file << "\tmovss\t" << XmmRegister << ",-" << offset << "(%rbp)" << std::endl;
                }
            }
            else if(value_.value_type & double_mask){
             /*   if(statement_type & array_mask){;}
                else if(statement_type & pointer_mask){;}
                else{*/
                    std::string label = func_double_label[func_info.function_name][value_.value_float].label;
                    label = label+ "(%rip)";
                    std::string XmmRegister = WhichXmmFree();
                    assemble_file << "\tmovsd\t" << label << "," << XmmRegister << std::endl;
                    assemble_file << "\tmovsd\t" << XmmRegister << ",-" << offset << "(%rbp)" << std::endl;
               // }
            }
        }
    }
    else if(CurrentTokenType == SYN_COLON){
#if defined(syntaxanalyzer)
    std::cout << "StatementID-> id[:ConstExpress] IdList;" << std::endl;
#endif
        Match(SYN_COLON);
        ConstExpress();
        IdList();
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_SQU_BRACE_L){
#if defined(syntaxanalyzer)
    std::cout << "StatementArray-> id[ ConstExpress ] Brace[=Primary];" << std::endl;
#endif

        TotalElement = 1;
        id_primary.arrayinfo.Dimension = 1;
        Match(SYN_SQU_BRACE_L);
        id_primary.arrayinfo.dims.push_back(ConstExpress());
        Match(SYN_SQU_BRACE_R);
        Brace();
        if(RunTimeTrans)
            for(auto iter: id_primary.arrayinfo.dims){
                TotalElement *= iter;
            }
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
            if(!StructDefineList){
                BuildSymbolTable();
                ResetAlias();
            }
        }
        FirstBlock = true;
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
    func_info.function_name = getTokenString();
    Match(SYN_FUNCTION);
    Match(SYN_PAREN_L);
    ArgumentList();
    Match(SYN_PAREN_R);
    if(CurrentTokenType == SYN_SEMIC){
        Match(SYN_SEMIC);
    }
    else if(CurrentTokenType == SYN_BRACE_L){
        
        if(RunTimeTrans){
            assemble_file << "\t.text" << std::endl;
            if(!(func_info.store_type & static_mask)){
                assemble_file << "\t.globl\t" << func_info.function_name << std::endl;
            }
            assemble_file << "\t.type\t" << func_info.function_name << ",@function" << std::endl;
            assemble_file << func_info.function_name <<":"    << std::endl;
            assemble_file << "\tpushq   %rbp" << std::endl;
            assemble_file << "\tmovq    %rsp,%rbp" << std::endl;
        }
        FunctionRegion = true;
        GlobalScopeValue = false;
        long TotalBytes = AMD64_SIZE;
        CalculatAllBytes(localvalue,false)
        CalculatAllBytes(Anonymous_domain,false)
        
        if(RunTimeTrans){
            
            while(TotalBytes % 8 || TotalBytes % 16) TotalBytes++;
            assemble_file << "\tsubq    $" <<   TotalBytes  <<  ",%rsp" << std::endl;
            assemble_file << "\tmovq    \%fs:40,%rax" << std::endl;
            assemble_file << "\tmovq    %rax,-8(%rbp)" << std::endl;
            assemble_file << "\txorl    \%eax,\%eax"  << std::endl;
        }

        CalculatAllBytes(localvalue,true)
        CalculatAllBytes(Anonymous_domain,true)
        //InitialLocalValue();
        CompoundSentence();
        FunctionRegion = false;
        GlobalScopeValue = false;
        

        /* Function Block */
        if(RunTimeTrans){
            assemble_file << "\tmovq    -8(%rbp),%rdx" << std::endl;
            assemble_file << "\txorq    \%fs:40,%rdx" << std::endl;
            assemble_file << "\tje      endofproc_" << func_info.function_name  << std::endl;
            assemble_file << "\tcall    __stack_chk_fail@PLT" << std::endl;
            assemble_file << "endofproc_" << func_info.function_name << ": " << std::endl;
            assemble_file << "\tleave" << std::endl;
           /* else{
                assemble_file << "\tpopq    %rbp" << std::endl;
            }*/
            assemble_file << "\tret" << std::endl;
            assemble_file << "\t.size\t" << func_info.function_name << ",.-" << func_info.function_name << std::endl;
            assemble_file << "\t.section\t.rodata" << std::endl;
            for(auto iter:func_double_label[func_info.function_name]){
                assemble_file << iter.second.label<< ":" << std::endl;
                if(iter.second.type & double_mask)
                    assemble_file << "\t.double\t" << iter.first << std::endl;
                else{
                    assemble_file << "\t.float\t" << iter.first << std::endl;
                }
            }
        }
    }
    ResetFuncDefine();
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
    std::cout << "Statement-> StoreTypeSymbol [ LimitTypeSymbol ] Type  process_id_or_function_statement;" << token.tokenValue.StringValue << std::endl;
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
        if(CurrentTokenType != SYN_SEMIC){
            Express();
            Match(SYN_SEMIC);
        }
        else{
            if(RunTimeTrans){
                assemble_file << "\tnop" << std::endl;
            }
            Match(SYN_SEMIC);
        }
    }
    else if(CurrentTokenType == SYN_BRACE_L){
#if defined(syntaxanalyzer)
    std::cout << "Statement->CompoundSentence" << std::endl;
#endif
        bool StoreStatus;
        bool StoreGlobalStatus ;
        if(FunctionRegion){
            if(InAnonymousDomain == 0){
                InAnonymousDomain++;
                domain_number++;
                StoreStatus = FunctionRegion;
                StoreGlobalStatus = GlobalScopeValue;
            }
            GlobalScopeValue = false;
            FunctionRegion = false;
            CompoundSentence();
            if(InAnonymousDomain != 0){
                InAnonymousDomain--;
                FunctionRegion = StoreStatus;
                GlobalScopeValue = StoreGlobalStatus;
            }
        }
        else{
            std::cout << "Line: " << LineNumber  << "  "<< std::flush;
            Error("Expect a ) before {",1)
        }
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
        struct Value value_ = Express();
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
                //Pointer();
                break;
        }
        Match(code);
    }
    else if(CurrentTokenType == SYN_MUL){
        Pointer();
    }
    else if(CurrentTokenType == SYN_KEYWORD){
        if(!(statement_type & (struct_mask | union_mask)) && !StructDefineList){
            alias_name = getTokenString();
            if(getAlias(alias_name) != ValueAlais.cend()){
                statement_type |= seldefine_mask;
                Match(SYN_KEYWORD);
            }
        }
    }
    return;
}

static long NextDims(void){
    static long Index = 0;
    auto dims = id_primary.arrayinfo.dims[Index];
    std::cout << "nextdism" << " :" << dims << std::endl;
    Index++;
    return dims;
}


struct Value SyntaxAnalyzer::Primary(int tokenvalue){
    bool InString = false;
    valueinfo.isSetValue = true;
    struct Value value_;

    switch(tokenvalue){
        case SYN_NUMBER_DOUBLE:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> double_num "<< token.tokenValue.StringValue << std::endl;
#endif
           
            id_primary.number.realNumber.floatNumber.DoubleNumber = token.tokenValue.number.realNumber.floatNumber.DoubleNumber;
            if(!RunTimeTrans){
                if(FunctionRegion){
                    func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].label = "floatnumber_" + std::to_string(double_label_counter);
                    func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].type = statement_type;
                    double_label_counter++;
                }
            }
            value_.value_float = token.tokenValue.number.realNumber.floatNumber.DoubleNumber;
            value_.value_name = "";

            
            if(RunTimeTrans && FunctionRegion){
                if(statement_type & double_mask)
                    value_.value_type = double_mask;
                else if(statement_type & float_mask)
                    value_.value_type = float_mask;
                long offset = value_offset[id_name];
                if(statement_type & float_mask){
                    if(statement_type & pointer_mask){
                        if(statement_type & array_mask){
                                ;
                        }
                        else {
                            ;
                        }
                    }
                    else if(statement_type & array_mask){;}
                    else {
                            assemble_file << "\tmovss\t" << func_double_label[func_info.function_name][value_.value_float].label << "(%rip)" << ",\%xmm0" << std::endl;
                            assemble_file << "\tmovss\t" << "\%xmm0" << ",-" << offset << "(%rbp)" << std::endl;
                    }
                }
                else if(statement_type & double_mask){
                    if(statement_type & array_mask){;
                            if(statement_type & pointer_mask){;}
                            else{
                                assemble_file << "\tmovsd\t" << func_double_label[func_info.function_name][value_.value_float].label << "(%rip)" << ",\%xmm0" << std::endl;
                                assemble_file << "\tmovsd\t" << "\%xmm0" << ",-" << offset << "(%rbp)" << std::endl;
                            }
                    }
                /*    else {
                            std::cout << func_double_label[func_info.function_name][value_.value_float].label << std::endl;
                            assemble_file << "\tmovsd\t" << func_double_label[func_info.function_name][value_.value_float].label << "(%rip)" << ",\%xmm0" << std::endl;
                            assemble_file << "\tmovsd\t" << "\%xmm0" << ",-" << offset << "(%rbp)" << std::endl;
                    }*/
                }
            }
            Match(SYN_NUMBER_DOUBLE);
            return value_;
        case SYN_NUMBER_LONG:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> long_num " << token.tokenValue.StringValue << " " << token.TokenType << std::endl;
#endif
           // statement_type |= long_mask;
            id_primary.number.realNumber.intgerNumber.LongNumber = token.tokenValue.number.realNumber.intgerNumber.LongNumber;
            if(RunTimeTrans){
                value_.value_integer = token.tokenValue.number.realNumber.intgerNumber.LongNumber;
                value_.value_name = "";
                value_.value_type = statement_type;
                if(RunTimeTrans){
                    long offset = value_offset[id_name];
                    if(statement_type & short_mask){
                        if(statement_type & array_mask){
                            if(statement_type & pointer_mask){
                                assemble_file << "\tmovq\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(long);
                            }
                            else {
                                assemble_file << "\tmovw\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(short);
                            }
                        }
                    }
                    else if(statement_type & int_mask){
                        if(statement_type & array_mask){
                            if(statement_type & pointer_mask){
                                assemble_file << "\tmovq\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(long);
                            }
                            else {
                                assemble_file << "\tmovl\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(int);
                            }
                        }
                    }
                    else if(statement_type & long_mask){
                        if(statement_type & array_mask){
                            if(statement_type & pointer_mask){
                                assemble_file << "\tmovq\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(long);
                            }
                            else {
                                assemble_file << "\tmovq\t" << "$" << value_.value_integer << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(long);
                            }
                        }
                    }
                }
            }
            Match(SYN_NUMBER_LONG);
            return value_;
        case SYN_STRING:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> string"<< token.tokenValue.StringValue  << std::endl;
#endif
            statement_type |= string_mask;
            statement_type |= char_mask;
            for(auto _char:getTokenString()){
                if(_char == '\''){
                    if(InString){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else if(_char == '\"'){
                    InString = true;
                }
            }
            if(InString){
                ReadOnlyData["string"].push_back(getTokenString());
            }
            id_primary.StringValue = token.tokenValue.StringValue;
            if(RunTimeTrans){
                value_.value_type = statement_type;
                value_.value_name = "";
                value_.const_char = token.tokenValue.StringValue;
            }
            if(RunTimeTrans){
                if(statement_type & char_mask){
                    long offset = value_offset[id_name];
                    if(statement_type & array_mask){
                        if(statement_type & pointer_mask){
                            long offset_long = value_offset[id_name];
                            if(statement_type & array_mask){
                                assemble_file << "\tleaq\t" << read_only_offset[id_primary.StringValue]  << "(%rip)" 
                                                << ",%rax" << std::endl;
                                assemble_file << "\tmovq\t" << "%rax," << "-" << offset_long  -array_offset<< "(%rbp)" << std::endl; 
                                array_offset += sizeof(long);
                            }   
                        }
                        else{
                            assemble_file << "\tmovb\t" << "$" << (long) (value_.const_char[1]) << "," << offset - array_offset << "(%rbp)" << std::endl;
                            array_offset += sizeof(char);
                        }
                    }

                }
            }
            Match(SYN_STRING);
            return value_;
        case SYN_KEYWORD:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> id "<< token.tokenValue.StringValue << std::endl;
#endif
            if(!FunctionRegion)
                CopyToNewId(getTokenString(),id_primary);
            if(RunTimeTrans){
                value_.value_name = getTokenString();
                value_.value_type = SYN_KEYWORD;
                long offset_long = value_offset[id_name];
                if(statement_type & char_mask) {
                    if(statement_type & pointer_mask){;}
                    else{
                        assemble_file << "\tmovb\t" << "-" << value_offset[value_.value_name] << "(%rbp)," << "\%al" << std::endl;
                        assemble_file << "\tmovb\t" << "\%al" << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(char);
                    }
                }
                else if(statement_type & short_mask){
                    if(statement_type & pointer_mask){;}
                    else{
                        assemble_file << "\tmovw\t" << "-" << value_offset[value_.value_name] << "(%rbp)," << "\%ax" << std::endl;
                        assemble_file << "\tmovw\t" << "\%ax" << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(short);
                    }        
                }
                else if(statement_type & int_mask){
                    if(statement_type & pointer_mask){;}
                    else{
                        assemble_file << "\tmovl\t" << "-" << value_offset[value_.value_name] << "(%rbp)," << "\%eax" << std::endl;
                        assemble_file << "\tmovl\t" << "\%eax" << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(int);
                    }        
                }
                else if(statement_type & long_mask){
                    if(statement_type & pointer_mask){;}
                    else{
                        std::string temp_register = WhichRegisterFree();
                        assemble_file << "\tmovq\t" << "-" << value_offset[value_.value_name] << "(%rbp)," << temp_register << std::endl;
                        assemble_file << "\tmovq\t" << temp_register << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(long);
                    }        
                }
                else if(statement_type & float_mask){
                    if(statement_type & pointer_mask){;}
                    else{
                        std::string temp_register = WhichXmmFree();
                        std::string offset_str;
                        getOffset(offset_str,getTokenString());
                        assemble_file << "\tmovss\t" << offset_str << "," << temp_register << std::endl;
                        assemble_file << "\tmovss\t" << temp_register << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(float);
                    }        
                }
                else if(statement_type & double_mask){
                    if(statement_type & pointer_mask){;}
                    else{
                        std::string temp_register = WhichXmmFree();
                        std::string offset_str;
                        getOffset(offset_str,getTokenString());
                        assemble_file << "\tmovsd\t" << offset_str << "," << temp_register << std::endl;
                        assemble_file << "\tmovsd\t" << temp_register << ",-" << offset_long - array_offset << "(%rbp)" << std::endl;
                        array_offset += sizeof(double);
                    }        
                }
            }

            Match(SYN_KEYWORD);
            return value_;
        case SYN_BRACE_L:
#if defined(syntaxanalyzer)
    std::cout << "Primary-> {PrimaryList [,]}" << std::endl;
#endif
            Match(SYN_BRACE_L);
            if(RunTimeTrans && FirstBlock){
                FirstBlock = false;
                array_offset = 0;
                long offset = value_offset[id_name];
                if(TotalElement == 0){
                    ;
                }
                else{
                    if(statement_type & char_mask){    
                        if(statement_type & pointer_mask){
                            for(long index = TotalElement;index;index--){
                                assemble_file <<"\tmovq\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(char *);                               
                            }
                        }  
                        else{      
                            if(TotalElement / 8){
                                long modvalue_long = TotalElement % 8;
                                if(modvalue_long){
                                    for(long index = modvalue_long;index; index--){
                                        assemble_file <<"\tmovb\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                        array_offset += sizeof(char);
                                    }
                                }
                                assemble_file << "\tleaq\t" << "-" << offset - array_offset << "(%rbp)" << ",%rdx" << std::endl;
                                assemble_file << "\tmovl\t$" << TotalElement / 8 << ",\%ecx" << std::endl;
                            }
                            else{
                                for(long index = TotalElement / 8;index; index--){
                                    assemble_file <<"\tmovb\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                    array_offset += sizeof(char);
                                }
                            }
                        }
                    }
                    else if(statement_type & short_mask){
                        if(TotalElement / 4){
                            long modvalue_long = TotalElement % 4;
                            if(modvalue_long){
                                for(long index = modvalue_long;index; index--){
                                    assemble_file <<"\tmovb\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                    array_offset += sizeof(short);
                                }
                            }
                            assemble_file << "\tleaq\t" << "-" << offset - array_offset << "(%rbp)" << ",%rdx" << std::endl;
                            assemble_file << "\tmovw\t$" << TotalElement / 4 << ",\%ecx" << std::endl;
                        }
                        else{
                            for(long index = TotalElement / 4;index; index--){
                                assemble_file <<"\tmovw\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(short);
                            }
                        }
                    }
                    else if(statement_type & int_mask){
                        if(TotalElement / 2){
                            long modvalue_long = TotalElement % 2;
                            if(modvalue_long){
                                for(long index = modvalue_long;index; index--){
                                    assemble_file <<"\tmovl\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                    array_offset += sizeof(int);
                                }
                            }
                            assemble_file << "\tleaq\t" << "-" << offset - array_offset << "(%rbp)" << ",%rdx" << std::endl;
                            assemble_file << "\tmovl\t$" << TotalElement / 2 << ",\%ecx" << std::endl;
                        }
                        else{
                            for(long index = TotalElement / 2;index; index--){
                                assemble_file <<"\tmovl\t" << "$0" << ",-" << offset - array_offset << "(%rbp)" << std::endl;
                                array_offset += sizeof(int);
                            }
                        }
                    }
                    else if(statement_type & long_mask)
                        assemble_file << "\tmovl\t$" << TotalElement << ",\%ecx" << std::endl;
                    if(!RegisterBitMap["eax"])
                        assemble_file << "\txorl\t\%eax,\%eax" << std::endl;
                    
                    if(!(statement_type &(float_mask | double_mask))){
                        assemble_file << "\tmovq\t%rdx,%rdi" << std::endl;
                        assemble_file << "\trep stosq" << std::endl;
                    }
                 //   array_offset = 0;
                }
            }
            PrimaryList();
            if(CurrentTokenType == SYN_COMMA){
                Match(SYN_COMMA);
            }
            Match(SYN_BRACE_R);
            return value_;
        case SYN_BIT_AND:
            Match(SYN_BIT_AND);
            address_value = getTokenString();
            value_.Type = 2;
            value_.value_address = address_value;
            Match(SYN_KEYWORD);
            if(RunTimeTrans){
                std::string src_offset_str;
                long dest_offset_long = value_offset[id_name];
                std::string register_ = WhichRegisterFree() ;
                getOffset(src_offset_str,value_.value_address);

                assemble_file << "\tleaq\t" << src_offset_str << "," << register_ << std::endl;
                assemble_file << "\tmovq\t" << register_ << ",-"  << dest_offset_long - array_offset << "(%rbp)" << std::endl;
                array_offset += sizeof(long);
            }
            return value_;
    }
    return value_;
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
    if(GlobalScopeValue){
        id_primary.value_type = statement_type;
        if(StructDefineList){
            struct_body.push_back(id_primary);
        }
        else{
            struct_info.push_back(id_primary);
        }
    }
    if(CurrentTokenType == SYN_COMMA){
#if defined(syntaxanalyzer)
    std::cout << "PList-> ,Primary PList" << std::endl;
#endif
        Match(SYN_COMMA);
        if(CurrentTokenType == SYN_BRACE_R){
            if(!StructDefineList){
                BuildSymbolTable();
                ResetAlias();
            }
            return;
        }
        Primary(CurrentTokenType);
        PList();
    }
    else{
#if defined(syntaxanalyzer)
    std::cout << "PList->" << std::endl;
#endif  
        BuildSymbolTable();
        ResetAlias();
    }
    return;
}


void SyntaxAnalyzer::BuildSymbolTable(void){
    if(!BuildCode){
        if((GlobalScopeValue || FunctionRegion || InAnonymousDomain) && store_type != TYPEDEF){
            if(statement_type & seldefine_mask){
                auto alias = getAlias(alias_name);
                if(alias != ValueAlais.cend()){
                    valueinfo.store_type = alias->store_type;
                    valueinfo.limit_type = alias->limit_type;
                    valueinfo.value_type = alias->value_type;
                    valueinfo.value.arrayinfo = alias->arrayinfo;
                    valueinfo.struct_name = alias->struct_name;
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
                    valueinfo.block_value.assign(struct_info.cbegin(),struct_info.cend());          
                }
                else if(statement_type & (struct_mask | enum_mask | union_mask)){
                    if(!StructDefineList){
                        valueinfo.struct_body.assign(struct_body.cbegin(),struct_body.cend());
                    }
                    else
                        valueinfo.block_value.assign(struct_info.cbegin(),struct_info.cend()); 
                    CopyValue(statement_type,id_primary,valueinfo)
                }
                else {
                    CopyValue(statement_type,id_primary,valueinfo)
                }
                valueinfo.struct_name = struct_name;
            }  
            valueinfo.value_name = id_name;
            valueinfo.value.value_address = address_value;

            if(GlobalScopeValue)
                GlobalValue.push_back(valueinfo);
            else if(FunctionRegion && !InAnonymousDomain)
            {
                if(localvalue.count(func_info.function_name)){
                    localvalue[func_info.function_name].value_info.push_back(valueinfo);
                }
                else{
                    local_value.function_name = func_info.function_name;
                    local_value.value_info.push_back(valueinfo);
                    localvalue.insert(std::pair<std::string,struct LocalValue>(func_info.function_name,local_value));
                }
            }
            else if(FunctionRegion && InAnonymousDomain){
                if(Anonymous_domain.count(func_info.function_name)){
                    Anonymous_domain[func_info.function_name].value_info.push_back(valueinfo);
                }
                else{
                    anonymous_domain_value.function_name = "";
                    anonymous_domain_value.value_info.push_back(valueinfo);
                    Anonymous_domain.insert(std::pair<std::string,struct LocalValue>(func_info.function_name,anonymous_domain_value));
                }
            }

        }
        else if(GlobalScopeValue && store_type == TYPEDEF){
            aliasname.limit_type = limit_type;
            aliasname.value_type = statement_type;
            aliasname.alias = id_name;
            aliasname.arrayinfo = id_primary.arrayinfo;
            aliasname.struct_name = struct_name;
            ValueAlais.push_back(aliasname);
        }
      //  if(!InIdList)
      // ResetAlias();
    }
    
    return ;
}

void SyntaxAnalyzer::IdList(void){
        
        if(StructDefineList){
            struct_body.push_back(id_primary);
        }
        else{
            InIdList = true;
            BuildSymbolTable();   
        }
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
        if(StructDefineList){
            BuildSymbolTable();
            ResetAlias();
        }
        InIdList = false;
        ResetAlias();
    }
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

    func_info.args_type.push_back(args_type);
    args_type.type =0;
    args_type.argument_name ="";
    ResetAlias();

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
        args_type.type = -1;
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
        id_name = getTokenString();
        Match(SYN_KEYWORD);
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            Primary(CurrentTokenType);
        }
        args_type.type = statement_type;
        args_type.argument_name = id_name;
    }
    else if(CurrentTokenType == SYN_NUMBER_LONG){
        Match(SYN_NUMBER_LONG);
    }
    else if(CurrentTokenType == SYN_NUMBER_DOUBLE){
        if(!RunTimeTrans){
            func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].label = "floatnumber_" + std::to_string(double_label_counter);
            func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].type = statement_type;
        }
        Match(SYN_NUMBER_DOUBLE);
    }
    else if(CurrentTokenType == SYN_STRING){
        std::string temp_str = getTokenString();
        if(temp_str[1] == '\''){
            ;
        }
        else {
            
            ReadOnlyData["string"].push_back(temp_str);
        }
        Match(SYN_STRING);
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
        if(CurrentTokenType != SYN_SET){
            BuildSymbolTable();
            ResetAlias();
        }

    }
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
            ReadOnlyData["double"].push_back(getTokenString());
            if(!RunTimeTrans)           
                if(FunctionRegion){
                    func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].label = "floatnumber_" + std::to_string(double_label_counter);
                    func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].type = statement_type;
                    double_label_counter++;
                }
            Match(SYN_NUMBER_DOUBLE);
            return 0;
        case SYN_STRING:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> string" << std::endl;
#endif
            std::cout << getTokenString() << std::endl;
            ReadOnlyData["string"].push_back(getTokenString());
            Match(SYN_STRING);
            return 0;
        case SYN_KEYWORD:
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> id" << std::endl;
#endif

            Match(SYN_KEYWORD);
            return 0;
        default:
            return 0;
            Error("Symbol Error!",1)
    }
    return 0;
}

void SyntaxAnalyzer::EnumList(void){
#if defined(syntaxanalyzer)
    std::cout << "EnumList-> id[=Primary] Enum" << std::endl;
#endif
    int enum_counter = 0;
    StructDefineList = true;
    id_primary.value_type |= long_mask;
    while(CurrentTokenType != SYN_BRACE_R){
        id_primary.StringValue = getTokenString();
        Match(SYN_KEYWORD);
        if(CurrentTokenType == SYN_SET){
            Match(SYN_SET);
            enum_counter = token.tokenValue.number.realNumber.intgerNumber.LongNumber;
            Match(SYN_NUMBER_LONG);
        }
        id_primary.number.realNumber.intgerNumber.LongNumber = enum_counter;
        if(StructDefineList){
            struct_body.push_back(id_primary);
        }
        if(CurrentTokenType != SYN_BRACE_R)
            Match(SYN_COMMA);
        enum_counter++;
    }
    StructDefineList = false;
}

void SyntaxAnalyzer::StructList(void){
#if defined(syntaxanalyzer)
    std::cout << "StructList-> Statement" << std::endl;
#endif
    StructDefineList = true;
    int type_copy = statement_type;
    while(CurrentTokenType != SYN_BRACE_R ){
        Statement();
    }
    statement_type = type_copy;
    StructDefineList = false;
    return;
}

void SyntaxAnalyzer::UnionList(void){
#if defined(syntaxanalyzer)
    std::cout << "id[=Primary] Union" << std::endl;
#endif
 /*   Match(SYN_KEYWORD);
    if(CurrentTokenType == SYN_SET){
        Match(SYN_SET);
        Primary(CurrentTokenType);
    }
    Union();*/
    StructDefineList = true;
    int type_copy = statement_type;
    while(CurrentTokenType != SYN_BRACE_R ){
        Statement();
    }
    statement_type = type_copy;
    StructDefineList = false;
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
struct Value SyntaxAnalyzer::Express(void){
#if defined(syntaxanalyzer)
    std::cout << "Express-> AssignmentExpress Express1" << std::endl;
#endif
    struct Value assign_value = AssignmentExpress();
    Express1();
    return assign_value;
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
        //case SYN_FUNCTION:
            return true;
        default:
            return false;       
    }
}

static bool isaRegister(std::string value_name){
    if(RegisterBitMap.count(value_name)){
        return true;
    }
    return false;
}

static bool  _isConstExpress(std::string value_name){
    for(auto iter:Anonymous_domain[func_info.function_name].value_info){
        if(iter.value_name == value_name)
            return false;
    }
    for(auto iter:localvalue[func_info.function_name].value_info){
        if(iter.value_name == value_name)
            return false;
    }
    for(auto iter_begin:GlobalValue){
        if(iter_begin.value_name == value_name){
                return false;
        }
    }
    return true;
}


static std::string address(std::string value_name){
    int boolvalue = 0;
    for(auto iter:Anonymous_domain[func_info.function_name].value_info)
        if(iter.value_name == value_name){
            boolvalue++;
            break;
        }
    
    for(auto iter:localvalue[func_info.function_name].value_info)
        if(iter.value_name == value_name){
            boolvalue++;
            break;
        }

    if(boolvalue){
        std::string offset = std::to_string(value_offset[value_name]);
        
        return "-" + offset + "(%rbp)";
    }
    else{
        std::string offset ;
        /*
            Process global value
        */
        return offset;
    }
}
bool isAssignement = true;
struct Value  SyntaxAnalyzer::AssignmentExpress(void){
    if(isUnaryExpress(CurrentTokenType) && isAssignement){
#if defined(syntaxanalyzer)
    std::cout << "AssignmentExpress-> UnaryExpress AssignmentOperator AssignmentExpress" << std::endl;
#endif
        struct Value LeftValue;
        struct Value RightValue;
        LeftValue = UnaryExpress();
        int OperatoerType = AssignmentOperator();
        isAssignement = false;
        RightValue = AssignmentExpress();
        if(RunTimeTrans){

                switch(OperatoerType){
                    case SYN_SET:
                    if(LeftValue.value_type & char_mask ){
                        if(_isConstExpress(RightValue.value_name)){
                            std::string AddressRef = address(LeftValue.value_name);
                            assemble_file << "\tmovb\t" << "$" << (long) RightValue.const_char.c_str()[1] << "," << AddressRef << std::endl;
                        }
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovb\t" <<  offset_str << ",\%al" << std::endl;
                            assemble_file << "\tmovb\t" << "\%al," << dest_offset_str << std::endl; 
                        }
                    }
                    else if(LeftValue.value_type & short_mask){
                        if(_isConstExpress(RightValue.value_name)){
                            std::string AddressRef = address(LeftValue.value_name);
                            assemble_file << "\tmovw\t$" << RightValue.value_integer << "," << AddressRef << std::endl;
                        }
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovw\t" <<  offset_str << ",\%ax" << std::endl;
                            assemble_file << "\tmovw\t" << "\%ax," << dest_offset_str << std::endl;    
                        }
                    }
                    else if(LeftValue.value_type & int_mask){
                        if(_isConstExpress(RightValue.value_name)){
                            std::string AddressRef = address(LeftValue.value_name);
                            assemble_file << "\tmovl\t$" << RightValue.value_integer << "," << AddressRef << std::endl;
                        }
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovl\t" <<  offset_str << ",\%eax" << std::endl;
                            assemble_file << "\tmovl\t" << "\%eax," << dest_offset_str << std::endl;    
                        }
                    }
                    else if(LeftValue.value_type & long_mask ){
                        if(isaRegister(RightValue.value_name)){
                            ;
                        }
                        else if(_isConstExpress(RightValue.value_name)){
                            std::string AddressRef = address(LeftValue.value_name);
                            assemble_file << "\tmovq\t$" << RightValue.value_integer << "," << AddressRef << std::endl;
                        }
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovq\t" <<  offset_str << ",\%rax" << std::endl;
                            assemble_file << "\tmovq\t" << "\%rax," << dest_offset_str << std::endl;    
                        }
                    }
                    else if((LeftValue.value_type & float_mask)){
                        if(isaRegister(RightValue.value_name)){
                            ;
                        }
                        else if(_isConstExpress(RightValue.value_name)){
                            std::string label = func_double_label[func_info.function_name][RightValue.value_float].label;
                            label = label+ "(%rip)";
                            std::string AddressRef = WhichXmmFree();
                            assemble_file << "\tmovss\t" << label << "," << AddressRef << std::endl;
                            assemble_file << "\tmovss\t" << AddressRef << "," << address(LeftValue.value_name) << std::endl;
                        }  
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovss\t" <<  offset_str << ",\%xmm0" << std::endl;
                            assemble_file << "\tmovss\t" << "\%xmm0," << dest_offset_str << std::endl;    
                        }
                    }
                    else if((LeftValue.value_type & double_mask)){
                        
                        if(isaRegister(RightValue.value_name)){
                            ;
                        }
                        else if(_isConstExpress(RightValue.value_name)){
                            std::string label = func_double_label[func_info.function_name][RightValue.value_float].label;
                            label = label+ "(%rip)";
                            std::string AddressRef = WhichXmmFree();
                            assemble_file << "\tmovsd\t" << label << "," << AddressRef << std::endl;
                            assemble_file << "\tmovsd\t" << AddressRef << "," << address(LeftValue.value_name) << std::endl;
                        }
                        else{
                            std::string offset_str ;
                            getOffset(offset_str,RightValue.value_name);
                            std::string dest_offset_str;
                            getOffset(dest_offset_str,LeftValue.value_name);
                            assemble_file << "\tmovsd\t" <<  offset_str << ",\%xmm0" << std::endl;
                            assemble_file << "\tmovsd\t" << "\%xmm0," << dest_offset_str << std::endl;    
                        }
                    } 
                }
        }

        return LeftValue;
    }
    else {
#if defined(syntaxanalyzer)
    std::cout << "AssignmentExpress-> ConditionExpress" << std::endl;
#endif
        isAssignement = true;
        return  ConditionExpress();
    }
}

int SyntaxAnalyzer::AssignmentOperator(void){
    switch(CurrentTokenType){
        case SYN_SET:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> = " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_SET;
        case SYN_ME:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator->  *= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_ME;
        case SYN_DE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> /= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_DE;
        case SYN_MODEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> %= " << std::endl;
#endif
        Match(SYN_MODEQ);
        return SYN_MODEQ;
        case SYN_AE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> += " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_AE;
        case SYN_SE:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> -= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_SE;
        case SYN_BIT_SHLEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> <<= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_BIT_SHLEQ;
        case SYN_BIT_SHREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> >>= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_BIT_SHREQ;
        case SYN_BIT_ANDEQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator->  &= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_BIT_ANDEQ;
        case SYN_BIT_XOREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> ^= " << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_BIT_XOREQ;
        case SYN_BIT_OREQ:
#if defined(syntaxanalyzer)
    std::cout << "AssignmentOperator-> |=" << std::endl;
#endif
        Match(getTokenCoding());
        return SYN_BIT_OREQ;
    }
    return ERROR;
}

struct Value SyntaxAnalyzer::ConditionExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "ConditionExpres-> LogicOrExpress [ ? Express:ConditionExpress]" << std::endl;
#endif
    struct Value logic_or_value = LogicOrExpress();
    if(CurrentTokenType == SYN_QUES){
        Match(SYN_QUES);
        Express();
        Match(SYN_COLON);
        ConditionExpress();
    }
    return logic_or_value;
}

struct Value SyntaxAnalyzer::LogicOrExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "LogicOrExpress-> LogicAndExpress LogicOrExpress1" << std::endl;
#endif
    struct Value logic_and_value =  LogicAndExpress();
    LogicOrExpress1();
    return logic_and_value;
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

struct Value SyntaxAnalyzer::LogicAndExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "LogicAndExpress-> BitOrExpress LogicAndExpress1" << std::endl;
#endif
    struct Value bit_or_value = BitOrExpress();
    LogicAndExpress1();
    return bit_or_value;
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

struct Value SyntaxAnalyzer::BitOrExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitOrExpress->BitXorExpress BitOrExpress1" << std::endl;
#endif
    struct Value bit_xor_value = BitXorExpress();
    BitOrExpress1();
    return bit_xor_value;
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

struct Value SyntaxAnalyzer::BitXorExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitXorExpress-> BitAndExpress BitXorExpress1" << std::endl;
#endif
    struct Value bit_and_value = BitAndExpress();
    BitXorExpress1();
    return bit_and_value;
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

struct Value SyntaxAnalyzer::BitAndExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "BitAndExpress-> EqualClassExpress BitAndExpress1" << std::endl;
#endif
    struct Value equal_class_value = EqualClassExpress();
    BitAndExpress1();
    return equal_class_value;
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

struct Value SyntaxAnalyzer::EqualClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "EqualClassExpress-> RelationExpress EqualClassExpress1" << std::endl;
#endif  
    struct Value relation_value = RelationExpress();
    EqualClassExpress1();
    return relation_value;
}

void SyntaxAnalyzer::EqualClassExpress1(void){
    if(CurrentTokenType == SYN_NOTEQ || CurrentTokenType == SYN_EQ){
#if defined(syntaxanalyzer)
    std::cout << "EqualClassExpress1->(== | !=) RelationExpress EqualClassExpress1" << std::endl;
#endif
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

struct Value SyntaxAnalyzer::RelationExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "RelationExpress-> ShiftExpress RelationExpress1" << std::endl;
#endif  
    struct Value shift_value = ShiftExpress();
    RelationExpress1();
    return shift_value;
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

struct Value  SyntaxAnalyzer::ShiftExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "ShiftExpress-> AddClassExpress ShiftExpress" << std::endl;
#endif
    struct Value add_class_value = AddClassExpress();
    ShiftExpress1();
    return add_class_value;
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

struct Value SyntaxAnalyzer::AddClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "AddClassExpress-> MulClassExpress AddClassExpress1" << std::endl;
#endif
    struct Value mul_class_value = MulClassExpress();
    AddClassExpress1();
    return mul_class_value;
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

struct Value SyntaxAnalyzer::MulClassExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "MulClassExpress-> ForeceTranExpress MulClassExpress1" << std::endl;
#endif
    struct Value force_value = ForceTranExpress();
    MulClassExpress1();
    return force_value;
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

struct Value SyntaxAnalyzer::ForceTranExpress(void){
    if(CurrentTokenType == SYN_PAREN_L){
#if defined(syntaxanalyzer)
    std::cout << "ForceTranExpress-> (Type) ForceTranExpress" << std::endl;
#endif
        Match(SYN_PAREN_L);
        Type();
        Match(SYN_PAREN_R);
        struct Value value_ = ForceTranExpress();
        return value_;
    }
 /*   else if(isType(CurrentTokenType)){
        Type();
        ForceTranExpress();
    }*/
    else{
#if defined(syntaxanalyzer)
    std::cout << "ForceTranExpress-> UnaryExpress" << std::endl;
#endif
        struct Value unary_value = UnaryExpress();
        return unary_value;
    }
}

static bool isUnaryOperator(int tokentype){
    switch(tokentype){
        case SYN_BIT_AND:
        case SYN_MUL:
        case SYN_ADD:
        case SYN_SUB:
        case SYN_BIT_NOT:
        case SYN_NOT:
    //    case SYN_FUNCTION:
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

void SyntaxAnalyzer::ArrayArgus(void){
    if(CurrentTokenType == SYN_SQU_BRACE_L){
        Match(SYN_SQU_BRACE_L);
        ConstExpress();
        Match(SYN_SQU_BRACE_R);
        ArrayArgus();
    }
    else{
        ;
    }
}

void SyntaxAnalyzer::Args(void){
    bool InString = false;
            if(CurrentTokenType == SYN_KEYWORD){
#if defined(syntaxanalyzer)
    std::cout << "Args-> id" << token.tokenValue.StringValue << std::endl;
#endif  
                if(CurrentTokenType == SYN_KEYWORD){
                    Match(SYN_KEYWORD);
                    if(CurrentTokenType == SYN_SQU_BRACE_L){
                        ArrayArgus();
                    }
                }
                else if(CurrentTokenType == SYN_FUNCTION){
                    Match(SYN_FUNCTION);
                    Match(SYN_PAREN_L);
                    Args();
                    RealArgument();
                    Match(SYN_PAREN_R);
                }
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
                    for(auto _char:getTokenString()){
                        if(_char == '\''){
                            if(InString){
                                continue;
                            }
                            else{
                                break;
                            }
                        }
                        else if(_char == '\"'){
                            InString = true;
                        }
                    }
                    if(InString){
                        ReadOnlyData["string"].push_back(getTokenString());
                    }
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
                if(isType(CurrentTokenType))
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

struct Value SyntaxAnalyzer::UnaryExpress(void){
    struct Value value_;
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
      /*  else if(CurrentTokenType == SYN_FUNCTION){
            Match(SYN_FUNCTION);
#if defined(syntaxanalyzer)
    std::cout << "UnaryExpress-> function(Args  RealArgument)" << std::endl;
#endif
            Match(SYN_PAREN_L);
            Args();
            RealArgument();
            Match(SYN_PAREN_R);
        }*/
        else
            Match(getTokenCoding());
        return ForceTranExpress();
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
        return PostfixExpress();
    }
    return value_;
}

struct Value SyntaxAnalyzer::PostfixExpress(void){
    struct Value post_value = PrimaryExpress();
    PostfixExpress1();
    return post_value;
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
        return ;
    }
}

struct Value SyntaxAnalyzer::PrimaryExpress(void){
#if defined(syntaxanalyzer)
    std::cout << "PrimaryExpress-> Id | ConstExpress | (Express)" << std::endl;
#endif
    struct Value value__;
    if(CurrentTokenType == SYN_KEYWORD){
#if defined(syntaxanalyzer)
    std::cout << "id-> " << token.tokenValue.StringValue << std::endl;
#endif
        struct Value value_;
        value_.value_name = token.tokenValue.StringValue;
        Match(SYN_KEYWORD);
        if(RunTimeTrans){
            for(auto iter:Anonymous_domain[func_info.function_name].value_info){
                if(iter.value_name == value_.value_name){
                    value_.value_type = iter.value_type;
                    return value_;
                }
            }
            for(auto iter:localvalue[func_info.function_name].value_info){
                if(iter.value_name == value_.value_name){
                    value_.value_type = iter.value_type;
                    return value_;
                }
            }
            for(auto iter:GlobalValue){
                if(iter.value_name == value_.value_name){
                    value_.value_type = iter.value_type;
                    return value_;
                }
            }
        }
        return value_;
    }
    else if(CurrentTokenType == SYN_NUMBER_DOUBLE){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        struct Value value_;
        if(RunTimeTrans){
            value_.value_float = token.tokenValue.number.realNumber.floatNumber.DoubleNumber;
            value_.value_name = "";
            value_.value_type = statement_type ;
            if(!RunTimeTrans)
            if(FunctionRegion){
                func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].label = "floatnumber_" + std::to_string(double_label_counter);
                func_double_label[func_info.function_name][token.tokenValue.number.realNumber.floatNumber.DoubleNumber].type = statement_type ;
                double_label_counter++;
            }
        }
        Match(SYN_NUMBER_DOUBLE);
        return value_;
    }
    else if(CurrentTokenType == SYN_NUMBER_LONG){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        struct Value value_;
        value_.value_integer = token.tokenValue.number.realNumber.intgerNumber.LongNumber;
        value_.value_name = "";
        value_.value_type = statement_type;
        Match(SYN_NUMBER_LONG);
        return value_;
    }
    else if(CurrentTokenType == SYN_STRING){
#if defined(syntaxanalyzer)
    std::cout << "ConstExpress-> " << token.tokenValue.StringValue << std::endl;
#endif
        struct Value value_;
        value_.value_integer = 0;
        value_.value_name = "";
        value_.const_char = token.tokenValue.StringValue;
        value_.value_type = statement_type;
        if(getTokenString()[0] == '\'')
            ;
        else
        { 
            ReadOnlyData["string"].push_back(getTokenString());
        }
        Match(SYN_STRING);
        return value_;
    }
    else if(CurrentTokenType == SYN_PAREN_L){
        struct Value value_;
        Match(SYN_PAREN_L);
        value_ = Express();
        Match(SYN_PAREN_R);
        return value_;

    }
    else if(CurrentTokenType == SYN_FUNCTION){
        struct Value value_;
        value_.value_name = getTokenString();
        value_.Type = 3;
        if(RunTimeTrans)
            if(1){
                assemble_file << "\tcall\t" << value_.value_name <<"@PLT" << std::endl;
            }
        Match(SYN_FUNCTION);
        return value_;
    }
    return value__;
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


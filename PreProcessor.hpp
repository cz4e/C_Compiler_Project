#ifndef _PREPROCESSOR_H
#define _PREPROCESSOR_H
#endif

#include "TokenAnalyzer.hpp"
#define _FILENAME               1
#define PreProcessorFileName    "."
#define INCLUDEPATHPREFIX       "/usr/include/"

#define EeraseSubString(substring) do{\
                                            size_t pos = PreProcesstext.find(std::string(substring));\
                                            if(pos != PreProcesstext.npos)\
                                                PreProcesstext.erase(pos);\
                                    }while(0);
#define EraseSubString_(substring) do{\
                                            auto pos = text.find(std::string(substring));\
                                            auto length = std::string(substring).length();\
                                            if(pos != text.npos){\
                                                text.erase(pos,length);\
                                            }\
                                    }while(0);

#define ReplaceSubstring(str,repstring,substring) do{\
                                            for(auto pos = str.find(substring);pos != str.npos; pos = str.find(substring,pos+repstring.length())){\
                                                if(!LETTER_(str[pos - 1]) && !LETTER_(str[pos + substring.length()])){\
                                                    str.erase(pos,substring.length());\
                                                    str.insert(pos,repstring);\
                                                }\
                                            }\
                                        }while(0);

#define ReplaceMacroFunction(text,pos_,length_,name,argumentlist) do{\
                                                                    text.erase(pos_,length_);\
                                                                    std::string replacetext = MacroValue[name].textpart;\
                                                                    int index = 0;\
                                                                        for(auto argument : argumentlist){\
                                                                            ReplaceSubstring(replacetext,argument,MacroValue[name].arguments[index])\
                                                                            index++;\
                                                                        }\
                                                                    text.insert(pos_,replacetext);\
                                                                }while(0);
//#define MacroIf 1
class PreProcessor{
public:
    PreProcessor();
    ~PreProcessor();
    void getFileName(const std::string filename);                             // 获取源代码文件名
    void setFileName(const std::string _filename);                             // 设置中间文件文件名
    void StartPreProcessor(void);                       // 开始预处理
    void ProcessInclude(void);                          // 处理#include
    void ProcessDefine(void);                           // 处理#define
    void ProcessUndef(void);                            // 处理#Undef
    void ProcessLine(void);                             // 处理#Line
    void ProcessError(void);                            // 处理#Error
    void ProcessPragma(void);                           // 处理#pragma
    void ProcessPreProcessorConditionInstruction(void); // 处理预处理器条件指令(#if,#elif,#else,#endif)
    void ProcessConstorlInstruction(void);              // 处理控制指令
    void do_macroif(void);
    void do_macroifdef(void);
    void do_macroifndef(void);
    bool macroExpress(void);
    bool AssignmentExpress(void);
    bool LogicOrExpress(void);
    bool LogicOrExpress1(bool preresult);
    bool LogicAndExpress(void);
    bool LogicAndExpress1(long result);
    long BitOrExpress(void);
    long BitOrExpress1(long result);
    long BitXorExpress(void);
    long BitXorExpress1(long result);
    long BitAndExpress(void);
    long BitAndExpress1(long result);
    long EqualClassExpress(void);
    long EqualClassExpress1(long result);
    long RelationExpress(void);
    long RelationExpress1(long result);
    long ShiftExpress(void);
    long ShiftExpress1(long result);
    long AddClassExpress(void);
    long AddClassExpress1(long result);
    long MultiClassExpress(void);
    long MultiClassExpress1(long result);
    long ForceTransExpress(void);
    long UnaryExpress(void);
    long PostfixExpress(void);
    long PostfixExpress1(long result);
    long BaseExpress(void);
    bool ConditionExpress(void);
    void do_macro(bool BooleanValue);
    void do_replace(void);
    void copytoFile(std::ofstream &midfile);
    void WriteToMidFile(void);
    void ClearFile(void);
    void matchToken(void);                              // 获取Token
private:
    TokenAnalyzer tokenanalyzer;
    bool &PreProcess = tokenanalyzer.getPreProcessStatus();
    bool &Global = tokenanalyzer.getGlobalStatus();
    std::ofstream MidFile;
    std::string filename;
    int CurrentTokenType;
    std::ifstream _midfile;
    std::ofstream Objectfile;
};

PreProcessor::PreProcessor(){
    /*
        Nothing to do
    */
}


PreProcessor::~PreProcessor(){
    /*
        Nothing to do
    */
}

void PreProcessor::matchToken(void){
    TOKEN token = tokenanalyzer.NextToken();
    CurrentTokenType = token.TokenType;
    return;
}

static bool isMacro(int type){
    switch (type)
    {
        case SYN_MACRO_DEFINE:
        case SYN_MACRO_INCLUDE:
        case SYN_MACRO_UNDEF:
        case SYN_MACRO_IF:
        case SYN_MACRO_IFDEF:
        case SYN_MACRO_IFNDEF:
        case SYN_LINE:
        case SYN_ERROR:
        case SYN_PRAGMA:
        case SYN_MACRO_ENDIF:
            return true;
        default:
            return false;
    }
}

void PreProcessor::do_replace(void){
    if(Global){
        auto macro_iter = MacroValue.cbegin();
        std::string macroname;
        
        while(macro_iter != MacroValue.cend()){

            if(text.find(macro_iter->first) != text.npos){
                if(macro_iter->second.MacroType == 1){
                    ReplaceSubstring(text,macro_iter->second.textpart,macro_iter->first)
                }
                else if(macro_iter->second.MacroType == 2){
                    bool preProcessStatus = PreProcess,preGlobalStatus = Global;
                    PreProcess = false;
                    Global = false;
                    macroname = macro_iter->first + '(';
                    
                    char postchar = tokenanalyzer.ReadAChar();
                    text.push_back(postchar);
                    if(postchar == '(' && text.find(macroname) != text.npos){

                        int SubStringLength = macroname.length(), paren = 1;
                        std::string str;
                        std::vector<std::string> ArgumentString;

                        for(;paren != 0;){
                            postchar = tokenanalyzer.ReadAChar();
                            if(postchar == '('){
                                paren++;
                                str.push_back(postchar);
                            }
                            else if(postchar == ')'){
                                paren--;
                                if(paren){
                                    str.push_back(postchar);
                                    char temp = postchar;
                                    postchar = tokenanalyzer.ReadAChar();
                                    if(postchar == ','){
                                        SubStringLength++;
                                        text.push_back(temp);
                                        ArgumentString.push_back(str);
                                        str = "";
                                    }
                                    else{
                                        postchar = temp;
                                        tokenanalyzer.SeekFileHandler(-1L);
                                    }
                                }
                                else{
                                    ArgumentString.push_back(str);
                                    str = "";
                                }
                            }
                            else if(postchar == ','){
                                ArgumentString.push_back(str);
                                str = "";
                            }
                            else if(BLANCK(postchar)){
                                continue;
                            }
                            else if(postchar == '\\'){
                                char temp = postchar;
                                postchar = tokenanalyzer.ReadAChar();
                                if(postchar == '\n'){
                                    continue;
                                }
                                else{
                                    postchar = temp;
                                    tokenanalyzer.SeekFileHandler(-1L);
                                    str.push_back(postchar);
                                    continue;
                                }
                            }
                            else{
                                str.push_back(postchar);
                            }
                            SubStringLength++;
                            text.push_back(postchar);
                        }
                        for(auto pos_ = text.find(macroname);pos_ != text.npos ; pos_ = text.find(macroname,pos_ + macroname.length())){
                            ReplaceMacroFunction(text,pos_,SubStringLength,macro_iter->first,ArgumentString) 
                        }
                    }
                    else{
                        text.pop_back();
                        tokenanalyzer.SeekFileHandler(-1L);
                    }
                    PreProcess = preProcessStatus;
                    Global = preGlobalStatus;
                }
            }
            macro_iter++;
        }
    }
}

void PreProcessor::copytoFile(std::ofstream &midfile){
    do_replace();
    midfile << text << std::flush;
    text = "";
    return;
}

void PreProcessor::StartPreProcessor(void){
    matchToken();
//
// Process 

    while(!tokenanalyzer.isEOF()){
        if(isMacro(CurrentTokenType)){
            Global = false;
            switch(CurrentTokenType){
                case SYN_MACRO_DEFINE:
                    EraseSubString_("#define")
                    copytoFile(midfile);
                    ProcessDefine();
                    break;
                case SYN_MACRO_INCLUDE:
                    EraseSubString_("#include")
                    copytoFile(midfile);
                    ProcessInclude();
                    break;
                case SYN_MACRO_UNDEF:
                    EraseSubString_("#undef")
                    copytoFile(midfile);
                    ProcessUndef();
                    break;
                case SYN_MACRO_IF:
                    EraseSubString_("#if")
                    copytoFile(midfile);
                    ProcessPreProcessorConditionInstruction();
                    break;
                case SYN_MACRO_IFDEF:
                    EraseSubString_("#ifdef")
                    copytoFile(midfile);
                    ProcessPreProcessorConditionInstruction();
                    break;
                case SYN_MACRO_IFNDEF:
                    EraseSubString_("#ifndef")
                    copytoFile(midfile);
                    ProcessPreProcessorConditionInstruction();
                    break;
                case SYN_LINE:
                    EraseSubString_("#line")
                    copytoFile(midfile);
                    ProcessLine();
                    break;
                case SYN_ERROR:
                    EraseSubString_("#error")
                    copytoFile(midfile);
                    ProcessError();
                    break;
                case SYN_PRAGMA:
                    EraseSubString_("#pragma")
                    copytoFile(midfile);
                    ProcessPragma();
                    break;
                case SYN_MACRO_ENDIF:
                    EraseSubString_("#endif")
                    break;
            }
            Global = true;
        }
        else{
            copytoFile(midfile);
        }
        matchToken();
    }
    return;
}

void PreProcessor::getFileName(const std::string filename){
    tokenanalyzer.SetFileName(filename);
    return;
}

void PreProcessor::ClearFile(void){
    char error_char = 0xff;
    char CharReadFromFile;
    midfile.close();
    std::ifstream _midfile;
    _midfile.open(filename,std::ios_base::in);
    while(_midfile){
        CharReadFromFile = _midfile.get();
        if(CharReadFromFile == error_char){
            CharReadFromFile = ' ';
        }
        Objectfile << CharReadFromFile;
    }
    _midfile.close();
    Objectfile.close();
    return;
}
void PreProcessor::setFileName(const std::string _filename){
    filename = PreProcessorFileName + _filename ;
    midfile.open(filename,std::ios_base::out);
    Objectfile.open(".source_" + _filename,std::ios_base::out);
    return;
}

void PreProcessor::WriteToMidFile(void){
    midfile << PreProcesstext << std::flush;
    PreProcesstext = "";
}



static bool isProcessDefine(const std::string macroname){
    if(MacroValue.find(macroname) != MacroValue.end()){
        return true;
    }
    return false;
}

void PreProcessor::ProcessUndef(void){
    matchToken();
    std::string MacroName = tokenanalyzer.tokenString();
    if(isProcessDefine(MacroName)){
        MacroValue.erase(MacroName);
    }
    else{
        ;
    }
}                            // 处理#Undef

void PreProcessor::ProcessLine(void){
    ;
}                             // 处理#Line

void PreProcessor::ProcessError(void){
    ;
}                            // 处理#Error

void PreProcessor::ProcessPragma(void){
    ;
} 

void PreProcessor::ProcessInclude(void){
    matchToken();
    std::string _filename ;
    PreProcessor preprocess;
    
    if(CurrentTokenType == SYN_STRING){
        std::string tempstr = tokenanalyzer.tokenString();
        for(auto str : tempstr)
            if(str != '\"')
            _filename.push_back(str);
        preprocess.getFileName(_filename); 
        preprocess.StartPreProcessor();
        return;
    }
    else if(CurrentTokenType == SYN_LT){
        matchToken();
        _filename = INCLUDEPATHPREFIX + tokenanalyzer.tokenString();
        preprocess.getFileName(_filename);        
        preprocess.StartPreProcessor();
        matchToken();
        return;
    }
}

bool PreProcessor::macroExpress(void){
#if defined(MacroIf)
    std::cout << "macroExpres-> AssignmentExpress" << std::endl;
#endif
    return AssignmentExpress();   
}

bool PreProcessor::AssignmentExpress(void){
#if defined(MacroIf)
    std::cout << "AssignmentExpress-> ConditionExpress" << std::endl;
#endif
    return ConditionExpress();
}

bool PreProcessor::ConditionExpress(void){
#if defined(MacroIf)
    std::cout << "ConditionExpress-> LogicOrExpress[?macroExpress:ConditionExpress]" << std::endl;
#endif
    auto result = LogicOrExpress();
    if(CurrentTokenType == SYN_QUES){
        matchToken();
        if(result){
            result = macroExpress();
            matchToken();
            ConditionExpress();
            return result;
        }
        else{
            macroExpress();
            matchToken();
            result = ConditionExpress();
            return result;
        }
    }
    else{
        return result;
    }
}

bool PreProcessor::LogicOrExpress(void){
#if defined(MacroIf)
    std::cout << "LogicOrExpress-> LogicAndExpress LogicOrExpress1" << std::endl;
#endif
    auto result = LogicAndExpress();
    return LogicOrExpress1(result);
}

bool PreProcessor::LogicOrExpress1(bool preresult){
#if defined(MacroIf)
    std::cout << "LogicOrExpress1->|| LogicAndExpress LogicOrExpress1" << std::endl;
#endif
    if(preresult){
        if(CurrentTokenType == SYN_OR){
            matchToken();
            LogicAndExpress();
            LogicOrExpress1(true);
            return preresult;
        }
        else{
            return preresult;
        }
    }
    else{
        if(CurrentTokenType == SYN_OR){
            matchToken();
            long result = LogicAndExpress();
            result = LogicOrExpress1(result);
            return result || preresult;
        }
        else{
            return preresult;
        }
    }
}

bool PreProcessor::LogicAndExpress(void){
#if defined(MacroIf)
    std::cout << "LogicAndExpress->BitOrExpress LogicAndExpress1" << std::endl;
#endif
    long result = BitOrExpress();
    return LogicAndExpress1(result);
}

bool PreProcessor::LogicAndExpress1(long result){
#if defined(MacroIf)
    std::cout << "LogicAndExpress1-> && BitOrExpress LogicAndExpress1" << std::endl;
#endif
    if(result){
        if(CurrentTokenType == SYN_AND){
            matchToken();
            long result_ = BitOrExpress();
            result_ = LogicAndExpress1(result_);
            return result_ && result;
        }
        else{
            return result;
        }
    }
    else{
        if(CurrentTokenType == SYN_AND){
            matchToken();
            BitOrExpress();
            LogicOrExpress1(1);
        }
        return result;
    }
}

long PreProcessor::BitOrExpress(void){
#if defined(MacroIf)
    std::cout << "BitOrExpress->BitXorExpress BitOrExpress1" << std::endl;
#endif
    long result = BitXorExpress();
    return BitOrExpress1(result);
}

long PreProcessor::BitOrExpress1(long result){
#if defined(MacroIf)
    std::cout << "BitOrExpress1-> | BitXorExpress BitOrExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_BIT_OR){
        matchToken();
        long result_ = BitXorExpress();
        result_ = BitOrExpress1(result_);
        return result | result_;
    }
    else{
        return result;
    }
}

long PreProcessor::BitXorExpress(void){
#if defined(MacroIf)
    std::cout << "BitXorExpress->BitAndExpress BitXorExpress1" << std::endl;
#endif
    long result = BitAndExpress();
    return BitXorExpress1(result);
}

long PreProcessor::BitXorExpress1(long result){
#if defined(MacroIf)
    std::cout << "BitXorExpress1-> ^ BitAndExpress BitXorExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_BIT_XOR){
        matchToken();
        long result_ = BitAndExpress();
        result_ = BitXorExpress1(result_);
        return result_ ^ result;
    }
    else{
        return result;
    }
}

long PreProcessor::BitAndExpress(void){
#if defined(MacroIf)
    std::cout << "BitAndExpress-> EqualClassExpress BitAndExpress1" << std::endl;
#endif
    long result = EqualClassExpress();
    return BitAndExpress1(result);
}

long PreProcessor::BitAndExpress1(long result){
#if defined(MacroIf)
    std::cout << "BitAndExpress1-> & EqualClassExpress BitAndExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_BIT_AND){
        matchToken();
        long result_ = EqualClassExpress();
        result_ = BitAndExpress1(result_);
        return result & result_;
    }
    else{
        return result;
    }
}

long PreProcessor::EqualClassExpress(void){
#if defined(MacroIf)
    std::cout << "EqualClassExpress-> RelationExpress EqualClassExpress1" << std::endl;
#endif
    long result = RelationExpress();
    return EqualClassExpress1(result);
}

long PreProcessor::EqualClassExpress1(long result){
#if defined(MacroIf)
    std::cout << "EqualClassExpress-> (== | != )RelationExpress EqualClassExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_EQ){
        matchToken();
        long result_ = RelationExpress();
        result_ = EqualClassExpress1(result_);
        return result_ == result;
    }
    else if(CurrentTokenType == SYN_NOTEQ){
        matchToken();
        long result_ = RelationExpress();
        result_ = EqualClassExpress1(result_);
        return result != result_;
    }
    else{
        return result;
    }
}

long PreProcessor::RelationExpress(void){
#if defined(MacroIf)
    std::cout << "RelationExpress-> ShiftExpress RelationExpress1" << std::endl;
#endif
    long result = ShiftExpress();
    return RelationExpress1(result);
}

long PreProcessor::RelationExpress1(long result){
#if defined(MacroIf)
    std::cout << "RelationExpress1-> (< |> |<= | >=) ShiftExpress RelationExpress1" << std::endl;
#endif

    if(CurrentTokenType == SYN_LT) {
        matchToken();
        long result_ = ShiftExpress();
        result_ = RelationExpress1(result_);
        return result_ < result;
    }
    else if(CurrentTokenType == SYN_GT) {
        matchToken();
        long result_ = ShiftExpress();
        result_ = RelationExpress1(result_);
        return result_ > result;
    }
    else if(CurrentTokenType == SYN_LE) {
        matchToken();
        long result_ = ShiftExpress();
        result_ = RelationExpress1(result_);
        return result_ <= result;
    }
    else if(CurrentTokenType == SYN_GE) {
        matchToken();
        long result_ = ShiftExpress();
        result_ = RelationExpress1(result_);
        return result_ >= result;
    }
    else{
        return result;
    }
}

long PreProcessor::ShiftExpress(void){
#if defined(MacroIf)
    std::cout << "ShiftExpress->AddClassExpress ShiftExpress1" << std::endl;
#endif
    long result = AddClassExpress();
    return ShiftExpress1(result);
}

long PreProcessor::ShiftExpress1(long result){
#if defined(MacroIf)
    std::cout << "ShiftExpress1-> (<< |>>) AddClassExpress ShiftExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_BIT_SHL){
        matchToken();
        long result_ = AddClassExpress();
        result_ = ShiftExpress1(result_);
        return result << result_;
    }
    else if(CurrentTokenType == SYN_BIT_SHR){
        matchToken();
        long result_ = AddClassExpress();
        result_ = ShiftExpress1(result_);
        return result >> result_;
    }
    else{
        return result;
    }
}

long PreProcessor::AddClassExpress(void){
#if defined(MacroIf)
    std::cout << "AddClassExpress->MultiExpress AddClassExpress1" << std::endl;
#endif
    long result = MultiClassExpress();
    return AddClassExpress1(result);
}

long PreProcessor::AddClassExpress1(long result){
#if defined(MacroIf)
    std::cout << "AddClassExpress1-> (+|-) MultiExpress AddClassExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_ADD){
        matchToken();
        long result_ = MultiClassExpress();
        result_ = AddClassExpress1(result_);
        return result + result_;
    }
    else if(CurrentTokenType == SYN_SUB){
        matchToken();
        long result_ = MultiClassExpress();
        result_ = AddClassExpress1(result_);
        return result - result_;
    }
    else{
        return result;
    }
}

long PreProcessor::MultiClassExpress(void){
#if defined(MacroIf)
    std::cout << "ForceTransExpress-> ForceTransExpress MultiClassExpress1" << std::endl;
#endif
    long result = ForceTransExpress();
    return MultiClassExpress1(result);
}

long PreProcessor::MultiClassExpress1(long result){
#if defined(MacroIf)
    std::cout << "MultiClassExpress1-> (*|/|%) ForceTransExpress MultiClassExpress1" << std::endl;
#endif
    if(CurrentTokenType == SYN_MUL){
        matchToken();
        long result_ = ForceTransExpress();
        result_ = MultiClassExpress1(result_);
        return result * result_;
    }
    else if(CurrentTokenType == SYN_DIV){
        matchToken();
        long result_ = ForceTransExpress();
        result_ = MultiClassExpress1(result_);
        return result / result_;
    }
    else if(CurrentTokenType == SYN_MOD){
        matchToken();
        long result_ = ForceTransExpress();
        result_ = MultiClassExpress1(result_);
        return result % result_;
    }
    else{
        return result;
    }
}

long PreProcessor::ForceTransExpress(void){
#if defined(MacroIf)
    std::cout << "ForceTransExpress-> ..." << std::endl;
#endif
    if(CurrentTokenType == SYN_PAREN_L){
        matchToken();
        matchToken();
        matchToken();
        ForceTransExpress();
    }
    else{
        return UnaryExpress();
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
            return true;
        default:
            return false;
    }

}

long PreProcessor::UnaryExpress(void){
    long result;
    switch(CurrentTokenType){
        case SYN_INC:
            matchToken();
            result = UnaryExpress();
            result++;
            return result;
        case SYN_DEC:
            matchToken();
            result = UnaryExpress();
            result--;
            return result;
        case SYN_KEYWORD:
            if(tokenanalyzer.tokenString() == std::string("defined")){
                if(CurrentTokenType == SYN_KEYWORD){
                    if(MacroValue.find(tokenanalyzer.tokenString()) != MacroValue.end()){
                        matchToken();
                        return true;
                    }
                    else{
                        matchToken();
                        return false;
                    }
                }
            }
        case SYN_FUNCTION:
                matchToken();
                if(CurrentTokenType == '('){
                    matchToken();
                    if(MacroValue.find(tokenanalyzer.tokenString()) != MacroValue.end()){
                        //result =  atol(MacroValue[tokenanalyzer.tokenString()].textpart.c_str());
                        matchToken();
                        return true;
                    }
                    else{
                        matchToken();
                        return false;
                    }
                }
        default:
            if(isUnaryOperator(CurrentTokenType)){
                switch(CurrentTokenType){
                    case SYN_NOT:
                        matchToken();
                        return ! UnaryExpress();
                }
            }
            else{
                return PostfixExpress();
            }
    }
}

long PreProcessor::PostfixExpress(void){
    long result = BaseExpress();
    return PostfixExpress1(result);
}

long PreProcessor::PostfixExpress1(long result){
    if(CurrentTokenType == SYN_INC){
        matchToken();
        long result_ = PostfixExpress1(result);
        result_++;
        return result_;
    }
    else if(CurrentTokenType == SYN_DEC){
        matchToken();
        long result_ = PostfixExpress1(result);
        result_--;
        return result_;
    }
    else{
        return BaseExpress();
    }
}

long PreProcessor::BaseExpress(void){
    long result;
    switch(CurrentTokenType){
        case SYN_KEYWORD:
            if(MacroValue.find(tokenanalyzer.tokenString()) != MacroValue.end()){
                result =  atol(MacroValue[tokenanalyzer.tokenString()].textpart.c_str());
                matchToken();
                return result;
            }
            else{
                std::cout << "Not define " << tokenanalyzer.tokenString() << std::endl;
                exit(1);
            }
        case SYN_STRING: 
            if(tokenanalyzer.tokenString() == ""){
                matchToken();
                return 0;
            }
            else{
                matchToken();
                return 1;
            }
        case SYN_PAREN_L:
            matchToken();
            result = macroExpress();
            matchToken();
            return result;
        case SYN_NUMBER_LONG:
            result = atol(tokenanalyzer.tokenString().c_str());
            matchToken();
            return result;
        case SYN_NUMBER_DOUBLE:
            result =  std::stod(tokenanalyzer.tokenString().c_str());
            matchToken();
            return result;
    }
}

void PreProcessor::do_macro(bool BooleanValue){
    if(CurrentTokenType == SYN_MACRO_DEFINE){
        EeraseSubString("#define")
        PreProcess = false;
        ProcessDefine();
        PreProcess = true;
    }
    else if(CurrentTokenType == SYN_MACRO_ELIF && ! BooleanValue){
        do_macroif();
    }
    else if(CurrentTokenType == SYN_MACRO_ELSE && ! BooleanValue){
        PreProcess = true;
        while(CurrentTokenType != SYN_MACRO_ENDIF)
            matchToken();
        PreProcess = false;
    }
    else if(CurrentTokenType == SYN_MACRO_IF){
        do_macroif();
    }
    else if(CurrentTokenType == SYN_MACRO_IFDEF){
        do_macroifdef();
    }
    else if(CurrentTokenType == SYN_MACRO_IFNDEF){
        do_macroifndef();
    }
    else if(CurrentTokenType == SYN_MACRO_INCLUDE && BooleanValue){
        EeraseSubString("#include")
        PreProcess = false;
        ProcessInclude();
        PreProcess = true;
    }
}
void PreProcessor::do_macroif(void){
    matchToken();
    bool isExpressisTrue = macroExpress();
    long offset = tokenanalyzer.tokenLength();
    offset = 0 - offset;
    tokenanalyzer.SeekFileHandler(offset);
    if(isExpressisTrue){
        PreProcess = true;
        while(CurrentTokenType != SYN_MACRO_ENDIF){
            matchToken();
            do_macro(true);
            if(CurrentTokenType == SYN_MACRO_ENDIF)
                break;  
        }
        if(CurrentTokenType == SYN_MACRO_ENDIF){
            EeraseSubString("#endif")
        }
        PreProcess = false;
    }
    else{
        PreProcess = false;
        while(CurrentTokenType != SYN_MACRO_ENDIF){
            matchToken();
            do_macro(false);
            if(CurrentTokenType == SYN_MACRO_ENDIF)
                break;
        }
        if(CurrentTokenType == SYN_MACRO_ENDIF){
            EeraseSubString("#endif")
        }
        PreProcess = false;
    }
    WriteToMidFile();
}

void PreProcessor::do_macroifdef(void){
    matchToken();
    std::string macroname = tokenanalyzer.tokenString();
    EraseSubString_("#ifdef");
    if(isProcessDefine(macroname)){
        PreProcess = true;
        while(CurrentTokenType != SYN_MACRO_ELSE && CurrentTokenType != SYN_MACRO_ENDIF){
            matchToken();
            if(CurrentTokenType == SYN_MACRO_DEFINE){
                EeraseSubString("#define")
                PreProcess = false;
                ProcessDefine();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_INCLUDE){
                EeraseSubString("#include")
                PreProcess = false;
                ProcessInclude();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IFDEF){
                EeraseSubString("#ifdef")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IFNDEF){
                EeraseSubString("#ifndef")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IF){
                EeraseSubString("#if")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
        }
        if(CurrentTokenType == SYN_MACRO_ELSE){
            EeraseSubString("#else")
            PreProcess = false;
            while(CurrentTokenType != SYN_MACRO_ENDIF)
                matchToken();
            EeraseSubString("#endif")
        }
        else {
            EeraseSubString("#endif")
            PreProcess = false;
        }
    }
    else {
        PreProcess = false;
        while(CurrentTokenType != SYN_MACRO_ENDIF)
            matchToken();
        EeraseSubString("#endif")
    }
    WriteToMidFile();
}

void PreProcessor::do_macroifndef(void){
    matchToken();
    std::string macroname = tokenanalyzer.tokenString();
    if(!isProcessDefine(macroname)){
        PreProcess = true;
        while(CurrentTokenType != SYN_MACRO_ELSE && CurrentTokenType != SYN_MACRO_ENDIF){
            matchToken();
            if(CurrentTokenType == SYN_MACRO_DEFINE){
                EeraseSubString("#define")
                PreProcess = false;
                ProcessDefine();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_INCLUDE){
                EeraseSubString("#include")
                PreProcess = false;
                ProcessInclude();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IFDEF){
                EeraseSubString("#ifdef")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IFNDEF){
                EeraseSubString("#ifndef")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
            else if(CurrentTokenType == SYN_MACRO_IF){
                EeraseSubString("#if")
                PreProcess = false;
                ProcessPreProcessorConditionInstruction();
                PreProcess = true;
            }
        }
        if(CurrentTokenType == SYN_MACRO_ELSE){
            EeraseSubString("#else")
            PreProcess = false;
            while(CurrentTokenType != SYN_MACRO_ENDIF)
                matchToken();
            EeraseSubString("#endif")
        }
        else {
            EeraseSubString("#endif")
            PreProcess = false;
        }
    }
    else {
        PreProcess = false;
        while(CurrentTokenType != SYN_MACRO_ENDIF)
            matchToken();
        EeraseSubString("#endif")
    }
    WriteToMidFile();
}

void PreProcessor::ProcessPreProcessorConditionInstruction(void){
    switch(CurrentTokenType){
        case SYN_MACRO_IF:
            do_macroif();
            break;
        case SYN_MACRO_IFDEF:
            do_macroifdef();
            break;
        case SYN_MACRO_IFNDEF:
            do_macroifndef();
            break;
    }
}

void PreProcessor::ProcessDefine(void){

    std::string keyname;
    struct textPart macropart;
    matchToken();
    keyname = tokenanalyzer.tokenString();
    int Count = 0;
    char TempChar;
    
    TempChar = tokenanalyzer.ReadAChar();
    if(TempChar == '\n'){
        macropart.MacroType = -1;
        MacroValue[keyname] = macropart;
        return;
    }
    else{
        tokenanalyzer.SeekFileHandler(-1L);
    }
    matchToken();

    if(CurrentTokenType == SYN_PAREN_L){
        macropart.MacroType = 2;
        while(CurrentTokenType != SYN_PAREN_R){
            matchToken();
            if(CurrentTokenType == SYN_KEYWORD){
                macropart.arguments.push_back(tokenanalyzer.tokenString());
            }
        }
        matchToken();
        if(CurrentTokenType == SYN_PAREN_L){
            macropart.textpart.push_back('(');
            unsigned int ParenCount = 1;
            char TempChar;
            for(TempChar = tokenanalyzer.ReadAChar() ; ParenCount ; TempChar = tokenanalyzer.ReadAChar()){
                if(TempChar == '\\' && tokenanalyzer.ReadAChar() == '\n'){
                    tokenanalyzer.SeekFileHandler(-1L);
                    continue;
                }
                else if(TempChar == '\n' || TempChar == '\t'){
                    continue;
                }
                else{
                    if(TempChar == '(')
                        ParenCount++;
                    else if(TempChar == ')')
                    {
                        ParenCount--;   
                    }
                    macropart.textpart.push_back(TempChar);
                }
            }
        }
        else {
            macropart.textpart.append(tokenanalyzer.tokenString());
        }
    }
    else if(CurrentTokenType == SYN_NUMBER_LONG || CurrentTokenType == SYN_NUMBER_DOUBLE || CurrentTokenType == SYN_STRING || CurrentTokenType ==SYN_KEYWORD){
        macropart.MacroType = 1;
        macropart.textpart = tokenanalyzer.tokenString();
    }
    MacroValue[keyname] = macropart;
}


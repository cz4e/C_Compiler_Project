//#include "PreProcessor.hpp"
#include "./LL.hpp"
#include <iostream>
#include <string>

int main(int argc,char *argv[]){
#if defined(StartSyntaxAnalysis)
    SyntaxAnalyzer Syntaxanalyzer(argv[1]);
    Syntaxanalyzer.BuildAST();
    BulidObejctCode(argv[1]);
    Syntaxanalyzer.ReOpenFile(argv[1]);
    Syntaxanalyzer.BuildAST();
    WriteInfo(assemble_file,"main");
#elif defined(StartTokenAnalysis)
    TokenAnalyzer TokenAnalyzer;
    TokenAnalyzer.SetFileName(argv[1]);
    TOKEN token  = TokenAnalyzer.NextToken();
    while(!TokenAnalyzer.isEOF()){
        std::cout << token.tokenValue.StringValue << std::endl;
        token = TokenAnalyzer.NextToken();
    }
#elif defined(StartPreProcess)
    PreProcessor Preprocessor;
    Preprocessor.getFileName(argv[_FILENAME]);
    Preprocessor.setFileName(argv[_FILENAME]);
    Preprocessor.StartPreProcessor();
    Preprocessor.ClearFile();
#endif
    return 0;
}

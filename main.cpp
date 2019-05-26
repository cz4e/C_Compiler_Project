//#include "PreProcessor.hpp"
#include "./LL.hpp"
#include <iostream>
#include <string>

int main(int argc,char *argv[]){
#if defined(StartSyntaxAnalysis)
    SyntaxAnalyzer Syntaxanalyzer(argv[1]);
    Syntaxanalyzer.BuildAST();
    auto iter_begin = GlobalValue.cbegin();
  /* while(iter_begin != GlobalValue.cend()){
        std::cout << "value " << std::endl;
        std::cout << "     name: " << iter_begin->value_name << std::endl;
        std::cout << "     struct_name: " << iter_begin->struct_name << std::endl;
        std::cout << "     store_type: " << iter_begin->store_type << std::endl;
        std::cout << "     limit_type: " << iter_begin->limit_type << std::endl;
        std::cout << "     value_type: " << iter_begin->value_type << std::endl;
        if(iter_begin->value_type & double_mask)
            std::cout << "     value: " << iter_begin->value.number.realNumber.floatNumber.DoubleNumber << std::endl;
        else if(iter_begin->value_type & int_mask && !( iter_begin->value_type & array_mask))
            std::cout << "     value: " << iter_begin->value.number.realNumber.intgerNumber.IntNumber << std::endl;
        else if(iter_begin->value_type & char_mask)
            std::cout << "     value: " << iter_begin->value.StringValue << std::endl;
        std::cout << "     dimension: " << iter_begin->value.arrayinfo.Dimension << std::endl;
        std::cout << "     dims: " << std::flush;
        for(auto dim:iter_begin->value.arrayinfo.dims){
            std::cout << dim << " "<< std::flush;
        }
        std::cout << "\n     block_value: " << std::flush;
        for(auto struct_:iter_begin->block_value){   
            std::cout << struct_.number.realNumber.intgerNumber.IntNumber << " " << std::flush;
        }
        std::cout << "\n     struct_body:" << std::endl;
        for(auto body:iter_begin->struct_body){
           std::cout << "       value_type: " << body.number.realNumber.intgerNumber.LongNumber << std::endl;
            std::cout << "          " << body.StringValue << std::endl;
        }
        std::cout  << std::endl;
        iter_begin++;
    }*/
/*    auto iter_begin = ValueAlais.cbegin();
    while(iter_begin != ValueAlais.cend()){
        std::cout << "limit_type: " << iter_begin->limit_type << std::endl;
        std::cout << "value_type: " << iter_begin->value_type << std::endl;
        std::cout << "alias: " << iter_begin->alias << std::endl;
        iter_begin++;
    }*/
   /* for(auto iter:FuncInfo){
        std::cout << "funtion: "<< iter.function_name << "\n" 
                    << "return_type: " << iter.return_type << "\n"
                    << std::flush;
        for(auto iter_:iter.args_type){
            std::cout <<"arg_name: " << iter_.argument_name << "\n" 
                        << "type: " << iter_.type << std::endl;
        } 
    }*/
    for(auto iter:ReadOnlyData){
        std::cout << iter << std::endl;
    }
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

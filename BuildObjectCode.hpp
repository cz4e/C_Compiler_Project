#ifndef _OBJECTCODE_H
#define _OBJECTCODE_H
#endif 

#define CompilerInfo    "\"GNU C Like Simple C Compiler\""
#define isUnsignedShort(dest_value_type)    (dest_value_type & (unsigned_mask | short_mask))
#define isChar(dest_value_type)             (dest_value_type & (unsigned_mask | signed_mask | char_mask))
#define isSignedShort(dest_value_type)      (dest_value_type & (signed_mask | short_mask))
#define isUnsignedInt(dest_value_type)      (dest_value_type & (unsigned_mask | int_mask))
#define isSignedInt(dest_value_type)        (dest_value_type & (signed_mask | int_mask))
#define isUnsignedLong(dest_value_type)     (dest_value_type & (unsigned_mask | long_mask))
#define isSignedLong(dest_value_type)       (dest_value_type & (signed_mask | long_mask))
#define isSignedFloat(dest_value_type)      (dest_value_type & (signed_mask | float_mask))
#define isSignedDouble(dest_value_type)     (dest_value_type & (signed_mask | double_mask))
 
#define CopyValue(dest_value_type,source_value,valueinfo_object) do{\
                                                                if(dest_value_type & string_mask){\
                                                                    valueinfo_object.value.StringValue = source_value.StringValue;\
                                                                }\
                                                                else if(dest_value_type & long_mask){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.IntNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(dest_value_type & short_mask){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.ShortNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(dest_value_type & int_mask){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.IntNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(dest_value_type & double_mask){\
                                                                    valueinfo_object.value.number.realNumber.floatNumber.DoubleNumber = source_value.number.realNumber.floatNumber.DoubleNumber;\
                                                                }\
                                                                else if(dest_value_type & float_mask){\
                                                                    valueinfo_object.value.number.realNumber.floatNumber.FloatNumber = source_value.number.realNumber.floatNumber.FloatNumber;\
                                                                }\
                                                                else if(isChar(dest_value_type)){\
                                                                    valueinfo_object.value.StringValue = source_value.StringValue;\
                                                                }\
                                                                else if(isUnsignedShort(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.UnSignedShortNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isSignedShort(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.ShortNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isUnsignedInt(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.UnSignedIntNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isSignedInt(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.IntNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isUnsignedLong(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.UnSignedLongNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isSignedLong(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.intgerNumber.LongNumber = source_value.number.realNumber.intgerNumber.LongNumber;\
                                                                }\
                                                                else if(isSignedFloat(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.floatNumber.FloatNumber = source_value.number.realNumber.floatNumber.DoubleNumber;\
                                                                }\
                                                                else if(isSignedDouble(dest_value_type)){\
                                                                    valueinfo_object.value.number.realNumber.floatNumber.DoubleNumber = source_value.number.realNumber.floatNumber.DoubleNumber;\
                                                                }\
                                                                else if(dest_value_type & pointer_mask){\
                                                                    valueinfo_object.value.value_address = source_value.value_address;\
                                                                }\
                                                            }while(0);


#define LongTypePointer(type)       do{\
                                            file_handler << "\t.section\t\t.data.rel.local,\"aw\"" << std::endl;\
                                            file_handler << "\t.align\t" << sizeof(long) << "\n"\
                                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                            file_handler << "\t.size\t" << global.value_name << "," << sizeof(long) << std::endl;\
                                            file_handler << global.value_name << ":" << std::endl;\
                                            file_handler << "\t.quad\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define IntTypePointer(type)        do{\
                                            file_handler << "\t.section\t\t.data.rel.local,\"aw\"" << std::endl;\
                                            file_handler << "\t.align\t" << sizeof(int) << "\n"\
                                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                            file_handler << "\t.size\t" << global.value_name << "," << sizeof(int) << std::endl;\
                                            file_handler << global.value_name << ":" << std::endl;\
                                            file_handler << "\t.long\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define ShortTypePointer(type)      do{\
                                            file_handler << "\t.section\t\t.data.rel.local,\"aw\"" << std::endl;\
                                            file_handler << "\t.align\t" << sizeof(short) << "\n"\
                                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                            file_handler << "\t.size\t" << global.value_name << "," << sizeof(short) << std::endl;\
                                            file_handler << global.value_name << ":" << std::endl;\
                                            file_handler << "\t.value\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define CharTypePointer(type)       do{\
                                            file_handler << "\t.section\t\t.data.rel.local,\"aw\"" << std::endl;\
                                            file_handler << "\t.align\t" << sizeof(char) << "\n"\
                                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                            file_handler << "\t.size\t" << global.value_name << "," << sizeof(char) << std::endl;\
                                            file_handler << global.value_name << ":" << std::endl;\
                                            file_handler << "\t.byte\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define FloatTypePointer(type)      do{\
                                        file_handler << "\t.section \t\t.data.rel.local,\"aw\"" << std::endl;\
                                        file_handler << "\t.align\t" << sizeof(float) << "\n"\
                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                        file_handler << "\t.size\t" << global.value_name << "," << sizeof(float) << std::endl;\
                                        file_handler << global.value_name << ":" << std::endl;\
                                        file_handler << "\t.float\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define DoubleTypePointer(type)     do{\
                                        file_handler << "\t.section \t\t.data.rel.local,\"aw\"" << std::endl;\
                                        file_handler << "\t.align\t" << sizeof(double) << "\n"\
                                            << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                        file_handler << "\t.size\t" << global.value_name << "," << sizeof(double) << std::endl;\
                                        file_handler << global.value_name << ":" << std::endl;\
                                        file_handler << "\t.double\t" << global.value.value_address << std::endl;\
                                    }while(0);

#define isGlobalValue(type,size)    do{\
                                        file_handler << "\t.align\t" << sizeof(type) << "\n"\
                                                        << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                        file_handler << "\t.size\t" << global.value_name << "," << sizeof(type) << std::endl;\
                                        file_handler << global.value_name << ":" << std::endl;\
                                        if(global.value_type & char_mask){\
                                            file_handler << "\t." << size << "\t" << global.value.StringValue[1] - '\0'<< std::endl;\
                                        }\
                                        else if(global.value_type & (float_mask | double_mask)){\
                                            file_handler << "\t." << size << "\t" << global.value.number.realNumber.floatNumber.DoubleNumber << std::endl;\
                                        }\
                                        else\
                                            file_handler << "\t." << size << "\t" << global.value.number.realNumber.intgerNumber.IntNumber << std::endl;\
                                    }while(0);

#define ProcessPointer(_name,type,_typename)  do{\
                                                if(global.isSetValue){\
                                                    file_handler << "\t.globl\t" << global.value_name << std::endl;\
                                                    if(times == 0){\
                                                        file_handler << "\t.data" << std::endl;\
                                                        times++;\
                                                    }\
                                                    if(global.value.value_address != ""){\
                                                        _name(type)\
                                                    }\
                                                    else{\
                                                        isGlobalValue(type,_typename)\
                                                    }\
                                                }\
                                                else{\
                                                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(type) << "," << sizeof(type) \
                                                                << std::endl;\
                                                }\
                                            }while(0);

#define FillValue(_type)            do{\
                                        file_handler << "\t.align\t" << sizeof(_type) << std::endl;\
                                        file_handler << "\t.type\t" << global.value_name << ",@object" << std::endl;\
                                        file_handler << "\t.size\t" << global.value_name << "," << ElementCount*sizeof(_type) << std::endl;\
                                        file_handler << global.value_name << ":" << std::endl;\
                                    }while(0);


void CopyToNewId(const std::string idname,struct TokenValue & _valueinfo){
    auto iter = GlobalValue.begin();
    struct ValueInfo valueinfo_;
    while(iter != GlobalValue.end()){
        if(iter->value_name == idname){
            break;
        }
        iter++;
    }
    if(iter != GlobalValue.end()){
        CopyValue(iter->value_type,(*iter).value,valueinfo_)
        _valueinfo = valueinfo_.value;
    }
    else{
        std::cout << "Can not find id: " << idname << std::endl;
        exit(1);
    }
    return;
}

void WriteGlobalValue(std::ofstream &file_handler){
    file_handler << "\t.text" << std::endl;
    int times = 0;
    for(auto global:GlobalValue){
        if(     global.value_type & char_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(CharTypePointer,char,"byte")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(char)
                        for(auto body:global.block_value){
                            file_handler << "\t.byte\t" << body.StringValue[1] - '\0' << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(char) << std::endl;
                        }
                }
                else{
                    int ElementCount = 1;
                    for(auto dims:global.value.arrayinfo.dims){
                        ElementCount *= dims;
                    }
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(char) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(char,"byte")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(char) << "," << sizeof(char)
                                    << std::endl;                   
                }
            }
        }
        else if(global.value_type & short_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(ShortTypePointer,short,"value")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(short)
                        for(auto body:global.block_value){
                            file_handler << "\t.value\t" << body.number.realNumber.intgerNumber.ShortNumber << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(short) << std::endl;
                        }
                }
                else{
                    int ElementCount = 1;
                    for(auto dims:global.value.arrayinfo.dims){
                        ElementCount *= dims;
                    }
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(short) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(short,"value")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(short) << "," << sizeof(short) 
                                    << std::endl;
                }
            }
        }
        else if(global.value_type & int_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(IntTypePointer,int,"long")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(int)
                        for(auto body:global.block_value){
                            file_handler << "\t.long\t" << body.number.realNumber.intgerNumber.IntNumber << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(int) << std::endl;
                        }
                }
                else{
                    int ElementCount = 1;
                    for(auto dims:global.value.arrayinfo.dims){
                        ElementCount *= dims;
                    }
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(int) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(int,"long")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(int) << "," << sizeof(int) 
                                    << std::endl;
                }
            }
        }
        else if(global.value_type & long_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(LongTypePointer,long,"quad")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(long)
                        for(auto body:global.block_value){
                            file_handler << "\t.quad\t" << body.number.realNumber.intgerNumber.LongNumber << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(long) << std::endl;
                        }
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(long) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(long,"quad")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(long) << "," << sizeof(long) 
                                    << std::endl;
                }
            }
        }
        else if(global.value_type & float_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(FloatTypePointer,float,"float")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(float)
                        for(auto body:global.block_value){
                            file_handler << "\t.float\t" << body.number.realNumber.floatNumber.DoubleNumber << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(float) << std::endl;
                        }
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(float) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(float,"float")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(float) << "," << sizeof(float) 
                                    << std::endl;
                }
            }
        }
        else if(global.value_type & double_mask){
            if(global.value_type & pointer_mask){
                ProcessPointer(DoubleTypePointer,double,"double")
            }
            else if(global.value_type & array_mask){
                int ElementCount = 1;
                for(auto dims:global.value.arrayinfo.dims){
                    ElementCount *= dims;
                }
                if(global.isSetValue){
                        int Count = 0;
                        file_handler << "\t.globl\t" << global.value_name << std::endl;
                        if(times == 0){
                            file_handler << "\t.data" << std::endl;
                            times++;
                        }
                        FillValue(double)
                        for(auto body:global.block_value){
                            file_handler << "\t.double\t" << body.number.realNumber.floatNumber.DoubleNumber << std::endl;
                            Count++;
                        }
                        if(Count <= ElementCount){
                            file_handler << "\t.zero\t" << (ElementCount - Count)*sizeof(double) << std::endl;
                        }
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << ElementCount*sizeof(double) << "," << 32 << std::endl;
                }
            }
            else{
                if(global.isSetValue){
                    file_handler << "\t.globl\t" << global.value_name << std::endl;
                    if(times == 0){
                        file_handler << "\t.data" << std::endl;
                        times++;
                    }
                    isGlobalValue(double,"double")
                }
                else{
                    file_handler << "\t.comm\t" << global.value_name << "," << sizeof(double) << "," << sizeof(double) 
                                    << std::endl;
                }
            }
        }
    }
}

void WriteInfo(std::ofstream & assemble_file,std::string last_function){

    assemble_file << "\t.ident\t\t" << CompilerInfo << std::endl;
    assemble_file << "\t.section\t" << ".note.GNU-stack,\"\",@progbits" << std::endl;
    return ; 
}

void WriteReadOnlyData(std::ofstream &assemble_file){
    int ValueNo = 0;
    assemble_file << "\t.text" << std::endl;
    assemble_file << "\t.section\t.rodata" << std::endl;
    
    for(auto read_only_data:ReadOnlyData){
        assemble_file << ".LC" << ValueNo << ":" << std::endl;
        assemble_file << "\t.string \t" << read_only_data << std::endl;
        ValueNo++;
    }
}

void WriteFunction(std::ofstream &assemble_file){
        assemble_file << "\t.text" << std::endl;
        assemble_file << "\t.globl\t" << func_info.function_name << std::endl;
        assemble_file << "\t.type\t" << func_info.function_name << ",@function" << std::endl;
        assemble_file << func_info.function_name <<":"    << std::endl;
        assemble_file << "\tpushq   %rbp" << std::endl;
        assemble_file << "\tmovq    %rsp,%rbp" << std::endl;
        /*
            Function Block
        */
       assemble_file << "\tpopq     %rbp" << std::endl;
       assemble_file << "\tret" << std::endl;
       assemble_file << "\t.size\t" << func_info.function_name << ".-" << func_info.function_name << std::endl;
}

void WriteHeadInfo(std::ofstream &assemble_file,const std::string filename){
    if(!RunTimeTrans){
        assemble_file << "\t.file\t" << "\"" << filename << "\"" << std::endl;
        WriteGlobalValue(assemble_file);
        WriteReadOnlyData(assemble_file);
        RunTimeTrans = true;
        GlobalScopeValue = false;
    }
}



void BulidObejctCode(const std::string filename){
    if(!RunTimeTrans){
        assemble_file.open("assembel.s",std::ios_base::out);
    }

    WriteHeadInfo(assemble_file,filename);

    if(!RunTimeTrans){
        WriteReadOnlyData(assemble_file);
        WriteInfo(assemble_file,"main");
    }
}
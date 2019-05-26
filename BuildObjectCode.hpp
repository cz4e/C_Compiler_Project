#ifndef _OBJECTCODE_H
#define _OBJECTCODE_H
#endif 

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

/*void BulidObejctCode(void){
    WriteHeadInfo(filename);
    WriteGlobalValue();
    WriteFunction();
}*/
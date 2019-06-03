double c=11.3;
int main(void){
	long a = 11;
	long b = 12;
	double d  = 11.1;
	long e = 100;
	d = c;
/*	float b;
	float d;
	b = c;
	c = b;*/
}
/*
            std::string register_ = WhichRegisterFree();
                std::string XmmRegister = WhichXmmFree() ;
                std::string dest_offset_str,src_offset_str;
                getOffset(src_offset_str,value_.value_name);
                getOffset(dest_offset_str,id_name);

                if(statement_type & char_mask){
                    if(statement_type & pointer_mask){
                        ;
                    }
                    else if(statement_type & array_mask){
                        assemble_file << "\tmovzbl\t" << src_offset_str << ",\%eax"  << std::endl;
                        assemble_file << "\tmovb\t" << "\%al" << "," << dest_offset_str << std::endl;                        
                    }
                    else{
                        assemble_file << "\tmovb\t" << src_offset_str << "," << register_ << std::endl;
                        assemble_file << "\tmovb\t" << register_ << "," << dest_offset_str << std::endl;
                    }
                }
*/
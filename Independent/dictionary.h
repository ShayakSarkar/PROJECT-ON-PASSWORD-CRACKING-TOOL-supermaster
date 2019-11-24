void tryPassEnhance(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password,int hash_type);
void tryPass(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password,int hash_type);
void gen(char* dictionary_path,char* target_hashed_password,int hash_type,int enhance);
void driver();

#include <iostream>
#include <fstream>
#include <thread>
#include <fcntl.h>
#include <string.h>
#include <vector>
#include <string>

#include "../hash-library-master/md5.h"
#include "../hash-library-master/sha1.h"
#include "../hash-library-master/sha3.h"
#include "../hash-library-master/sha256.h"
#include "Rule_Applier.cpp"

using namespace std;

vector<string> hashingLibEnhance(char* unhashed_pass,int hash_type)
{	vector<string> hashed_passwords;
	string temp(unhashed_pass);
	hashed_passwords=RuleApplier(temp);

	if(hash_type==1)
	{
		for(auto it=hashed_passwords.begin();it!=hashed_passwords.end();it++)
		{	MD5 md5_obj;
			//cout<<*it<<" ";
			string ans=md5_obj.modGetHashSS(*it);
			*it=ans;
		}
		
		//cout<<endl;
		//string temp;
		//cin>>temp;
	}
	else if(hash_type==2)
	{
		for(auto it=hashed_passwords.begin();it!=hashed_passwords.end();it++)
		{	SHA1 sha1_obj;
			//cout<<*it<<" ";
			string ans=sha1_obj.modGetHashSS(*it);
			*it=ans;
		}
		//cout<<endl;
		//string temp;
		//cin>>temp;
	}
	else if(hash_type==3)
	{
		for(auto it=hashed_passwords.begin();it!=hashed_passwords.end();it++)
		{	SHA3 sha3_obj;
			//cout<<*it<<" ";
			string ans=sha3_obj.modGetHashSS(*it);
			*it=ans;
		}
		//cout<<endl;
		//string temp;
		//cin>>temp;
	}
	else 
	{
		for(auto it=hashed_passwords.begin();it!=hashed_passwords.end();it++)
		{	SHA256 sha256_obj;
			//cout<<*it<<" ";
			string ans=sha256_obj.modGetHashSS(*it);
			*it=ans;
		}
		//cout<<endl;
		//string temp;
		//cin>>temp;
	}
	return hashed_passwords;
}
	
void tryPassEnhanced(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password,int hash_type)
{
	static bool match_found=false;
	char* unhashed_password=(char*)malloc(100*1+1);
	int delta=0;		//stores the extra bytes we need to travers in order to get to the starting of the next password
	if(offset!=0)
	{	fseek(input_file_stream,offset-1,SEEK_SET);
		char *temp=(char*)malloc(1);
		*temp=' ';
		while(*temp!='\n')
		{	fread(temp,1,1,input_file_stream);
			delta++;
		}
		free(temp);
	}
	offset+=delta-1;	//updated offset marking the starting of the password from which checking is to be done
	
	fseek(input_file_stream,offset,SEEK_SET);
	cout<<"line # 91"<<endl;
	cout<<no_of_bytes<<endl;	

	for(int i=0;i<no_of_bytes;i++)
	{
		if(match_found)
		{	free(unhashed_password);
			return;
		}
		char* temp=(char*)malloc(1);
		*temp=' ';
		int j=0;

		//cout<<"line 105"<<endl;
		while(true)
		{	fread(temp,1,1,input_file_stream);
			if(*temp=='\n')	
			{	unhashed_password[j]='\0';
				break;
			}	
			unhashed_password[j]=*temp;
			j++;
		}
		free(temp);
		i+=j;
		
		//cout<<"line 117"<<endl;

		//cout<<unhashed_password<<endl;
		string temporary;
		//cin>>temporary;

		//cout<<"line 123"<<endl;
		//cin>>temporary;
		//cout<<"line 125"<<endl;
		vector<string> unhashed_passwords=RuleApplier(unhashed_password);
		
		//cout<<"echo1"<<endl;
		//cin>>temporary;
		//for(auto it = unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
		//{
			//cout<<*it<<endl;			
		//}

		//for(auto it=unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
			//cout<<*it<<" ";
		//cout<<endl;

		if(hash_type==1)
		{
			for(auto it=unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
			{
				MD5 md5_obj;
				string hashed_password=md5_obj.modGetHashSS(*it);
				if(hashed_password.compare(target_hashed_password)==0)
				{	cout<<"****************************************MATCH FOUND*****************************"<<endl;
					match_found=true;
					cout<<"The password is "<<*it<<endl;
					return;
			
				}
			}
			
		}

		else if(hash_type==2)
		{
			for(auto it=unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
			{
				SHA1 sha1_obj;
				string hashed_password=sha1_obj.modGetHashSS(*it);
				if(hashed_password.compare(target_hashed_password)==0)
				{	cout<<"****************************************MATCH FOUND*****************************"<<endl;
					match_found=true;
					cout<<"The password is "<<*it<<endl;
					return;
				}
			}
			
		}
		
		else if(hash_type==3)
		{
			for(auto it=unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
			{
				SHA3 sha3_obj;
				string hashed_password=sha3_obj.modGetHashSS(*it);
				if(hashed_password.compare(target_hashed_password)==0)
				{	cout<<"**************************************MATCH FOUND*****************************"<<endl;
					match_found=true;
					cout<<"The password is "<<*it<<endl;
					return;
				}
			}
			
		}

		else if(hash_type==4)
		{
			for(auto it=unhashed_passwords.begin();it!=unhashed_passwords.end();it++)
			{
				SHA256 sha256_obj;
				string hashed_password=sha256_obj.modGetHashSS(*it);
				if(hashed_password.compare(target_hashed_password)==0)
				{	cout<<"****************************************MATCH FOUND*****************************"<<endl;
					match_found=true;
					cout<<"The password is "<<*it<<endl;
					return;
				}
			}
			
		}
		/*
		for(auto it=hashed_passwords.begin();it!=hashed_passwords.end();it++)
			cout<<*it<<" ";
		cout<<endl;
		*/
	}
	free(unhashed_password);	
}	

string hashLib(string s,int hash_type)
{
	if(hash_type==1)
	{
		MD5 obj;
		return obj.modGetHashSS(s);
	}
	else if(hash_type==2)
	{
		SHA1 obj;
		return obj.modGetHashSS(s);
	}
	else if(hash_type==3)
	{
		SHA3 obj;
		return obj.modGetHashSS(s);
	}
	else 
	{
		SHA256 obj;
		return obj.modGetHashSS(s);
	}
	return "";
}


int tryPass(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password,int hash_type)
{
	static bool match_found=false;
	char* hashed_password=(char*)malloc(100*1+1);
	int delta=0;		//stores the extra bytes we need to travers in order to get to the starting of the next password
	if(offset!=0)
	{	fseek(input_file_stream,offset-1,SEEK_SET);
		char *temp=(char*)malloc(1);
		*temp=' ';
		while(*temp!='\n')
		{	fread(temp,1,1,input_file_stream);
			delta++;
		}
		free(temp);
	}
	offset+=delta-1;	//updated offset marking the starting of the password from which checking is to be done
	
	fseek(input_file_stream,offset,SEEK_SET);
	cout<<"offset set"<<endl;

	for(int i=0;i<no_of_bytes;i++)
	{
		int return_value=i;
		if(match_found)
		{	free(hashed_password);
			return -1;
		}
		char* temp=(char*)malloc(1);
		*temp=' ';
		int j=0;
		while(true)
		{	fread(temp,1,1,input_file_stream);
			if(*temp=='\n')	
			{	hashed_password[j]='\0';
				break;
			}	
			hashed_password[j]=*temp;
			j++;
		}
		i+=j;
		free(temp);
		//cout<<hashed_password<<endl;
		//string temporary;
		//cin>>temporary;
		string s_hashed_password(hashed_password);
		s_hashed_password=hashLib(hashed_password,hash_type);
		if(s_hashed_password.compare(target_hashed_password)==0)
		{
			cout<<"*************************************************Match found**************************************"<<endl;
			match_found=true;
			cout<<hashed_password<<endl;
			free(hashed_password);
			return return_value;
		}
		//cout<<hashed_password<<endl;
		//cin>>temp;
	}
	free(hashed_password);
	return -1;
}	
	
string getPassword(int line_number)
{
	int fd=open("../data/dictionary/common#password.txt",0);
	FILE* fstr=fdopen(fd,"r");
	char* temp=(char*)malloc(sizeof(char));
	string pass;
	char* s_line_number=(char*)malloc(sizeof(char)*100);
	int i_line_number=0;
	int read=1;
	int j=0;
	while(read!=0)
	{
		fread(temp,1,1,fstr);
		if(*temp==' ')
		{
			i_line_number=stoi(s_line_number);
			if(i_line_number==line_number)
			{	*temp=' ';
				while(*temp!='\n')
				{
					fread(temp,1,1,fstr);
					pass=pass+*temp;
				}
				return pass;
			}
		}
		s_line_number[j]=*temp;
		j++;
	}
	return "";			
}
int tryPassRainbow(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password,int hash_type)
{
	static bool match_found=false;
	char* hashed_password=(char*)malloc(100*1+1);
	char* line_number=(char*)malloc(100*1+1);
	
	int delta=0;		//stores the extra bytes we need to travers in order to get to the starting of the next password
	if(offset!=0)
	{	fseek(input_file_stream,offset-1,SEEK_SET);
		char *temp=(char*)malloc(1);
		*temp=' ';
		while(*temp!='\n')
		{	fread(temp,1,1,input_file_stream);
			delta++;
		}
		free(temp);
	}
	offset+=delta-1;	//updated offset marking the starting of the password from which checking is to be done
	
	fseek(input_file_stream,offset,SEEK_SET);
	cout<<"offset set"<<endl;
	
	for(int i=0;i<no_of_bytes;i++)
	{
		int return_value=i;
		if(match_found)
		{	free(hashed_password);
			return -1;
		}
		char* temp=(char*)malloc(1);
		*temp=' ';
		int j=0;
		
		while(true)
		{	fread(temp,1,1,input_file_stream);
			if(*temp==' ')	
			{	hashed_password[j]='\0';
				j++;
				break;
			}	
			line_number[j]=*temp;
			j++;
		}
		i+=j;
		j=0;
		while(true)
		{	fread(temp,1,1,input_file_stream);
			if(*temp=='\n')	
			{	hashed_password[j]='\0';
				j++;
				break;
			}	
			hashed_password[j]=*temp;
			j++;
		}
		i+=j;
		free(temp);
		//cout<<hashed_password<<endl;
		//string temporary;
		//cin>>temporary;
		string s_hashed_password(hashed_password);
		s_hashed_password=hashLib(hashed_password,hash_type);
		if(s_hashed_password.compare(target_hashed_password)==0)
		{
			cout<<"*************************************************Match found**************************************"<<endl;
			match_found=true;
			cout<<line_number<<endl;
			getPassword(stoi(line_number));
			free(hashed_password);
			return return_value;
		}
		//cout<<hashed_password<<endl;
		//cin>>temp;
	}
	free(hashed_password);
	return -1;
}	
void gen(char* dictionary_path,char* target_hashed_password,int hash_type,int enhance,int is_rainbow)	 // dictionary [input file path]
{
	char* destination_buffer1=(char*)malloc(300*1+1);
	char* destination_buffer2=(char*)malloc(300*1+1);
	char* destination_buffer3=(char*)malloc(300*1+1);
	char* destination_buffer4=(char*)malloc(300*1+1);
	char* size_in_string;					//Size of the dictionary got by executing GetFileInfo.py
	int fd_input1,fd_input2,fd_input3,fd_input4;		//file descriptors corresponding to four different copies of the same dict 
	int size,interval;				//interval is the number of passwords to be checked by a thread
	int fd_size_file=open("temp.txt",0);
	
	FILE *input_file_stream1,*input_file_stream2,*input_file_stream3,*input_file_stream4;
	FILE *fstr;
	//cout<<"hello"<<endl;
	cout<<dictionary_path<<endl;
	fd_input1=open(dictionary_path,0);
	fd_input2=open(dictionary_path,0);
	fd_input3=open(dictionary_path,0);
	fd_input4=open(dictionary_path,0);
	
	fstr=fdopen(fd_size_file,"r");
	
	input_file_stream1=fdopen(fd_input1,"r");
	input_file_stream2=fdopen(fd_input2,"r");
	input_file_stream3=fdopen(fd_input3,"r");
	input_file_stream4=fdopen(fd_input4,"r");
	
	cout<<"Echo1"<<endl;
	size_in_string=(char*)malloc(100*1);
	int i=0;
	for(i=0;i<100;i++)
	{
		fread(size_in_string+i,1,1,fstr);
		cout<<size_in_string[i]<<endl;
		if(size_in_string[i]==':')
		{	size_in_string[i]='\0';
			break;
		}
	}	
	if(i==100)
	{	cout<<"Sorry file size is larger than permissible"<<endl;
		return ;
	}
	cout<<endl;
	cout<<size_in_string<<endl;	
	
	size=stoi(size_in_string);	
	
	string s;
	cin>>s;
	
	interval=size/4;
	cout<<"Echo2"<<endl;	
	if(is_rainbow)
	{
		thread th1(tryPass,input_file_stream1,0,interval,destination_buffer1,target_hashed_password,hash_type);
		thread th2(tryPass,input_file_stream2,1*interval,interval,destination_buffer2,target_hashed_password,hash_type);
		thread th3(tryPass,input_file_stream3,2*interval,interval,destination_buffer3,target_hashed_password,hash_type);
		thread th4(tryPass,input_file_stream4,3*interval,interval,destination_buffer4,target_hashed_password,hash_type);
	
		th1.join();th2.join();th3.join();th4.join();
	}
	else if(enhance==0)
	{	thread th1(tryPass,input_file_stream1,0,interval,destination_buffer1,target_hashed_password,hash_type);
		thread th2(tryPass,input_file_stream2,1*interval,interval,destination_buffer2,target_hashed_password,hash_type);
		thread th3(tryPass,input_file_stream3,2*interval,interval,destination_buffer3,target_hashed_password,hash_type);
		thread th4(tryPass,input_file_stream4,3*interval,interval,destination_buffer4,target_hashed_password,hash_type);
	
		th1.join();th2.join();th3.join();th4.join();
	}
	else
	{	thread th1(tryPassEnhanced,input_file_stream1,0,interval,destination_buffer1,target_hashed_password,hash_type);
		thread th2(tryPassEnhanced,input_file_stream2,1*interval,interval,destination_buffer2,target_hashed_password,hash_type);
		thread th3(tryPassEnhanced,input_file_stream3,2*interval,interval,destination_buffer3,target_hashed_password,hash_type);
		thread th4(tryPassEnhanced,input_file_stream4,3*interval,interval,destination_buffer4,target_hashed_password,hash_type);
	
		th1.join();th2.join();th3.join();th4.join();
	}
	free(destination_buffer1);free(destination_buffer2);free(destination_buffer3);free(destination_buffer4);
	fclose(input_file_stream1);fclose(input_file_stream2);fclose(input_file_stream3);fclose(input_file_stream4);
	fclose(fstr);
	free(size_in_string);	
		
}
void driver()
{
	char* target_hashed_password=(char*)malloc(300);
	char* path=(char*)malloc(300);
	char* dict_name=(char*)malloc(100);
	char* cmd=(char*)malloc(300);
	int is_rainbow;
	int hash_type,enhance;
	cout<<"Do you want to do a rainbow attack (1/0): ";
	cin>> is_rainbow;
	cout<<"Enter the hashing type: \n1)MD5\n2)SHA1\n3)SHA3\n4)SHA256\nEnter your choice: ";
	cin>>hash_type;
	cout<<"Do you want to enhance the dictionary on the basis of rules available in the RuleBook? (1/0): ";
	cin>>enhance;
	cout<<"Enter the hashed password whose plaintext is to be found"<<endl;
	cin>>target_hashed_password;
	cout<<"Enter the dictionay name: ";
	cin>>dict_name;				//In case of using a rainbow table enter the name as <hashtype-dir>/filename
	sprintf(path,"/home/shayak/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-supermaster/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/%s",dict_name);
	cout<<"Path is \n"<<path<<endl<<endl;
	sprintf(cmd,"python3 /home/shayak/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-supermaster/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/headers/GetFileInfo.py %s",path);
	system(cmd);
	gen(path,target_hashed_password,hash_type,enhance,is_rainbow);
	free(path);free(dict_name);free(cmd);
}
int main()
{
	driver();
	return 0;
}

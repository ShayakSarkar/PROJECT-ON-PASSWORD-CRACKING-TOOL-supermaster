#include<iostream>
#include<fstream>
#include <thread>
#include <fcntl.h>

using namespace std;

void tryPass(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer)
{
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
	}
	offset+=delta;	//updated offset marking the starting of the password from which checking is to be done
	for(int i=0;i<no_of_bytes;i++)
	{
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
		cout<<hashed_password<<endl;
	}
				
}	
	
	
int main(int argc,char** argv)		// dictionary [input file path]
{
	char* destination_buffer1=(char*)malloc(100*1+1);
	char* destination_buffer2=(char*)malloc(100*1+1);
	char* destination_buffer3=(char*)malloc(100*1+1);
	char* destination_buffer4=(char*)malloc(100*1+1);
	char* size_in_string;
	
	int fd_input1,fd_input2,fd_input3,fd_input4;
	int size,interval;
	int fd_size_file=open("temp.txt",0);
	
	FILE *input_file_stream1,*input_file_stream2,*input_file_stream3,*input_file_stream4;
	FILE *fstr;
	cout<<"hello"<<endl;
	cout<<argv[1]<<endl;
	fd_input1=open(argv[1],0);
	fd_input2=open(argv[1],0);
	fd_input3=open(argv[1],0);
	fd_input4=open(argv[1],0);
	
	fstr=fdopen(fd_size_file,"r");
	
	input_file_stream1=fdopen(fd_input1,"r");
	input_file_stream2=fdopen(fd_input2,"r");
	input_file_stream3=fdopen(fd_input3,"r");
	input_file_stream4=fdopen(fd_input4,"r");
	
	size_in_string=(char*)malloc(100*1);
	int i=0;
	for(i=0;i<100;i++)
	{
		fread(size_in_string+i,1,1,fstr);
		cout<<size_in_string[i];
		if(size_in_string[i]==':')
		{	size_in_string[i]='\0';
			break;
		}
	}	
	if(i==100)
	{	cout<<"Sorry file size is larger than permissible"<<endl;
		return 1;
	}
	cout<<endl;
	cout<<size_in_string<<endl;	
	
	size=stoi(size_in_string);	
	
	string s;
	cin>>s;
	
	interval=size/4;
	
	thread th1(tryPass,input_file_stream1,0,interval,destination_buffer1);
	thread th2(tryPass,input_file_stream2,1*interval,interval,destination_buffer2);
	thread th3(tryPass,input_file_stream3,2*interval,interval,destination_buffer3);
	thread th4(tryPass,input_file_stream4,3*interval,interval,destination_buffer4);
	
	th1.join();th2.join();th3.join();th4.join();
	
	free(destination_buffer1);free(destination_buffer2);free(destination_buffer3);free(destination_buffer4);
	fclose(input_file_stream1);fclose(input_file_stream2);fclose(input_file_stream3);fclose(input_file_stream4);
	fclose(fstr);
	free(size_in_string);		
}

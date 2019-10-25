#include <iostream>
#include <thread>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

char* trimLeft(char* arr,int l,int pointer)
{
	char* string=(char*)malloc((pointer+1)*sizeof(char));
	string=&arr[l-pointer];
	string[pointer]='\0';		
	return string;	
}		

int increment(char* arr,int l,int low, int high)	//returns the length of the current password
{
	int i=l-1;
	int length=0;
	while(arr[i]==high)
	{	arr[i]=(char)low;
		i--;
		length++;
	}
	if(arr[i]==' ')
		arr[i]=(char)low;
	else
		arr[i]=(char)(arr[i]+1);
	while(arr[i]!=' ')
	{	i--;
		length++;
	}
	return length;	
}			
void printArray(char* arr,int l)
{	for(int i=0;i<l;i++)
		cout<<arr[i];
}
char* realign(char* buf,int l,int no_of_fields)	//Realigns the buf towards the right so that the increment fucntion can work on it properly.
{	char* temp=(char*)malloc(l+1*sizeof(char));	
	for(int i=0;i<l;i++)
		temp[(l-no_of_fields+i)%l]=buf[i];
	temp[l]='\0';
	buf=temp;	
	return buf;
}				
void gen(char* destination_buffer,int max_size,int starting_password_number,int ending_password_number,int low,int high)	//tries password by 														 utting it in  destination_buffer(which may be target) whose maximum size is max_size  
																		
{	
	//SEGMENT FOR DETERMINING THE STARTING PASSWORD
	
	double temp=log(starting_password_number)/log(high-low+1);
	char index[max_size];
	char* starting_password;
	char* ending_password;	
	for(int i=0;i<max_size;i++)
		index[i]=' ';
	int no_of_fields=(int)(log(starting_password_number)/log(high-low+1))+1;
	starting_password_number-=pow((high-low+1),no_of_fields-1)+1;
	for(int i=0;i<no_of_fields;i++)
	{	int temp=(((starting_password_number+1)/(int)pow((high-low+1),i))%(high-low+1))+low;
		index[no_of_fields-1-i]=(char)temp;
	}
	starting_password=index;
	starting_password=realign(starting_password,max_size,no_of_fields);
	
	
	//SEGMENT FOR DETERMINING THE ENDING PASSWORD
	
	temp=log(ending_password_number)/log(high-low+1);	
	
	for(int i=0;i<max_size;i++)
		index[i]=' ';
	
	no_of_fields=(int)(log(ending_password_number)/log(high-low+1))+1;
	ending_password_number-=pow((high-low+1),no_of_fields-1)+1;
	
	for(int i=0;i<no_of_fields;i++)
	{	int temp=(((ending_password_number+1)/(int)pow((high-low+1),i))%(high-low+1))+low;
		index[no_of_fields-1-i]=(char)temp;
	}
	
	ending_password=index;
	ending_password=realign(ending_password,max_size,no_of_fields);
	
	//int fd=open(file_path,1);
	//FILE* fstr=fdopen(fd,"w");
	for(int i=0;strcmp(starting_password,ending_password)!=0;i++)
	{	
		int pointer=increment(starting_password,max_size,low,high);
		destination_buffer=trimLeft(starting_password,max_size,pointer);
		//cout<<destination_buffer<<endl;
		//fwrite(destination_buffer,sizeof(char),max_size,fstr);
		//char* p=(char*)malloc(sizeof(char));
		//p[0]='\n';
		//fwrite(p,sizeof(char),sizeof(char),fstr);
	}
	
}

void multiThread(char* file_path)
{	char *buf1,*buf2,*buf3,*buf4;
	int no,low,high;
	cout<<"Enter the number of passwords: ";
	cin>>no;
	cout<<"Enter the lower limit of charset: ";
	cin>>low;
	cout<<"Enter the higher limit of the charset: ";
	cin>>high;
	int interval=(no-0)/4;
	thread th1(gen,buf1,10,1,1+interval,low,high);
	thread th2(gen,buf2,10,1+interval,1+2*interval,low,high);
	thread th3(gen,buf3,10,1+2*interval,1+3*interval,low,high);
	thread th4(gen,buf4,10,1+3*interval,1+4*interval,low,high);
	th1.join();th2.join();th3.join();th4.join();
}
int main()
{
	char* file_path=(char*)malloc(1*10);
	multiThread(file_path);
}


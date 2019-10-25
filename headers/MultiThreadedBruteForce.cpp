#include <iostream>
#include <thread>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "../hash-library-master/md5.h"
#include "../hash-library-master/sha1.h"
#include "../hash-library-master/sha256.h"
#include "../hash-library-master/sha3.h"

using namespace std;

char* trimLeft(char* arr,int l,int pointer)
{
	static char *temp;
	free(temp);
	char* string=(char*)malloc((pointer+1)*sizeof(char));
	temp=string;
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
string hashLib(char* destination_buffer,int hash_type)
{	if(hash_type==1)
	{	MD5 md5_obj;
		string temp(destination_buffer);
		string ans=md5_obj.modGetHashSS(temp);
		return ans;
	}
	else if(hash_type==2)
	{
		SHA1 sha1_obj;
		string temp(destination_buffer);
		string ans=sha1_obj.modGetHashSS(temp);
		return ans;
	}
	else if(hash_type==3)
	{
		SHA3 sha3_obj;
		string temp(destination_buffer);
		string ans=sha3_obj.modGetHashSS(temp);
		return ans;
	}
	else 
	{
		SHA256 sha256_obj;
		string temp(destination_buffer);
		string ans=sha256_obj.modGetHashSS(temp);
		return ans;
	}
	return NULL;	
}
void gen(char* destination_buffer,int max_size,long int starting_password_number,long int ending_password_number,int low,int high,char* target_hashed_password,int hash_type)	//tries password by putting it in  destination_buffer(which may be target) whose maximum size is max_size  
																		
{	
	static bool match_found=false;
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
	
	for(int i=0;strcmp(starting_password,ending_password)!=0;i++)
	{	
		if(match_found)
			return;
		int pointer=increment(starting_password,max_size,low,high);
		destination_buffer=trimLeft(starting_password,max_size,pointer);
		string hashed_destination_buffer=hashLib(destination_buffer,hash_type);
		//cout<<destination_buffer<<" == ";
		//cout<<hashed_destination_buffer<<endl;
		//string temp_inp;
		//cin>>temp_inp;
		if(hashed_destination_buffer.compare(target_hashed_password)==0)
		{	match_found=true;	
			
			cout<<"************************************************match found********************************************"<<endl;
			cout<<"reqd pass: "<<destination_buffer<<endl;
			return;
		}

	}
	
}

void multiThread()
{	char *buf1,*buf2,*buf3,*buf4,*target_hashed_password;
	target_hashed_password=(char*)malloc(200);
	long int no;
	int hash_type,low,high;
	cout<<"Enter the hashed password whose plaintext is to be found"<<endl;
	cin>>target_hashed_password;
	cout<<"Enter the number of passwords: ";
	cin>>no;
	cout<<"Enter the lower limit of charset: ";
	cin>>low;
	cout<<"Enter the higher limit of the charset: ";
	cin>>high;
	cout<<"Enter the type of hashing: "<<endl<<"1) MD5\n2) SHA3 \n3)SHA1 \n4)SHA256\nEnter your choice: ";
	cin>>hash_type;	
	long int interval=(no-0)/4;
	thread th1(gen,buf1,10,1,1+interval,low,high,target_hashed_password,hash_type);
	thread th2(gen,buf2,10,1+interval,1+2*interval,low,high,target_hashed_password,hash_type);
	thread th3(gen,buf3,10,1+2*interval,1+3*interval,low,high,target_hashed_password,hash_type);
	thread th4(gen,buf4,10,1+3*interval,1+4*interval,low,high,target_hashed_password,hash_type);
	th1.join();th2.join();th3.join();th4.join();
}

int main()
{
	multiThread();
	return 0;
}

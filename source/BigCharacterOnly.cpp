#include <iostream>

using namespace std;

char* printArray(char* arr,int l,int pointer)
{
	char* string=(char*)malloc((pointer+1)*sizeof(char));
	string=&arr[l-pointer];
	int j=0;	
	
	string[pointer]='\0';		
	return string;	
}		

int increment(char* arr,int l)	//returns the length of the current password
{
	int i=l-1;
	int length=0;
	while(arr[i]==90)
	{	arr[i]=(char)65;
		i--;
		length++;
	}
	if(arr[i]==' ')
		arr[i]=(char)65;
	else
		arr[i]=(char)(arr[i]+1);
	while(arr[i]!=' ')
	{	i--;
		length++;
	}
	return length;	
}			
	
void gen(char* destination_buffer,int max_size)	//tries password by putting it in  destination_buffer(which may be target) whose maximum size is max_size	
{	
	char index[max_size];
	for(int i=0;i<max_size;i++)
		index[i]=' ';
	for(int i=0;i<=26*26*26*26*26;i++)
	{	int pointer=increment(index,max_size);
		destination_buffer=printArray(index,max_size,pointer);
		cout<<destination_buffer<<endl;
	}
}
int main()
{	char* buf;	
	gen(buf,10);
}	
		
	

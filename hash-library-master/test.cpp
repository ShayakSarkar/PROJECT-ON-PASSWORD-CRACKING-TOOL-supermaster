#include <iostream>
#include "md5.cpp"
#include <string.h>
#include <string>

using namespace std;

int main()
{
	cout<<"Hello World"<<endl;
	char* destination_buffer=(char*)malloc(100);
	strcpy(destination_buffer,"How are you??");
	MD5 obj;
	string temp(destination_buffer);
	string s=obj.modGetHashSS(temp);
	cout<<s<<endl;
}

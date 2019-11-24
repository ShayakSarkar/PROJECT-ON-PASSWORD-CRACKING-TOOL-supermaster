#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

void genPass(char* destination_buffer)	//Desinaion buffer stores the location where the password is to tried
{	int ctr=1;
	int power=1;	
	for(int i=0;i<10000000;i++)
	{	ostringstream s;
		s<<i;
		string temp=s.str();
		if(ctr-1==pow(10,power))
		{	power++;
			for(int i=0;i<power;i++)
				destination_buffer[i]='0';
			cout<<destination_buffer<<endl;
			i--;
			continue;
			ctr++;
		}		
		for(int i=0;i<temp.length();i++)
			destination_buffer[i]=temp.at(i);
		cout<<destination_buffer<<endl;
		ctr++;
	}
}
int main()
{	char* dest=(char*)malloc(sizeof(char));	
	genPass(dest);
}
	
	
	

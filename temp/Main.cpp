#include <iostream>
#include "source/MultiThreadedBruteForce.cpp"
#include "source/ErrorHandler.cpp" 
#include <map>

using namespace std;

int main(int argc,char** argv)
{
	//cout<<"hello"<<endl;
   	// format for the tool
   	// [toolname] [-filetype] [filepath] [...added options...]		
   	
   	
   	int status=0,file_type,attack_type;	//file_type: stores an integer based on the string supplied as command line argument which is used as 											switching variable. attack_type: stores an integer based on the string supplied for attack_method
   	char* file_path;			
   	map<string,int>file_map;	//Maps file type to integer value
   	map<string,int>attack_map;	//Maps attack type to integer
   	
   	
   	if(argc<3)
   	status=1;
   	if(status!=0)
    {	cout<<"Too few arguments"<<endl;
   		return -1;
   	}
   	
   	file_map["--pdf"]=1;			//Pdf file is to be cracked
   	file_map["--wd"]=2;				//Word document is to be cracked	
   	file_map["--eacc"]=3;			//Email account is to be cracked
   	file_map["--usracc"]=4;			//User acount is to be cracked
   	file_map["--fbacc"]=5;			//Facebook account is to be cracked
   	
   	attack_map["--mbf"]=1;			//maps to multi thread brute force
   	attack_map["--method2"]=2;	
   	attack_map["--method3"]=3;
   	attack_map["--method4"]=4;
   

   	file_type=file_map[argv[1]];
   	file_path=argv[2];
   	if(attack_map.count(argv[3])==0)
   	{ 	cout<<"Sorry wrong method"<<endl;
   		return -1;
   	}		
   	attack_type=attack_map[argv[3]];
 	    
	switch(file_type)
	{
		case 1: cout<<"This is a pdf"<<endl;
				switch(attack_type)
				{
					case 1: cout<<"Multithreaded approach selected: "<<endl;
							multiThread(file_path);
							break;
							
					case 2: cout<<"Method 2 has been selected: "<<endl;
							break;
					
					case 3: cout<<"Method 3 has been selected: "<<endl;
							break;
						
					case 4: cout<<"Method 4 has been selected: "<<endl;
							break;
					
					case 5: cout<<"Method 5 has been selected: "<<endl;
							break;
							
					default:cout<<"Wrong choice of method sorry :("<<endl;
				}
				break;
		case 2: cout<<"This is a word document"<<endl;
				switch(attack_type)
				{
					case 1: cout<<"Multithreaded approach selected: "<<endl;
							multiThread(file_path);
							break;
							
					case 2: cout<<"Method 2 has been selected: "<<endl;
							break;
					
					case 3: cout<<"Method 3 has been selected: "<<endl;
							break;
						
					case 4: cout<<"Method 4 has been selected: "<<endl;
							break;
					
					case 5: cout<<"Method 5 has been selected: "<<endl;
							break;
							
					default:cout<<"Wrong choice of method sorry :("<<endl;
				}
				break;	
						
		case 3: cout<<"This is email account: "<<endl;
				switch(attack_type)
				{
					case 1: cout<<"Multithreaded approach selected: "<<endl;
							multiThread(file_path);
							break;
							
					case 2: cout<<"Method 2 has been selected: "<<endl;
							break;
					
					case 3: cout<<"Method 3 has been selected: "<<endl;
							break;
						
					case 4: cout<<"Method 4 has been selected: "<<endl;
							break;
					
					case 5: cout<<"Method 5 has been selected: "<<endl;
							break;
							
					default:cout<<"Wrong choice of method sorry :("<<endl;
				}
				break;					
							
		case 4: cout<<"This is a user account: "<<endl;
				switch(attack_type)
				{
					case 1: cout<<"Multithreaded approach selected: "<<endl;
							multiThread(file_path);
							break;
							
					case 2: cout<<"Method 2 has been selected: "<<endl;
							break;
					
					case 3: cout<<"Method 3 has been selected: "<<endl;
							break;
						
					case 4: cout<<"Method 4 has been selected: "<<endl;
							break;
					
					case 5: cout<<"Method 5 has been selected: "<<endl;
							break;
							
					default:cout<<"Wrong choice of method sorry :("<<endl;
				}
				break;					
		
		case 5: cout<<"This is facebook account: "<<endl;
				switch(attack_type)
				{
					case 1: cout<<"Multithreaded approach selected: "<<endl;
							multiThread(file_path);
							break;
							
					case 2: cout<<"Method 2 has been selected: "<<endl;
							break;
					
					case 3: cout<<"Method 3 has been selected: "<<endl;
							break;
						
					case 4: cout<<"Method 4 has been selected: "<<endl;
							break;
					
					case 5: cout<<"Method 5 has been selected: "<<endl;
							break;
							
					default:cout<<"Wrong choice of method sorry :("<<endl;
				}
				break;					
		default:cout<<"Sorry file type selected is wrong :( "<<endl;
	}
}



 


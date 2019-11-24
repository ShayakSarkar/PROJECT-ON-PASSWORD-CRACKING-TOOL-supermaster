
import os;
import hashlib

fl=open("../data/dictionary/common#password.txt","r")
inp="c"
ctr=0;
while(inp!=""):
	inp=fl.readline();
	inp=inp[0:len(inp)-1]
	inp=hashlib.md5(inp.encode())
	print(ctr,inp.hexdigest())
	ctr+=1
	#input()
	
	

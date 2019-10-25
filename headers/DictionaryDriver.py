import os
import sys
import time

hashing_type=0

print("Enter the type of hashing you want to apply to the passwords: \n1)MD5\n2)SHA1\n3)SHA256:")

try:
	hashing_type=int(input())
except Exception:
	print("Sorry wrong choice of hashing type: ")
	exit()	

if hashing_type==1:
	l=list(os.walk("/home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master(1)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputMD5"))
	input_files=l[0][2]
	for i in input_files:
		os.system(("python3 ./GetFileInfo.py /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputMD5/"+i))
		os.system(("./a.out /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputMD5/"+i))

elif hashing_type==2:
	l=list(os.walk("/home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master(1)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA1"))
	input_files=l[0][2]
	for i in input_files:
		os.system(("python3 ./GetFileInfo.py /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA1/"+i))
		os.system(("./a.out /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA1/"+i))
		
elif hashing_type==3:
	l=list(os.walk("/home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master(1)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA256"))
	input_files=l[0][2]
	for i in input_files:
		os.system(("python3 ./GetFileInfo.py /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA256/"+i))
		os.system(("./a.out /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-master\(1\)/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/OutputSHA256/"+i))
		
else:
	print("Sorry Wrong choice of hashing type")
	

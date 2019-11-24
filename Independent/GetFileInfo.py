import os
import sys
info=os.stat(sys.argv[1])
print(info)
FILE=open('temp.txt','w')
FILE.write(str(info.st_size))
FILE.write(":")
FILE.close()




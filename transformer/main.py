import os
import sys
from transformer import transform
from cutter import cut
from rebuilder import rebuild
from combiner import combine

dirPath=sys.argv[1]
baseName=sys.argv[2]
fileName=sys.argv[3]
num = int(sys.argv[4])
sys.argv=[]
filePath=os.path.join(dirPath,baseName,fileName)
headPath=os.path.join(dirPath,baseName,'head.png')
srcPath=os.path.join(dirPath,baseName,'src')
targetPath=os.path.join(dirPath,baseName,'target')
resultPath=os.path.join(dirPath,baseName,'result.gif')

left,top=cut(filePath,headPath)
# cutter

if(not os.path.exists(srcPath)):
	os.mkdir(srcPath)
transform(num,headPath,srcPath)
# transformer


if(not os.path.exists(targetPath)):
	os.mkdir(targetPath)
rebuild(num,left,top,filePath,srcPath,targetPath)
# rebuilder


combine(num,targetPath,resultPath)
# combine
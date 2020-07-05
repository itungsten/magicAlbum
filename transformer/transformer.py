def transform(num,infile,outfile,ausPath):
	import ganimation.gan as gan
	gan.test(num,infile,outfile,ausPath)

if __name__=='__main__':
	transform(10,'./head.png','./src','')
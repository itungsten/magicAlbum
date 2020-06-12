def transform(num,infile,outfile):
	import ganimation.gan as gan
	gan.test(num,infile,outfile)

if __name__=='__main__':
	transform('D:/magicAlbum/warehouse/person/head.png','D:/magicAlbum/warehouse/person/src')
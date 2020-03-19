from PIL import Image
def resize(sz=224,infile='D:/magicAlbum/sharePool/poster/poster.png',outfile='D:/magicAlbum/sharePool/poster/poster.png'):
    im = Image.open(infile)
    out = im.resize((sz, sz))
    out.save(outfile)
if __name__=='__main__':
	resize()
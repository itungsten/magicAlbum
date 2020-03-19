from PIL import Image
def resize(infile='D:/magicAlbum/sharePool/poster/poster.png'):
    outfile='D:/magicAlbum/sharePool/poster/poster.png'
    im = Image.open(infile)
    out = im.resize((224, 224))
    out.save(outfile)
if __name__=='__main__':
	resize()
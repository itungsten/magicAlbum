from PIL import Image
def resize(infile='poster.png'):
    outfile='new'+infile
    im = Image.open(infile)
    out = im.resize((224, 224))
    out.save(outfile)
if __name__=='__main__':
	resize()
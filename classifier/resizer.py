from PIL import Image
from main import test
def resize(infile='D:/magicAlbum/sharePool/poster/poster.png'):
    outfile='D:/magicAlbum/sharePool/poster/poster.png'
    im = Image.open(infile)
    out = im.resize((224, 224))
    out.save(outfile)
    # print(test())
    return test()
if __name__=='__main__':
	resize()
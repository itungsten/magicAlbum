# from transformer import transform
def trans(top,bottom,left,right,width,height):
    lists=[]
    for i in range(128,504,4):
        lists.append(i)
    # print(lists)
    #竖向
    dis=bottom-top
    target=dis
    for item in lists:
        # print(dis,item)
        if(dis<=item):
            dis=item-target
            target=item
            print('the item is ',item)
            break
    # 对于没有找到的情况我也没办法

    top=top-int(dis/2)
    bottom=bottom+int(dis/2)
    if((bottom-top)!=target):
        top=top-1
    #修改到指定大小
    
    #超出范围，则平移
    if(top<0):
        bottom=bottom-top
        top=0
    if(bottom>height):
        top=top-(bottom-height)
        bottom=height

    #对于横向
    dis=right-left
    target=dis
    for item in lists:
        # print(dis,item)
        if(dis<=item):
            dis=item-target
            target=item
            # print('the item is ',item)
            break
    #对于没有找到的情况我也没办法
    
    left=left-int(dis/2)
    right=right+int(dis/2)
    if((right-left)!=target):
        left=left-1
    #修改到指定大小

    #超出范围，则平移
    if(left<0):
        right=right-left
        left=0
    if(right>width):
        left=left-(right-width)
        right=width
    return (top,bottom,left,right)


def cut(input,output):
    from PIL import Image
    import face_recognition
    import cv2
    # Load the jpg file into a numpy array
    image = face_recognition.load_image_file(input)
    x=image.shape[0]
    y=image.shape[1]
     
    # Find all the faces in the image using the default HOG-based model.
    # This method is fairly accurate, but not as accurate as the CNN model and not GPU accelerated.
     
    face_locations = face_recognition.face_locations(image, number_of_times_to_upsample=0, model="cnn")
    for face_location in face_locations:
     
        top, right, bottom, left = face_location
        # print(top,bottom,left,right)

        d_dep=int((bottom-top));
        d_wid=int((right-left));
        top=int(top-d_dep*0.2)
        bottom=int(bottom+d_dep*0.2)
        right=int(right+d_wid*0.2)
        left=int(left-d_wid*0.15)
        # 这一块代码，对于人脸占比不是太大的图片来说有用，对于训练集的图片会导致负数错误

 
        # print(top,bottom,left,right)
        (top,bottom,left,right)=trans(top,bottom,left,right,x,y)
        # print(top,bottom,left,right)

        face_image = image[top:bottom, left:right]
        pil_image = Image.fromarray(face_image)
        #pil_image.show()
        pil_image.save(output)

        return (left,top)

if __name__=='__main__':
    cut("000058.jpg","head.png")
    # ausList=[0.0,0.0,0.0, 0.4,1.31,0.0 ,0.08 ,0.7 ,2.18,0.75,0.0 , 0.08 ,0.16 ,0.0 ,1.25,0.73 ,0.0]
    # transform(2,'D:/magicAlbum/transformer/head.png','D:/magicAlbum/transformer/src','D:/magicAlbum/warehouse/loli/aus.pkl',ausList)
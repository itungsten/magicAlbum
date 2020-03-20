def cut(input,output):
    from PIL import Image
    import face_recognition
    import cv2
    # Load the jpg file into a numpy array
    image = face_recognition.load_image_file(input)
     
    # Find all the faces in the image using the default HOG-based model.
    # This method is fairly accurate, but not as accurate as the CNN model and not GPU accelerated.
     
    face_locations = face_recognition.face_locations(image, number_of_times_to_upsample=0, model="cnn")
     
    for face_location in face_locations:
     
        top, right, bottom, left = face_location
        d_dep=int((bottom-top)/3);
        d_wid=int((right-left)/4);
        top=int(top-d_dep*1.3)
        right=int(right+d_wid*1.4)
        left=int(left-d_wid*0.6)
        bottom=int(bottom+d_dep)
        face_image = image[top:bottom, left:right]

        pil_image = Image.fromarray(face_image)
        #pil_image.show()
        pil_image.save(output)

        return (left,top)

if __name__=='__main__':
    cut("D:/magicAlbum/sharePool/person.png","D:/magicAlbum/sharePool/head.png")
import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms as T
from PIL import Image
import os
from option import opt
from dataloader import getTrainDataLoader,getTestDataLoader
from models import AlexNet

def train(**kwargs):
	opt._parse(kwargs)
	trainLoader=getTrainDataLoader(opt)
	model=AlexNet(opt)
	criterion=t.nn.CrossEntropyLoss()
	optimizer=model.getOptimizer(opt.lr,opt.weight_decay)

	if(opt.load_model_path!=None):
		model.load(opt.load_model_path)
	model.train()
	totalCnt=0

	for epoch in range(opt.epochs):
		for idx,(bdata,blable) in enumerate(trainLoader):
			optimizer.zero_grad()
			totalCnt+=opt.batch_size
			target=model(bdata)
			loss=criterion(target,blable)
			loss.backward()
			optimizer.step()

			if(idx%64==0):
				# 有关loss信息
				print('epoch:%d batch:%d loss:%.6f' %(epoch,idx,loss))
				
				print(blable)
				a,b=target.max(dim=1)
				print(b)

				s=t.nn.Softmax()
				print(target)
				
				print('\n')
			if(totalCnt>4900):
				model.save("D:/magicAlbum/classifier/checkpoints")
				totalCnt=0	


def eval():
	opt._parse({})
	opt.batch_size=1
	#偷懒，减少命令行参数
	testLoader=getTestDataLoader(opt)
	model=AlexNet(opt)
	model.load(opt.load_model_path)
	model.eval()


	filepath="D:/magicAlbum/sharePool/poster/poster.png"
	data=Image.open(filepath)
	normalize = T.Normalize(mean=[0.485],std=[0.229])
	mytransform=[T.Resize(224),
				T.CenterCrop(224),
				T.ToTensor(),
				normalize]
	mytransform=T.Compose(mytransform)
	data=mytransform(data)
	data=data.unsqueeze(0)
	target=model(data)
	value,tag=target.max(dim=1)
	tag=tag.item()
	return tag

	# for data in testLoader:
	# 	print("hi")
	# 	return 20
	# 	#batch_size==1
		
	# 	# print(tag)
	# 	return tag

if __name__=='__main__':
	import fire
	fire.Fire()
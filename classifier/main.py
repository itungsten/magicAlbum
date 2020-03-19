import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
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
	totcnt=0

	for epoch in range(opt.epochs):
		for idx,(bdata,blable) in enumerate(trainLoader):
			optimizer.zero_grad()
			totcnt+=opt.batch_size
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
			if(totcnt>4900):
				model.save("D:\\pytorch-book\\chapter6\\dataset\\checkpoints")
				totcnt=0
			


def test(**kwargs):
	opt._parse(kwargs)
	testLoader=getTestDataLoader(opt)

if __name__=='__main__':
	import fire
	fire.Fire()
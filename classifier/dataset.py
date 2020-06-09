import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms as T
from torch.utils.data import Dataset
from PIL import Image
import os
import sys


class MultiDataset(Dataset):
	def __init__(self,opt,isTrain=True):
		super(MultiDataset,self).__init__()
		self.opt=opt
		self.opt.isTrain=isTrain
		self.transform=[]
		self.imgs=[]
		normalize = T.Normalize(mean=[0.485],std=[0.229])
		if(isTrain):
			self.imgs=[os.path.join(opt.train_data_root,img) for img in os.listdir(opt.train_data_root)]
			self.transform=[T.Resize(64),
							T.RandomCrop(64),
							T.RandomHorizontalFlip(),
							T.ToTensor(),
							normalize]
			self.transform=T.Compose(self.transform)

		else:
			self.imgs=[os.path.join(opt.test_data_root,img) for img in os.listdir(opt.test_data_root)]
			self.transform=[T.Resize(64),
							T.CenterCrop(64),
							T.ToTensor(),
							normalize]
			self.transform=T.Compose(self.transform)

	def __getitem__(self,idx):
		filepath=self.imgs[idx]
		data=Image.open(self.imgs[idx])
		data=self.transform(data)

		if(self.opt.isTrain):
			filepath=filepath.split('\\')[-1]
			label=1 if 'circle' in filepath.split('.')[0] else 0
			#circle is 1 & arc is 0
			return data,int(label)
		else:
			label=filepath.split('.')[0]
			return data


	def __len__(self):
		return len(self.imgs)
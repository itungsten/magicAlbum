import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from PIL import Image
import os
from option import opt
from torch.utils.data import DataLoader
from dataset import MultiDataset

def getTestDataLoader(opt):
	testset=MultiDataset(opt,False)
	return DataLoader(testset,batch_size=opt.batch_size,shuffle=(not opt.no_shuffle),num_workers=opt.num_workers)

def getTrainDataLoader(opt):
	trainset=MultiDataset(opt,True)
	return DataLoader(trainset,batch_size=opt.batch_size,shuffle=(not opt.no_shuffle),num_workers=opt.num_workers)

import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from PIL import Image
import os
import time
import datetime
class Flatten(t.nn.Module):
	def __init__(self):
		super(Flatten,self).__init__()

	def forward(self,x):
		return x.view(x.shape[0],-1)

class BasicModel(t.nn.Module):
	def __init__(self):
		super(BasicModel,self).__init__()
		self.name='BasicModel'

	def forward(self,x):
		pass

	def load(self,path):
		self.load_state_dict(t.load(path))

	def save(self,root):
		path=self.name+'_'+time.strftime('%m%d_%H_%M_%S.ckpt')
		path=os.path.join(root,path)
		t.save(self.state_dict(),path)

	def getOptimizer(self,lr,weight_decay):
		return t.optim.Adam(self.parameters(),lr=lr,weight_decay=weight_decay)
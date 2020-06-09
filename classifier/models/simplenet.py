import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from PIL import Image
import os
from .basicmodel import Flatten,BasicModel

class SimpleNet(BasicModel):
    def __init__(self,opt):
        super(SimpleNet,self).__init__()
        self.opt=opt
        self.name='SimpleNet'
        self.features=nn.Sequential(
            nn.Conv2d(1,64,kernel_size=2,stride=2),
            nn.ReLU(inplace=True),
            nn.Conv2d(64,128,kernel_size=2,stride=2),
            nn.ReLU(inplace=True),
            nn.Conv2d(128,256,kernel_size=2,stride=2),
            nn.ReLU(inplace=True),
            nn.Conv2d(256,512,kernel_size=2,stride=2),
            nn.ReLU(inplace=True),
            )
        self.classifier=nn.Sequential(
                        nn.Dropout(),
                        nn.Linear(512*4*4,512),
                        nn.ReLU(inplace=True),
                        nn.Dropout(),
                        nn.Linear(512,512),
                        nn.ReLU(inplace=True),
                        nn.Linear(512,int(self.opt.num_classes)),
            )
        self.falt=Flatten()

    def forward(self,x):
        # print(x.size())
        x=self.features(x)
        x=self.falt(x)
        x=self.classifier(x)
        return x



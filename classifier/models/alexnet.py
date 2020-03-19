import torch as t 
import torch.nn as nn
import torch.nn.functional as F
from torchvision import transforms
from PIL import Image
import os
from .basicmodel import Flatten,BasicModel

class AlexNet(BasicModel):
    def __init__(self,opt):
        super(AlexNet,self).__init__()
        self.opt=opt
        self.name='AlexNet'
        self.features=nn.Sequential(
            nn.Conv2d(1,64,kernel_size=11,stride=4,padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3,stride=2),
            nn.Conv2d(64,192,kernel_size=5,padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3,stride=2),
            nn.Conv2d(192,384,kernel_size=3,padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(384,256,kernel_size=3,padding=1),
            nn.ReLU(inplace=True),
            nn.Conv2d(256,256,kernel_size=3,padding=1),
            nn.ReLU(inplace=True),

            nn.MaxPool2d(kernel_size=3,stride=2),

    		)
        self.classifier=nn.Sequential(
                        nn.Dropout(),
                        nn.Linear(256*6*6,4096),
                        nn.ReLU(inplace=True),
                        nn.Dropout(),
                        nn.Linear(4096,4096),
                        nn.ReLU(inplace=True),
                        nn.Linear(4096,int(self.opt.num_classes)),
            )
        self.falt=Flatten()

    def forward(self,x):
        x=self.features(x)
        x=self.falt(x)
        x=self.classifier(x)
        return x



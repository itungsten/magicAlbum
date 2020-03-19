# coding:utf8
import warnings
import torch as t

class DefaultConfig(object):
    no_shuffle=False  #加载数据集时是否shuffle
    num_classes=2
    train_data_root = 'train/'  # 训练集存放路径
    test_data_root = 'D:/magicAlbum/sharePool/poster'  # 测试集存放路径
    load_model_path = 'D:/magicAlbum/classifier/checkpoints/AlexNet_0213_12_09_21.ckpt'  # 加载预训练的模型的路径，为None代表不加载

    batch_size = 12# batch size
    use_gpu = False  # user GPU or not
    num_workers = 4  # how many workers for loading data (threads)

    epochs = 10
    weight_decay=0e-5
    lr = 0.001  # initial learning rate

    def _parse(self, kwargs):
        """
        根据字典kwargs 更新 config参数
        """
        for k, v in kwargs.items():
            if not hasattr(self, k):
                warnings.warn("Warning: opt has not attribut %s" % k)
            setattr(self, k, v)
        

        # print('user config:')
        # for k, v in self.__class__.__dict__.items():
        #     if not k.startswith('_'):
        #         print(k, getattr(self, k))

opt = DefaultConfig()

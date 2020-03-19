# Classifier
使用AlexNet进行的二分类

## 用法
python main.py test

## 输入值
test/一张图片

## 返回值
1 or 0
1代表circle 0 代表 arc

## 注意
1.实际使用的是多分类算法，便于扩展分类数目
2.实际可以自行实现并且训练其他网络模型，模型构架存放在/models
3.imageMaker是生成训练集用的图片生成器
4.其余阅读option.py
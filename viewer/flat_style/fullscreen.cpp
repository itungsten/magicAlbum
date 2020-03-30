#include "fullscreen.h"
#include "ui_fullscreen.h"
#include "widget.h"
#include "ui_widget.h"
#include "Python.h"
#include<QKeyEvent>
#include<QImage>
#include<QDebug>

FullScreen::FullScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullScreen)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);//设置相对独立样式
}

FullScreen::~FullScreen()
{
    delete ui;
}

void FullScreen::keyReleaseEvent(QKeyEvent *event)
{
    //设置escape退出全屏，并调用父类事件
    if(event->key()==Qt::Key_Escape){
        Widget* ptr=static_cast<Widget*>(this->parent());//父对象指针
        if(ptr->previewIndex!=-1){
            ptr->ui->movielbl->setMovie(ptr->editor->now);
            //更新预览界面
        }
        ptr->timer->stop(); //停止计时
        hide();//隐藏
    }
    return QWidget::keyReleaseEvent(event);
}

void FullScreen::mousePressEvent(QMouseEvent *ev)
{
      Widget* ptr=static_cast<Widget*>(this->parent());//父对象指针
      ptr->timer->stop(); //停止计时
      if(ev->button()==Qt::LeftButton){
          img=QImage(this->height(),this->height(),QImage::Format_Grayscale8);
          //创建一个正方形的，大小是y轴宽度的8位灰度图
          img.fill(QColor(255,255,255));
          //涂成白色
          lastPoint=nowPoint=ev->pos();
          //初始化点位置
          painter.begin(&img);
          painter.translate(0,0);
          //开始绘图，begin，end搭配使用
          painter.setPen(QPen(QBrush(QColor(0,0,0)),15));
          //大家都喜欢粗一点的
      }
      return QWidget::mousePressEvent(ev);
}
void FullScreen::mouseMoveEvent(QMouseEvent *ev){
      if(ev->buttons()==Qt::LeftButton){
          painter.drawLine(lastPoint-disPoint,nowPoint-disPoint);
          //坐标变换
          //画直为曲
          lastPoint=nowPoint;
          nowPoint=ev->pos();
          //更新
      }
      return QWidget::mouseMoveEvent(ev);
}

void FullScreen::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        painter.end();
        //好习惯会帮助你减少bug

        Widget* ptr=static_cast<Widget*>(this->parent());//父对象指针
        QString extName(ptr->editor->target.split('.')[1]);
        if(extName=="png"){
            if(QFile::exists(PERSONNAME)){
                QFile::remove(PERSONNAME);
            }
            QFile::copy(ptr->editor->target,PERSONNAME);
            //直接复制过去
        }
        else if(extName=="jpg"||extName=="jpeg"){
            QImage currentIMage(ptr->editor->target);
            currentIMage.save(PERSONNAME);
            //转化为png格式
        }else{
            ptr->timer->start(ptr->interval); //开始计时
            return QWidget::mouseReleaseEvent(ev);
        }
        img.save(POSTERNAME);
        if(classifier()){
            Widget* ptr=static_cast<Widget *>(this->parent());
            this->ui->label->setMovie(ptr->editor->now);
            delete anima;
            ptr->timer->start(ptr->interval); //开始计时
            //circle
        }
        else{
            //arc
            transformer();
        }
    }
    return QWidget::mouseReleaseEvent(ev);
}
int FullScreen::classifier(){
    PyObject* resizerModule = PyImport_ImportModule("resizer");
    PyObject* resizeFunction = PyObject_GetAttrString(resizerModule,"resize");
    PyObject* args=Py_BuildValue("(iss)",224,"D:/magicAlbum/sharePool/poster/poster.png","D:/magicAlbum/sharePool/poster/poster.png");
    PyObject_CallObject(resizeFunction,args);
    Py_DecRef(args);
    //resize

    PyObject* classifierModule=PyImport_ImportModule("classifier");
    PyObject* classifyFunction=PyObject_GetAttrString(classifierModule,"eval");
    args=Py_BuildValue("({s:i,s:s,s:s})","batch_size",1,"test_data_root","D:/magicAlbum/sharePool/poster","load_model_path","D:/magicAlbum/classifier/checkpoints/AlexNet_0213_12_09_21.ckpt");
    PyObject* pTag=PyObject_CallObject(classifyFunction,args);
    long tag=PyLong_AsLong(pTag);
    Py_DecRef(pTag);
    Py_DecRef(args);
    //classify

    return static_cast<int>(tag);
}
void FullScreen::transformer(){
    PyObject* cutterModule=PyImport_ImportModule("cutter");
    PyObject* cutFunction=PyObject_GetAttrString(cutterModule,"cut");
    PyObject* args=Py_BuildValue("(ss)","D:/magicAlbum/sharePool/person.png","D:/magicAlbum/sharePool/head.png");
    PyObject* pTuple=PyObject_CallObject(cutFunction,args);
    int left,top;
    PyArg_ParseTuple(pTuple,"ii",&left,&top);
    Py_DecRef(args);
    Py_DecRef(pTuple);
    qDebug()<<233;
    //cutter

    PyObject* transformerModule=PyImport_ImportModule("transformer");
    PyObject* transformeFunction=PyObject_GetAttrString(transformerModule,"transform");
    args=Py_BuildValue("(ss)","D:/magicAlbum/sharePool/head.png","D:/magicAlbum/sharePool/src");
    PyObject_CallObject(transformeFunction,args);
    Py_DecRef(args);
    //transformer

    int num=6;
    PyObject* rebuilderModule=PyImport_ImportModule("rebuilder");
    PyObject* rebuildFunction=PyObject_GetAttrString(rebuilderModule,"rebuild");
    args=Py_BuildValue("(iiisss)",num,left,top,"D:/magicAlbum/sharePool/person.png","D:/magicAlbum/sharePool/src","D:/magicAlbum/sharePool/target");
    PyObject_CallObject(rebuildFunction,args);
    Py_DecRef(args);
    //rebuilder

    PyObject* combinerModule=PyImport_ImportModule("combiner");
    PyObject* combineFunction=PyObject_GetAttrString(combinerModule,"combine");
    args=Py_BuildValue("(iss)",num,"D:/magicAlbum/sharePool/target","D:/magicAlbum/sharePool/result.gif");
    PyObject* pRet=PyObject_CallObject(combineFunction,args);
    Py_DecRef(args);
    int ret=PyLong_AsLong(pRet);
    qDebug()<<ret;
    Py_DecRef(pRet);
    //combiner

    anima=new QMovie("D:/magicAlbum/sharePool/result.gif");
    this->ui->label->setMovie(anima);
    anima->start();
}

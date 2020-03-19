#include "fullscreen.h"
#include "ui_fullscreen.h"
#include "widget.h"
#include "ui_widget.h"
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
      if(ev->button()==Qt::LeftButton){
          img=QImage(this->height(),this->height(),QImage::Format_Grayscale8);
          //创建一个正方形的，大小是y轴宽度的8位灰度图
          img.fill(QColor(243,243,243));
          //涂成白色，默认是灰色,现在变成灰色，统一颜色
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
        img.save("map.png");
        //输出用户图片
    }
    return QWidget::mouseReleaseEvent(ev);
}

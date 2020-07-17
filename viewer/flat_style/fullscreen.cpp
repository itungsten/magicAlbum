#include "fullscreen.h"
#include "ui_fullscreen.h"
#include "widget.h"
#include "ui_widget.h"
#include<QKeyEvent>
#include<QImage>
#include<Windows.h>
#include<QDebug>
#include"conf.h"

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
        TerminateProcess(stProcessInfo.hProcess,0);
        hide();//隐藏
    }
    return QWidget::keyReleaseEvent(event);
}

void FullScreen::mousePressEvent(QMouseEvent *ev)
{
//      Widget* ptr=static_cast<Widget*>(this->parent());//父对象指针
//      ptr->timer->stop(); //停止计时
//      if(ev->button()==Qt::LeftButton){
//          img=QImage(this->height(),this->height(),QImage::Format_Grayscale8);
//          //创建一个正方形的，大小是y轴宽度的8位灰度图
//          img.fill(QColor(255,255,255));
//          //涂成白色
//          lastPoint=nowPoint=ev->pos();
//          //初始化点位置
//          painter.begin(&img);
//          painter.translate(0,0);
//          //开始绘图，begin，end搭配使用
//          painter.setPen(QPen(QBrush(QColor(0,0,0)),15));
//          //大家都喜欢粗一点的
//      }
      return QWidget::mousePressEvent(ev);
}
void FullScreen::mouseMoveEvent(QMouseEvent *ev){
//      if(ev->buttons()==Qt::LeftButton){
//          painter.drawLine(lastPoint-disPoint,nowPoint-disPoint);
//          //坐标变换
//          //画直为曲
//          lastPoint=nowPoint;
//          nowPoint=ev->pos();
//          //更新
//      }
      return QWidget::mouseMoveEvent(ev);
}

void FullScreen::mouseReleaseEvent(QMouseEvent *ev)
{
//    if(ev->button()==Qt::LeftButton){
//        painter.end();
//        //好习惯会帮助你减少bug
//        clock_t beg=clock();
//        Widget* ptr=static_cast<Widget*>(this->parent());//父对象指针
//        QString extName(ptr->editor->target.split('.')[1]);
//        if(extName=="png"){
//            if(QFile::exists(PERSONNAME)){
//                QFile::remove(PERSONNAME);
//            }
//            QFile::copy(ptr->editor->target,PERSONNAME);
//            //直接复制过去
//        }
//        else if(extName=="jpg"||extName=="jpeg"){
//            QImage currentIMage(ptr->editor->target);
//            currentIMage.save(PERSONNAME);
//            //转化为png格式
//        }else{
//            ptr->timer->start(ptr->interval); //开始计时
//            return QWidget::mouseReleaseEvent(ev);
//        }
//        img=img.scaled(64,64);
//        img.save(POSTERNAME);

//        qDebug()<<"save img"<<clock()-beg;
//        beg=clock();

//        if(1){
//            Widget* ptr=static_cast<Widget *>(this->parent());
//            this->ui->label->setMovie(ptr->editor->now);
//            delete anima;
//            ptr->timer->start(ptr->interval); //开始计时
//            //circle
//        }
//        else{
//            //arc
//            anima=new QMovie("D:/magicAlbum/sharePool/result.gif");
//            this->ui->label->setMovie(anima);
//            anima->start();
//        }
//    }
    return QWidget::mouseReleaseEvent(ev);
}

bool FullScreen::openPipe()
{
    STARTUPINFO stStartUpInfo;
    ::memset(&stStartUpInfo, 0 ,sizeof(stStartUpInfo));
    stStartUpInfo.cb = sizeof(stStartUpInfo);


    ::memset(&stProcessInfo, 0 ,sizeof(stProcessInfo));

    TCHAR szPath[]=TEXT( PYTHONWPATH );

    TCHAR szCmd[]=TEXT( CLIENTPATH );

    bool bRet = ::CreateProcess(
        szPath,
        szCmd,
        nullptr,
        nullptr,
        false,
        CREATE_NEW_CONSOLE,
        nullptr,
        nullptr,
        &stStartUpInfo,
        &stProcessInfo);

    if (bRet)
    {
//        ::CloseHandle(stProcessInfo.hProcess);
//        ::CloseHandle(stProcessInfo.hThread);
//        stProcessInfo.hProcess = nullptr;
//        stProcessInfo.hThread = nullptr;
//        stProcessInfo.dwProcessId = 0;
//        stProcessInfo.dwThreadId = 0;
    }
    else
    {
        DWORD dwErrCode = GetLastError();
        printf_s("ErrCode : %d\n",dwErrCode);

    }


    hPipe = nullptr;
    hPipe = CreateNamedPipe(
        EXAMP_PIPE,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE |
        PIPE_READMODE_MESSAGE |
        PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        BUF_SIZE,
        BUF_SIZE,
        0,
        nullptr);

    if (hPipe==INVALID_HANDLE_VALUE)
    {
        qDebug()<<"Create Read Pipe Error";
        return FALSE;
    }

    if (!ConnectNamedPipe(hPipe, nullptr))
    {
        qDebug()<<"Connect Failed";
        return FALSE;
    }
    return true;
}
void FullScreen::closePipe()
{
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
}

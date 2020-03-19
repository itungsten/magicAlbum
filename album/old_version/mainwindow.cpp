#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMovie>
#include<QPushButton>
#include<QIcon>
#include<QToolButton>
#include<QDebug>
#include<QResizeEvent>
#include<QMessageBox>
#include<QTime>
#include "visbutton.h"
#include "ui_visbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    setWindowIcon(QIcon(":/picture.png"));


    ui->fullBtn->setIcon(QIcon(":/full.png"));
    ui->fullBtn->setIconSize(QSize(ui->fullBtn->size().height()/2,ui->fullBtn->size().width()/2));
//全屏


    movieStart();
    this->isRun=false;
    this->zoom=0;
//中心视频标签



    connect(ui->fullBtn,&QToolButton::clicked,[=](){
        FullScreen* fullscreen=new FullScreen();
        fullscreen->showFullScreen();
        this->fullmovie=new QMovie(target,QByteArray(),fullscreen);
        this->fullmovie->setScaledSize(fullscreen->size());
        fullscreen->ui->label->setMovie(this->fullmovie);
        this->fullmovie->start();
    });
    //全屏
    connect(ui->actioninfo,&QAction::triggered,[=](){
        QMessageBox::about(this,"关于","该项目在周毅老师指导下,由代宇涛和王正仁共同完成.");
    });
    //关于
    connect(ui->actionctrl,&QAction::triggered,[=](){
        if(this->isRun==false){
            this->ui->actionctrl->setIcon(QIcon(":/stop.png"));
            this->movie->setPaused(false);
            this->isRun=true;
        }
        else{
            this->ui->actionctrl->setIcon(QIcon(":/run.png"));
            this->movie->setPaused(true);
            this->isRun=false;
        }
    });
    //播放&暂停
    connect(ui->actionbig,&QAction::triggered,[=](){
        if(zoom==0){
            QMessageBox::warning(this,"警告","已到原图大小");
            return;
        }
        this->ui->label->setScaledContents(true);
        zoom--;
        currentSize*=1.33333;
        this->ui->label->setFixedSize(currentSize);
        if(this->isRun==false){
            movie->setPaused(false);
            movie->setPaused(true);
        }
    });

    //放大
    connect(ui->actionsmall,&QAction::triggered,[=](){
        zoom++;
        currentSize*=0.75;
        this->ui->label->setFixedSize(currentSize);
        if(this->isRun==false){
            this->movie->setPaused(false);
            this->movie->setPaused(true);
        }
    });
    //缩小

    connect(this->ui->visBtn,&VisButton::clickedSignal,[=](){
       QMessageBox::information(this,"nice","left");
    });
    connect(this->ui->visBtn2,&VisButton::clickedSignal,[=](){
        QMessageBox::information(this,"nice","right");
    });

    //目前的左右键****************待办
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::movieStart()
{
    target=":/cat.gif";
    movie=new QMovie(target);

    ui->label->setMovie(movie);


    movie->start();
    movie->setPaused(true);
    this->ui->label->setScaledContents(true);
    originSize=movie->currentImage().size();
//    qDebug()<<originSize.width();
//    qDebug()<<originSize.height();
    currentSize=QSize(originSize.width(),originSize.height());
    this->ui->label->setFixedSize(currentSize);
}

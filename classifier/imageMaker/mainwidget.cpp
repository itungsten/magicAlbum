#include "mainwidget.h"
#include "ui_mainwidget.h"
#include<QPaintEvent>
#include<QPainter>
#include<QDebug>
#include<QPixmap>
#include<QString>
#include<QBitmap>
#include<cstdlib>
#include<QTime>
#include<QDir>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    std::srand(QTime::currentTime().second());
    ui->setupUi(this);
    this->w=224;
    this->h=224;
    batch=10000;
    connect(ui->circleBtn,&QPushButton::clicked,[=](){
        if(!QDir("circle/").exists()){
            system("mkdir circle");
        }
        for(int i=0;i<batch;++i)
        {
            map=QImage(QSize(this->w,this->h),QImage::Format_Grayscale8);
            map.fill(Qt::white);
            tempx=rand();
            tempy=rand();
            while(tempx>this->w){
                tempx=rand();
            }
            tempx=120>tempx?120:tempx;
            while(tempy>h){
                tempy=rand();
            }
            tempy=120>tempy?120:tempy;
            painter.begin(&map);
            painter.setPen(QPen(QBrush(QColor(0,0,0)),5));
            painter.translate(this->w/2,this->h/2);
            painter.rotate(rand());
            painter.translate(-this->w/2,-this->h/2);
            painter.drawArc((this->w-tempx)/2,(this->h-tempy)/2,tempx,tempy,rand()*16,(rand()%90+270)*16);
            painter.end();
            QString filename="circle/circle."+QString::number(++(this->cntcirclc))+".png";
            map=map.scaled(64,64);
            map.save(filename);
        }
    });

    connect(ui->arcBtn,&QPushButton::clicked,[=](){
        if(!QDir("arc/").exists()){
            system("mkdir arc");
        }
        for(int i=0;i<batch;++i)
        {
            map=QImage(QSize(this->w,this->h),QImage::Format_Grayscale8);
            map.fill(Qt::white);
            tempx=rand();
            tempy=rand();

            while(tempx>w){
                tempx=rand();
            }
            tempx=200>tempx?200:tempx;
            while(tempy>h){
                tempy=rand();
            }
            tempy=200>tempy?200:tempy;
            painter.begin(&map);
            painter.setPen(QPen(QBrush(QColor(0,0,0)),5));
            painter.translate(this->w/2,this->h/2);
            painter.rotate(rand());
            painter.translate(-this->w/2,-this->h/2);
            painter.drawArc((this->w-tempx)/2,(this->h-tempy)/2,tempx,tempy,rand()*16,(rand()%60+150)*16);
            painter.end();
            QString filename="arc/arc."+QString::number(++(this->cntarc))+".png";
            map=map.scaled(64,64);
            map.save(filename);
        }
    });

    void (QSpinBox:: *myptr)(int)=&QSpinBox::valueChanged;
    connect(ui->spinBox,myptr,[=](int x){
        this->batch=x;
    });
    connect(ui->spinBox2,myptr,[=](int x){
        this->w=x;
        this->h=x;
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::closeEvent(QCloseEvent *event)
{
//    system("cd C:\\Users\\tungsten\\Desktop\\build-makeimgs-Desktop_Qt_5_13_2_MSVC2017_64bit-Debug&del *.png");
    return QWidget::closeEvent(event);
}

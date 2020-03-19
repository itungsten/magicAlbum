#include "fullscreen.h"
#include "ui_fullscreen.h"
#include<QMovie>

FullScreen::FullScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullScreen)
{
    ui->setupUi(this);
}

FullScreen::~FullScreen()
{
    delete ui;
}

void FullScreen::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Escape){
        this->close();
    }
}
//全屏时退出

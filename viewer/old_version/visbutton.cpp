#include "visbutton.h"
#include "ui_visbutton.h"
#include<QString>
#include<QIcon>
#include<QMessageBox>
#include<QDebug>
#pragma warning(disable:C4100)

VisButton::VisButton(QString target,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisButton)
{
    ui->setupUi(this);
    ui->visBtn->setVisible(false);
    ui->visBtn->setIcon(QIcon(target));
    ui->visBtn->setIconSize(QSize(ui->visBtn->size().width()/2,ui->visBtn->size().height()/2));
    ui->visBtn->setDisabled(true);
}

VisButton::~VisButton()
{
    delete ui;
}

void VisButton::enterEvent(QEvent *event)
{
    this->ui->visBtn->setVisible(true);
}

void VisButton::leaveEvent(QEvent *event)
{
//    qDebug()<<"2qe32423432431432141324432";
    this->ui->visBtn->setVisible(false);
}

void VisButton::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug()<<"ssdfsdfsdfsdfafadfadfdasfadfs";
       emit VisButton::clickedSignal();
}

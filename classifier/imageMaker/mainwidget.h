#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    int cntarc=0;
    int cntcirclc=0;
    int cntother=0;
    int w;
    int h;
    int batch;
    QPainter painter;
    QImage map;
    int tempx,tempy;
    void closeEvent(QCloseEvent *event);

    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H

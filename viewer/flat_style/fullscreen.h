#ifndef FULLSCREEN_H
#define FULLSCREEN_H
#include <QWidget>
#include<QMovie>
#include<QImage>
#include<Windows.h>
#include<QPainter>


namespace Ui {
class FullScreen;
}

class FullScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FullScreen(QWidget *parent = nullptr);
    ~FullScreen();

    void keyReleaseEvent(QKeyEvent *event);

    //用户交互图
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    bool openPipe();
    void closePipe();
    QImage img;
    QPoint lastPoint,nowPoint,disPoint;
    QPainter painter;
    QMovie* anima;

    HANDLE hPipe;
    PROCESS_INFORMATION stProcessInfo;

    char lastCode=0;

    Ui::FullScreen *ui;
};

#endif // FULLSCREEN_H

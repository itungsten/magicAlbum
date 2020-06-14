#ifndef FULLSCREEN_H
#define FULLSCREEN_H
#define BUF_SIZE 65535
#define EXAMP_PIPE   L"\\\\.\\pipe\\AlbumPipe"
// 定义管道名 , 如果是跨网络通信 , 则在圆点处指定服务器端程序所在的主机名

#include <QWidget>
#include<QMovie>
#include<QImage>
#include<Windows.h>
#include<QPainter>
#define POSTERNAME "D:/magicAlbum/sharePool/poster/poster.png"
#define PERSONNAME "D:/magicAlbum/sharePool/person.png"

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

    Ui::FullScreen *ui;
};

#endif // FULLSCREEN_H

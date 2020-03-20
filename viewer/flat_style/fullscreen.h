#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QWidget>
#include<QMovie>
#include<QImage>
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
    int classifier();
    void transformer();
    QImage img;
    QPoint lastPoint,nowPoint,disPoint;
    QPainter painter;
    QMovie* anima;

    Ui::FullScreen *ui;
};

#endif // FULLSCREEN_H

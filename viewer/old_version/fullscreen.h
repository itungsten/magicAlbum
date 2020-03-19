#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QWidget>
#include "ui_fullscreen.h"
#include<QMovie>
#include<QKeyEvent>

namespace Ui {
class FullScreen;
}

class FullScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FullScreen(QWidget *parent = nullptr);
    ~FullScreen();

//private:
//    QString target;
    void keyReleaseEvent(QKeyEvent *ev);
    Ui::FullScreen *ui;
};

#endif // FULLSCREEN_H

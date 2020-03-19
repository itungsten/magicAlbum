#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<fullscreen.h>
#include<vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void movieStart();
    ~MainWindow();
//    void resizeEvent(QResizeEvent* size);
    std::vector<QString> lists;//记录所有movie

private:
    Ui::MainWindow *ui;
    QString target;//当前播放movie的路径
    QMovie* movie;//初始界面movie的指针
    QMovie* fullmovie;//全屏界面moive的指针
    bool isRun;//记录movie的播放状态
    int zoom;
    QSize originSize;
    QSize currentSize;
};
#endif // MAINWINDOW_H

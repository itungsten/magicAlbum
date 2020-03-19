#ifndef VISBUTTON_H
#define VISBUTTON_H

#include <QWidget>

namespace Ui {
class VisButton;
}

class VisButton : public QWidget
{
    Q_OBJECT

public:
    explicit VisButton(QString target,QWidget *parent = nullptr);
    ~VisButton();
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    Ui::VisButton *ui;
signals:
    void clickedSignal();
//private:
};

#endif // VISBUTTON_H

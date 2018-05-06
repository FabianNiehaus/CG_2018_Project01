#ifndef BEZIERWINDOW_H
#define BEZIERWINDOW_H

#include <QMainWindow>

namespace Ui {
class BezierWindow;
}

class BezierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BezierWindow(QWidget *parent = 0);
    ~BezierWindow();

private:
    Ui::BezierWindow *ui;
};

#endif // BEZIERWINDOW_H

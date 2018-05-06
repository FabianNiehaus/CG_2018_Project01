#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include <QMainWindow>

namespace Ui {
class CubeWindow;
}

class CubeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CubeWindow(QWidget *parent = 0);
    ~CubeWindow();

private:
    Ui::CubeWindow *ui;
};

#endif // CUBEWINDOW_H

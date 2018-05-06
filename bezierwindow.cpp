#include "bezierwindow.h"
#include "ui_bezierwindow.h"

BezierWindow::BezierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BezierWindow)
{
    ui->setupUi(this);
}

BezierWindow::~BezierWindow()
{
    delete ui;
}

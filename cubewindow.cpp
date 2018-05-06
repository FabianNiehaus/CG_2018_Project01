#include "cubewindow.h"
#include "ui_cubewindow.h"

CubeWindow::CubeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeWindow)
{
    ui->setupUi(this);
}

CubeWindow::~CubeWindow()
{
    delete ui;
}

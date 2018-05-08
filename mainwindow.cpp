#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cubewindow.h"
#include "bezierwindow.h"
#include "scenewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    CubeWindow * cw = new CubeWindow();
    cw->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    BezierWindow * bw = new BezierWindow();
    bw->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    SceneWindow * sw = new SceneWindow();
    sw->show();
}

/********************************************************************************
** Form generated from reading UI file 'cubewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUBEWINDOW_H
#define UI_CUBEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "oglwidget.h"
#include "oglwidget2.h"
#include "oglwidget3.h"

QT_BEGIN_NAMESPACE

class Ui_CubeWindow
{
public:
    QWidget *centralwidget;
    OGLWidget3 *openGLWidget_3;
    OGLWidget2 *openGLWidget_2;
    OGLWidget *openGLWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CubeWindow)
    {
        if (CubeWindow->objectName().isEmpty())
            CubeWindow->setObjectName(QStringLiteral("CubeWindow"));
        CubeWindow->resize(703, 510);
        centralwidget = new QWidget(CubeWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget_3 = new OGLWidget3(centralwidget);
        openGLWidget_3->setObjectName(QStringLiteral("openGLWidget_3"));
        openGLWidget_3->setGeometry(QRect(470, 240, 220, 220));
        openGLWidget_2 = new OGLWidget2(centralwidget);
        openGLWidget_2->setObjectName(QStringLiteral("openGLWidget_2"));
        openGLWidget_2->setGeometry(QRect(470, 10, 220, 220));
        openGLWidget = new OGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 10, 450, 450));
        CubeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CubeWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 703, 21));
        CubeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CubeWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CubeWindow->setStatusBar(statusbar);

        retranslateUi(CubeWindow);

        QMetaObject::connectSlotsByName(CubeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CubeWindow)
    {
        CubeWindow->setWindowTitle(QApplication::translate("CubeWindow", "Teilprojekt 1", 0));
    } // retranslateUi

};

namespace Ui {
    class CubeWindow: public Ui_CubeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBEWINDOW_H

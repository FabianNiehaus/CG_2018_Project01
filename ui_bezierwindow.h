/********************************************************************************
** Form generated from reading UI file 'bezierwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEZIERWINDOW_H
#define UI_BEZIERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "oglwidgetbezier01.h"

QT_BEGIN_NAMESPACE

class Ui_BezierWindow
{
public:
    QWidget *centralwidget;
    OGLWidgetBezier01 *openGLWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BezierWindow)
    {
        if (BezierWindow->objectName().isEmpty())
            BezierWindow->setObjectName(QStringLiteral("BezierWindow"));
        BezierWindow->resize(800, 600);
        centralwidget = new QWidget(BezierWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new OGLWidgetBezier01(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 10, 771, 531));
        BezierWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BezierWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        BezierWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BezierWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        BezierWindow->setStatusBar(statusbar);

        retranslateUi(BezierWindow);

        QMetaObject::connectSlotsByName(BezierWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BezierWindow)
    {
        BezierWindow->setWindowTitle(QApplication::translate("BezierWindow", "Teilprojekt 2", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierWindow: public Ui_BezierWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIERWINDOW_H

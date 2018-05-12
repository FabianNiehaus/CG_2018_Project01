/********************************************************************************
** Form generated from reading UI file 'scenewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEWINDOW_H
#define UI_SCENEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "oglscenewidget.h"

QT_BEGIN_NAMESPACE

class Ui_SceneWindow
{
public:
    QWidget *centralwidget;
    OGLSceneWidget *openGLWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SceneWindow)
    {
        if (SceneWindow->objectName().isEmpty())
            SceneWindow->setObjectName(QStringLiteral("SceneWindow"));
        SceneWindow->resize(800, 600);
        centralwidget = new QWidget(SceneWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new OGLSceneWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 10, 740, 540));
        SceneWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SceneWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SceneWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SceneWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SceneWindow->setStatusBar(statusbar);

        retranslateUi(SceneWindow);

        QMetaObject::connectSlotsByName(SceneWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SceneWindow)
    {
        SceneWindow->setWindowTitle(QApplication::translate("SceneWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SceneWindow: public Ui_SceneWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEWINDOW_H

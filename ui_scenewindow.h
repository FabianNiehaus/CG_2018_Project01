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
#include <QtWidgets/QHBoxLayout>
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
    QHBoxLayout *horizontalLayout;
    OGLSceneWidget *openGLWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SceneWindow)
    {
        if (SceneWindow->objectName().isEmpty())
            SceneWindow->setObjectName(QStringLiteral("SceneWindow"));
        SceneWindow->resize(900, 900);
        centralwidget = new QWidget(SceneWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        openGLWidget = new OGLSceneWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        horizontalLayout->addWidget(openGLWidget);

        SceneWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SceneWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
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

/*
 * Datum: 14.05.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QMainWindow>

namespace Ui {
class SceneWindow;
}

class SceneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SceneWindow(QWidget *parent = 0);
    ~SceneWindow();

private:
    Ui::SceneWindow *ui;
};

#endif // SCENEWINDOW_H

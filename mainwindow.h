#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "stations.h"
#include "commands.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* keyEvent);

private:
    Ui::MainWindow *m_ui;
    Stations m_stations;
    Commands m_commands;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "stations.h"
#include "commands.h"
#include "player.h"

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
    void updateVolumeStatus();

    Ui::MainWindow *m_ui;
    Stations m_stations;
    Commands m_commands;
    Player m_player;
};

#endif // MAINWINDOW_H

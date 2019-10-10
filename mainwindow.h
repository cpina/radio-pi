#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "actions.h"
#include "stations.h"
#include "commands.h"
#include "player.h"
#include "settings.h"
#include "volume.h"
#include "inputhandling.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void changeSongName(const QString& songName);
    void changeToStation(const QString& text);

    void nextRadioStation();
    void previousRadioStation();

    void updateVolumeStatus(int volume);


private:
    void setupInputHandling();
    int greaterStationNumber();

    Ui::MainWindow *m_ui;
    Actions m_actions;
    Commands m_commands;
    Player m_player;
    Volume m_volume;
    Settings m_settings;
    InputHandling m_inputHandling;

    int m_currentStation;
};

#endif // MAINWINDOW_H

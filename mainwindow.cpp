#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QString error = m_stations.loadStations();
    if (!error.isEmpty())
    {
        m_ui->Station->setText(error);
    }

    error = m_commands.loadCommands();
    if (!error.isEmpty())
    {
        m_ui->Station->setText(error);
    }

    m_currentVolume = m_settings.readInt(Settings::Volume);
    changeVolume(0);
    updateVolumeStatus();

    QString stationNumber = m_settings.readString(Settings::StationNumber);
    changeToStation(stationNumber);

    connect(&m_player, SIGNAL(song(QString)),
            this, SLOT(changeSongName(QString)));
}

void MainWindow::changeToStation(const QString& text)
{
    qDebug() << "Changing to station:" << text;
    m_ui->Station->setText(m_stations.name(text));
    m_settings.writeString(Settings::StationNumber, text);
    m_player.play(m_stations.stream(text));
    m_currentStation = text.toInt();
}

void MainWindow::nextRadioStation()
{
    m_currentStation++;
    if (m_currentStation == 10)
    {
        m_currentStation = 1;
    }
    changeToStation(QString::number(m_currentStation));
}

void MainWindow::previousRadioStation()
{
    m_currentStation--;
    if (m_currentStation == 0)
    {
        m_currentStation = 9;
    }
    changeToStation(QString::number(m_currentStation));
}

void MainWindow::changeVolume(int percentage)
{
    m_currentVolume += percentage;

    if (m_currentVolume > 100)
    {
        m_currentVolume = 100;
    }
    else if (m_currentVolume < 0)
    {
        m_currentVolume = 0;
    }

    m_commands.executeCommand(Commands::SetVolume, m_currentVolume);
    if (m_currentVolume == 0)
    {
        m_commands.executeCommand(Commands::Mute);
    }
    updateVolumeStatus();
}

void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
{
    QString text = keyEvent->text();

    if (!m_stations.stream(text).isEmpty())
    {
        changeToStation(text);
        return;
    }

    switch (keyEvent->key())
    {
        case Qt::Key_Up:
        {
            nextRadioStation();
            break;
        }
        case Qt::Key_Down:
        {
            previousRadioStation();
            break;
        }
        case Qt::Key_Right:
        case 161:               // Volume-up in the remote. TODO: in the config file
        case 61:                // Volume-up in the remote in the Raspberrypi
        {
            changeVolume(5);
            break;
        }
        case Qt::Key_Left:
        case 39:                // Volume-down in the remote. TODO: in the config file
        case 45:                // Volume-up in the remote in the Raspberrypi
        {
            changeVolume(-5);
            break;
        }
        default:
        {
            qDebug() << "Not found key:" << keyEvent->key();
        }
    }
}

void MainWindow::changeSongName(const QString &songName)
{
    m_ui->Song->setText(songName);
}

void MainWindow::updateVolumeStatus()
{
    m_ui->Volume->setText(QString("%1 %").arg(m_currentVolume));
    m_settings.writeInt(Settings::Volume, m_currentVolume);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

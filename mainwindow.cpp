#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setupInputHandling();

    connect(&m_player, &Player::song,
            this, &MainWindow::changeSongName);

    QString error = m_commands.loadCommands();
    if (!error.isEmpty())
    {
        m_ui->station->setText(error);
    }

    error = m_actions.loadActions();
    if (!error.isEmpty())
    {
        m_ui->station->setText(error);
    }

    m_inputHandling.setPossibleNumbers(m_actions.numbers());
    QString stationNumber = m_settings.readString(Settings::StationNumber);
    changeToStation(stationNumber);

    updateVolumeStatus(m_volume.currentVolume());
}

void MainWindow::changeToStation(const QString& text)
{
    qDebug() << "Changing to station:" << text;

    QVariant action = m_actions.action(text);

    if (action.canConvert<Stations::Station>())
    {
        Stations::Station station = action.value<Stations::Station>();
        QString stationName = station.name;
        m_ui->station->setText(QString("%1: %2").arg(text, stationName));
        m_settings.writeString(Settings::StationNumber, text);
        m_currentStation = text.toInt();
        m_player.play(station.stream);
    }
    else if (action.canConvert<Commands::Command>())
    {
        Commands::Command commandName = action.value<Commands::Command>();
        m_commands.executeCommand(commandName);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void MainWindow::nextRadioStation()
{
    m_currentStation++;

    QVariant action = m_actions.action(QString::number(m_currentStation));

    if (!action.canConvert<Stations::Station>())
    {
        m_currentStation = 1;
    }

    changeToStation(QString::number(m_currentStation));
}

void MainWindow::setupInputHandling()
{
    installEventFilter(&m_inputHandling);

    connect(&m_inputHandling, &InputHandling::changeToStation,
            this, &MainWindow::changeToStation);

    connect(&m_inputHandling, &InputHandling::stationUp,
            this, &MainWindow::nextRadioStation);

    connect(&m_inputHandling, &InputHandling::stationDown,
            this, &MainWindow::previousRadioStation);

    connect(&m_inputHandling, &InputHandling::volumeUp,
            &m_volume, &Volume::volumeUp);

    connect(&m_inputHandling, &InputHandling::volumeDown,
            &m_volume, &Volume::volumeDown);

    connect(&m_volume, &Volume::volumeChanged,
            this, &MainWindow::updateVolumeStatus);
}

int MainWindow::greaterStationNumber()
{
    QStringList actions = m_actions.numbers().toList();

    std::sort(actions.begin(), actions.end(), [](QString a, QString b) { return a.toInt() > b.toInt();});

    int i = 0;

    while(i < actions.length())
    {
        if (m_actions.action(QString::number(i)).canConvert<Stations::Station>())
        {
            break;
        }
        i++;
    }

    if (i == actions.length())
    {
        qDebug() << "Cannot find station number to go back after going down";
    }

    return actions[i].toInt();
}

void MainWindow::previousRadioStation()
{
    m_currentStation--;
    if (m_currentStation == 0)
    {
        m_currentStation = greaterStationNumber();
    }
    changeToStation(QString::number(m_currentStation));
}

void MainWindow::changeSongName(const QString &songName)
{
    m_ui->song->setText(songName);
}

void MainWindow::updateVolumeStatus(int volume)
{
    m_ui->volume->setText(QString("%1 %").arg(volume));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

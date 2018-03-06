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

    connect(&m_player, SIGNAL(song(QString)),
            this, SLOT(changeSongName(QString)));

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
        m_ui->station->setText(stationName);
        m_settings.writeString(Settings::StationNumber, text);
        m_currentStation = text.toInt();
        m_player.play(station.stream);
    }
    else if (action.canConvert<Commands::CommandName>())
    {
        Commands::CommandName commandName = action.value<Commands::CommandName>();
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
    if (m_currentStation == 10)
    {
        m_currentStation = 1;
    }
    changeToStation(QString::number(m_currentStation));
}

void MainWindow::setupInputHandling()
{
    installEventFilter(&m_inputHandling);

    connect(&m_inputHandling, SIGNAL(changeToStation(QString)),
            this, SLOT(changeToStation(QString)));

    connect(&m_inputHandling, SIGNAL(stationUp()),
            this, SLOT(nextRadioStation()));

    connect(&m_inputHandling, SIGNAL(stationDown()),
            this, SLOT(previousRadioStation()));

    connect(&m_inputHandling, SIGNAL(volumeUp()),
            &m_volume, SLOT(volumeUp()));

    connect(&m_inputHandling, SIGNAL(volumeDown()),
            &m_volume, SLOT(volumeDown()));

    connect(&m_volume, SIGNAL(volumeChanged(int)),
            this, SLOT(updateVolumeStatus(int)));
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

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

    connect(&m_player, SIGNAL(song(QString)),
            this, SLOT(changeSongName(QString)));
}

void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
{
    QString text = keyEvent->text();

    if (!m_stations.stream(text).isEmpty())
    {
        m_ui->Station->setText(m_stations.name(text));
        m_player.play(m_stations.stream(text));
        return;
    }

    switch (keyEvent->key())
    {
        case Qt::Key_Up:
        {
            m_commands.executeCommand(Commands::VolumeUp);
            updateVolumeStatus();
            break;
        }
        case Qt::Key_Down:
        {
            m_commands.executeCommand(Commands::VolumeDown);
            updateVolumeStatus();
            break;
        }
    }
}

void MainWindow::changeSongName(const QString &songName)
{
    m_ui->Song->setText(songName);
}

void MainWindow::updateVolumeStatus()
{
    QString volume = m_commands.executeCommand(Commands::VolumeStatus);
    m_ui->Volume->setText(QString("%1 %").arg(volume));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

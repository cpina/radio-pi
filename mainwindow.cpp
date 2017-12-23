#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>

#include <QKeyEvent>

void kill_mplayer()
{
    QProcess::execute("killall", QStringList{"mplayer"});
}

void mplayer(const QString& url)
{
    kill_mplayer();
    QProcess::startDetached("mplayer", QStringList{url});
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    boost::optional<QString> error = m_stations.loadStations();
    if (error)
    {
        m_ui->Station->setText(error.value());
    }

    error = m_commands.loadCommands();
    if (error)
    {
        m_ui->Station->setText(error.value());
    }
}

void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
{
    QString text = keyEvent->text();

    QString stream = m_stations.stream(text);

    if (!stream.isEmpty())
    {
        m_ui->Station->setText(m_stations.name(text));
        mplayer(stream);
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

void MainWindow::updateVolumeStatus()
{
    QString volume = m_commands.executeCommand(Commands::VolumeStatus);
    m_ui->Volume->setText(QString("%1 %").arg(volume));
}

MainWindow::~MainWindow()
{
    kill_mplayer();
    delete m_ui;
}

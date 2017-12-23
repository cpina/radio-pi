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

    if (m_stations.play(text))
    {
        m_ui->Station->setText(m_stations.name(text));
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
    delete m_ui;
}

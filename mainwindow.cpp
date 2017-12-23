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

void play_rac105()
{
    kill_mplayer();
    mplayer("http://178.32.113.2:80/");
}

void play_smooth()
{
    kill_mplayer();
    mplayer("http://media-ice.musicradio.com/SmoothUKMP3?amsparams=playerid:UKRP;skey:1513640000;&amp;awparams=kxsegs:||;&amp;kuid=");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
{
    switch (keyEvent->key())
    {
        case Qt::Key_Up:
        {
            QStringList up;
            up << "-M" << "set" << "PCM" << "5%+";
            QProcess::execute("amixer", up);
            break;
        }
        case Qt::Key_Down:
        {
            QStringList down;
            down << "-M" << "set" << "PCM" << "5%-";
            QProcess::execute("amixer", down);
            break;
        }
        case Qt::Key_5:
        {
            play_rac105();
            ui->label->setText("RAC 105");
            break;
        }
        case Qt::Key_1:
        {
            play_smooth();
            ui->label->setText("Smooth");
            break;
        }
        default:
        {
            qDebug() << "Unrecognized key:" << keyEvent->key();
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

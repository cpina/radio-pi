#include "player.h"

#include <QProcess>
#include <QDebug>
#include <QRegExp>

Player::Player(QObject* parent)
    :
      QObject(parent)
{
}

Player::~Player()
{
    stopPlaying();
}

void Player::play(const QString &url)
{
    stopPlaying();
    m_player.reset(new QProcess);

    connect(m_player.data(), SIGNAL(readyReadStandardOutput()),
            this, SLOT(processMplayerOutput()));

    m_player->start("mplayer", QStringList{"--quiet", url});
    emit song(QString());
}

void Player::processMplayerOutput()
{
    QString output = m_player->readAllStandardOutput();

    QRegExp rx("icy-title: (.*)\n");
    rx.setMinimal(true);

    if (rx.indexIn(output) > -1)
    {
        QString name = rx.cap(1);
        emit song(name);
    }

    rx = QRegExp("ICY Info: StreamTitle='(.*)';");
    rx.setMinimal(true);
    if (rx.indexIn(output) > -1)
    {
        QString name = rx.cap(1);
        emit song(name);
    }
}

void Player::stopPlaying()
{
    if (m_player)
    {
        m_player->kill();
        m_player->waitForFinished();
        m_player.reset();
    }
}



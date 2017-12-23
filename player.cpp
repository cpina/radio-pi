#include "player.h"

#include <QProcess>
#include <QDebug>

Player::Player(QObject* parent)
    :
      QObject(parent)
{

}

Player::~Player()
{

}

void Player::play(const QString &url)
{
    m_player.reset(new QProcess);
    m_player->start("mplayer", QStringList{"--quiet", url});

    connect(m_player.data(), SIGNAL(readyReadStandardOutput()),
            this, SLOT(processMplayerOutput()));
}

void Player::processMplayerOutput()
{
    qDebug() << "Mplayer output:" << m_player->readAllStandardOutput();
}

void Player::stopPlaying()
{
    if (m_player)
    {
        m_player->kill();
    }
}



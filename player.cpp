#include "player.h"

#include <QProcess>
#include <QDebug>
#include <QRegularExpression>

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

    connect(m_player.data(), &QProcess::readyReadStandardOutput,
            this, &Player::processMplayerOutput);

    startAndLog("mplayer", QStringList{"-quiet", url});
    emit song("Loading...");
}

QString Player::argumentsToString(const QStringList& arguments)
{
    QString result;

    for (const QString& argument : arguments)
    {
        if (!result.isEmpty())
        {
            result += " ";
        }
        result += QString("\"%1\"").arg(argument);
    }

    return result;
}

void Player::startAndLog(const QString& programName, const QStringList& arguments)
{
    qDebug() << "Executing: " << programName << argumentsToString(arguments);
    m_player->start(programName, arguments);
}

void Player::executeAndLog(const QString& programName, const QStringList& arguments)
{
    qDebug() << "Executing (static): " << programName << argumentsToString(arguments);
    QProcess::execute(programName, arguments);
}

QString Player::findRegularExpression(const QStringList& regExps, const QString& mplayerOutput)
{
    for (const QString &regexp : regExps) {
        QRegularExpression rx(regexp);
        QRegularExpressionMatch match = rx.match(mplayerOutput);

        if (match.hasMatch()) {
            return match.captured(1);
        }
    }

    return QString();
}

void Player::processMplayerOutput()
{
    QString output = m_player->readAllStandardOutput();
    qDebug() << "Output:" << output;

    QString songName = findRegularExpression(QStringList{"icy-title: (.*)\n",
                                                "ICY Info: StreamTitle='(.*?)';"}, output);
    if (!songName.isEmpty())
    {
        emit song(songName);
        return;
    }

    // Initially it shows "Loading...", now there is some output
    // so we remove "Loading..."

    // \\n is included because findRegularExpression uses QRegularExpression::setMinimal(true);
    QString audioOutputLine = findRegularExpression(QStringList{"^AO:(.*)\\n"}, output);
    if (!audioOutputLine.isEmpty())
    {
        emit song(QString());
    }
}

void Player::stopPlaying()
{
    if (m_player)
    {
        m_player->kill();
        m_player->waitForFinished();

        // mplayer has a child process and is not being finished in the RaspberryPi
        // Meanwhile does the killall mplayer.
        // mplayer client mode is different at the moment in mplayer and mpv so not using it yet
        executeAndLog("killall", QStringList{"mplayer"});
        m_player.reset();
    }
}



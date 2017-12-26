#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QObject>
#include <QProcess>

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject* parent = 0);
    ~Player();

    void play(const QString& url);
    void stopPlaying();

Q_SIGNALS:
    void song(const QString& url);

private Q_SLOTS:
    void processMplayerOutput();

private:
    // calls start() method from m_player
    void startAndLog(const QString& programName, const QStringList& arguments);

    // calls QProcess::execute
    static void executeAndLog(const QString& programName, const QStringList& arguments);

    static QString argumentsToString(const QStringList& arguments);
    static QString findRegularExpression(const QStringList &regExps, const QString& mplayerOutput);

    QScopedPointer<QProcess> m_player;
};

#endif // PLAYER_H

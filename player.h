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
    QScopedPointer<QProcess> m_player;
};

#endif // PLAYER_H

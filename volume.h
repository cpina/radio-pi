#ifndef VOLUME_H
#define VOLUME_H

#include "settings.h"
#include "commands.h"

#include <QObject>

class Volume : public QObject
{
    Q_OBJECT

public:
    Volume(QObject* parent = 0);
    ~Volume();

public Q_SLOTS:
    void volumeUp();
    void volumeDown();

Q_SIGNALS:
    void volumeChanged(int volume);

private:
    void changeVolume(int percentage);

    int m_currentVolume;

    Settings m_settings;
    Commands m_commands;
};

#endif // VOLUME_H

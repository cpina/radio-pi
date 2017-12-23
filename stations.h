#ifndef STATIONS_H
#define STATIONS_H

#include <QString>
#include <QMap>

#include "utils.h"

class Stations
{
public:
    struct Station
    {
        QString name;
        QString stream;
    };

    Stations();
    ~Stations();

    QString loadStations();
    QString stream(const QString& text);
    QString name(const QString& text);
    bool play(const QString& stationName);
    void stopPlaying();

private:
    QHash<QString, Station> m_keyToStreams;
};

#endif // STATIONS_H

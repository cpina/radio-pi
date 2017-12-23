#ifndef STATIONS_H
#define STATIONS_H

#include <boost/optional.hpp>

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

    boost::optional<QString> loadStations();
    QString stream(const QString& text);
    QString name(const QString& text);
    bool play(const QString& stationName);
    void stopPlaying();

private:
    QHash<QString, Station> m_keyToStreams;
};

#endif // STATIONS_H

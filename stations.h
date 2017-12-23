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

    boost::optional<QString> loadStations();
    QString stream(const QString& text);
    QString name(const QString& text);

private:
    QHash<QString, Station> m_keyToStreams;
};

#endif // STATIONS_H

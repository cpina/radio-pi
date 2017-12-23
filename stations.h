#ifndef STATIONS_H
#define STATIONS_H

#include <QString>
#include <QMap>

#include <boost/optional.hpp>

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
    QMap<QString, Station> m_keyToStreams;
};

#endif // STATIONS_H

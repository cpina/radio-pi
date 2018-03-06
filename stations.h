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

private:
    QHash<QString, Station> m_keyToStreams;
};

Q_DECLARE_METATYPE(Stations::Station)

#endif // STATIONS_H

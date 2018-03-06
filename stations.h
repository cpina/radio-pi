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
};

Q_DECLARE_METATYPE(Stations::Station)

#endif // STATIONS_H

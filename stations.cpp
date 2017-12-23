#include "stations.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QFileInfo>
#include <QProcess>

Stations::Stations()
{

}

Stations::~Stations()
{
}

QString Stations::stream(const QString& text)
{
    if (m_keyToStreams.contains(text))
    {
        return m_keyToStreams.value(text).stream;
    }
    return QString();
}

QString Stations::name(const QString& text)
{
    if (m_keyToStreams.contains(text))
    {
        return m_keyToStreams.value(text).name;
    }
    return QString();
}

QString Stations::loadStations()
{
    Utils::ErrorOrValue errorOrvalue = Utils::readJsonToVariant("configuration/stations.json");
    m_keyToStreams.clear();

    if (!errorOrvalue.error.isEmpty())
    {
        return errorOrvalue.error;
    }

    QMap<QString, QVariant> radioMap = errorOrvalue.value.toMap();

    for (const QString& key : radioMap.keys())
    {
        Station station;

        QMap<QString, QVariant> stationMap = radioMap.value(key).toMap();
        station.name = stationMap.value("name").toString();
        station.stream = stationMap.value("stream").toString();
        m_keyToStreams.insert(key, station);
    }

    return QString();
}

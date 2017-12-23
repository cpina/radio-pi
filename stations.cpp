#include "stations.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QFileInfo>

Stations::Stations()
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

boost::optional<QString> Stations::loadStations()
{
    QString val;
    QFile file;

    QFileInfo configurationFileInfo("configuration/stations.json");
    QString configurationAbsoluteFilePath = configurationFileInfo.absoluteFilePath();

    file.setFileName(configurationAbsoluteFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QObject::tr("Cannot open: %1").arg(configurationAbsoluteFilePath);
    }

    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

    QVariant radios = d.toVariant();

    QMap<QString, QVariant> radioMap = radios.toMap();

    for (const QString& key : radioMap.keys())
    {
        Station station;

        QMap<QString, QVariant> stationMap = radioMap.value(key).toMap();
        station.name = stationMap.value("name").toString();
        station.stream = stationMap.value("stream").toString();
        m_keyToStreams.insert(key, station);
    }

    return boost::optional<QString>();
    /*
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("appName"));
    qWarning() << value;
    QJsonObject item = value.toObject();
    qWarning() << tr("QJsonObject of description: ") << item;

    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue subobj = item["description"];
    qWarning() << subobj.toString();

    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    QJsonArray test = item["imp"].toArray();
    qWarning() << test[1].toString();
    */
}

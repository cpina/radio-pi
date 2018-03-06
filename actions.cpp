#include "actions.h"

#include <QDebug>

#include "stations.h"
#include "commands.h"

Actions::Actions()
{

}

QString Actions::loadActions()
{
    Utils::ErrorOrValue errorOrvalue = Utils::readJsonToVariant("configuration/stations.json");
    m_keyToAction.clear();

    if (!errorOrvalue.error.isEmpty())
    {
        return errorOrvalue.error;
    }

    QMap<QString, QVariant> actions = errorOrvalue.value.toMap();

    for (const QString& key : actions.keys())
    {
        QMap<QString, QVariant> action = actions.value(key).toMap();

        if (action.contains("stream") && action.contains("name"))
        {
            Stations::Station station;
            station.name = action.value("name").toString();
            station.stream = action.value("stream").toString();

            m_keyToAction.insert(key, QVariant::fromValue(station));
        }
        else if (action.contains("command"))
        {
            Commands::CommandName commandName = Commands::fromString(action.value("command").toString());

            m_keyToAction.insert(key, commandName);
        }
        else
        {
            qDebug() << "Warning ignored:" << action;
        }
    }

    return QString();
}

QVariant Actions::action(const QString& key)
{
    return m_keyToAction.value(key);
}

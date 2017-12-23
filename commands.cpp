#include "commands.h"

#include <boost/optional.hpp>
#include <QDebug>
#include <QProcess>

#include "utils.h"

Commands::Commands()
{

}

boost::optional<QString> Commands::loadCommands()
{
    Utils::ErrorOrValue errorOrvalue = Utils::readJsonToVariant("configuration/commands.json");
    m_commandToCommandLine.clear();

    if (!errorOrvalue.error.isEmpty())
    {
        return errorOrvalue.error;
    }

    QMap<QString, QVariant> commandsMap = errorOrvalue.value.toMap();

    for (const QString& command : commandsMap.keys())
    {
        m_commandToCommandLine.insert(command, commandsMap.value(command).toString());
    }
    /*
    for (const QString& key : radioMap.keys())
    {
        Station station;

        QMap<QString, QVariant> stationMap = radioMap.value(key).toMap();
        station.name = stationMap.value("name").toString();
        station.stream = stationMap.value("stream").toString();
        m_keyToStreams.insert(key, station);
    }
*/

    return boost::optional<QString>();
}

QString Commands::executeCommand(CommandName commandName)
{
    switch(commandName)
    {
        case VolumeUp:
        {
            execute(m_commandToCommandLine.value("volume_up"));
            break;
        }
        case VolumeDown:
        {
            execute(m_commandToCommandLine.value("volume_down"));
            break;
        }
        case Silence:
        {
            qDebug() << "Not implemented";
            break;
        }
        case PowerOff:
        {
            break;
        }
    }
    return QString();
}

QString Commands::execute(const QString& commandLine)
{
    QStringList args = commandLine.split(" ");
    QString executable = args.takeFirst();
    QProcess::execute(executable, args);

    return QString(); // TODO
}

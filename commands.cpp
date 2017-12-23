#include "commands.h"

#include <boost/optional.hpp>
#include <QDebug>
#include <QProcess>
#include <QRegExp>

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
        case VolumeStatus:
        {
            return volumeFrom(execute(m_commandToCommandLine.value("volume_status")));
            break;
        }
        case Silence:
        {
            qDebug() << "Not implemented";
            break;
        }
        case PowerOff:
        {
            execute(m_commandToCommandLine.value("power_off"));
            break;
        }
    }
    return QString();
}

QString Commands::volumeFrom(const QString& amixerOutput)
{
    QRegExp rx("\\[(\\d{1,3})%\\]");

    if (rx.indexIn(amixerOutput) > -1)
    {
        QString volume = rx.cap(1);
        qDebug() << volume;
        return volume;
    }
    return QString();
}

QString Commands::execute(const QString& commandLine)
{
    QStringList args = commandLine.split(" ");
    QString executable = args.takeFirst();

    QProcess process;
    process.start(executable, args);
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    return output;
}

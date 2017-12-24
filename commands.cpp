#include "commands.h"

#include <QDebug>
#include <QProcess>
#include <QRegExp>

#include "utils.h"

Commands::Commands()
{

}

QString Commands::loadCommands()
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

    return QString();
}

QString Commands::executeCommand(CommandName commandName, int value)
{
    switch(commandName)
    {
        case SetVolume:
        {
            QString command = m_commandToCommandLine.value("set_volume");
            command.replace("%d", QString(value));
            return execute(command);
        }
        default:
        {
            Q_ASSERT(false);
        }
    }
    return QString();
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
        case Volume:
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
        default:
        {
            Q_ASSERT(false);
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

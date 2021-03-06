#include "commands.h"

#include <QDebug>
#include <QProcess>
#include <QRegExp>

#include "utils.h"

Commands::Commands(QObject* parent)
    :
    QObject(parent)
{
}

Commands::~Commands()
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

QString Commands::executeCommand(Command commandName, int value)
{
    switch(commandName)
    {
        case SetVolume:
        {
            QString command = m_commandToCommandLine.value("set_volume");
            command.replace("%d", QString::number(value));
            execute(command);

            execute(m_commandToCommandLine.value("unmute"));
            return QString();
        }
        default:
        {
            Q_ASSERT(false);
        }
    }
    return QString();
}

Commands::Command Commands::fromString(const QString &command)
{
    // TODO refactor
    if (command == "power_off")
    {
        return PowerOff;
    }
    else
    {
        return Undefined;
    }
}

QString Commands::executeCommand(Command commandName)
{
    switch(commandName)
    {
        case Mute:
        {
            return execute(m_commandToCommandLine.value("mute"));
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

QString Commands::execute(const QString& commandLine)
{
    QStringList args = commandLine.split(" ");
    QString executable = args.takeFirst();

    QProcess process;
    qDebug() << "Executing:" << executable << args;
    process.start(executable, args);
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    return output;
}

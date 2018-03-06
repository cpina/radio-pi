#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QHash>
#include <QObject>

class Commands
{
public:
    enum CommandName
    {
        Undefined,
        Mute,
        PowerOff,
        Volume,
        SetVolume
    };

    Commands();

    QString loadCommands();

    QString executeCommand(CommandName commandName);
    QString executeCommand(CommandName commandName, int value);

    static CommandName fromString(const QString& command);

private:
    QString execute(const QString& command);

    QHash<QString, QString> m_commandToCommandLine;
};

Q_DECLARE_METATYPE(Commands::CommandName)

#endif // COMMANDS_H

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QHash>

class Commands
{
public:
    enum CommandName
    {
        Mute,
        PowerOff,
        Volume,
        SetVolume
    };

    Commands();

    QString loadCommands();

    QString executeCommand(CommandName commandName);
    QString executeCommand(CommandName commandName, int value);

private:
    QString execute(const QString& command);

    QHash<QString, QString> m_commandToCommandLine;
};

#endif // COMMANDS_H

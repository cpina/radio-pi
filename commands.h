#ifndef COMMANDS_H
#define COMMANDS_H

#include <boost/optional.hpp>

#include <QString>
#include <QHash>

class Commands
{
public:
    enum CommandName
    {
        VolumeUp,
        VolumeDown,
        Silence,
        PowerOff
    };

    Commands();

    boost::optional<QString> loadCommands();

    QString executeCommand(CommandName commandName);

private:
    QString execute(const QString& command);

    QHash<QString, QString> m_commandToCommandLine;

};

#endif // COMMANDS_H

#ifndef COMMANDS_H
#define COMMANDS_H

#include <boost/optional.hpp>

#include <QString>

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

    boost::optional<QString> readCommands();

    QString executeCommand(CommandName commandName);

};

#endif // COMMANDS_H

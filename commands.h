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
        PowerOff,
        VolumeStatus
    };

    Commands();

    boost::optional<QString> loadCommands();

    QString executeCommand(CommandName commandName);

private:
    QString execute(const QString& command);
    static QString volumeFrom(const QString& amixerOutput);

    QHash<QString, QString> m_commandToCommandLine;

};

#endif // COMMANDS_H

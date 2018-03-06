#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QHash>
#include <QObject>

class Commands : public QObject
{
    Q_OBJECT

public:
    enum CommandName
    {
        Undefined,
        Mute,
        PowerOff,
        Volume,
        SetVolume
    };
    Q_ENUM(CommandName)

    Commands(QObject* parent = 0);
    ~Commands();

    QString loadCommands();

    QString executeCommand(CommandName commandName);
    QString executeCommand(CommandName commandName, int value);

    static CommandName fromString(const QString& command);

private:
    QString execute(const QString& command);

    QHash<QString, QString> m_commandToCommandLine;
};

#endif // COMMANDS_H

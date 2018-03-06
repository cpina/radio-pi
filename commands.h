#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QHash>
#include <QObject>

class Commands : public QObject
{
    Q_OBJECT

public:
    enum Command
    {
        Undefined,
        Mute,
        PowerOff,
        Volume,
        SetVolume
    };
    Q_ENUM(Command)

    Commands(QObject* parent = 0);
    ~Commands();

    QString loadCommands();

    QString executeCommand(Command commandName);
    QString executeCommand(Command commandName, int value);

    static Command fromString(const QString& command);

private:
    QString execute(const QString& command);

    QHash<QString, QString> m_commandToCommandLine;
};

#endif // COMMANDS_H

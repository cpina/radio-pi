#include "commands.h"

#include <boost/optional.hpp>
#include <QDebug>

Commands::Commands()
{

}

boost::optional<QString> Commands::readCommands()
{

}

QString Commands::executeCommand(CommandName commandName)
{
    switch(commandName)
    {
        case VolumeUp:
        {
            break;
        }
        case VolumeDown:
        {
            break;
        }
        case Silence:
        {
            qDebug() << "Not implemented";
            break;
        }
        case PowerOff:
        {
            break;
        }
    }
}

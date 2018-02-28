#include "volume.h"

Volume::Volume(QObject *parent)
    :
    QObject(parent)
{
    // TODO: check errors and report
    m_commands.loadCommands();

    m_currentVolume = m_settings.readInt(Settings::Volume);
    changeVolume(m_currentVolume);
}

Volume::~Volume()
{

}

void Volume::volumeUp()
{
    m_currentVolume += 5;
    if (m_currentVolume > 100)
    {
        m_currentVolume = 100;
    }
    changeVolume(m_currentVolume);
}

void Volume::volumeDown()
{
    m_currentVolume -= 5;
    if (m_currentVolume < 0)
    {
        m_currentVolume = 0;
    }
    changeVolume(m_currentVolume);
}

void Volume::changeVolume(int volume)
{
    m_commands.executeCommand(Commands::SetVolume, m_currentVolume);
    if (volume == 0)
    {
        m_commands.executeCommand(Commands::Mute);
    }

    m_settings.writeInt(Settings::Volume, m_currentVolume);
    emit volumeChanged(m_currentVolume);
}

int Volume::currentVolume() const
{
    return m_currentVolume;
}

/*
 * Unnused
QString Volume::volumeFrom(const QString& amixerOutput)
{
    QRegExp rx("\\[(\\d{1,3})%\\]");

    if (rx.indexIn(amixerOutput) > -1)
    {
        QString volume = rx.cap(1);
        return volume;
    }
    return QString();
}
*/

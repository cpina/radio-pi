#include "volume.h"

Volume::Volume(QObject *parent)
    :
    QObject(parent)
{
    m_currentVolume = m_settings.readInt(Settings::Volume);
}

Volume::~Volume()
{

}

void Volume::volumeUp()
{
    changeVolume(5);
}

void Volume::volumeDown()
{
    changeVolume(-5);
}

void Volume::changeVolume(int percentage)
{
    m_currentVolume += percentage;

    if (m_currentVolume > 100)
    {
        m_currentVolume = 100;
    }
    else if (m_currentVolume < 0)
    {
        m_currentVolume = 0;
    }

    m_commands.executeCommand(Commands::SetVolume, m_currentVolume);
    if (m_currentVolume == 0)
    {
        m_commands.executeCommand(Commands::Mute);
    }

    m_settings.writeInt(Settings::Volume, m_currentVolume);
    emit volumeChanged(m_currentVolume);
}

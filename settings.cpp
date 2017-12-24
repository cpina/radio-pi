#include "settings.h"

Settings::Settings()
    :
    m_settings(new QSettings("RadioPi", "RadioPi"))

{
    m_keysToStrings.insert(Settings::Volume, "General/Volume");
    m_keysToStrings.insert(Settings::StationNumber, "General/StationNumber");
}

Settings::~Settings()
{
    m_settings.reset();
}

int Settings::readInt(Keys key)
{
    Q_ASSERT(m_keysToStrings.contains(key));
    return m_settings->value(m_keysToStrings.value(key)).toInt();
}

void Settings::writeInt(Keys key, int value)
{
    Q_ASSERT(m_keysToStrings.contains(key));
    m_settings->setValue(m_keysToStrings.value(key), value);
}

QString Settings::readString(Keys key)
{
    Q_ASSERT(m_keysToStrings.contains(key));
    return m_settings->value(m_keysToStrings.value(key)).toString();
}

void Settings::writeString(Keys key, const QString& value)
{
    Q_ASSERT(m_keysToStrings.contains(key));
    m_settings->setValue(m_keysToStrings.value(key), value);
}

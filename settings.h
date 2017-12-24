#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QHash>
#include <QSettings>

class Settings
{
public:
    enum Keys
    {
        Volume,
        StationNumber
    };

    Settings();
    ~Settings();

    int readInt(Keys key);
    void writeInt(Keys key, int value);

    QString readString(Keys Key);
    void writeString(Keys key, const QString& value);

private:
    QHash<Keys, QString> m_keysToStrings;
    QScopedPointer<QSettings> m_settings;
};

#endif // SETTINGS_H

#include "inputhandling.h"

#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#include "utils.h"

InputHandling::InputHandling(QObject *parent)
    :
    QObject(parent)
{
    m_stringToSignal.insert("change_station_up", &InputHandling::stationUp);
    m_stringToSignal.insert("change_station_down", &InputHandling::stationDown);
    m_stringToSignal.insert("volume_up", &InputHandling::volumeUp);
    m_stringToSignal.insert("volume_down", &InputHandling::volumeDown);

    loadKeys();
}

QString InputHandling::loadKeys()
{
    Utils::ErrorOrValue errorOrvalue = Utils::readJsonToVariant("configuration/keys.json");
    m_keyToSignal.clear();

    if (!errorOrvalue.error.isEmpty())
    {
        return errorOrvalue.error;
    }

    QMap<QString, QVariant> keys = errorOrvalue.value.toMap();

    // TODO: refactor this 3 fors
    for (const QString& key : keys.keys())
    {
        SignalType signalName = m_stringToSignal.value(key);

        for (const QVariant& configurationKeys : keys.values(key))
        {
            for (const QVariant& configurationKey : configurationKeys.toList())
            {
                Qt::Key key;
                bool ok;
                int configurationKeyInt = configurationKey.toInt(&ok);

                // The key in the configuration file was an int
                if (ok)
                {
                    key = static_cast<Qt::Key>(configurationKeyInt);
                    m_keyToSignal.insert(key, signalName);
                    continue;
                }

                // The key in the configuration file was a QString very likely representing a Qt::Key
                QMetaEnum metaEnum = QMetaEnum::fromType<Qt::Key>();

                key = static_cast<Qt::Key>(metaEnum.keyToValue("Key_Right", &ok));

                qDebug() << "Key_Right";
                qDebug() << configurationKey;


                key = static_cast<Qt::Key>(metaEnum.keyToValue(configurationKey.toString().toUtf8().constData(), &ok));

                if (ok)
                {
                    m_keyToSignal.insert(key, signalName);
                    continue;
                }
            }
        }
    }

    return QString();
}

bool InputHandling::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);

    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

    if (!keyEvent || keyEvent->type() != QEvent::KeyPress)
    {
        return false;
    }

    QString text = keyEvent->text();
    bool ok;
    text.toInt(&ok);
    if (ok)
    {
        // It's a simple number change to the station
        emit changeToStation(text);
        return true;
    }

    Qt::Key key = static_cast<Qt::Key>(keyEvent->key());
    if (m_keyToSignal.contains(key))
    {
        SignalType signalName = m_keyToSignal.value(key);
        (this->*signalName)();
        return true;
    }
    return false;
}
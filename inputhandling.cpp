#include "inputhandling.h"

#include <QKeyEvent>
#include <QMetaEnum>
#include <QDebug>

#include "utils.h"

InputHandling::InputHandling(QObject *parent)
    :
    QObject(parent)
{
    m_signalName.insert("change_station_up", "stationUp()");
    m_signalName.insert("change_station_down", "stationDown()");
    m_signalName.insert("volume_up", "volumeUp()");
    m_signalName.insert("volume_down", "volumeDown()");

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

    // TODO: refactor the three fors!
    for (const QString& key : keys.keys())
    {
        QString signalName = m_signalName.value(key);

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
        qDebug() << "it should emit:" << m_keyToSignal.value(key);
        emit SIGNAL(m_keyToSignal.value(key));
        return true;
    }
    return false;
    /*

    switch (keyEvent->key())
    {
        case Qt::Key_Up:
        {
            nextRadioStation();
            break;
        }
        case Qt::Key_Down:
        {
            previousRadioStation();
            break;
        }
        case Qt::Key_Right:
        case 161:               // Volume-up in the remote. TODO: in the config file
        case 61:                // Volume-up in the remote in the Raspberrypi
        {
            changeVolume(5);
            break;
        }
        case Qt::Key_Left:
        case 39:                // Volume-down in the remote. TODO: in the config file
        case 45:                // Volume-up in the remote in the Raspberrypi
        {
            changeVolume(-5);
            break;
        }
        default:
        {
            qDebug() << "Not found key:" << keyEvent->key();
        }
    }
*/
}

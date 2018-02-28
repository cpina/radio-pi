#ifndef INPUTHANDLING_H
#define INPUTHANDLING_H

#include <QObject>
#include <QHash>

/** Handles user input. Initially only keyboard input but
 * might be extended for other types like knobs.
 */

class InputHandling : public QObject
{
    Q_OBJECT

public:
    InputHandling(QObject* parent = 0);

protected:
    bool eventFilter(QObject* object, QEvent* event);

Q_SIGNALS:
    void changeToStation(const QString& station);

    void stationUp();
    void stationDown();

    void volumeUp();
    void volumeDown();

private:
    QString loadKeys();
    QHash<Qt::Key, QString> m_keyToSignal;
    QHash<QString, QString> m_signalName;
};

#endif // INPUTHANDLING_H

#ifndef INPUTHANDLING_H
#define INPUTHANDLING_H

#include <QTimer>
#include <QObject>
#include <QHash>
#include <QSet>

/** Handles user input. Initially only keyboard input but
 * might be extended for other types like knobs.
 */

class InputHandling : public QObject
{
    Q_OBJECT

public:
    InputHandling(QObject* parent = 0);

    void setPossibleNumbers(const QSet<QString>& numbers);

protected:
    bool eventFilter(QObject* object, QEvent* event);

Q_SIGNALS:
    void changeToStation(const QString& station);

    void stationUp();
    void stationDown();

    void volumeUp();
    void volumeDown();

    void powerOff();

private Q_SLOTS:
    void finishedWritingStationNumber();

private:
    int startsWith(const QString& text);

    using SignalType = decltype(&InputHandling::stationUp);

    QString loadKeys();
    QHash<Qt::Key, SignalType> m_keyToSignal;
    QHash<QString, SignalType> m_stringToSignal;

    QSet<QString> m_possibleNumbers;

    QString m_currentInput;
    QTimer m_waitForKeys;
};

#endif // INPUTHANDLING_H

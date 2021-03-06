#ifndef ACTIONS_H
#define ACTIONS_H

#include <QString>

#include "utils.h"

class Actions
{
public:
    Actions();

    QString loadActions();
    QVariant action(const QString& key) const;

    QSet<QString> numbers() const;

private:
    QHash<QString, QVariant> m_keyToAction;
};

#endif // ACTIONS_H

#ifndef UTILS_H
#define UTILS_H

#include <QVariant>

class Utils
{
public:
    struct ErrorOrValue
    {
        QString error;
        QVariant value;
    };

    static ErrorOrValue readJsonToVariant(const QString& filePath);

private:
    Utils();
};

#endif // UTILS_H

#include "utils.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

Utils::Utils()
{

}

Utils::ErrorOrValue Utils::readJsonToVariant(const QString& filePath)
{
    QString val;
    QFile file;

    QString applicationPath = QCoreApplication::applicationDirPath();
    QString configurationAbsolutePath = QDir::cleanPath(applicationPath + QDir::separator() + filePath);

    file.setFileName(configurationAbsolutePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ErrorOrValue errorOrvalue;
        errorOrvalue.error = QObject::tr("Cannot open: %1").arg(configurationAbsolutePath);
        return errorOrvalue;
    }

    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

    QVariant variant = d.toVariant();

    ErrorOrValue errorOrValue;
    errorOrValue.value = variant;

    return errorOrValue;
}

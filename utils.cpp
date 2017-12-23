#include "utils.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QFileInfo>

Utils::Utils()
{

}

Utils::ErrorOrValue Utils::readJsonToVariant(const QString& filePath)
{
    QString val;
    QFile file;

    QFileInfo configurationFileInfo(filePath);
    QString configurationAbsoluteFilePath = configurationFileInfo.absoluteFilePath();

    file.setFileName(configurationAbsoluteFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ErrorOrValue errorOrvalue;
        errorOrvalue.error = QObject::tr("Cannot open: %1").arg(configurationAbsoluteFilePath);
    }

    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

    QVariant variant = d.toVariant();

    ErrorOrValue errorOrValue;
    errorOrValue.value = variant;

    return errorOrValue;
}

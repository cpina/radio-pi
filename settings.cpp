#include "settings.h"

#include <QSettings>

Settings::Settings()
{
    QSettings settings("RadioPi", "RadioPi");
}

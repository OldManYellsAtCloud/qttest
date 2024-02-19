#include "settings.h"

#include <QFileInfo>
#include <QDebug>
#include <ios>


void Settings::init(QString path)
{
    QFileInfo f {path};
    if (!f.exists() || f.isDir()) {
        qDebug() << f << " must be an existing file!";
        throw std::ios_base::failure(path.toStdString() + " is not a file!");
    }
    qSettings = new QSettings{path, QSettings::IniFormat};
}

QVariant Settings::getValue(QString key)
{
    if (qSettings == nullptr) {
        throw std::ios_base::failure("Settings has not been initialized with the config file!");
    }

    return qSettings->value(key);
}

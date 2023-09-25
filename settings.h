#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings
{
private:
    Settings(){};
    QSettings* qSettings;

public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;
    void init(QString path);
    QVariant getValue(QString key);

    static Settings& getSettings(){
        static Settings s;
        return s;
    }
};

#endif // SETTINGS_H

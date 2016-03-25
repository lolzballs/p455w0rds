#pragma once

#include <QSettings>

class Settings
{
private:
    Settings();
    Settings(Settings const& copy);
    Settings& operator=(Settings const& copy);

    QSettings* settings;

public:
    QString passdir;
    QString gpgexe;
    QString gpguser;

    static Settings& getInstance()
    {
        static Settings instance;
        return instance;
    }

    QString findGPGLocation();
    void readSettings();
    void writeSettings();
};
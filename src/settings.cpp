#include "settings.h"

#include <QDir>
#include <QProcess>

Settings::Settings()
{
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "p455w0rds");
}

QString Settings::findGPGLocation()
{
    QProcess p;
#if defined(Q_OS_WIN)
    p.start("where", QStringList() << "gpg");
#elif defined(Q_OS_UNIX)
    p.start("whereis", QStringList() << "gpg");
#else
    qDebug() << "Unknown architecture!";
    return "";
#endif
    if (!p.waitForStarted()) {
        qCritical("Unable to start where/whereis not started!");
    }

    p.waitForFinished();
    return p.readAllStandardOutput().simplified();
}


void Settings::readSettings()
{
    passdir = settings->value("directory", QDir::home().filePath("Documents/p455w0rds")).toString();
    QString path = settings->value("gpgexecutable").toString();
    if (path.isEmpty())
    {
        gpgexe = findGPGLocation();
    }
    else
    {
        gpgexe = path;
    }
    gpguser = settings->value("gpguser").toString();
}

void Settings::writeSettings() {
    settings->setValue("directory", passdir);
    settings->setValue("gpgexecutable", gpgexe);
    settings->setValue("gpguser", gpguser);
}
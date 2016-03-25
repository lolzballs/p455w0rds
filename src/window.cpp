#include "window.h"
#include "new_password_dialog.h"

#include <QDebug>
#include <QSettings>
#include <QMenuBar>
#include <QMessageBox>
#include <QProcess>

Window::Window() {
    setObjectName("window");

    // Central Widget
    content = new QSplitter(this);
    content->setOrientation(Qt::Vertical);
    setCentralWidget(content);

    createActions();
    createMenus();

    readSettings();

    qDebug() << "Passwords directory: " + passdir.path();

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::Files);
    fileModel->setNameFilters(QStringList("*.p455"));
    QModelIndex root = fileModel->setRootPath(passdir.path());

    fileList = new QListView(this);
    fileList->setModel(fileModel);
    fileList->setRootIndex(root);
    connect(fileList, &QListView::doubleClicked, this, &Window::fileClicked);
    content->addWidget(fileList);

    fileView = new QTextEdit(this);
    fileView->setTextInteractionFlags(Qt::TextSelectableByMouse);
    fileView->setEnabled(false);
    content->addWidget(fileView);
}

void Window::createActions() {
    actAbout = new QAction("About", this);
    connect(actAbout, &QAction::triggered, this, &Window::about);
    actNew = new QAction("New", this);
    connect(actNew, &QAction::triggered, this, &Window::newPass);
    actSettings = new QAction("Settings", this);
    connect(actSettings, &QAction::triggered, this, &Window::openSettings);
    actExit = new QAction("Exit", this);
    connect(actExit, &QAction::triggered, this, &Window::close);
}

void Window::createMenus() {
    menuFile = menuBar()->addMenu("File");
    menuFile->addAction(actNew);
    menuFile->addAction(actSettings);
    menuFile->addAction(actExit);
    menuHelp = menuBar()->addMenu("Help");
    menuHelp->addAction(actAbout);
}

void Window::readSettings() {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "p455w0rds");
    passdir = QDir(settings.value("directory", QDir::home().filePath("Documents/p455w0rds")).toString());
    QString path = settings.value("gpgexecutable").toString();
    if (path.isEmpty()) {
        gpgexe = findGPGLocation();
    } else {
        gpgexe = path;
    }
    gpguser = settings.value("gpguser").toString();
}

void Window::writeSettings() {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "p455w0rds");
    settings.setValue("directory", passdir.path());
    settings.setValue("gpgexecutable", gpgexe);
    settings.setValue("gpguser", gpguser);
}

QString Window::findGPGLocation() {
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

QString Window::decrypt(QString file) {
    QProcess p;
    p.start(gpgexe, QStringList() << "--decrypt" << file);
    if (!p.waitForStarted()) {
        qFatal("Failed to start gpg");
    }

    p.waitForFinished();
    return p.readAllStandardOutput().simplified();
}

QString Window::encrypt(QString pass) {
    QProcess p;
    p.start(gpgexe, QStringList() << "--encrypt" << "--armor" << "-r" << gpguser);
    if (!p.waitForStarted()) {
        qFatal("Failed to start gpg");
    }
    p.write(pass.toUtf8());
    p.closeWriteChannel();

    p.waitForFinished();
    return p.readAllStandardOutput();
}

void Window::fileClicked(const QModelIndex& index) {
    QString file = passdir.filePath(fileModel->data(index).toString());
    fileView->setEnabled(true);
    fileView->setText(decrypt(file));
}

void Window::closeEvent(QCloseEvent*) {
    writeSettings();
}

void Window::about() {
    QMessageBox::about(this, "About", "<b>p455w0rds</b> is an application written in Qt to GPG encrypt passwords for storage.");
}

void Window::openSettings()
{

}

void Window::newPass() {
    NewPasswordDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString pass = dialog.getPass();
        QString encrypted = encrypt(pass);

        QFile file(passdir.filePath(name + ".p455"));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open: " + file.fileName();
            return;
        }
        QTextStream out(&file);
        out << encrypted;
        file.close();
    }
}

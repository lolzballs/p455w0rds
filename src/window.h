#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QDir>
#include <QListView>
#include <QFileSystemModel>
#include <QTextEdit>
#include <QSplitter>

class Window : public QMainWindow {
    Q_OBJECT

public:
    Window();

protected:
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;

private:
    QDir passdir;
    QString gpgexe;
    QString gpguser;

    QFileSystemModel* fileModel;

    QSplitter* content;
    QListView* fileList;
    QTextEdit* fileView;

    QMenu* menuFile;
    QMenu* menuHelp;

    QAction* actAbout;
    QAction* actNew;
    QAction* actSettings;
    QAction* actExit;

    void createActions();
    void createMenus();

    void readSettings();
    void writeSettings();

    QString findGPGLocation();
    QString decrypt(QString file);
    QString encrypt(QString pass);

private slots:
    void fileClicked(const QModelIndex& index);

    void about();
    void openSettings();
    void newPass();
};

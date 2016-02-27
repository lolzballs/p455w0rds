#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QtWidgets/qdialogbuttonbox.h>

class NewPasswordDialog : public QDialog {
    Q_OBJECT

public:
    NewPasswordDialog(QWidget* parent = 0);
    QString getName() { return name; };
    QString getPass() { return pass; };

public slots:
    void accept() Q_DECL_OVERRIDE;

private:
    QLineEdit* editName;
    QLineEdit* editPass;
    QDialogButtonBox* btnBox;
    QString name;
    QString pass;

};

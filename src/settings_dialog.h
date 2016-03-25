#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    SettingsDialog(QWidget* parent = 0);

public slots:
    void accept() Q_DECL_OVERRIDE;

private:
    QDialogButtonBox* btnBox;
    QLineEdit* editPath;
    QLineEdit* editGPGPath;
    QLineEdit* editGPGUser;

};

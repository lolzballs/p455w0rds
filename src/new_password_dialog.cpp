#include "new_password_dialog.h"

#include <QFormLayout>

NewPasswordDialog::NewPasswordDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("New Password");
    QFormLayout* mainLayout = new QFormLayout(this);

    editName = new QLineEdit;
    mainLayout->addRow("Name:", editName);

    editPass = new QLineEdit;
    editPass->setEchoMode(QLineEdit::Password);
    mainLayout->addRow("Password:", editPass);

    btnBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    mainLayout->addRow(btnBox);
    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void NewPasswordDialog::accept() {
    name = editName->text();
    pass = editPass->text();
    done(Accepted);
}
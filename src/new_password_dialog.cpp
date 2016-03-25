#include "new_password_dialog.h"

#include <QFormLayout>

NewPasswordDialog::NewPasswordDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("New Password");
    QFormLayout* mainLayout = new QFormLayout;
    setLayout(mainLayout);

    editName = new QLineEdit;
    mainLayout->addRow("Name:", editName);

    editPass = new QLineEdit;
    editPass->setEchoMode(QLineEdit::Password);
    mainLayout->addRow("Password:", editPass);

    btnBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    mainLayout->addRow(btnBox);
    connect(btnBox, &QDialogButtonBox::accepted, this, &NewPasswordDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this, &NewPasswordDialog::reject);
}

void NewPasswordDialog::accept() {
    name = editName->text();
    pass = editPass->text();
    done(Accepted);
}
#include "settings_dialog.h"
#include "settings.h"

#include <QFormLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Settings");

    QFormLayout* mainLayout = new QFormLayout;
    setLayout(mainLayout);

    QHBoxLayout* pathLayout = new QHBoxLayout;
    mainLayout->addRow("p455w0rds Path:", pathLayout);

    editPath = new QLineEdit(this);
    editPath->setText(Settings::getInstance().passdir);
    pathLayout->addWidget(editPath);

    QPushButton* btnPath = new QPushButton(this);
    btnPath->setText("...");
    btnPath->setMaximumWidth(btnPath->fontMetrics().boundingRect(btnPath->text()).width() + 10);
    btnPath->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    pathLayout->addWidget(btnPath);
    connect(btnPath, &QPushButton::clicked, this, [=]()
    {
        QString path = QFileDialog::getExistingDirectory(this, "Choose Directory for p455w0rds", editPath->text());
        if (!path.isEmpty())
        {
            editPath->setText(path);
        }
    });

    QHBoxLayout* gpgPathLayout = new QHBoxLayout;
    mainLayout->addRow("GPG Executable:", gpgPathLayout);

    editGPGPath = new QLineEdit(this);
    editGPGPath->setText(Settings::getInstance().gpgexe);
    gpgPathLayout->addWidget(editGPGPath);

    QPushButton* btnExe = new QPushButton(this);
    btnExe->setText("...");
    btnExe->setMaximumWidth(btnPath->fontMetrics().boundingRect(btnPath->text()).width() + 10);
    btnExe->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    gpgPathLayout->addWidget(btnExe);
    connect(btnExe, &QPushButton::clicked, this, [=]()
    {
        QString path = QFileDialog::getOpenFileName(this, "Select GPG Executable", editGPGPath->text());
        if (!path.isEmpty())
        {
            editGPGPath->setText(path);
        }
    });

    QHBoxLayout* gpgUserLayout = new QHBoxLayout;
    mainLayout->addRow("GPG User:", gpgUserLayout);

    editGPGUser = new QLineEdit(this);
    editGPGUser->setText(Settings::getInstance().gpguser);
    gpgUserLayout->addWidget(editGPGUser);

    btnBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    mainLayout->addRow(btnBox);
    connect(btnBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
}

void SettingsDialog::accept() {
    Settings& settings = Settings::getInstance();
    settings.passdir = editPath->text();
    settings.gpgexe = editGPGPath->text();
    settings.gpguser = editGPGUser->text();
    settings.writeSettings();

    done(Accepted);
}
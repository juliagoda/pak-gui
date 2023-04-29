#include "packageinputwindow.h"

#include "logger.h"

#include <QPushButton>
#include <QDialogButtonBox>


PackageInputWindow::PackageInputWindow(QWidget* parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    setWindowTitle(i18n("Package input"));
    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(m_ui.package_lineedit, &QLineEdit::textEdited, this, &PackageInputWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit packageNameInserted(m_ui.package_lineedit->text()); }, Qt::AutoConnection);
}


void PackageInputWindow::toggleOkButton(const QString& new_package_name)
{
    auto ok_button = m_ui.buttonBox->button(QDialogButtonBox::Ok);
    ok_button->setEnabled(!new_package_name.isEmpty());
    Logger::logger()->logDebug(new_package_name.isEmpty() ? "Package name is empty" : "Package name is not empty");
    Logger::logger()->logDebug(ok_button->isEnabled() ? "OK button is now enabled" : "OK button is now disabled");
}


#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'packageinput.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKAGEINPUT_H
#define UI_PACKAGEINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PackageInputWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *package_lineedit;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *PackageInputWindow)
    {
        if (PackageInputWindow->objectName().isEmpty())
            PackageInputWindow->setObjectName(QString::fromUtf8("PackageInputWindow"));
        PackageInputWindow->resize(450, 150);
        verticalLayout = new QVBoxLayout(PackageInputWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        label = new QLabel(PackageInputWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        package_lineedit = new QLineEdit(PackageInputWindow);
        package_lineedit->setObjectName(QString::fromUtf8("package_lineedit"));

        verticalLayout->addWidget(package_lineedit);

        buttonBox = new QDialogButtonBox(PackageInputWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PackageInputWindow);

        QMetaObject::connectSlotsByName(PackageInputWindow);
    } // setupUi

    void retranslateUi(QWidget *PackageInputWindow)
    {
        PackageInputWindow->setWindowTitle(tr2i18n("Form", nullptr));
        label->setText(tr2i18n("Enter the package name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PackageInputWindow: public Ui_PackageInputWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PACKAGEINPUT_H


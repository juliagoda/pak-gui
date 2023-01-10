#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'packagesinfosettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKAGESINFOSETTINGS_H
#define UI_PACKAGESINFOSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "kactionselector.h"

QT_BEGIN_NAMESPACE

class Ui_PackagesInfoSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    KActionSelector *packages_info_selector;

    void setupUi(QWidget *PackagesInfoSettings)
    {
        if (PackagesInfoSettings->objectName().isEmpty())
            PackagesInfoSettings->setObjectName(QString::fromUtf8("PackagesInfoSettings"));
        PackagesInfoSettings->resize(686, 548);
        verticalLayout_2 = new QVBoxLayout(PackagesInfoSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(PackagesInfoSettings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 664, 526));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        packages_info_selector = new KActionSelector(scrollAreaWidgetContents);
        packages_info_selector->setObjectName(QString::fromUtf8("packages_info_selector"));

        verticalLayout_3->addWidget(packages_info_selector);


        verticalLayout_4->addLayout(verticalLayout_3);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PackagesInfoSettings);

        QMetaObject::connectSlotsByName(PackagesInfoSettings);
    } // setupUi

    void retranslateUi(QWidget *PackagesInfoSettings)
    {
        PackagesInfoSettings->setWindowTitle(tr2i18n("Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PackagesInfoSettings: public Ui_PackagesInfoSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PACKAGESINFOSETTINGS_H


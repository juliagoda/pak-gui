#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'logssettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGSSETTINGS_H
#define UI_LOGSSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogsSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayout_2;
    QCheckBox *kcfg_save_logs_into_file;
    QLineEdit *kcfg_logs_filename;
    QLabel *label;
    QLineEdit *kcfg_logs_filepath;
    QCheckBox *kcfg_show_debug;
    QCheckBox *kcfg_hide_info_logs;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LogsSettings)
    {
        if (LogsSettings->objectName().isEmpty())
            LogsSettings->setObjectName(QString::fromUtf8("LogsSettings"));
        LogsSettings->resize(508, 433);
        verticalLayout_2 = new QVBoxLayout(LogsSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(LogsSettings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 486, 411));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        kcfg_save_logs_into_file = new QCheckBox(scrollAreaWidgetContents);
        kcfg_save_logs_into_file->setObjectName(QString::fromUtf8("kcfg_save_logs_into_file"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, kcfg_save_logs_into_file);

        kcfg_logs_filename = new QLineEdit(scrollAreaWidgetContents);
        kcfg_logs_filename->setObjectName(QString::fromUtf8("kcfg_logs_filename"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, kcfg_logs_filename);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label);

        kcfg_logs_filepath = new QLineEdit(scrollAreaWidgetContents);
        kcfg_logs_filepath->setObjectName(QString::fromUtf8("kcfg_logs_filepath"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, kcfg_logs_filepath);


        verticalLayout_5->addLayout(formLayout_2);

        kcfg_show_debug = new QCheckBox(scrollAreaWidgetContents);
        kcfg_show_debug->setObjectName(QString::fromUtf8("kcfg_show_debug"));

        verticalLayout_5->addWidget(kcfg_show_debug);

        kcfg_hide_info_logs = new QCheckBox(scrollAreaWidgetContents);
        kcfg_hide_info_logs->setObjectName(QString::fromUtf8("kcfg_hide_info_logs"));

        verticalLayout_5->addWidget(kcfg_hide_info_logs);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LogsSettings);

        QMetaObject::connectSlotsByName(LogsSettings);
    } // setupUi

    void retranslateUi(QWidget *LogsSettings)
    {
        LogsSettings->setWindowTitle(tr2i18n("Form", nullptr));
        kcfg_save_logs_into_file->setText(tr2i18n("Save logs into file", nullptr));
        label->setText(tr2i18n("in path", nullptr));
        kcfg_show_debug->setText(tr2i18n("show debug", nullptr));
        kcfg_hide_info_logs->setText(tr2i18n("hide information logs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogsSettings: public Ui_LogsSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGSSETTINGS_H


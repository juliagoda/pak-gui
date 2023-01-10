#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'generalsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALSETTINGS_H
#define UI_GENERALSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralSettings
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QSpinBox *kcfg_internet_reconnection_time_in_minutes;
    QSpinBox *kcfg_update_check_time_in_days;
    QSpinBox *kcfg_update_check_time_in_hours;
    QSpinBox *kcfg_history_store_time_in_days;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label_9;
    QSpinBox *kcfg_history_file_size_limit_in_Mb;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label;
    QLabel *label_3;
    QSpinBox *kcfg_update_check_time_in_minutes;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *kcfg_overwrite_full_history_file;
    QCheckBox *kcfg_use_system_tray_icon;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *GeneralSettings)
    {
        if (GeneralSettings->objectName().isEmpty())
            GeneralSettings->setObjectName(QString::fromUtf8("GeneralSettings"));
        GeneralSettings->resize(747, 674);
        verticalLayout = new QVBoxLayout(GeneralSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(GeneralSettings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 725, 652));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        kcfg_internet_reconnection_time_in_minutes = new QSpinBox(scrollAreaWidgetContents);
        kcfg_internet_reconnection_time_in_minutes->setObjectName(QString::fromUtf8("kcfg_internet_reconnection_time_in_minutes"));

        gridLayout->addWidget(kcfg_internet_reconnection_time_in_minutes, 2, 1, 1, 1);

        kcfg_update_check_time_in_days = new QSpinBox(scrollAreaWidgetContents);
        kcfg_update_check_time_in_days->setObjectName(QString::fromUtf8("kcfg_update_check_time_in_days"));

        gridLayout->addWidget(kcfg_update_check_time_in_days, 3, 1, 1, 1);

        kcfg_update_check_time_in_hours = new QSpinBox(scrollAreaWidgetContents);
        kcfg_update_check_time_in_hours->setObjectName(QString::fromUtf8("kcfg_update_check_time_in_hours"));

        gridLayout->addWidget(kcfg_update_check_time_in_hours, 3, 3, 1, 1);

        kcfg_history_store_time_in_days = new QSpinBox(scrollAreaWidgetContents);
        kcfg_history_store_time_in_days->setObjectName(QString::fromUtf8("kcfg_history_store_time_in_days"));

        gridLayout->addWidget(kcfg_history_store_time_in_days, 0, 1, 1, 1);

        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 3, 2, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 3, 0, 1, 1);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 2, 2, 1, 1);

        kcfg_history_file_size_limit_in_Mb = new QSpinBox(scrollAreaWidgetContents);
        kcfg_history_file_size_limit_in_Mb->setObjectName(QString::fromUtf8("kcfg_history_file_size_limit_in_Mb"));

        gridLayout->addWidget(kcfg_history_file_size_limit_in_Mb, 1, 1, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 3, 6, 1, 1);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 3, 4, 1, 1);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        kcfg_update_check_time_in_minutes = new QSpinBox(scrollAreaWidgetContents);
        kcfg_update_check_time_in_minutes->setObjectName(QString::fromUtf8("kcfg_update_check_time_in_minutes"));

        gridLayout->addWidget(kcfg_update_check_time_in_minutes, 3, 5, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        kcfg_overwrite_full_history_file = new QCheckBox(scrollAreaWidgetContents);
        kcfg_overwrite_full_history_file->setObjectName(QString::fromUtf8("kcfg_overwrite_full_history_file"));

        verticalLayout_3->addWidget(kcfg_overwrite_full_history_file);

        kcfg_use_system_tray_icon = new QCheckBox(scrollAreaWidgetContents);
        kcfg_use_system_tray_icon->setObjectName(QString::fromUtf8("kcfg_use_system_tray_icon"));

        verticalLayout_3->addWidget(kcfg_use_system_tray_icon);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout_3);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(GeneralSettings);

        QMetaObject::connectSlotsByName(GeneralSettings);
    } // setupUi

    void retranslateUi(QWidget *GeneralSettings)
    {
        label_11->setText(tr2i18n("day(s)", nullptr));
        label_10->setText(tr2i18n("Check packages ready to update every ", nullptr));
        label_8->setText(tr2i18n("Try to reconnect to the internet every ", nullptr));
        label_2->setText(tr2i18n("days", nullptr));
        label_9->setText(tr2i18n("minutes", nullptr));
        label_13->setText(tr2i18n("minutes", nullptr));
        label_12->setText(tr2i18n("hours", nullptr));
        label->setText(tr2i18n("Store operations history for ", nullptr));
        label_3->setText(tr2i18n("Set limit of single operations history size to  ", nullptr));
        label_4->setText(tr2i18n("MB", nullptr));
        kcfg_overwrite_full_history_file->setText(tr2i18n("Overwrite operations history file (when full size)", nullptr));
        kcfg_use_system_tray_icon->setText(tr2i18n("Use system tray icon", nullptr));
        (void)GeneralSettings;
    } // retranslateUi

};

namespace Ui {
    class GeneralSettings: public Ui_GeneralSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GENERALSETTINGS_H


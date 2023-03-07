#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
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
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *operations_history_store_days;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *operations_history_store_size;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpinBox *operations_refresh_hours;
    QLabel *label_6;
    QSpinBox *operations_refresh_minutes;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QSpinBox *internet_reconnection_minutes;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QSpinBox *new_packages_to_update_check_days;
    QLabel *label_11;
    QSpinBox *new_packages_to_update_check_hours;
    QLabel *label_12;
    QSpinBox *new_packages_to_update_check_minutes;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *overwrite_full_history_file_checkbox;
    QCheckBox *minimalize_to_tray_checkbox;
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
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        operations_history_store_days = new QSpinBox(scrollAreaWidgetContents);
        operations_history_store_days->setObjectName(QString::fromUtf8("operations_history_store_days"));

        horizontalLayout->addWidget(operations_history_store_days);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        operations_history_store_size = new QSpinBox(scrollAreaWidgetContents);
        operations_history_store_size->setObjectName(QString::fromUtf8("operations_history_store_size"));

        horizontalLayout_2->addWidget(operations_history_store_size);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        operations_refresh_hours = new QSpinBox(scrollAreaWidgetContents);
        operations_refresh_hours->setObjectName(QString::fromUtf8("operations_refresh_hours"));

        horizontalLayout_3->addWidget(operations_refresh_hours);

        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        operations_refresh_minutes = new QSpinBox(scrollAreaWidgetContents);
        operations_refresh_minutes->setObjectName(QString::fromUtf8("operations_refresh_minutes"));

        horizontalLayout_3->addWidget(operations_refresh_minutes);

        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_8);

        internet_reconnection_minutes = new QSpinBox(scrollAreaWidgetContents);
        internet_reconnection_minutes->setObjectName(QString::fromUtf8("internet_reconnection_minutes"));

        horizontalLayout_4->addWidget(internet_reconnection_minutes);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_10);

        new_packages_to_update_check_days = new QSpinBox(scrollAreaWidgetContents);
        new_packages_to_update_check_days->setObjectName(QString::fromUtf8("new_packages_to_update_check_days"));

        horizontalLayout_5->addWidget(new_packages_to_update_check_days);

        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_5->addWidget(label_11);

        new_packages_to_update_check_hours = new QSpinBox(scrollAreaWidgetContents);
        new_packages_to_update_check_hours->setObjectName(QString::fromUtf8("new_packages_to_update_check_hours"));

        horizontalLayout_5->addWidget(new_packages_to_update_check_hours);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);

        new_packages_to_update_check_minutes = new QSpinBox(scrollAreaWidgetContents);
        new_packages_to_update_check_minutes->setObjectName(QString::fromUtf8("new_packages_to_update_check_minutes"));

        horizontalLayout_5->addWidget(new_packages_to_update_check_minutes);

        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_5->addWidget(label_13);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_5);

        overwrite_full_history_file_checkbox = new QCheckBox(scrollAreaWidgetContents);
        overwrite_full_history_file_checkbox->setObjectName(QString::fromUtf8("overwrite_full_history_file_checkbox"));

        verticalLayout_3->addWidget(overwrite_full_history_file_checkbox);

        minimalize_to_tray_checkbox = new QCheckBox(scrollAreaWidgetContents);
        minimalize_to_tray_checkbox->setObjectName(QString::fromUtf8("minimalize_to_tray_checkbox"));

        verticalLayout_3->addWidget(minimalize_to_tray_checkbox);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Preferred);

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
        label->setText(tr2i18n("Store operations history for ", nullptr));
        label_2->setText(tr2i18n("days", nullptr));
        label_3->setText(tr2i18n("Set limit of single operations history size to  ", nullptr));
        label_4->setText(tr2i18n("MB", nullptr));
        label_5->setText(tr2i18n("Refresh every ", nullptr));
        label_6->setText(tr2i18n("hours", nullptr));
        label_7->setText(tr2i18n("minutes", nullptr));
        label_8->setText(tr2i18n("Try to reconnect to the internet every ", nullptr));
        label_9->setText(tr2i18n("minutes", nullptr));
        label_10->setText(tr2i18n("Check packages ready to update every ", nullptr));
        label_11->setText(tr2i18n("day(s)", nullptr));
        label_12->setText(tr2i18n("hours", nullptr));
        label_13->setText(tr2i18n("minutes", nullptr));
        overwrite_full_history_file_checkbox->setText(tr2i18n("Overwrite operations history file (when full size)", nullptr));
        minimalize_to_tray_checkbox->setText(tr2i18n("Always minimalize to tray", nullptr));
        (void)GeneralSettings;
    } // retranslateUi

};

namespace Ui {
    class GeneralSettings: public Ui_GeneralSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTINGS_H


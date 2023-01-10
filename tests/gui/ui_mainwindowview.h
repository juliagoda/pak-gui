#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'mainwindowview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWVIEW_H
#define UI_MAINWINDOWVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "kled.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowView
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_13;
    QLabel *actions_spinning_animation_label;
    QCheckBox *progress_view_checkbox;
    QHBoxLayout *horizontalLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *installed_packages_layout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *installed_packages_label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QCheckBox *sort_installed_packages;
    QLineEdit *search_installed_packages_lineedit;
    QWidget *remove_spinning_widget;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer;
    QLabel *remove_spinning_label;
    QSpacerItem *verticalSpacer_2;
    QListWidget *installed_packages_list;
    QScrollArea *installed_preview_area;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *text_browser_tab_uninstall;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *uninstall_packages_button;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *console_view_uninstall;
    QCheckBox *search_installed_packages_checkbox;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *packages_to_update_layout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *packages_to_update_label;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *sort_packages_to_update;
    QLineEdit *search_packages_to_update_lineedit;
    QWidget *update_spinning_widget;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QSpacerItem *verticalSpacer_3;
    QLabel *update_spinning_label;
    QSpacerItem *verticalSpacer_4;
    QListWidget *packages_to_update_list;
    QScrollArea *updated_preview_area;
    QWidget *scrollAreaWidgetContents_5;
    QVBoxLayout *verticalLayout_5;
    QTextBrowser *text_browser_tab_update;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *update_packages_button;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *console_view_update;
    QCheckBox *search_packages_to_update_checkbox;
    QCheckBox *check_all_updates_checkbox;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *available_packages_layout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *accessible_packages;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *sort_available_packages;
    QLineEdit *search_available_packages_lineedit;
    QWidget *installation_spinning_widget;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_14;
    QSpacerItem *verticalSpacer_5;
    QLabel *installation_spinning_label;
    QSpacerItem *verticalSpacer_6;
    QListWidget *available_packages_list;
    QScrollArea *available_preview_area;
    QWidget *scrollAreaWidgetContents_6;
    QVBoxLayout *verticalLayout_6;
    QTextBrowser *text_browser_tab_install;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *install_packages_button;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *console_view_install;
    QCheckBox *search_available_packages_checkbox;
    QWidget *leds_widget;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_12;
    KLed *repos_kled;
    QLabel *repo_led_label;
    KLed *aur_kled;
    QLabel *aur_led_label;
    KLed *polaur_kled;
    QLabel *polaur_led_label;
    QSpacerItem *horizontalSpacer_14;

    void setupUi(QWidget *MainWindowView)
    {
        if (MainWindowView->objectName().isEmpty())
            MainWindowView->setObjectName(QString::fromUtf8("MainWindowView"));
        MainWindowView->resize(860, 632);
        MainWindowView->setAutoFillBackground(true);
        gridLayout = new QGridLayout(MainWindowView);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        actions_spinning_animation_label = new QLabel(MainWindowView);
        actions_spinning_animation_label->setObjectName(QString::fromUtf8("actions_spinning_animation_label"));
        actions_spinning_animation_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(actions_spinning_animation_label);

        progress_view_checkbox = new QCheckBox(MainWindowView);
        progress_view_checkbox->setObjectName(QString::fromUtf8("progress_view_checkbox"));

        horizontalLayout_10->addWidget(progress_view_checkbox);


        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(5, 5, 5, 5);
        scrollArea = new QScrollArea(MainWindowView);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 260, 702));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        installed_packages_layout = new QHBoxLayout();
        installed_packages_layout->setObjectName(QString::fromUtf8("installed_packages_layout"));
        installed_packages_layout->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        installed_packages_layout->addItem(horizontalSpacer_2);

        installed_packages_label = new QLabel(scrollAreaWidgetContents);
        installed_packages_label->setObjectName(QString::fromUtf8("installed_packages_label"));
        QFont font;
        font.setBold(true);
        installed_packages_label->setFont(font);
        installed_packages_label->setAlignment(Qt::AlignCenter);
        installed_packages_label->setWordWrap(true);

        installed_packages_layout->addWidget(installed_packages_label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        installed_packages_layout->addItem(horizontalSpacer);


        verticalLayout->addLayout(installed_packages_layout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        sort_installed_packages = new QCheckBox(scrollAreaWidgetContents);
        sort_installed_packages->setObjectName(QString::fromUtf8("sort_installed_packages"));

        horizontalLayout->addWidget(sort_installed_packages);

        search_installed_packages_lineedit = new QLineEdit(scrollAreaWidgetContents);
        search_installed_packages_lineedit->setObjectName(QString::fromUtf8("search_installed_packages_lineedit"));

        horizontalLayout->addWidget(search_installed_packages_lineedit);


        verticalLayout->addLayout(horizontalLayout);

        remove_spinning_widget = new QWidget(scrollAreaWidgetContents);
        remove_spinning_widget->setObjectName(QString::fromUtf8("remove_spinning_widget"));
        verticalLayout_8 = new QVBoxLayout(remove_spinning_widget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(3, 3, 3, 3);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        remove_spinning_label = new QLabel(remove_spinning_widget);
        remove_spinning_label->setObjectName(QString::fromUtf8("remove_spinning_label"));
        remove_spinning_label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(remove_spinning_label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);


        verticalLayout_8->addLayout(verticalLayout_7);


        verticalLayout->addWidget(remove_spinning_widget);

        installed_packages_list = new QListWidget(scrollAreaWidgetContents);
        installed_packages_list->setObjectName(QString::fromUtf8("installed_packages_list"));

        verticalLayout->addWidget(installed_packages_list);

        installed_preview_area = new QScrollArea(scrollAreaWidgetContents);
        installed_preview_area->setObjectName(QString::fromUtf8("installed_preview_area"));
        installed_preview_area->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 240, 210));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        text_browser_tab_uninstall = new QTextBrowser(scrollAreaWidgetContents_4);
        text_browser_tab_uninstall->setObjectName(QString::fromUtf8("text_browser_tab_uninstall"));
        text_browser_tab_uninstall->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: black;\n"
"font-family: Lucida Console,Lucida Sans Typewriter,monaco,Bitstream Vera Sans Mono,monospace;\n"
"padding: 3px;"));

        verticalLayout_4->addWidget(text_browser_tab_uninstall);

        installed_preview_area->setWidget(scrollAreaWidgetContents_4);

        verticalLayout->addWidget(installed_preview_area);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        uninstall_packages_button = new QPushButton(scrollAreaWidgetContents);
        uninstall_packages_button->setObjectName(QString::fromUtf8("uninstall_packages_button"));
        uninstall_packages_button->setEnabled(false);

        horizontalLayout_2->addWidget(uninstall_packages_button);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        console_view_uninstall = new QCheckBox(scrollAreaWidgetContents);
        console_view_uninstall->setObjectName(QString::fromUtf8("console_view_uninstall"));
        console_view_uninstall->setEnabled(true);

        horizontalLayout_5->addWidget(console_view_uninstall);

        search_installed_packages_checkbox = new QCheckBox(scrollAreaWidgetContents);
        search_installed_packages_checkbox->setObjectName(QString::fromUtf8("search_installed_packages_checkbox"));
        search_installed_packages_checkbox->setEnabled(false);

        horizontalLayout_5->addWidget(search_installed_packages_checkbox);


        verticalLayout->addLayout(horizontalLayout_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_8->addWidget(scrollArea);

        scrollArea_2 = new QScrollArea(MainWindowView);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 274, 523));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        packages_to_update_layout = new QHBoxLayout();
        packages_to_update_layout->setObjectName(QString::fromUtf8("packages_to_update_layout"));
        packages_to_update_layout->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        packages_to_update_layout->addItem(horizontalSpacer_3);

        packages_to_update_label = new QLabel(scrollAreaWidgetContents_2);
        packages_to_update_label->setObjectName(QString::fromUtf8("packages_to_update_label"));
        packages_to_update_label->setFont(font);
        packages_to_update_label->setAlignment(Qt::AlignCenter);

        packages_to_update_layout->addWidget(packages_to_update_label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        packages_to_update_layout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(packages_to_update_layout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(3, 3, 3, 3);
        sort_packages_to_update = new QCheckBox(scrollAreaWidgetContents_2);
        sort_packages_to_update->setObjectName(QString::fromUtf8("sort_packages_to_update"));
        sort_packages_to_update->setEnabled(true);

        horizontalLayout_9->addWidget(sort_packages_to_update);

        search_packages_to_update_lineedit = new QLineEdit(scrollAreaWidgetContents_2);
        search_packages_to_update_lineedit->setObjectName(QString::fromUtf8("search_packages_to_update_lineedit"));

        horizontalLayout_9->addWidget(search_packages_to_update_lineedit);


        verticalLayout_2->addLayout(horizontalLayout_9);

        update_spinning_widget = new QWidget(scrollAreaWidgetContents_2);
        update_spinning_widget->setObjectName(QString::fromUtf8("update_spinning_widget"));
        verticalLayout_13 = new QVBoxLayout(update_spinning_widget);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(3, 3, 3, 3);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_3);

        update_spinning_label = new QLabel(update_spinning_widget);
        update_spinning_label->setObjectName(QString::fromUtf8("update_spinning_label"));
        update_spinning_label->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(update_spinning_label);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_4);


        verticalLayout_13->addLayout(verticalLayout_12);


        verticalLayout_2->addWidget(update_spinning_widget);

        packages_to_update_list = new QListWidget(scrollAreaWidgetContents_2);
        packages_to_update_list->setObjectName(QString::fromUtf8("packages_to_update_list"));

        verticalLayout_2->addWidget(packages_to_update_list);

        updated_preview_area = new QScrollArea(scrollAreaWidgetContents_2);
        updated_preview_area->setObjectName(QString::fromUtf8("updated_preview_area"));
        updated_preview_area->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 254, 150));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        text_browser_tab_update = new QTextBrowser(scrollAreaWidgetContents_5);
        text_browser_tab_update->setObjectName(QString::fromUtf8("text_browser_tab_update"));
        text_browser_tab_update->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: black;\n"
"font-family: Lucida Console,Lucida Sans Typewriter,monaco,Bitstream Vera Sans Mono,monospace;\n"
"padding: 3px;"));

        verticalLayout_5->addWidget(text_browser_tab_update);

        updated_preview_area->setWidget(scrollAreaWidgetContents_5);

        verticalLayout_2->addWidget(updated_preview_area);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        update_packages_button = new QPushButton(scrollAreaWidgetContents_2);
        update_packages_button->setObjectName(QString::fromUtf8("update_packages_button"));
        update_packages_button->setEnabled(false);

        horizontalLayout_3->addWidget(update_packages_button);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(5, 5, 5, 5);
        console_view_update = new QCheckBox(scrollAreaWidgetContents_2);
        console_view_update->setObjectName(QString::fromUtf8("console_view_update"));
        console_view_update->setEnabled(true);

        horizontalLayout_6->addWidget(console_view_update);

        search_packages_to_update_checkbox = new QCheckBox(scrollAreaWidgetContents_2);
        search_packages_to_update_checkbox->setObjectName(QString::fromUtf8("search_packages_to_update_checkbox"));
        search_packages_to_update_checkbox->setEnabled(false);

        horizontalLayout_6->addWidget(search_packages_to_update_checkbox);

        check_all_updates_checkbox = new QCheckBox(scrollAreaWidgetContents_2);
        check_all_updates_checkbox->setObjectName(QString::fromUtf8("check_all_updates_checkbox"));
        check_all_updates_checkbox->setEnabled(false);

        horizontalLayout_6->addWidget(check_all_updates_checkbox);


        verticalLayout_2->addLayout(horizontalLayout_6);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_8->addWidget(scrollArea_2);

        scrollArea_3 = new QScrollArea(MainWindowView);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 274, 523));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        available_packages_layout = new QHBoxLayout();
        available_packages_layout->setObjectName(QString::fromUtf8("available_packages_layout"));
        available_packages_layout->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        available_packages_layout->addItem(horizontalSpacer_6);

        accessible_packages = new QLabel(scrollAreaWidgetContents_3);
        accessible_packages->setObjectName(QString::fromUtf8("accessible_packages"));
        accessible_packages->setFont(font);
        accessible_packages->setAlignment(Qt::AlignCenter);

        available_packages_layout->addWidget(accessible_packages);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        available_packages_layout->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(available_packages_layout);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(3, 3, 3, 3);
        sort_available_packages = new QCheckBox(scrollAreaWidgetContents_3);
        sort_available_packages->setObjectName(QString::fromUtf8("sort_available_packages"));
        sort_available_packages->setEnabled(true);

        horizontalLayout_11->addWidget(sort_available_packages);

        search_available_packages_lineedit = new QLineEdit(scrollAreaWidgetContents_3);
        search_available_packages_lineedit->setObjectName(QString::fromUtf8("search_available_packages_lineedit"));

        horizontalLayout_11->addWidget(search_available_packages_lineedit);


        verticalLayout_3->addLayout(horizontalLayout_11);

        installation_spinning_widget = new QWidget(scrollAreaWidgetContents_3);
        installation_spinning_widget->setObjectName(QString::fromUtf8("installation_spinning_widget"));
        verticalLayout_15 = new QVBoxLayout(installation_spinning_widget);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(3, 3, 3, 3);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_5);

        installation_spinning_label = new QLabel(installation_spinning_widget);
        installation_spinning_label->setObjectName(QString::fromUtf8("installation_spinning_label"));
        installation_spinning_label->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(installation_spinning_label);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_6);


        verticalLayout_15->addLayout(verticalLayout_14);


        verticalLayout_3->addWidget(installation_spinning_widget);

        available_packages_list = new QListWidget(scrollAreaWidgetContents_3);
        available_packages_list->setObjectName(QString::fromUtf8("available_packages_list"));

        verticalLayout_3->addWidget(available_packages_list);

        available_preview_area = new QScrollArea(scrollAreaWidgetContents_3);
        available_preview_area->setObjectName(QString::fromUtf8("available_preview_area"));
        available_preview_area->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 254, 150));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        text_browser_tab_install = new QTextBrowser(scrollAreaWidgetContents_6);
        text_browser_tab_install->setObjectName(QString::fromUtf8("text_browser_tab_install"));
        text_browser_tab_install->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: black;\n"
"font-family: Lucida Console,Lucida Sans Typewriter,monaco,Bitstream Vera Sans Mono,monospace;\n"
"padding: 3px;"));

        verticalLayout_6->addWidget(text_browser_tab_install);

        available_preview_area->setWidget(scrollAreaWidgetContents_6);

        verticalLayout_3->addWidget(available_preview_area);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        install_packages_button = new QPushButton(scrollAreaWidgetContents_3);
        install_packages_button->setObjectName(QString::fromUtf8("install_packages_button"));
        install_packages_button->setEnabled(false);

        horizontalLayout_4->addWidget(install_packages_button);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(5, 5, 5, 5);
        console_view_install = new QCheckBox(scrollAreaWidgetContents_3);
        console_view_install->setObjectName(QString::fromUtf8("console_view_install"));
        console_view_install->setEnabled(true);

        horizontalLayout_7->addWidget(console_view_install);

        search_available_packages_checkbox = new QCheckBox(scrollAreaWidgetContents_3);
        search_available_packages_checkbox->setObjectName(QString::fromUtf8("search_available_packages_checkbox"));
        search_available_packages_checkbox->setEnabled(false);

        horizontalLayout_7->addWidget(search_available_packages_checkbox);


        verticalLayout_3->addLayout(horizontalLayout_7);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        horizontalLayout_8->addWidget(scrollArea_3);


        verticalLayout_10->addLayout(horizontalLayout_8);

        leds_widget = new QWidget(MainWindowView);
        leds_widget->setObjectName(QString::fromUtf8("leds_widget"));
        verticalLayout_9 = new QVBoxLayout(leds_widget);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(2, 2, 2, 2);
        repos_kled = new KLed(leds_widget);
        repos_kled->setObjectName(QString::fromUtf8("repos_kled"));

        horizontalLayout_12->addWidget(repos_kled);

        repo_led_label = new QLabel(leds_widget);
        repo_led_label->setObjectName(QString::fromUtf8("repo_led_label"));

        horizontalLayout_12->addWidget(repo_led_label);

        aur_kled = new KLed(leds_widget);
        aur_kled->setObjectName(QString::fromUtf8("aur_kled"));

        horizontalLayout_12->addWidget(aur_kled);

        aur_led_label = new QLabel(leds_widget);
        aur_led_label->setObjectName(QString::fromUtf8("aur_led_label"));

        horizontalLayout_12->addWidget(aur_led_label);

        polaur_kled = new KLed(leds_widget);
        polaur_kled->setObjectName(QString::fromUtf8("polaur_kled"));

        horizontalLayout_12->addWidget(polaur_kled);

        polaur_led_label = new QLabel(leds_widget);
        polaur_led_label->setObjectName(QString::fromUtf8("polaur_led_label"));

        horizontalLayout_12->addWidget(polaur_led_label);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_14);


        verticalLayout_9->addLayout(horizontalLayout_12);


        verticalLayout_10->addWidget(leds_widget);


        gridLayout->addLayout(verticalLayout_10, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        installed_packages_label->setBuddy(installed_packages_list);
        packages_to_update_label->setBuddy(packages_to_update_list);
        accessible_packages->setBuddy(available_packages_list);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindowView);
        QObject::connect(search_packages_to_update_checkbox, SIGNAL(toggled(bool)), sort_packages_to_update, SLOT(setVisible(bool)));
        QObject::connect(search_packages_to_update_checkbox, SIGNAL(toggled(bool)), search_packages_to_update_lineedit, SLOT(setVisible(bool)));
        QObject::connect(search_available_packages_checkbox, SIGNAL(toggled(bool)), sort_available_packages, SLOT(setVisible(bool)));
        QObject::connect(search_available_packages_checkbox, SIGNAL(toggled(bool)), search_available_packages_lineedit, SLOT(setVisible(bool)));
        QObject::connect(search_installed_packages_checkbox, SIGNAL(toggled(bool)), search_installed_packages_lineedit, SLOT(setVisible(bool)));
        QObject::connect(search_installed_packages_checkbox, SIGNAL(toggled(bool)), sort_installed_packages, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(MainWindowView);
    } // setupUi

    void retranslateUi(QWidget *MainWindowView)
    {
        actions_spinning_animation_label->setText(QString());
        progress_view_checkbox->setText(tr2i18n("View progress", nullptr));
        installed_packages_label->setText(tr2i18n("INSTALLED", nullptr));
        sort_installed_packages->setText(tr2i18n("Reverse sorting", nullptr));
        remove_spinning_label->setText(QString());
        uninstall_packages_button->setText(tr2i18n("Uninstall", nullptr));
        console_view_uninstall->setText(tr2i18n("Preview", nullptr));
        search_installed_packages_checkbox->setText(tr2i18n("Search", nullptr));
        packages_to_update_label->setText(tr2i18n("TO UPDATE", nullptr));
        sort_packages_to_update->setText(tr2i18n("Reverse sorting", nullptr));
        update_spinning_label->setText(QString());
        update_packages_button->setText(tr2i18n("Update", nullptr));
        console_view_update->setText(tr2i18n("Preview", nullptr));
        search_packages_to_update_checkbox->setText(tr2i18n("Search", nullptr));
        check_all_updates_checkbox->setText(tr2i18n("Check all", nullptr));
        accessible_packages->setText(tr2i18n("AVAILABLE TO INSTALL", nullptr));
        sort_available_packages->setText(tr2i18n("Reverse sorting", nullptr));
        installation_spinning_label->setText(QString());
        install_packages_button->setText(tr2i18n("Install", nullptr));
        console_view_install->setText(tr2i18n("Preview", nullptr));
        search_available_packages_checkbox->setText(tr2i18n("Search", nullptr));
        repo_led_label->setText(tr2i18n("Repositories", nullptr));
        aur_led_label->setText(tr2i18n("AUR", nullptr));
        polaur_led_label->setText(tr2i18n("POLAUR", nullptr));
        (void)MainWindowView;
    } // retranslateUi

};

namespace Ui {
    class MainWindowView: public Ui_MainWindowView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWVIEW_H


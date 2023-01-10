#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'previewsappearancesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWSAPPEARANCESETTINGS_H
#define UI_PREVIEWSAPPEARANCESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "kcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_PreviewsAppearanceSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    KColorButton *kcfg_background_preview_color;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    KColorButton *kcfg_preview_font_color;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QFontComboBox *kcfg_preview_font_family;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *kcfg_preview_font_size;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PreviewsAppearanceSettings)
    {
        if (PreviewsAppearanceSettings->objectName().isEmpty())
            PreviewsAppearanceSettings->setObjectName(QString::fromUtf8("PreviewsAppearanceSettings"));
        PreviewsAppearanceSettings->resize(605, 513);
        verticalLayout_2 = new QVBoxLayout(PreviewsAppearanceSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(PreviewsAppearanceSettings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 583, 491));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        kcfg_background_preview_color = new KColorButton(scrollAreaWidgetContents);
        kcfg_background_preview_color->setObjectName(QString::fromUtf8("kcfg_background_preview_color"));

        horizontalLayout->addWidget(kcfg_background_preview_color);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        kcfg_preview_font_color = new KColorButton(scrollAreaWidgetContents);
        kcfg_preview_font_color->setObjectName(QString::fromUtf8("kcfg_preview_font_color"));

        horizontalLayout_2->addWidget(kcfg_preview_font_color);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        kcfg_preview_font_family = new QFontComboBox(scrollAreaWidgetContents);
        kcfg_preview_font_family->setObjectName(QString::fromUtf8("kcfg_preview_font_family"));

        horizontalLayout_3->addWidget(kcfg_preview_font_family);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        kcfg_preview_font_size = new QSpinBox(scrollAreaWidgetContents);
        kcfg_preview_font_size->setObjectName(QString::fromUtf8("kcfg_preview_font_size"));

        horizontalLayout_4->addWidget(kcfg_preview_font_size);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PreviewsAppearanceSettings);

        QMetaObject::connectSlotsByName(PreviewsAppearanceSettings);
    } // setupUi

    void retranslateUi(QWidget *PreviewsAppearanceSettings)
    {
        PreviewsAppearanceSettings->setWindowTitle(tr2i18n("Form", nullptr));
        label->setText(tr2i18n("background color ", nullptr));
        label_2->setText(tr2i18n("font color", nullptr));
        label_3->setText(tr2i18n("font family", nullptr));
        label_4->setText(tr2i18n("font size ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreviewsAppearanceSettings: public Ui_PreviewsAppearanceSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PREVIEWSAPPEARANCESETTINGS_H


#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'choicewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEWINDOW_H
#define UI_CHOICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChoiceWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *choice_label;
    QLabel *spinning_animation_label;
    QComboBox *choice_combo_box;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChoiceWindow)
    {
        if (ChoiceWindow->objectName().isEmpty())
            ChoiceWindow->setObjectName(QString::fromUtf8("ChoiceWindow"));
        ChoiceWindow->resize(450, 150);
        verticalLayout = new QVBoxLayout(ChoiceWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        choice_label = new QLabel(ChoiceWindow);
        choice_label->setObjectName(QString::fromUtf8("choice_label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        choice_label->setFont(font);
        choice_label->setAlignment(Qt::AlignCenter);
        choice_label->setWordWrap(true);

        horizontalLayout->addWidget(choice_label);

        spinning_animation_label = new QLabel(ChoiceWindow);
        spinning_animation_label->setObjectName(QString::fromUtf8("spinning_animation_label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinning_animation_label->sizePolicy().hasHeightForWidth());
        spinning_animation_label->setSizePolicy(sizePolicy);
        spinning_animation_label->setMaximumSize(QSize(50, 16777215));
        spinning_animation_label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(spinning_animation_label);


        verticalLayout->addLayout(horizontalLayout);

        choice_combo_box = new QComboBox(ChoiceWindow);
        choice_combo_box->setObjectName(QString::fromUtf8("choice_combo_box"));

        verticalLayout->addWidget(choice_combo_box);

        buttonBox = new QDialogButtonBox(ChoiceWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ChoiceWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChoiceWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChoiceWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChoiceWindow);
    } // setupUi

    void retranslateUi(QDialog *ChoiceWindow)
    {
        ChoiceWindow->setWindowTitle(tr2i18n("Dialog", nullptr));
        choice_label->setText(tr2i18n("Choose path for package save", nullptr));
        spinning_animation_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChoiceWindow: public Ui_ChoiceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CHOICEWINDOW_H


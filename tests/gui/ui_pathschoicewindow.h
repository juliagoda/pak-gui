#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'pathschoicewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHSCHOICEWINDOW_H
#define UI_PATHSCHOICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_pathsChoiceWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *paths_combo_box;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *pathsChoiceWindow)
    {
        if (pathsChoiceWindow->objectName().isEmpty())
            pathsChoiceWindow->setObjectName(QString::fromUtf8("pathsChoiceWindow"));
        pathsChoiceWindow->resize(450, 150);
        verticalLayout = new QVBoxLayout(pathsChoiceWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        label = new QLabel(pathsChoiceWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        paths_combo_box = new QComboBox(pathsChoiceWindow);
        paths_combo_box->setObjectName(QString::fromUtf8("paths_combo_box"));

        verticalLayout->addWidget(paths_combo_box);

        buttonBox = new QDialogButtonBox(pathsChoiceWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(pathsChoiceWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), pathsChoiceWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), pathsChoiceWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(pathsChoiceWindow);
    } // setupUi

    void retranslateUi(QDialog *pathsChoiceWindow)
    {
        pathsChoiceWindow->setWindowTitle(tr2i18n("Dialog", nullptr));
        label->setText(tr2i18n("Choose path for package save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pathsChoiceWindow: public Ui_pathsChoiceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PATHSCHOICEWINDOW_H


#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'progressview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSVIEW_H
#define UI_PROGRESSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressView
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *progress_view_tabwidget;
    QWidget *tab1;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *text_browser_tab1;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_5;
    QTextBrowser *text_browser_tab2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProgressView)
    {
        if (ProgressView->objectName().isEmpty())
            ProgressView->setObjectName(QString::fromUtf8("ProgressView"));
        ProgressView->resize(400, 300);
        verticalLayout = new QVBoxLayout(ProgressView);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        progress_view_tabwidget = new QTabWidget(ProgressView);
        progress_view_tabwidget->setObjectName(QString::fromUtf8("progress_view_tabwidget"));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        verticalLayout_2 = new QVBoxLayout(tab1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(tab1);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 358, 200));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        text_browser_tab1 = new QTextBrowser(scrollAreaWidgetContents_2);
        text_browser_tab1->setObjectName(QString::fromUtf8("text_browser_tab1"));

        verticalLayout_3->addWidget(text_browser_tab1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(scrollArea);

        progress_view_tabwidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        verticalLayout_4 = new QVBoxLayout(tab2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_2 = new QScrollArea(tab2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 358, 200));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        text_browser_tab2 = new QTextBrowser(scrollAreaWidgetContents_3);
        text_browser_tab2->setObjectName(QString::fromUtf8("text_browser_tab2"));

        verticalLayout_5->addWidget(text_browser_tab2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea_2);

        progress_view_tabwidget->addTab(tab2, QString());

        verticalLayout->addWidget(progress_view_tabwidget);

        buttonBox = new QDialogButtonBox(ProgressView);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProgressView);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProgressView, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProgressView, SLOT(reject()));

        progress_view_tabwidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ProgressView);
    } // setupUi

    void retranslateUi(QDialog *ProgressView)
    {
        ProgressView->setWindowTitle(tr2i18n("Dialog", nullptr));
        progress_view_tabwidget->setTabText(progress_view_tabwidget->indexOf(tab1), tr2i18n("Tab 1", nullptr));
        progress_view_tabwidget->setTabText(progress_view_tabwidget->indexOf(tab2), tr2i18n("Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProgressView: public Ui_ProgressView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PROGRESSVIEW_H


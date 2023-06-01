#pragma once

#include "availablepackagescolumn.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockAvailablePackagesColumn : public AvailablePackagesColumn
{
    Q_OBJECT

public:
    explicit MockAvailablePackagesColumn(QListWidget* new_list_widget,
                                         QLineEdit* new_search_lineedit,
                                         QCheckBox* new_reverse_sort_checkbox,
                                         QWidget* new_parent);
    friend class TestAvailablePackagesColumn;

protected:
    QStringList getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
};


class TestAvailablePackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestAvailablePackagesColumn(QObject* parent = nullptr);

private slots:
    void availableColumnLabelHasProperContent();
    void showAvailableColumnPreview();
    void hideAvailableColumnPreview();
    void availableColumnPreviewHasDefaultStyle();
    void availableColumnPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();
    void installButtonDisabledOnStart();
    void installButtonEnabledAfterPackageCheck();
    void installButtonDisabledAfterPackageUncheck();
    void installButtonDisabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();
    void packageOrderIsAlphabeticallByDefault();
    void checkedPackageIsStillCheckedAfterTextInputClear();
    void textInputSortBya52IsEqualToOne();
    void textInputSortByaaIsEqualToZero();
    void animationsRunOnStart();
    void animationWidgetIsVisible();
    void packagesListIsHiddenOnStart();
    void animationIsHiddenAfterSignalSend();
    void notEmptyPackagesListIsVisibleAfterSignalSend();
    void titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend();

    void cleanup();

private:
    MockMainWindowView main_window_view;
};

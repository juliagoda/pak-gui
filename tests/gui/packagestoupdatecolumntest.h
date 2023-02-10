#pragma once

#include "updatedpackagescolumn.h"

#include "packagescolumnfixtures.h"
#include "checkpackage.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockUpdatedPackagesColumn : public UpdatedPackagesColumn
{
    Q_OBJECT

public:
    explicit MockUpdatedPackagesColumn(QListWidget* new_list_widget,
                                       QLineEdit* new_search_lineedit,
                                       QWidget* new_parent);
    friend class TestUpdatedPackagesColumn;

protected:
    QHash<QString, Package::Source> getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
};



class MockCheckPackage : public CheckPackage
{
public:
    explicit MockCheckPackage(QString& package_content,
                              Package::Source new_source);
    friend class TestUpdatedPackagesColumn;
};



class TestUpdatedPackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestUpdatedPackagesColumn(QObject* parent = nullptr);

private slots:
    void updatedColumnLabelHasProperContent();
    void showUpdatedColumnPreview();
    void hideUpdatedColumnPreview();
    void updatedColumnPreviewHasDefaultStyle();
    void updatedColumnPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();
    void updateButtonDisabledOnStart();
    void updateButtonEnabledAfterPackageCheck();
    void updateButtonDisabledAfterPackageUncheck();
    void updateButtonDisabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();
    void checkedPackageIsStillCheckedAfterTextInputClear();
    void textInputSortBya52IsEqualToOne();
    void textInputSortByaaIsEqualToZero();
    void allPackagesCheckedAfterButtonCheck();
    void allPackagesUncheckedAfterButtonUncheck();
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

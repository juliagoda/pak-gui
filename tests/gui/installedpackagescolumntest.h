#pragma once


#include "installedpackagescolumn.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class MockInstalledPackagesColumn : public InstalledPackagesColumn
{
    Q_OBJECT

public:
    explicit MockInstalledPackagesColumn(QListWidget* new_list_widget,
                                         QLineEdit* new_search_lineedit,
                                         QWidget* new_parent);
    friend class TestInstalledPackagesColumn;

protected:
    QStringList getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
};



class TestInstalledPackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestInstalledPackagesColumn(QObject* parent = nullptr);

private slots:
    void installationLabelHasProperContent();
    void showInstallationPreview();
    void hideInstallationPreview();
    void installatonPreviewHasDefaultStyle();
    void installationPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();
    void uninstallButtonDisabledOnStart();
    void uninstallButtonEnabledAfterPackageCheck();
    void uninstallButtonDisabledAfterPackageUncheck();
    void uninstallButtonDisabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();
    void packageOrderIsAlphabeticallByDefault();
    void textInputSortBya52IsEqualToOne();
    void checkedPackageIsStillCheckedAfterTextInputClear();
    void textInputSortByaaIsEqualToZero();
    void animationsRunOnStart();
    void animationWidgetIsVisible();
    void packagesListIsHiddenOnStart();
    void animationIsHiddenAfterSignalSend();
    void notEmptyPackagesListIsVisibleAfterSignalSend();
    void titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend();
    void hasPackageTooltipAllSelectedInfo();

    void cleanup();

private:
    MockMainWindowView main_window_view;
};

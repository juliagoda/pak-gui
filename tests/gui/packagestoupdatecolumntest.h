// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#pragma once

#include "updatedpackagescolumn.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockUpdatedPackagesColumn : public UpdatedPackagesColumn
{
    Q_OBJECT

public:
    explicit MockUpdatedPackagesColumn(QListWidget* new_list_widget,
                                       QLineEdit* new_search_lineedit,
                                       QCheckBox* new_reverse_sort_checkbox,
                                       QWidget* new_parent);
    friend class TestUpdatedPackagesColumn;

protected:
    QHash<QString, Package::Source> getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
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

// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

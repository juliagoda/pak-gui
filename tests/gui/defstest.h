 #include "availablepackagescolumn.h"

#include "packagescolumnfixtures.h"
#include "actionsaccesschecker.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockActionsAccessChecker : public ActionsAccessChecker
{
    Q_OBJECT

public:
    explicit MockActionsAccessChecker(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent);
    friend class TestAvailablePackagesColumn;

protected:
   // QStringList getPackagesList() override;

public Q_SLOTS:
    //void sort(bool is_sorted) override;
};


MockActionsAccessChecker::MockActionsAccessChecker(QWidget* new_parent) :
    ActionsAccessChecker(new_parent)
{

}


class TestActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    TestActionsAccessChecker(QObject* parent = nullptr);

private slots:


    void cleanup();

private:
    MockActionsAccessChecker actions_access_checker;
};


TestActionsAccessChecker::TestActionsAccessChecker(QObject* parent) :
    QObject(parent),
    actions_access_checker(new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestActionsAccessChecker::cleanup()
{
    connect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, main_window_view.available_packages_column.data(), &InstalledPackagesColumn::sort);
    main_window_view.m_ui.available_packages_list->clear();
    main_window_view.m_ui.search_available_packages_lineedit->clear();
    main_window_view.m_ui.console_view_install->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_available_packages_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_available_packages_checkbox->setDisabled(true);
    main_window_view.m_ui.install_packages_button->setEnabled(false);
    main_window_view.m_ui.sort_available_packages->setCheckState(Qt::Unchecked);

    while(main_window_view.m_ui.available_packages_list->count() > 0)
    {
        if (main_window_view.m_ui.available_packages_list->item(0))
            delete main_window_view.m_ui.available_packages_list->takeItem(0);
    }
}

QTEST_MAIN(TestAvailablePackagesColumn)
#include "availablepackagescolumn.moc"

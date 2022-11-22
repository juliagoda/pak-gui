/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "qmovie.h"
#include "updatedpackagescolumn.h"
#include "pakGuiSettings.h"
#include "qcheckbox.h"
#include "qnamespace.h"
#include "qpushbutton.h"
#include "qscopedpointer.h"
#include "statistics.h"
#include "statisticscommandparser.h"
#include "process.h"
#include "packagedownloader.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
#include <QObject>
#include <QVariant>
#include <KMainWindow>
#include <QChartView>
#include <QPieSeries>



MainWindowView::MainWindowView(QSharedPointer<Process> new_process, QWidget *parent)
    : QWidget(parent),
      process(new_process),
      generated_previews_map(QMap<Process::Task, QPointer<QWidget>>()),
      progress_view(QSharedPointer<ProgressView>(new ProgressView)),
      spinning_animation(nullptr)
{
    m_ui.setupUi(this);

    emit initStarted();

    generated_previews_map.insert(Process::Task::Install, m_ui.installed_preview_area);
    generated_previews_map.insert(Process::Task::Uninstall, m_ui.updated_preview_area);
    generated_previews_map.insert(Process::Task::Update, m_ui.available_preview_area);

    QObject::connect(this, &MainWindowView::operationsAmountIncreased, m_ui.progress_view_checkbox, &QCheckBox::show);
    QObject::connect(m_ui.progress_view_checkbox, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) progress_view.data()->show(); else progress_view.data()->hide(); });
    QObject::connect(m_ui.console_view_install, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.available_preview_area->show(); else m_ui.available_preview_area->hide(); });
    QObject::connect(m_ui.console_view_uninstall, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.installed_preview_area->show(); else m_ui.installed_preview_area->hide(); });
    QObject::connect(m_ui.console_view_update, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.updated_preview_area->show(); else m_ui.updated_preview_area->hide(); });

    QObject::connect(process.data(), &Process::generatedOutput, this, [this](Process::Task task, const QString& line) {
        generated_previews_map.value(task)->findChild<QTextBrowser*>(QString("text_browser_tab_%1").arg(QVariant::fromValue(task).toString().toLower()))->append(line); }, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::acceptedTask, this, &MainWindowView::generatePreview);
    QObject::connect(process.data(), &Process::acceptedTask, this, &MainWindowView::showAnimation);
    QObject::connect(process.data(), &Process::finished, available_packages_column.data(), [=](Process::Task task, int exit_code, QProcess::ExitStatus exit_status) { finishProcess(task, exit_code, exit_status); }, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::finished, this, &MainWindowView::stopAnimation);

    init();
}


MainWindowView::~MainWindowView()
{

}


void MainWindowView::init()
{
    QThread* available_packages_thread(new QThread);
    QThread* installed_packages_thread(new QThread);
    QThread* updated_packages_thread(new QThread);

    m_ui.available_packages_list->hide();
    m_ui.installed_packages_list->hide();
    m_ui.packages_to_update_list->hide();

    m_ui.remove_spinning_widget->show();
    m_ui.installation_spinning_widget->show();
    m_ui.update_spinning_widget->show();

    spinning_animation.reset(new QMovie(":/waiting.gif"), &QObject::deleteLater);
    m_ui.installation_spinning_label->setMovie(spinning_animation.get());
    m_ui.remove_spinning_label->setMovie(spinning_animation.get());
    m_ui.update_spinning_label->setMovie(spinning_animation.get());
    spinning_animation->start();

    hideWidgets();

    // remember to add connect for situation when checkbox should be hidden again
    QObject::connect(available_packages_thread, &QThread::started, [=]() {  available_packages_column = QPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list, m_ui.search_available_packages_lineedit)); connectSignalsForAvailablePackages(); });
    QObject::connect(installed_packages_thread, &QThread::started, [=]() { installed_packages_column = QPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list, m_ui.search_installed_packages_lineedit)); connectSignalsForInstalledPackages(); });
    QObject::connect(updated_packages_thread, &QThread::started, [=]() { updated_packages_column = QPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list, m_ui.search_packages_to_update_lineedit)); connectSignalsForUpdatedPackages(); });
    QObject::connect(available_packages_thread, &QThread::finished, available_packages_thread,
                     &QThread::deleteLater);
    QObject::connect(installed_packages_thread, &QThread::finished, installed_packages_thread,
                     &QThread::deleteLater);
    QObject::connect(updated_packages_thread, &QThread::finished, updated_packages_thread,
                     &QThread::deleteLater);

    available_packages_thread->start();
    installed_packages_thread->start();
    updated_packages_thread->start();
}


void MainWindowView::hideWidgets()
{
    m_ui.installed_preview_area->hide();
    m_ui.updated_preview_area->hide();
    m_ui.available_preview_area->hide();
    m_ui.progress_view_checkbox->hide();
    m_ui.sort_available_packages->hide();
    m_ui.sort_installed_packages->hide();
    m_ui.sort_packages_to_update->hide();
    m_ui.search_installed_packages_lineedit->hide();
    m_ui.search_packages_to_update_lineedit->hide();
    m_ui.search_available_packages_lineedit->hide();
    m_ui.available_packages_list->hide();
    m_ui.installed_packages_list->hide();
    m_ui.packages_to_update_list->hide();
}


void MainWindowView::connectSignalsForAvailablePackages()
{
    if (m_ui.available_packages_list->count() > 0)
    {
        m_ui.available_packages_list->show();
        m_ui.search_available_packages_checkbox->setEnabled(true);   
    }

    m_ui.installation_spinning_widget->hide();
    QObject::connect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.available_packages_list, &QListWidget::itemChanged, available_packages_column.data(), &AvailablePackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_install->clear(); process->run(Process::Task::Install, available_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);

    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForInstalledPackages()
{
    if (m_ui.installed_packages_list->count() > 0)
    {
        m_ui.installed_packages_list->show();
        m_ui.search_installed_packages_checkbox->setEnabled(true);
    }

    m_ui.remove_spinning_widget->hide();
    QObject::connect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.installed_packages_list, &QListWidget::itemChanged, installed_packages_column.data(), &InstalledPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_uninstall->clear(); process->run(Process::Task::Uninstall, installed_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);

    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForUpdatedPackages()
{
    if (m_ui.packages_to_update_list->count() > 0)
    {
        m_ui.packages_to_update_list->show();
        m_ui.search_packages_to_update_checkbox->setEnabled(true);
    }

    if (m_ui.packages_to_update_list->count() == 0)
    {
        m_ui.packages_to_update_label->setStyleSheet("color: black; font-size: 15px;");
        m_ui.packages_to_update_label->setText(i18n("There aren't packages to update"));
    }

    m_ui.update_spinning_widget->hide();
    QObject::connect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list, &QListWidget::itemChanged, updated_packages_column.data(), &UpdatedPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.update_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.update_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_update->clear(); process->run(Process::Task::Update, updated_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);

    checkSpinningVisibility();
}


void MainWindowView::checkSpinningVisibility()
{
    if (m_ui.update_spinning_widget->isHidden() &&
        m_ui.remove_spinning_widget->isHidden() &&
        m_ui.installation_spinning_widget->isHidden())
    {
        emit initEnded();
    }
}


void MainWindowView::generatePreview(Process::Task task)
{
   QWidget* operation_preview = new QWidget;
   operation_preview->setObjectName(QVariant::fromValue(task).toString());
   QVBoxLayout* vertical_layout = new QVBoxLayout(operation_preview);
   QScrollArea* scroll_area = new QScrollArea(operation_preview);
   scroll_area->setWidgetResizable(true);
   QWidget* scroll_area_widget_contents = new QWidget();
   scroll_area_widget_contents->setGeometry(QRect(0, 0, 358, 200));
   QVBoxLayout* vertical_layout2 = new QVBoxLayout(scroll_area_widget_contents);
   QTextBrowser* text_browser_tab = new QTextBrowser(scroll_area_widget_contents);
   text_browser_tab->setObjectName(QString("text_browser_tab_%1").arg(QVariant::fromValue(task).toString().toLower()));

   vertical_layout2->addWidget(text_browser_tab);
   scroll_area->setWidget(scroll_area_widget_contents);
   vertical_layout->addWidget(scroll_area);
   generated_previews_map.insert(task, operation_preview);
   progress_view.data()->addProgressView(operation_preview);

   emit operationsAmountIncreased();
}


void MainWindowView::showAnimation()
{
    spinning_animation.reset(new QMovie(":/waiting-small.gif"), &QObject::deleteLater);
    m_ui.actions_spinning_animation_label->setMovie(spinning_animation.get());
    m_ui.actions_spinning_animation_label->show();
    spinning_animation->start();
}


void MainWindowView::stopAnimation()
{
    m_ui.actions_spinning_animation_label->hide();
    spinning_animation->stop();
}


void MainWindowView::showStatisticsWindow()
{
    QScopedPointer<StatisticsCommandParser> command_parser(new StatisticsCommandParser);
    auto list_result = command_parser.data()->retrieveInfo();
    auto map_result = command_parser.data()->convertToMap(list_result);

    QPointer<Statistics> statistics = new Statistics(map_result, this);
    statistics->resize(800, 500);
    statistics->show();
}

void MainWindowView::downloadPackage()
{
   QPointer<DownloadCommandParser> download_command_parser(new DownloadCommandParser(QString()));
   QPointer<DownloaderWindow> automatic_installation(new AutomaticInstallation(download_command_parser));
   QPointer<DownloaderWindow> package_input(new PackageInput(download_command_parser));
   QPointer<DownloaderWindow> paths_choice_input(new PathsChoiceInput(download_command_parser));
   QPointer<DownloaderWindow> repos_choice_input(new ReposChoiceInput(download_command_parser));

   automatic_installation->setNext(package_input)->setNext(paths_choice_input)->setNext(repos_choice_input);
   automatic_installation->handle();
}

void MainWindowView::finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status)
{
    switch(task)
    {
      case Process::Task::Install:
         available_packages_column.data()->update(exit_code, exit_status, tr("Installation"), tr("installed"));
      break;

      case Process::Task::Update:
        updated_packages_column.data()->update(exit_code, exit_status, tr("Update"), tr("updated"));
      break;

      case Process::Task::Uninstall:
        installed_packages_column.data()->update(exit_code, exit_status, tr("Uninstallation"), tr("removed"));
      break;

      default:
        progress_view.data()->removeProgressView(generated_previews_map.value(task));
        generated_previews_map.remove(task);
      break;
    }
}


void MainWindowView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = pakGuiSettings::colorBackground();
    pakGuiSettings::setColorBackground(pakGuiSettings::colorForeground());
    pakGuiSettings::setColorForeground(color);

    handleSettingsChanged();
}


void MainWindowView::handleSettingsChanged()
{
  //  QPalette palette = m_ui.templateLabel->palette();
  //  palette.setColor(QPalette::Window, pakGuiSettings::colorBackground());
  //  palette.setColor(QPalette::WindowText, pakGuiSettings::colorForeground());
  //  m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    //  m_ui.templateLabel->setText(i18n("This project is %1 days old", pakGuiSettings::ageInDays()));
}

void MainWindowView::refresh()
{
    emit initStarted();

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    available_packages_column.data()->clear();

    init();
}


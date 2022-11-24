#include "settings.h"
#include "mainwindow.h"
#include "pakGuiSettings.h"

#include <KConfigDialog>
#include <QPointer>

Settings::Settings(MainWindow* main_window)
{
   init(main_window);
}

void Settings::init(MainWindow* main_window)
{
    if (KConfigDialog::showDialog(QStringLiteral("settings")))
    {
        qWarning() << "Settings window cannot be opened more than once at the same time";
        return;
    }

    QPointer<KConfigDialog> dialog = new KConfigDialog(main_window, QStringLiteral("settings"), pakGuiSettings::self());
    QWidget *general_page = new QWidget;
    general_settings.setupUi(general_page);
    QWidget *previews_appearance_page = new QWidget;
    previews_appearance_settings.setupUi(previews_appearance_page);
    QWidget *packages_info_page = new QWidget;
    packages_info_settings.setupUi(packages_info_page);
    QWidget *logs_page = new QWidget;
    logs_settings.setupUi(logs_page);
    dialog->addPage(general_page, i18nc("@title:tab", "General"), QStringLiteral(":/icons/general-settings.png"));
    dialog->addPage(previews_appearance_page, i18nc("@title:tab", "Previews appearance"), QStringLiteral(":/icons/general-settings.png"));
    dialog->addPage(packages_info_page, i18nc("@title:tab", "Packages informations"), QStringLiteral(":/icons/package-info-settings.png"));
    dialog->addPage(logs_page, i18nc("@title:tab", "Logs"), QStringLiteral(":/icons/logs-settings.png"));
    //connect(dialog, &KConfigDialog::settingsChanged, mainWindowView, &MainWindowView::handleSettingsChanged);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

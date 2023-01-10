#include "progressview.h"

#include "logger.h"


ProgressView::ProgressView(QDialog* parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
    m_ui.progress_view_tabwidget->clear();
}


void ProgressView::addProgressView(QWidget* progress_view)
{
    Logger::logger()->logDebug(QStringLiteral("Generated operation tab in preview window titled \"%1\"").arg(progress_view->objectName()));
    m_ui.progress_view_tabwidget->addTab(progress_view, progress_view->objectName());
}


void ProgressView::removeProgressView(QWidget* progress_view)
{
    int index = m_ui.progress_view_tabwidget->indexOf(progress_view);

    if (index == -1)
    {
        Logger::logger()->logWarning(QStringLiteral("progress view titled \"%1\" couldn't be removed from tabwidget window - couldn't be found").arg(progress_view->objectName()));
        return;
    }

    Logger::logger()->logDebug(QStringLiteral("Removing tab widget titled \"%1\"").arg(progress_view->objectName()));
    m_ui.progress_view_tabwidget->removeTab(index);
}


int ProgressView::tabsCount()
{
    return m_ui.progress_view_tabwidget->count();
}

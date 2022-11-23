#include "progressview.h"

#include <QDebug>


ProgressView::ProgressView(QDialog* parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
    m_ui.progress_view_tabwidget->clear();
}


void ProgressView::addProgressView(QWidget* progress_view)
{
    m_ui.progress_view_tabwidget->addTab(progress_view, progress_view->objectName());
}


void ProgressView::removeProgressView(QWidget* progress_view)
{
    int index = m_ui.progress_view_tabwidget->indexOf(progress_view);

    if (index == -1)
    {
        qWarning() << "progress view titled \"" << progress_view->objectName() << "\" couldn't be removed from tabwidget window - couldn't be found";
        return;
    }

    m_ui.progress_view_tabwidget->removeTab(index);
}


int ProgressView::tabsCount()
{
    return m_ui.progress_view_tabwidget->count();
}

#include "choicewindow.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QComboBox>


ChoiceWindow::ChoiceWindow(const QString& new_title,
                           const QStringList& new_options,
                           QDialog* new_parent)
    : QDialog(new_parent),
      title(new_title),
      options(new_options)
{
    m_ui.setupUi(this);
    init();

    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(m_ui.choice_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChoiceWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit choiceDefined(m_ui.choice_combo_box->currentIndex()); }, Qt::AutoConnection);
}


void ChoiceWindow::toggleOkButton(int new_index)
{
    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(new_index > -1);
}


void ChoiceWindow::init()
{
   m_ui.choice_label->setText(title);
   m_ui.choice_combo_box->addItems(options);
}

#include "choicewindow.h"
#include "outputfilter.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QtDebug>


ChoiceWindow::ChoiceWindow(const QString& new_title,
                           QDialog* new_parent)
    : QDialog(new_parent),
      title(new_title)
{
    m_ui.setupUi(this);
    init();

    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(m_ui.choice_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChoiceWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit choiceDefined(m_ui.choice_combo_box->currentIndex()); }, Qt::AutoConnection);
}

void ChoiceWindow::toggleOkButton(int new_index)
{
    Q_UNUSED(new_index)
    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_ui.choice_combo_box->count() > 0);
}

void ChoiceWindow::fillComboBox(QString& output)
{
    QString result_output(output);
    QScopedPointer<OutputFilter> output_filter(new OutputFilter);
    result_output = output_filter->filteredOutput(result_output);
    qDebug() << result_output;
    QStringList splitted_list = result_output.split(QRegularExpression("\n"));
    m_ui.choice_combo_box->addItems(output_filter->filteredLines(splitted_list, OutputFilter::startsFromNumber));
}

void ChoiceWindow::init()
{
   m_ui.choice_label->setText(title);
}

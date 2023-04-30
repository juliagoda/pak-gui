#include "choicewindow.h"

#include "outputfilter.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QComboBox>


ChoiceWindow::ChoiceWindow(const QString& new_title,
                           QDialog* new_parent) :
    QDialog{new_parent},
    title{new_title}
{
    m_ui.setupUi(this);

    init();

    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(this, &ChoiceWindow::filledOptionsBox, this, [this]() { spinning_animation->stopSmallOnWidget(m_ui.spinning_animation_label); });
    connect(m_ui.choice_combo_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChoiceWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit choiceDefined(m_ui.choice_combo_box->currentIndex()); }, Qt::AutoConnection);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit choiceDefined(m_ui.choice_combo_box->currentText()); }, Qt::AutoConnection);
    connect(m_ui.buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, [this]() { emit cancelled(); }, Qt::AutoConnection);
}


ChoiceWindow::~ChoiceWindow()
{
   clearComboBox();
   toggleOkButton(0);
}


void ChoiceWindow::toggleOkButton(int new_index)
{
    Q_UNUSED(new_index)
    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_ui.choice_combo_box->count() > 0);
}


void ChoiceWindow::fillComboBox(QString& output)
{
    QString result_output{output};
    result_output = OutputFilter::filteredOutput(result_output);
    QStringList splitted_list{result_output.split(QRegularExpression("\n"))};
    m_ui.choice_combo_box->clear();
    m_ui.choice_combo_box->addItems(OutputFilter::filteredLines(splitted_list, OutputFilter::startsFromNumber));
    m_ui.choice_combo_box->update();

    if (m_ui.choice_combo_box->count() > 0)
        emit filledOptionsBox();
}


void ChoiceWindow::fillComboBox(QStringList output_list)
{
    m_ui.choice_combo_box->clear();
    m_ui.choice_combo_box->addItems(output_list);
    m_ui.choice_combo_box->update();
    emit filledOptionsBox();
}


QWeakPointer<SpinningAnimation> ChoiceWindow::retrieveSpinningAnimation()
{
    return spinning_animation.toWeakRef();
}


void ChoiceWindow::init()
{
    spinning_animation->startSmallOnWidget(m_ui.spinning_animation_label);
    m_ui.choice_label->setText(title);
}


Ui::ChoiceWindow* ChoiceWindow::retrieveUi()
{
   return &m_ui;
}


void ChoiceWindow::clearComboBox()
{
    m_ui.choice_combo_box->clear();
}

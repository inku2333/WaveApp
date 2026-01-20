#include "ConfigPage.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

ConfigPage::ConfigPage(QWidget *parent) : BasePage("Parameter Configuration", parent) {
    auto layout = new QVBoxLayout();

    auto group = new QGroupBox("Measurement Settings", this);
    auto form = new QFormLayout(group);
    form->setRowWrapPolicy(QFormLayout::DontWrapRows);
    form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    form->setLabelAlignment(Qt::AlignRight);

    form->addRow("Voltage Range (V):", new QComboBox());
    form->addRow("Current Limit (A):", new QDoubleSpinBox());
    form->addRow("Sample Rate (Hz):", new QSpinBox());

    layout->addWidget(group);
    layout->addStretch();

    // 保存按钮
    auto btnSave = new QPushButton("Save Configuration", this);
    btnSave->setProperty("class", "ToolBtn");
    btnSave->setFixedWidth(200);
    layout->addWidget(btnSave, 0, Qt::AlignCenter);

    this->setContentLayout(layout);
}

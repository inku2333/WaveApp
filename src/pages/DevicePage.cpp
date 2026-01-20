#include "DevicePage.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

DevicePage::DevicePage(QWidget *parent) : BasePage("Device Management", parent) {
    auto layout = new QVBoxLayout();

    // 1. 顶部操作栏
    auto topBar = new QHBoxLayout();
    auto btnScan = new QPushButton("Scan Devices", this);
    btnScan->setProperty("class", "ToolBtn");
    auto btnConnect = new QPushButton("Connect", this);
    btnConnect->setProperty("class", "ToolBtn");

    topBar->addWidget(btnScan);
    topBar->addWidget(btnConnect);
    topBar->addStretch();
    layout->addLayout(topBar);

    // 2. 表格区域
    m_table = new QTableView(this);
    m_model = new QStandardItemModel(this);
    m_model->setColumnCount(5);
    m_model->setHorizontalHeaderLabels({"Device ID", "Model", "Status", "Firmware", "Last Active"});

    m_table->setModel(m_model);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setAlternatingRowColors(true);
    m_table->setShowGrid(false);

    layout->addWidget(m_table);

    // 3. 底部信息
    auto infoLabel = new QLabel("Selected: None", this);
    layout->addWidget(infoLabel);

    this->setContentLayout(layout);
    initData();
}

void DevicePage::initData() {
    // 模拟数据
    QList<QStandardItem*> row1;
    row1 << new QStandardItem("DEV-001") << new QStandardItem("SMU-2000")
         << new QStandardItem("Connected") << new QStandardItem("v1.0.4") << new QStandardItem("Just now");

    QList<QStandardItem*> row2;
    row2 << new QStandardItem("DEV-002") << new QStandardItem("SMU-2000X")
         << new QStandardItem("Offline") << new QStandardItem("v1.0.2") << new QStandardItem("2026-01-14");

    m_model->appendRow(row1);
    m_model->appendRow(row2);
}

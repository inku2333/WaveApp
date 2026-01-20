#include "DataPage.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <random>

DataPage::DataPage(QWidget *parent) : BasePage("Data Acquisition", parent) {
    auto mainLayout = new QVBoxLayout();

    auto controlGroup = new QGroupBox("Control Panel", this);
    auto controlLayout = new QHBoxLayout(controlGroup);

    m_sampleRateSpinBox = new QDoubleSpinBox(this);
    m_sampleRateSpinBox->setRange(1, 200000000); // 200M
    m_sampleRateSpinBox->setValue(100);
    controlLayout->addWidget(new QLabel("Rate (Hz):"));
    controlLayout->addWidget(m_sampleRateSpinBox);

    m_startButton = new QPushButton("Start", this);
    m_stopButton = new QPushButton("Stop", this);
    m_stopButton->setEnabled(false);
    controlLayout->addWidget(m_startButton);
    controlLayout->addWidget(m_stopButton);
    controlLayout->addStretch();
    mainLayout->addWidget(controlGroup);

    m_plotter = new RealtimeChartPlotter(this);
    m_plotter->addChannel("SMU CH1", QColor(0, 255, 0));
    m_plotter->addChannel("SMU CH2", QColor(0, 180, 255));
    mainLayout->addWidget(m_plotter);

    this->setContentLayout(mainLayout);

    connect(m_startButton, &QPushButton::clicked, this, &DataPage::onStartClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &DataPage::onStopClicked);
    connect(&m_mockDataTimer, &QTimer::timeout, this, &DataPage::generateMockData);
}

DataPage::~DataPage() {
    m_mockDataTimer.stop();
}

void DataPage::onStartClicked() {
    m_currentX = 0;
    m_plotter->startPlotting(33);
    m_mockDataTimer.start(static_cast<int>(1000.0 / m_sampleRateSpinBox->value()));
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
}

void DataPage::onStopClicked() {
    m_plotter->stopPlotting();
    m_mockDataTimer.stop();
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
}

void DataPage::generateMockData() {
    static std::default_random_engine e;
    static std::normal_distribution<double> d(5.0, 0.1);
    m_plotter->appendData(0, m_currentX, d(e));
    m_plotter->appendData(1, m_currentX, d(e) * 0.5);
    m_currentX++;
}

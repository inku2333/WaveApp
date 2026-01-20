#pragma once
#include "BasePage.h"
#include "../charts/RealtimeChartPlotter.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QComboBox>
#include <QtCore/QTimer>

class DataPage : public BasePage {
    Q_OBJECT
public:
    explicit DataPage(QWidget *parent = nullptr);
    ~DataPage();

private slots:
    void onStartClicked();
    void onStopClicked();
    void generateMockData(); // 模拟生成数据

private:
    RealtimeChartPlotter* m_plotter = nullptr;
    QDoubleSpinBox* m_sampleRateSpinBox = nullptr;
    QPushButton* m_startButton = nullptr;
    QPushButton* m_stopButton = nullptr;

    QTimer m_mockDataTimer; // 模拟数据生成定时器
    int m_currentX = 0; // 模拟X轴时间
};

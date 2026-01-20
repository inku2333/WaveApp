#include "RealtimeChartPlotter.h"
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QLegend>
#include <limits>

RealtimeChartPlotter::RealtimeChartPlotter(QWidget *parent)
    : QWidget(parent)
{
    // 1. 初始化图表对象
    m_chart = new QChart();
    m_chart->setTitle("Real-time SMU Trace");
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    // 2. 初始化坐标轴
    m_axisX = new QValueAxis();
    m_axisX->setTitleText("Time/Samples");
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    m_axisY = new QValueAxis();
    m_axisY->setTitleText("Value");
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    // 3. 初始化视图
    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // 4. 布局设置（关键：直接使用 m_chartView）
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_chartView);
    setLayout(layout);

    // 5. 定时刷新逻辑
    connect(&m_refreshTimer, &QTimer::timeout, this, &RealtimeChartPlotter::updateChart);
}

RealtimeChartPlotter::~RealtimeChartPlotter() {
    m_refreshTimer.stop();
}

void RealtimeChartPlotter::addChannel(const QString& name, const QColor& color) {
    QLineSeries* series = new QLineSeries();
    series->setName(name);
    series->setColor(color);

    // Qt6 推荐对大数据量开启 OpenGL 提升渲染速度
    series->setUseOpenGL(true);

    m_chart->addSeries(series);
    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);

    ChartChannelData channel;
    channel.series = series;
    channel.color = color;
    channel.name = name;
    m_channels.append(channel);
}

void RealtimeChartPlotter::clearChannels() {
    QMutexLocker locker(&m_dataMutex);
    for (auto& ch : m_channels) {
        m_chart->removeSeries(ch.series);
        delete ch.series;
    }
    m_channels.clear();
}

void RealtimeChartPlotter::setMaxDataPoints(int maxPoints) {
    m_maxDataPoints = maxPoints;
}

void RealtimeChartPlotter::startPlotting(int refreshIntervalMs) {
    m_refreshTimer.start(refreshIntervalMs);
}

void RealtimeChartPlotter::stopPlotting() {
    m_refreshTimer.stop();
}

void RealtimeChartPlotter::appendData(int channelIndex, double x, double y) {
    if (channelIndex < 0 || channelIndex >= m_channels.size()) return;

    QMutexLocker locker(&m_dataMutex);
    m_channels[channelIndex].dataBuffer.append(QPointF(x, y));

    // 维持滑动窗口
    if (m_channels[channelIndex].dataBuffer.size() > m_maxDataPoints) {
        m_channels[channelIndex].dataBuffer.removeFirst();
    }
}

void RealtimeChartPlotter::updateChart() {
    QMutexLocker locker(&m_dataMutex);
    if (m_channels.isEmpty()) return;

    double minX = std::numeric_limits<double>::max();
    double maxX = -std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxY = -std::numeric_limits<double>::max();
    bool hasData = false;

    for (auto& channel : m_channels) {
        if (!channel.dataBuffer.isEmpty()) {
            hasData = true;
            // 批量替换数据，这是 Qt Charts 性能最高的更新方式
            channel.series->replace(channel.dataBuffer);

            // 计算轴范围
            for (const auto& p : channel.dataBuffer) {
                if (p.x() < minX) minX = p.x();
                if (p.x() > maxX) maxX = p.x();
                if (p.y() < minY) minY = p.y();
                if (p.y() > maxY) maxY = p.y();
            }
        }
    }

    if (hasData) {
        m_axisX->setRange(minX, maxX);
        // 增加 10% 的垂直间距
        double padding = (maxY - minY) * 0.1;
        if (padding == 0) padding = 1.0;
        m_axisY->setRange(minY - padding, maxY + padding);
    }
}

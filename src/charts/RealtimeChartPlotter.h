#ifndef REALTIMECHARTPLOTTER_H
#define REALTIMECHARTPLOTTER_H

#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtCore/QMutex>
#include <QtCore/QTimer>
#include <QtGui/QColor>
#include <QtCore/QPointF>

// 直接包含具体头文件
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

struct ChartChannelData {
    QLineSeries* series = nullptr;
    QVector<QPointF> dataBuffer;
    QColor color;
    QString name;
};

class RealtimeChartPlotter : public QWidget {
    Q_OBJECT

public:
    explicit RealtimeChartPlotter(QWidget *parent = nullptr);
    ~RealtimeChartPlotter();

    // 基础配置接口
    void addChannel(const QString& name, const QColor& color);
    void clearChannels();
    void setMaxDataPoints(int maxPoints);
    void startPlotting(int refreshIntervalMs = 30);
    void stopPlotting();

public slots:
    // 数据输入接口（线程安全）
    void appendData(int channelIndex, double x, double y

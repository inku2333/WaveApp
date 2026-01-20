#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

// 所有功能页面的基类，统一风格
class BasePage : public QWidget {
    Q_OBJECT
public:
    explicit BasePage(const QString& title, QWidget *parent = nullptr) : QWidget(parent) {
        auto mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(30, 30, 30, 30); // 统一边距
        mainLayout->setSpacing(20);

        // 统一的标题栏
        auto titleLabel = new QLabel(title, this);
        titleLabel->setProperty("class", "PageTitle"); // 用于QSS
        mainLayout->addWidget(titleLabel);

        // 内容容器
        m_contentArea = new QWidget(this);
        m_contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        mainLayout->addWidget(m_contentArea);
    }

    QWidget* contentWidget() { return m_contentArea; }
    void setContentLayout(QLayout* layout) { m_contentArea->setLayout(layout); }

private:
    QWidget* m_contentArea;
};

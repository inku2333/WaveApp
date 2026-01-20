#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void setupSidebar();
    void setupContent();
    
    // 辅助函数：添加带图标的导航项
    void addNavItem(const QString& text, const QString& iconName);

private:
    QListWidget *m_navBar;
    QStackedWidget *m_contentStack;
};

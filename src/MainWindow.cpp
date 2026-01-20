#include "MainWindow.h"
#include "pages/DevicePage.h"
#include "pages/ConfigPage.h"
#include "pages/DataPage.h"
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtGui/QIcon>
#include <QtGui/QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    initUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI() {
    this->resize(1200, 768);
    this->setWindowTitle("SMU Control System (Qt 6.10)");

    auto centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    auto mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_navBar = new QListWidget(this);
    m_navBar->setObjectName("NavBar");
    m_navBar->setFixedWidth(240);
    mainLayout->addWidget(m_navBar);

    m_contentStack = new QStackedWidget(thi

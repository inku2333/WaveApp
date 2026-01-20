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

    m_contentStack = new QStackedWidget(this);
    mainLayout->addWidget(m_contentStack);

    setupSidebar();
    setupContent();

    auto statusBar = this->statusBar();
    statusBar->showMessage(tr("System Initialized (Qt6)"));

    connect(m_navBar, &QListWidget::currentRowChanged,
            m_contentStack, &QStackedWidget::setCurrentIndex);

    if(m_navBar->count() > 0) m_navBar->setCurrentRow(0);
}

void MainWindow::setupSidebar() {
    auto add = [&](const QString& text, QStyle::StandardPixmap icon) {
        auto item = new QListWidgetItem(this->style()->standardIcon(icon), text);
        m_navBar->addItem(item);
    };

    add(tr("Device Manager"), QStyle::SP_ComputerIcon);
    add(tr("Configuration"), QStyle::SP_FileDialogDetailedView);
    add(tr("Data Acquisition"), QStyle::SP_DriveHDIcon); // <-- 新增
    add(tr("System Logs"), QStyle::SP_MessageBoxInformation);
    add(tr("Settings"), QStyle::SP_BrowserReload);
}

void MainWindow::setupContent() {
    m_contentStack->addWidget(new DevicePage(this));
    m_contentStack->addWidget(new ConfigPage(this));
    m_contentStack->addWidget(new DataPage(this));

    // 占位页面
    m_contentStack->addWidget(new BasePage("System Logs (Coming Soon)", this));
    m_contentStack->addWidget(new BasePage("Settings (Coming Soon)", this));
}

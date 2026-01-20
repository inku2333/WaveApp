#pragma once
#include "BasePage.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

class DevicePage : public BasePage {
    Q_OBJECT
public:
    explicit DevicePage(QWidget *parent = nullptr);

private:
    void initData();
    QTableView* m_table;
    QStandardItemModel* m_model;
};

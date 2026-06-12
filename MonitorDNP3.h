#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MonitorDNP3.h"
#include <opendnp3/DNP3Manager.h>

class MonitorDNP3 : public QMainWindow
{
    Q_OBJECT

public:
    MonitorDNP3(QWidget *parent = nullptr);
    ~MonitorDNP3();

private:
    Ui::MonitorDNP3Class ui;
};


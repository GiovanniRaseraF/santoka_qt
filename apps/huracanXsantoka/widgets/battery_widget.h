#ifndef BATTERY_WIDGET_H
#define BATTERY_WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QTimer>
#include "displayer/evbms_0x356_filter.h"

namespace Ui {
class battery_widget;
}

class battery_widget : public QWidget
{
    Q_OBJECT

public slots:
    void setSOC(uint16_t newSOC);
    void setBatteryStatus(evBatteryStatus s);
    void timeoutToUpdateGraphics();

public:
    explicit battery_widget(QWidget *parent = nullptr);
    ~battery_widget();

private:
    Ui::battery_widget *ui;
    std::shared_ptr<QTimer> updateDatetime;
    evBatteryStatus status;
    uint16_t internalSOCRepresentation = 0;
    bool connected = false;
};

#endif // BATTERY_WIDGET_H

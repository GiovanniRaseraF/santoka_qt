#ifndef BATTERYFULLWIDGET_H
#define BATTERYFULLWIDGET_H

#include <QWidget>

#include <memory>

#include "displayer/battery_filter.h"
#include "widgets/batterywidget.h"

/*
 * General info
 * border-radius: 150px;
 * background-color: qconicalgradient(
 * 	cx:0,
 * 	cy:0.7,
 * 	angle:90,
 * 	stop:0.700
 * 	rgba(255, 0, 127, 0),
 * 	stop:0.75
 * 	rgba(85, 170, 255, 255));
*/

namespace Ui {
class batteryFullWidget;
}

class batteryFullWidget : public QWidget
{
    Q_OBJECT

public:
    explicit batteryFullWidget(std::shared_ptr<battery_filter> _battery = nullptr, QWidget *parent = nullptr);
    ~batteryFullWidget();

public slots:
    void setSOC(uint8_t);

private:
    Ui::batteryFullWidget *ui;

    // filter
    std::shared_ptr<battery_filter> battery;

};

#endif // BATTERYFULLWIDGET_H

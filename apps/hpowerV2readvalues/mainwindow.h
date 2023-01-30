#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "dataproducer.h"
#include "displayer/battery_filter.h"

namespace Ui {
class MainWindow;
}
Q_DECLARE_METATYPE(struct can_frame)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectBatteryFilterToGraphics();

public slots:
    void setSOC(uint8_t newSOC);
    void setPowerTemperature(uint8_t newPowerTemperature);
    void setPower(float newPower);

    void setSpeed(uint16_t newSpeed);
    void setMotorTemperature(uint8_t newMotorTemperature);
    void setMotorSpeed(uint16_t newMotorSpeed);


private:
    Ui::MainWindow *ui;

    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus_producer;

    // Displayer
    std::shared_ptr<battery_filter> battery;
};

#endif // MAINWINDOW_H

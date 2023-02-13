#ifndef BOATINFOWINDOW_H
#define BOATINFOWINDOW_H

#include <QMainWindow>
#include <QObject>

#include <memory>

#include "dataproducer.h"
#include "displayer/battery_filter.h"
#include "displayer/command_filter.h"
#include "displayer/generalinfo_filter.h"
#include "displayer/motor_filter.h"
#include "displayer/thermicmotor_filter.h"
#include "displayer/vahicle_filter.h"

#include "widgets/hp_widget_generic_infostring.h"
#include "widgets/hp_batterydesign.h"
#include "widgets/hp_motordesign.h"
#include "widgets/hp_generalinfo.h"

#define PASSSHARED(cl, name) \
    std::shared_ptr<cl> name = nullptr

#define PASSSHARED_NONULL(cl, name) \
    std::shared_ptr<cl> name

namespace Ui {
class BoatInfoWindow;
}

class BoatInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoatInfoWindow(QWidget *parent = 0);
    ~BoatInfoWindow();

    void connectInformations(
        PASSSHARED(battery_filter, _battery),
        PASSSHARED(command_filter, _command),
        PASSSHARED(generalinfo_filter, _generalinfo),
        PASSSHARED(motor_filter, _motor)
    );

private slots:
    void on_pb_close_clicked();

private:
    Ui::BoatInfoWindow *ui;

    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus;

    // Displayer
    std::shared_ptr<filter> logger;
    std::shared_ptr<battery_filter> battery;
    std::shared_ptr<command_filter> command;
    std::shared_ptr<generalinfo_filter> generalinfo;
    std::shared_ptr<motor_filter> motor;

    // Graphics
    std::shared_ptr<hp_widget_generic_infostring> batterydesign;
    std::shared_ptr<hp_widget_generic_infostring> motordesign;
    std::shared_ptr<hp_widget_generic_infostring> generalinfodesign;

};

#endif // BOATINFOWINDOW_H

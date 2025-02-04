#ifndef BATTERYPAGE_H
#define BATTERYPAGE_H

#include <QMainWindow>
#include <memory>

#include "dataproducer.h"
#include "displayer/evbms_0x351_filter.h"
#include "displayer/evbms_0x355_filter.h"

#define PASSSHARED(cl, name) \
    std::shared_ptr<cl> name = nullptr

#define PASSSHARED_NONULL(cl, name) \
    std::shared_ptr<cl> name

namespace Ui {
class batterypage;
}

class batterypage : public QMainWindow
{
    Q_OBJECT

public:
    explicit batterypage(QWidget *parent = nullptr);
    ~batterypage();

    void connectInformations(
        PASSSHARED(evbms_0x351, _ev0x351),
        PASSSHARED(evbms_0x355, _ev0x355)
    );

private slots:
    void on_pb_close_clicked();

    void setSOC(uint16_t newSOC);
private:
    Ui::batterypage *ui;
    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus;

    // evbms
    std::shared_ptr<evbms_0x351> ev0x351;
    std::shared_ptr<evbms_0x355> ev0x355;
};
#endif // BATTERYPAGE_H

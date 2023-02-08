#ifndef COMMAND_FILTER_H
#define COMMAND_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class command_filter : public filter
{
    Q_OBJECT
public:
    explicit command_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_cmd_Throttle(uint8_t);
    void new_cmd_gearRequested(uint8_t);
    void new_cmd_gearValidated(uint8_t);
    void new_cmd_TrimPosition(uint8_t);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    uint8_t cmd_Throttle = 0;					// %
    uint8_t cmd_gearRequested = 0;				// Avanti:0x7E Neutro: 0x7D Indietro: 0x7C
    uint8_t cmd_gearValidated = 0;				// Avanti:0x7E Neutro: 0x7D Indietro: 0x7C
    uint8_t cmd_TrimPosition = 0;				// %

private:
    virtual bool canupdateinfo() override;
};

#endif // COMMAND_FILTER_H

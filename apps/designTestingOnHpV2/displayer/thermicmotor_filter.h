#ifndef THERMICMOTOR_FILTER_H
#define THERMICMOTOR_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class thermicmotor_filter : public filter
{
    Q_OBJECT
public:
    explicit thermicmotor_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:

public slots:
    void receivednewframe(const can_frame newframe);

private:
    /*
    dsl_engineSpeed = 0					# rpm
        dsl_coolingTemperature = 0			# °C
        dsl_batteryVoltage = 0				# V
        dsl_Throttle = 0					# %
        dsl_GlowPlugStatus = 0				# 0:OFF; 1:ON
        dsl_status = 0						# 0 = WAIT; 10 = WAIT CRANKING; 50 = RUNNING; 110 = FAULT
        dsl_FuelLevel1 = 0					# %
        dsl_FuelLevel2 = 0					# %
        */
private:
    virtual bool canupdateinfo() override;
};

#endif // THERMICMOTOR_FILTER_H

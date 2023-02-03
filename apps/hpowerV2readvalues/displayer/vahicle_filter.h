#ifndef VAHICLE_FILTER_H
#define VAHICLE_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class vahicle_filter : public filter
{
    Q_OBJECT
public:
    explicit vahicle_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:

public slots:
    void receivednewframe(const can_frame newframe);

private:
    /*
    vcl_status = 0						# bitfield
        vcl_mapInUse = 0 					# #
        vcl_inSeaWaterTemperature = 0		# °C
        vcl_outSeaWaterTemperature = 0		# °C
        vcl_inGlycoleTemperature = 0		# °C
        vcl_outGlycoleTemperature = 0		# °C
        vcl_TotalHourCounter = 0			# min
        vcl_ElectricMotorHourCounter = 0	# min
        vcl_ThermicMotorHourCounter = 0		# min
        vcl_warnings = 0					# bitfield
        vcl_faults = 0						# bitfield
        */
private:
    virtual bool canupdateinfo() override;
};

#endif // VAHICLE_FILTER_H

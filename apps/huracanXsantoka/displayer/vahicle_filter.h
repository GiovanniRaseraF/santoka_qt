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
    void new_vcl_status(uint16_t);
    void new_vcl_mapInUse(uint8_t);
    void new_vcl_inSeaWaterTemperature(uint8_t);
    void new_vcl_outSeaWaterTemperature(uint8_t);
    void new_vcl_inGlycoleTemperature(uint8_t);
    void new_vcl_outGlycoleTemperature(uint8_t);
    void new_vcl_TotalHourCounter(int32_t);
    void new_vcl_ElectricMotorHourCounter(int32_t);
    void new_vcl_ThermicMotorHourCounter(int32_t);
    void new_vcl_warnings(uint32_t);
    void new_vcl_faults(uint32_t);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    uint16_t vcl_status = 0;						// bitfield
    uint8_t vcl_mapInUse = 0; 					// #
    uint8_t vcl_inSeaWaterTemperature = 0;		// °C
    uint8_t vcl_outSeaWaterTemperature = 0;		// °C
    uint8_t vcl_inGlycoleTemperature = 0;		// °C
    uint8_t vcl_outGlycoleTemperature = 0;		// °C
    int32_t vcl_TotalHourCounter = 0;			// min
    int32_t vcl_ElectricMotorHourCounter = 0;	// min
    int32_t vcl_ThermicMotorHourCounter = 0;		// min
    uint32_t vcl_warnings = 0;					// bitfield
    uint32_t vcl_faults = 0;						// bitfield

private:
    virtual bool canupdateinfo() override;
};

#endif // VAHICLE_FILTER_H

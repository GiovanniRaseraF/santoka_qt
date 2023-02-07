#ifndef GENERALINFO_FILTER_H
#define GENERALINFO_FILTER_H

#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

class generalinfo_filter : public filter
{
    Q_OBJECT
public:
    explicit generalinfo_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_info_BoatType(uint8_t);
    void new_info_ProtocolVersion(std::string);
    void new_info_ECUVersion(std::string);
    void new_info_DriveVersion(std::string);
    void new_info_ThermicEngineType(uint8_t);
    void new_info_ElectricMotorType(uint8_t);

    void to_QString(QString) override;

public slots:
    void receivednewframe(const can_frame newframe);

private:
    uint8_t info_BoatType = 0;			            // bitfield
    std::string info_ProtocolVersion = "1.0";		// #
    std::string info_ECUVersion = "1.00";			// #
    std::string info_DriveVersion = "1.00";			// #
    uint8_t info_ThermicEngineType = 0;			    // index
    uint8_t info_ElectricMotorType = 0;			    // index
    
private:
    virtual bool canupdateinfo() override;
    QString __to_QString() override;
};


#endif // GENERALINFO_FILTER_H

#ifndef GENERALINFO_LISTENER_H
#define GENERALINFO_LISTENER_H

#include <QObject>
#include "listener.h"
#include <unistd.h>
#include <map>
#include <tuple>
#include <functional>
#include <QtXml>
#include <QFile>

#define CONVERSION(totype, varname) \
    private: \
        totype varname;

class generalinfo_listener : public listener
{
    Q_OBJECT
public:
    explicit generalinfo_listener(QObject *parent = nullptr);

signals:

public slots:
    void newcanvalue(const struct can_frame frame);

private:
    // name
    std::map<std::string, std::tuple<int, int, int, int, float>> maps_conversion{
    };

// variable signals
private:
    uint8_t info_BoatType = 0;
    std::string info_BoatType_str = "info_BoatType";
signals:
    void info_BoatType_signal(uint8_t newdata);
private:
    float info_ProtocolVersion;
    std::string info_ProtocolVersion_str = "info_ProtocolVersion";
signals:
    void info_ProtocolVersion_signal(float newvalue);
private:
    float info_ECUVersion;
    std::string info_ECUVersion_str = "info_ECUVersion";
signals:
    void info_ECUVersion_signal(float newvalue);
private:
    float  info_DriveVersion;
    std::string  info_DriveVersion_str = " info_DriveVersion";
signals:
    void  info_DriveVersion_signal(float newvalue);
private:
    float info_ThermicEngineType;
    std::string info_ThermicEngineType_str = "info_ThermicEngineType";
signals:
    void info_ThermicEngineType_signal(float newvalue);
private:
    float info_ElectricMotorType;
    std::string info_ElectricMotorType_str = "info_ElectricMotorType";
signals:
    void info_ElectricMotorType_signal(float newvalue);

  //  float info_ElectricMotorType = 1.00;
};
#endif // GENERALINFO_LISTENER_H

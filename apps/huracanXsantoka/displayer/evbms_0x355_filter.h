#ifndef EVBMS_0X355_FILTER_H
#define EVBMS_0X355_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x355
class evbms_0x355: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x355(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_SOC(uint16_t);
    void new_ev_SOH(uint16_t);
    void new_ev_ResidualDischargeTime(uint16_t);
    void new_ev_Capacity(uint16_t);
    void to_QString(QString) override;

public slots:
    void receivednewframe(const can_frame newframe);

private:
    uint16_t ev_SOC                     = 0;
    uint16_t ev_SOH                     = 0;
    uint16_t ev_ResidualDischargeTime   = 0;
    uint16_t ev_Capacity                = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0X355_FILTER_H

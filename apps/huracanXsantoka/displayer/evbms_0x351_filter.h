#ifndef EVBMS_0X351_FILTER_H
#define EVBMS_0X351_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x351
class evbms_0x351: public filter
{
    Q_OBJECT
public:
    QString description = "Charge and discharge voltage and current limit";
    explicit evbms_0x351(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_CharginVoltageLimit(float);
    void new_ev_CharginCurrentLimit(float);
    void new_ev_DischargeCurrentLimit(float);
    void new_ev_DischargeVoltageLimit(float);
    void to_QString(QString) override;

public slots:
    void receivednewframe(const can_frame newframe);

private:
    float ev_CharginVoltageLimit    = 0;
    float ev_CharginCurrentLimit    = 0;
    float ev_DischargeCurrentLimit  = 0;
    float ev_DischargeVoltageLimit  = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0X351_FILTER_H

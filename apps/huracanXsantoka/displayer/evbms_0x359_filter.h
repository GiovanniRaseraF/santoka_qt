#ifndef EVBMS_0x359_FILTER_H
#define EVBMS_0x359_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x359
class evbms_0x359: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x359(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_MaxTemperature(int16_t);
    void new_ev_ModuleMaxTemp(uint8_t);
    void new_ev_CellMaxTemp(uint8_t);
    void new_ev_MinTemperature(int16_t);
    void new_ev_ModuleMinTemp(uint8_t);
    void new_ev_CellMinTemp(uint8_t);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    int16_t ev_MaxTemperature = 0;
    uint8_t ev_ModuleMaxTemp = 0;
    uint8_t ev_CellMaxTemp = 0;
    int16_t ev_MinTemperature = 0;
    uint8_t ev_ModuleMinTemp = 0;
    uint8_t ev_CellMinTemp = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0x359_FILTER_H

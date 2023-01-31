#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QVariant>

#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include <chrono>
//#include <optional>

#include "dataproducer.h"

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:

public slots:
    // Simple printer
    virtual void newdatafromcan(const can_frame newframe);

protected:
    std::vector<int> on;
    std::string name;

    // time interval
    std::chrono::time_point<std::chrono::steady_clock> start;
    int mininterval_millis = 1000;

protected:
    // Standard filter
    uint8_t to_uint8(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor);
    uint16_t to_uint16(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor);

    virtual bool canupdateinfo(){
        return true;
    }
};

#endif // FILTER_H

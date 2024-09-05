#ifndef SNIFFER_H
#define SNIFFER_H

#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>

#include "filter.h"

class sniffer_filter : public filter
{
    Q_OBJECT
public:
    explicit sniffer_filter (std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_canpacket(QString);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    virtual bool canupdateinfo() override;
};

#endif // SNIFFER_H

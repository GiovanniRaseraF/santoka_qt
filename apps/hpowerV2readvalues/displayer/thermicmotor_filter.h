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

private:
    virtual bool canupdateinfo() override;
};

#endif // THERMICMOTOR_FILTER_H
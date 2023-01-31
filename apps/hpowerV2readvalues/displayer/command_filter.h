#ifndef COMMAND_FILTER_H
#define COMMAND_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class command_filter : public filter
{
    Q_OBJECT
public:
    explicit command_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:

public slots:
    void receivednewframe(const can_frame newframe);

private:

private:
    virtual bool canupdateinfo() override;
};

#endif // COMMAND_FILTER_H

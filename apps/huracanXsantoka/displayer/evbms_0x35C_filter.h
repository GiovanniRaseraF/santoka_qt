#ifndef EVBMS_0x35C_FILTER_H
#define EVBMS_0x35C_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QPair>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x35C
class evbms_0x35C: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x35C(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
public slots:
    void receivednewframe(const can_frame newframe);

private:

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0x35C_FILTER_H

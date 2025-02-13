#ifndef EVBMS_0x35A_FILTER_H
#define EVBMS_0x35A_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QVector>
#include <tuple>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x35A
class evbms_0x35A: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x35A(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_WarningProtection(QVector<bool>);
public slots:
    void receivednewframe(const can_frame newframe);

private:
    QVector<bool> ev_WarningProtection;
private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

enum wft{
   WARNING, FAULT, RESERVED
};

static QMap<int, std::tuple<QString, wft>> WP_GLOBAL ={
    // 0
    {0 , {"BMU communication failure", WARNING}},
    {1 , {"Total voltage overvoltage", WARNING}},
    {2 , {"Total voltage undervoltage", WARNING}},
    {3 , {"High charging temperature", WARNING}},
    {4 , {"Low charging temperature", WARNING}},
    {5 , {"Cell overvoltage", WARNING}},
    {6 , {"Cell undervoltage", WARNING}},
    {7 , {"Discharge overvoltage", WARNING}},
    // 1
    {8 , {"", WARNING}},
    {9 , {"", WARNING}},
    {10 , {"", WARNING}},
    {11 , {"", WARNING}},
    {12 , {"", WARNING}},
    {13 , {"", WARNING}},
    {14 , {"", WARNING}},
    {15 , {"", WARNING}},
    // 2
    {16 , {"", WARNING}},
    {17 , {"", WARNING}},
    {18 , {"", WARNING}},
    {19 , {"", WARNING}},
    {20 , {"", WARNING}},
    {21 , {"", WARNING}},
    {22 , {"", WARNING}},
    {23 , {"", WARNING}},
};

#endif // EVBMS_0x35A_FILTER_H

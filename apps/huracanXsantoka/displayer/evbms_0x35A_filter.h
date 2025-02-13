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
    void new_ev_PRIMARY_PROTECTIONProtection(QVector<bool>);
public slots:
    void receivednewframe(const can_frame newframe);

private:
    QVector<bool> ev_PRIMARY_PROTECTIONProtection;
private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

enum wft{
   PRIMARY_PROTECTION, SECONDARY_PROTECTION, ALARM, RESERVED
};

static QMap<int, std::tuple<QString, wft>> WP_GLOBAL ={
    // 0
    {0 , {"BMU communication failure", PRIMARY_PROTECTION}},
    {1 , {"Total voltage overvoltage", PRIMARY_PROTECTION}},
    {2 , {"Total voltage undervoltage", PRIMARY_PROTECTION}},
    {3 , {"High charging temperature", PRIMARY_PROTECTION}},
    {4 , {"Low charging temperature", PRIMARY_PROTECTION}},
    {5 , {"Cell overvoltage", PRIMARY_PROTECTION}},
    {6 , {"Cell undervoltage", PRIMARY_PROTECTION}},
    {7 , {"Discharge overvoltage", PRIMARY_PROTECTION}},
    // 1
    {8 , {"Charging overcurrent", PRIMARY_PROTECTION}},
    {9 , {"High discharge temperature", PRIMARY_PROTECTION}},
    {10 , {"Low discharge temperature", PRIMARY_PROTECTION}},
    {11 , {"", RESERVED}},
    {12 , {"Cell imbalance", PRIMARY_PROTECTION}},
    {13 , {"Unbalanced temperature", PRIMARY_PROTECTION}},
    {14 , {"Low SOC", PRIMARY_PROTECTION}},
    {15 , {"Low insulation resistance", PRIMARY_PROTECTION}},
    // 2
    {16 , {"", RESERVED}},
    {17 , {"", RESERVED}},
    {18 , {"", RESERVED}},
    {19 , {"", RESERVED}},
    {20 , {"", RESERVED}},
    {21 , {"", RESERVED}},
    {22 , {"", RESERVED}},
    {23 , {"", RESERVED}},
    // 3
    {24 , {"", RESERVED}},
    {25 , {"", RESERVED}},
    {26 , {"", RESERVED}},
    {27 , {"", RESERVED}},
    {28 , {"", RESERVED}},
    {29 , {"", RESERVED}},
    {30 , {"", RESERVED}},
    {31 , {"", RESERVED}},
    // 4
    {32 , {"BMU communication failure", ALARM}},
    {33 , {"Total voltage overvoltage", ALARM}},
    {34 , {"Total voltage undervoltage", ALARM}},
    {35 , {"High charging temperature", ALARM}},
    {36 , {"Low charging temperature", ALARM}},
    {37 , {"Cell overvoltage", ALARM}},
    {38 , {"Cell undervoltage", ALARM}},
    {39 , {"Discharge overvoltage", ALARM}},
    // 5
    {40 , {"Charging overcurrent", ALARM}},
    {41 , {"High discharge temperature", ALARM}},
    {42 , {"Low discharge temperature", ALARM}},
    {43 , {"", RESERVED}},
    {44 , {"Cell imbalance", ALARM}},
    {45 , {"Unbalanced temperature", ALARM}},
    {46 , {"Low SOC", ALARM}},
    {47 , {"Low insulation resistance", ALARM}},
    // 6
    {48 , {"", RESERVED}},
    {49 , {"Total voltage overvoltage", SECONDARY_PROTECTION}},
    {50 , {"Total voltage undervoltage", SECONDARY_PROTECTION}},
    {51 , {"High charging temperature", SECONDARY_PROTECTION}},
    {52 , {"Low charging temperature", SECONDARY_PROTECTION}},
    {53 , {"Cell overvoltage", SECONDARY_PROTECTION}},
    {54 , {"Cell undervoltage", SECONDARY_PROTECTION}},
    {55 , {"Discharge overvoltage", SECONDARY_PROTECTION}},
    // 7
    {56 , {"Charging overcurrent", SECONDARY_PROTECTION}},
    {57 , {"High discharge temperature", SECONDARY_PROTECTION}},
    {58 , {"Low discharge temperature", SECONDARY_PROTECTION}},
    {59 , {"External Protection", SECONDARY_PROTECTION}},
    {60 , {"Cell imbalance", SECONDARY_PROTECTION}},
    {61 , {"Unbalanced temperature", SECONDARY_PROTECTION}},
    {62 , {"Low SOC", SECONDARY_PROTECTION}},
    {63 , {"Low insulation resistance", SECONDARY_PROTECTION}},
};

#endif // EVBMS_0x35A_FILTER_H

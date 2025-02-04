#ifndef EVBMS_FILTER_H
#define EVBMS_FILTER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

//// 0x351
//class evbms_0x351: public filter
//{
//    Q_OBJECT
//public:
//    QString description = "Charge and discharge voltage and current limit";
//    explicit evbms_0x351(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

//signals:
//    void new_ev_CharginVoltageLimit(float);
//    void new_ev_CharginCurrentLimit(float);
//    void new_ev_DischargeCurrentLimit(float);
//    void new_ev_DischargeVoltageLimit(float);
//    void to_QString(QString) override;

//public slots:
//    void receivednewframe(const can_frame newframe);

//private:
//    float ev_CharginVoltageLimit    = 0;
//    float ev_CharginCurrentLimit    = 0;
//    float ev_DischargeCurrentLimit  = 0;
//    float ev_DischargeVoltageLimit  = 0;

//private:
//    virtual bool canupdateinfo() override;

//    QString __to_QString() override;

//};

//// 0x355
//class evbms_0x355: public filter
//{
//    Q_OBJECT
//public:
//    QString description = "";
//    explicit evbms_0x355(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

//signals:
//    void new_ev_SOC(uint16_t);
//    void new_ev_SOH(uint16_t);
//    void new_ev_ResidualDischargeTime(uint16_t);
//    void new_ev_Capacity(uint16_t);
//    void to_QString(QString) override;

//public slots:
//    void receivednewframe(const can_frame newframe);

//private:
//    uint16_t ev_SOC                     = 0;
//    uint16_t ev_SOH                     = 0;
//    uint16_t ev_ResidualDischargeTime   = 0;
//    uint16_t ev_Capacity                = 0;

//private:
//    virtual bool canupdateinfo() override;

//    QString __to_QString() override;

//};


// // 0x356
// class evbms_0x356: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x356(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };


// // 0x358
// class evbms_0x358: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x358(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };

// // 0x359
// class evbms_0x359: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x359(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };

// // 0x35A
// class evbms_0x35A: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x35A(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };

// // 0x35B
// class evbms_0x35B: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x35B(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };

// // 0x35C
// class evbms_0x35C: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x35C(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };

// // 0x3D2
// class evbms_0x3D2: public filter
// {
//     Q_OBJECT
// public:
//     QString description = "";
//     explicit evbms_0x3D2(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

// signals:
//     void to_QString(QString) override;

// public slots:
//     void receivednewframe(const can_frame newframe);

// private:

// private:
//     virtual bool canupdateinfo() override;

//     QString __to_QString() override;

// };
#endif // EVBMS_FILTER_H

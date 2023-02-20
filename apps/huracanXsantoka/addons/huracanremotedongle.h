#ifndef HURACANREMOTEDONGLE_H
#define HURACANREMOTEDONGLE_H

/*
 * This must be a thread that allows comunication with
 * Huracan Remote Dongle
*/

#include <QObject>
#include <QThread>
#include <QSerialPort>

#include <memory>

class HuracanRemoteDongle : public QThread {
    Q_OBJECT
public:
    HuracanRemoteDongle(QObject *parent = nullptr);
    ~HuracanRemoteDongle(){}

    virtual void run() override;
    virtual void stop(){}

signals:
    void newlineread(QString line);

private:
    std::shared_ptr<QSerialPort> serial;
};

#endif // HURACANREMOTEDONGLE_H

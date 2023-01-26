#ifndef GENERALINFO_UI_H
#define GENERALINFO_UI_H

#include <QObject>
#include <generalinfo_listener.h>
#include <unistd.h>

class generalinfo_ui : public QObject
{
    Q_OBJECT
public:
    explicit generalinfo_ui(QObject *parent = nullptr, std::shared_ptr<generalinfo_listener> gen = nullptr);

private:
    //MainWindow *ui;

public slots:
    void info_BoatType_slot(uint8_t info_BoatType);
    void info_ProtocolVersion_slot(float info_ProtocolVersion);
    void info_ECUVersion_slot(float info_ECUVersion);
    void info_DriveVersion_slot(float info_DriveVersion);
    void info_ThermicEngineType_slot(float info_ThermicEngineType);
    void info_ElectricMotorType_slot(float info_ElectricMotorType);
};

#endif // GENERALINFO_UI_H

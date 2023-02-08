#include "generalinfo_ui.h"

generalinfo_ui::generalinfo_ui(QObject *parent, std::shared_ptr<generalinfo_listener> gen, Ui::MainWindow *ui) : QObject(parent)
{
    connect(gen.get(), SIGNAL(info_BoatType_signal(uint8_t)), this, SLOT(info_BoatType_slot(uint8_t)));
    connect(gen.get(), SIGNAL(info_ProtocolVersion_signal(float)), this, SLOT(info_DriveVersion_slot(float)));
    connect(gen.get(), SIGNAL(info_ECUVersion_signal(float)), this, SLOT(info_ECUVersion_slot(float)));
    connect(gen.get(), SIGNAL(info_DriveVersion_signal(float)), this, SLOT(info_DriveVersion_slot(float)));
    connect(gen.get(), SIGNAL(info_ThermicEngineType_signal(float)), this, SLOT(info_ThermicEngineType_slot(float)));
    connect(gen.get(), SIGNAL(info_ElectricMotorType_signal(float)), this, SLOT(info_ElectricMotorType_slot(float)));
}

void generalinfo_ui::info_BoatType_slot(uint8_t info_BoatType)
{

}

void generalinfo_ui::info_ProtocolVersion_slot(float info_ProtocolVersion)
{

}

void generalinfo_ui::info_ECUVersion_slot(float info_ECUVersion)
{

}

void generalinfo_ui::info_DriveVersion_slot(float info_DriveVersion)
{

}

void generalinfo_ui::info_ThermicEngineType_slot(float info_ThermicEngineType)
{

}

void generalinfo_ui::info_ElectricMotorType_slot(float info_ElectricMotorType)
{

}

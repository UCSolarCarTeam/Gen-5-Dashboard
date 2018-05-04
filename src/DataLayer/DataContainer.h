#pragma once

#include <QScopedPointer>

class I_AuxBmsData;
class I_BatteryData;
class I_BatteryFaultsData;
class I_DriverControlsData;
class I_KeyMotorData;
class I_LightsData;
class I_MpptData;
class I_MotorDetailsData;
class I_MotorFaultsData;

class DataContainer
{
public:
    DataContainer();
    ~DataContainer();

    I_AuxBmsData& auxBmsData();
    I_BatteryData& batteryData();
    I_BatteryFaultsData& batteryFaultsData();
    I_DriverControlsData& driverControlsData();
    I_KeyMotorData& keyMotorData();
    I_LightsData& lightsData();
    I_MpptData& mpptData();
    I_MotorDetailsData& motorDetailsData();
    I_MotorFaultsData& motorFaultsData();

private:
    QScopedPointer<I_AuxBmsData> auxBmsData_;
    QScopedPointer<I_BatteryData> batteryData_;
    QScopedPointer<I_BatteryFaultsData> batteryFaultsData_;
    QScopedPointer<I_DriverControlsData> driverControlsData_;
    QScopedPointer<I_KeyMotorData> keyMotorData_;
    QScopedPointer<I_LightsData> lightsData_;
    QScopedPointer<I_MpptData> mpptData_;
    QScopedPointer<I_MotorDetailsData> motorDetailsData_;
    QScopedPointer<I_MotorFaultsData> motorFaultsData_;
};

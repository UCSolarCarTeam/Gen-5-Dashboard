﻿#include "BatteryView.h"

namespace
{
    const QString BATTERY_ALIVE = "background-color:rgb(93, 234, 140); \
                              border-radius:8px; \
                              border: 1px solid white;";
    const QString BATTERY_DEAD = "background-color:rgb(147, 147, 147); \
                             border-radius:8px; \
                             border: 1px solid white;";

    const QString VOLTAGE_UNIT = "V";
    const QString MILLI_VOLTAGE_UNIT = "mV";
    const QString CURRENT_UNIT = "A";
    const QString AMPHOURS_UNIT = "Ah";
    const QString PERCENT_UNIT = "%";
    const QString TEMPERATURE_UNIT = "<sup>o</sup>C";

    const QString ON = "color: rgb(250, 187, 28);";
    const QString OFF = "color: grey;";

    const QString FAN_ON = "background-color: rgb(250, 187, 28);";
    const QString REQUESTED_FAN_ON = "background-color: rgb(64, 161, 191);";
    const QString FAN_OFF = "background-color: grey;";

}

BatteryView::BatteryView(BatteryPresenter& batteryPresenter,
                         I_BatteryUi& ui)
    : batteryPresenter_(batteryPresenter)
    , ui_(ui)
{
    connectBattery(batteryPresenter_);
}

BatteryView::~BatteryView()
{
}

void BatteryView::connectBattery(BatteryPresenter& batteryPresenter)
{
    connect(&batteryPresenter, SIGNAL(aliveReceived(const bool)),
            this, SLOT(aliveReceived(bool)));

    connect(&batteryPresenter, SIGNAL(bmsRelayStatusReceived(BmsRelayStatusFlags)),
            this, SLOT(bmsRelayStatusReceived(BmsRelayStatusFlags)));

    connect(&batteryPresenter, SIGNAL(populatedCellsReceived(const int)),
            this, SLOT(populatedCellsReceived(const int)));

    connect(&batteryPresenter, SIGNAL(inputVoltage12VReceived(const double)),
            this, SLOT(inputVoltage12VReceived(const double)));

    connect(&batteryPresenter, SIGNAL(fanVoltageReceived(const double)),
            this, SLOT(fanVoltageReceived(const double)));

    connect(&batteryPresenter, SIGNAL(packCurrentReceived(double)),
            this, SLOT(packCurrentReceived(double)));

    connect(&batteryPresenter, SIGNAL(packVoltageReceived(const double)),
            this, SLOT(packVoltageReceived(const double)));

    connect(&batteryPresenter, SIGNAL(packStateofChargeReceived(const double)),
            this, SLOT(packStateofChargeReceived(const double)));

    connect(&batteryPresenter, SIGNAL(packAmphoursReceived(const double)),
            this, SLOT(packAmphoursReceived(const double)));

    connect(&batteryPresenter, SIGNAL(packDepthOfDischargeReceived(const double)),
            this, SLOT(packDepthOfDischargeReceived(const double)));

    connect(&batteryPresenter, SIGNAL(highTemperatureReceived(const int)),
            this, SLOT(highTemperatureReceived(const int)));

    connect(&batteryPresenter, SIGNAL(highThermistorIdReceived(const int)),
            this, SLOT(highThermistorIdReceived(const int)));

    connect(&batteryPresenter, SIGNAL(lowTemperatureReceived(const int)),
            this, SLOT(lowTemperatureReceived(const int)));

    connect(&batteryPresenter, SIGNAL(lowThermistorIdReceived(const int)),
            this, SLOT(lowThermistorIdReceived(const int)));

    connect(&batteryPresenter, SIGNAL(averageTemperatureReceived(const int)),
            this, SLOT(averageTemperatureReceived(const int)));

    connect(&batteryPresenter, SIGNAL(internalTemperatureReceived(const int)),
            this, SLOT(internalTemperatureReceived(const int)));

    connect(&batteryPresenter, SIGNAL(fanSpeedReceived(const int)),
            this, SLOT(fanSpeedReceived(const int)));

    connect(&batteryPresenter, SIGNAL(requestedFanSpeedReceived(const int)),
            this, SLOT(requestedFanSpeedReceived(const int)));

    connect(&batteryPresenter, SIGNAL(lowCellVoltageReceived(const int)),
            this, SLOT(lowCellVoltageReceived(const int)));

    connect(&batteryPresenter, SIGNAL(lowCellVoltageIdReceived(const int)),
            this, SLOT(lowCellVoltageIdReceived(const int)));

    connect(&batteryPresenter, SIGNAL(highCellVoltageReceived(const int)),
            this, SLOT(highCellVoltageReceived(const int)));

    connect(&batteryPresenter, SIGNAL(highCellVoltageIdReceived(const int)),
            this, SLOT(highCellVoltageIdReceived(const int)));

    connect(&batteryPresenter, SIGNAL(averageCellVoltageReceived(const int)),
            this, SLOT(averageCellVoltageReceived(const int)));

    connect(&batteryPresenter, SIGNAL(prechargeStateReceived(const QString)),
            this, SLOT(prechargeStateReceived(const QString)));

    connect(&batteryPresenter, SIGNAL(auxVoltageReceived(const int)),
            this, SLOT(auxVoltageReceived(const int)));

    connect(&batteryPresenter, SIGNAL(auxBmsAliveReceived(const bool)),
            this, SLOT(auxBmsAliveReceived(const bool)));

    connect(&batteryPresenter, SIGNAL(packNetPowerReceived(const double)),
            this, SLOT(packNetPowerReceived(const double)));
}




void BatteryView::aliveReceived(bool alive)
{
    if (alive)
    {
        ui_.aliveWidget().setStyleSheet(BATTERY_ALIVE);
    }
    else
    {
        ui_.aliveWidget().setStyleSheet(BATTERY_DEAD);
    }
}

void BatteryView::bmsRelayStatusReceived(BmsRelayStatusFlags)
{
    if(BmsRelayStatusFlags.alwaysOnSignalStatus())
    {
        ui_.BMSOn().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSOn().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.isChargingSignalStatus())
    {
        ui_.BMSCharging().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSCharging().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.isReadySignalStatus())
    {
        ui_.BMSReady().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSReady().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.dischargeRelayEnabled())
    {
        ui_.BMSDischargeRelayEnabled().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSDischargeRelayEnabled().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.chargeRelayEnabled())
    {
        ui_.BMSChargeRelayEnabled().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSChargeRelayEnabled().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.chargerSafetyEnabled())
    {
        ui_.BMSChargerSafetyEnabled().setStyleSheet(ON);
    }
    else
    {
        ui_.BMSChargerSafetyEnabled().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.malfunctionIndicatorActive())
    {
        ui_.malfunctionIndicatorActive().setStyleSheet(ON);
    }
    else
    {
        ui_.malfunctionIndicatorActive().setStyleSheet(OFF);
    }

    if(BmsRelayStatusFlags.multiPurposeInputSignalStatus())
    {
        ui_.multipurposeInputSignalStatus().setStyleSheet(ON);
    }
    else
    {
        ui_.multipurposeInputSignalStatus().setStyleSheet(OFF);
    }

}

void BatteryView::populatedCellsReceived(int populatedCells)
{
    ui_.populatedCellsLabel().setNum(populatedCells);
}

void BatteryView::inputVoltage12VReceived(double inputVoltage)
{
    ui_.inputVoltage12VLabel().setText(QString::number(inputVoltage) + VOLTAGE_UNIT);
}


void BatteryView::fanVoltageReceived(double fanVoltage)
{
    ui_.fanVoltage().setText(QString::number(fanVoltage) + VOLTAGE_UNIT);
}

void BatteryView::packCurrentReceived(double packCurrent)
{
    ui_.packInfoCurrent().setText(QString::number(packCurrent) + CURRENT_UNIT);
}

void BatteryView::packVoltageReceived(double packVoltage)
{
    ui_.packInfoVoltage().setText(QString::number(packVoltage) + VOLTAGE_UNIT);
}

void BatteryView::packStateOfChargeReceived(double packStateOfCharge)
{

}

void BatteryView::packAmphoursReceived(double packAmphours)
{
    ui_.packInfoAmphours().setText(QString::number(packAmphours) + AMPHOURS_UNIT);
}

void BatteryView::packDepthOfDischargeReceived(double packDepthOfDischarge)
{
    ui_.packInfoDepthofDischarge().setText(QString::number(packDepthOfDischarge) + PERCENT_UNIT);
}

void BatteryView::highTemperatureReceived(int highTemperature)
{
    ui_.tempHighLabel().setText(QString::number(highTemperature) + TEMPERATURE_UNIT);
}

void BatteryView::highThermistorIdReceived(int highThermistorId)
{
    ui_.tempHighThermistorIDLabel().setNum(highThermistorId);
}

void BatteryView::lowTemperatureReceived(int lowTemperature)
{
    ui_.tempLowLabel().setText(QString::number(lowTemperature) + TEMPERATURE_UNIT);
}

void BatteryView::lowThermistorIdReceived(int lowThermistorId)
{
    ui_.tempLowThermistorIDLabel().setNum(lowThermistorId);
}

void BatteryView::averageTemperatureReceived(int averageTemperature)
{
    averageTemperature = (lowTemperature + highTemperature) / 2;
    ui_.tempAvgLabel().setText(QString::number(averageTemperature) + TEMPERATURE_UNIT);
}

void BatteryView::internalTemperatureReceived(int internalTemperature)
{
    ui_.internalTempLabel().setText(QString::number(lowTemperature) + TEMPERATURE_UNIT);
}

void BatteryView::fanSpeedReceived(int fanSpeed)
{
    ui_.fanSpeedLabel().setNum(fanSpeed);

    if(fanSpeed == 0)
    {
        ui_.fanSpeed1().setStyleSheet(FAN_OFF);
        ui_.fanSpeed2().setStyleSheet(FAN_OFF);
        ui_.fanSpeed3().setStyleSheet(FAN_OFF);
        ui_.fanSpeed4().setStyleSheet(FAN_OFF);
        ui_.fanSpeed5().setStyleSheet(FAN_OFF);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
    }

    if(fanSpeed == 1)
    {
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed1().setStyleSheet(FAN_OFF);
        ui_.fanSpeed3().setStyleSheet(FAN_OFF);
        ui_.fanSpeed4().setStyleSheet(FAN_OFF);
        ui_.fanSpeed5().setStyleSheet(FAN_OFF);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
    }

    if(fanSpeed == 2)
    {
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed3().setStyleSheet(FAN_OFF);
        ui_.fanSpeed4().setStyleSheet(FAN_OFF);
        ui_.fanSpeed5().setStyleSheet(FAN_OFF);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
    }

    if(fanSpeed == 3)
    {
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed3().setStyleSheet(FAN_ON);
        ui_.fanSpeed4().setStyleSheet(FAN_OFF);
        ui_.fanSpeed5().setStyleSheet(FAN_OFF);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
    }

   if(fanSpeed == 4)
   {
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed3().setStyleSheet(FAN_ON);
        ui_.fanSpeed4().setStyleSheet(FAN_ON);
        ui_.fanSpeed5().setStyleSheet(FAN_OFF);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
   }

   if(fanSpeed == 5)
   {
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed1().setStyleSheet(FAN_ON);
        ui_.fanSpeed3().setStyleSheet(FAN_ON);
        ui_.fanSpeed4().setStyleSheet(FAN_ON);
        ui_.fanSpeed5().setStyleSheet(FAN_ON);
        ui_.fanSpeed6().setStyleSheet(FAN_OFF);
   }

   if(fanSpeed == 6)
   {
       ui_.fanSpeed1().setStyleSheet(FAN_ON);
       ui_.fanSpeed1().setStyleSheet(FAN_ON);
       ui_.fanSpeed3().setStyleSheet(FAN_ON);
       ui_.fanSpeed4().setStyleSheet(FAN_ON);
       ui_.fanSpeed5().setStyleSheet(FAN_ON);
       ui_.fanSpeed6().setStyleSheet(FAN_ON);
   }
}

void BatteryView::requestedFanSpeedReceived(int requestedFanSpeed)
{
    ui_.requestedFanSpeedLabel().setNum(requestedFanSpeed);

    if(requestedFanSpeed == 0)
    {
        ui_.requestedSpeed1().setStyleSheet(FAN_OFF);
        ui_.requqestedSpeed2().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed3().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed4().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed5().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
    }

    if(requestedFanSpeed == 1)
    {
        ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed1().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed3().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed4().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed5().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
    }

    if(requestedFanSpeed == 2)
    {
        ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed3().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed4().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed5().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
    }

    if(requestedFanSpeed == 3)
    {
        ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed3().setStyleSheet(REQUESTED_FAN_ON);
        ui_.requestedSpeed4().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed5().setStyleSheet(FAN_OFF);
        ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
    }

   if(requestedFanSpeed == 4)
   {
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed3().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed4().setStyleSheet(REUESTED_FAN_ON);
       ui_.requestedSpeed5().setStyleSheet(FAN_OFF);
       ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
   }

   if(requestedFanSpeed == 5)
   {
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed3().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed4().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed5().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed6().setStyleSheet(FAN_OFF);
   }

   if(requestedFanSpeed == 6)
   {
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed1().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed3().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed4().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed5().setStyleSheet(REQUESTED_FAN_ON);
       ui_.requestedSpeed6().setStyleSheet(REQUESTED_FAN_ON);
   }
}

void BatteryView::lowCellVoltageReceived(int lowCellVoltage)
{
    ui_.lowCellVoltageLabel().setText(QString::number(lowCellVoltage) + MILLI_VOLTAGE_UNIT);
}

void BatteryView::lowCellVoltageIdReceived(int lowCellVoltageId)
{
    ui_.lowCellVoltageIDLabel().setNum(lowCellVoltageId);
}

void BatteryView::highCellVoltageReceived(int highCellVoltage)
{
    ui_.highCellVoltageLabel().setText(QString::number(highCellVoltage) + MILLI_VOLTAGE_UNIT);
}

void BatteryView::highCellVoltageIdReceived(int highCellVoltageId)
{
    ui_.highCellVoltageIDLabel().setNum(highCellVoltageId)
}

void BatteryView::averageCellVoltageReceived(int lowCellVoltage, int highCellVoltage)
{
    int averageCellVoltage = (lowCellVoltage + highCellVoltage)/2;
    ui_.avgCellVoltageLabel().setText(QString::number(averageCellVoltage) + VOLTAGE_UNIT);
}

void BatteryView::prechargeStateReceived(QString prechargeState)
{

}

void BatteryView::auxVoltageReceived(int auxVoltage)
{
    ui_.auxVoltageLabel().setText(QString::number(auxVoltage) + CURRENT_UNIT);
}

void BatteryView::auxBmsAliveReceived(bool auxBmsAlive)
{
    if (auxBmsAlive)
    {
        ui_.auxBmsAliveWidget().setStyleSheet(BATTERY_ALIVE);
    }
    else
    {
        ui_.auxBmsAliveWidget().setStyleSheet(BATTERY_DEAD);
    }

}

void BatteryView::packNetPowerReceived(double packNetPower)
{

}




#include "RaceModeDashboardView.h"
#include "../../PresenterLayer/BatteryPresenter/BatteryPresenter.h"
#include "../../PresenterLayer/DriverControlsPresenter/DriverControlsPresenter.h"
#include "../../PresenterLayer/KeyMotorPresenter/KeyMotorPresenter.h"
#include "../../PresenterLayer/LightsPresenter/LightsPresenter.h"
#include "../../PresenterLayer/MpptPresenter/MpptPresenter.h"
#include "../../PresenterLayer/MotorDetailsPresenter/MotorDetailsPresenter.h"
#include "../../PresenterLayer/MotorFaultsPresenter/MotorFaultsPresenter.h"
#include "../RaceModeDisplay/RaceModeDisplayUI/I_RaceModeDashboardUI.h"

namespace
{
    const double RED_SLOPE = -1;
    const int RED_INITIAL = 220;
    const double GREEN_SLOPE = 1.7;
    const int GREEN_INITIAL = 10;
    const int BLUE_INITIAL = 20;
    const QString DEFAULT_STYLESHEET = "QProgressBar:horizontal {\
            border: 1px solid white;\
            border-radius: 7px;\
            background: black;\
            }\
            QProgressBar::chunk:horizontal{\
            border-radius: 7px;\
            background: ";
}

RaceModeDashboardView::RaceModeDashboardView(BatteryPresenter& batteryPresenter,
        BatteryFaultsPresenter& batteryFaultsPresenter,
        DriverControlsPresenter& driverControlsPresenter,
        KeyMotorPresenter& keyMotorPresenter,
        LightsPresenter& lightsPresenter,
        MpptPresenter& mpptPresenter,
        MotorDetailsPresenter& motorDetailsPresenter,
        MotorFaultsPresenter& motorFaultsPresenter,
        I_RaceModeDashboardUI& ui,
        FaultList& motorZeroFaultsList,
        FaultList& motorOneFaultsList)
    : batteryPresenter_(batteryPresenter)
    , batteryFaultsPresenter_(batteryFaultsPresenter)
    , driverControlsPresenter_(driverControlsPresenter)
    , keyMotorPresenter_(keyMotorPresenter)
    , lightsPresenter_(lightsPresenter)
    , mpptPresenter_(mpptPresenter)
    , motorDetailsPresenter_(motorDetailsPresenter)
    , motorFaultsPresenter_(motorFaultsPresenter)
    , ui_(ui)
    , motorZeroFaultsList_(motorZeroFaultsList)
    , motorOneFaultsList_(motorOneFaultsList)
{
    connectBattery(batteryPresenter_);
    connectBatteryFaults(batteryFaultsPresenter_);
    connectDriverControls(driverControlsPresenter_);
    connectKeyMotor(keyMotorPresenter_);
    connectLights(lightsPresenter_);
    connectMppt(mpptPresenter_);
    connectMotorDetails(motorDetailsPresenter_);
    connectMotorFaults(motorFaultsPresenter_);
    //ui_.showMaximized();
    ui_.show();
}
RaceModeDashboardView::~RaceModeDashboardView()
{
}

void RaceModeDashboardView::connectBattery(BatteryPresenter& batteryPresenter)
{
    connect(&batteryPresenter, SIGNAL(aliveReceived(bool)),
            this, SLOT(aliveReceived(bool)));
    connect(&batteryPresenter, SIGNAL(prechargeStateReceived(QString)),
            this, SLOT(prechargeStateReceived(QString)));
    connect(&batteryPresenter, SIGNAL(packNetPowerReceived(double)),
            this, SLOT(packNetPowerReceived(double)));
}

void RaceModeDashboardView::connectBatteryFaults(BatteryFaultsPresenter& batteryFaultsPresenter)
{
    connect(&batteryFaultsPresenter, SIGNAL(errorFlagsReceived(BatteryErrorFlags)),
            this, SLOT(errorFlagsReceived(BatteryErrorFlags)));
    connect(&batteryFaultsPresenter, SIGNAL(limitFlagsReceived(BatteryLimitFlags)),
            this, SLOT(limitFlagsReceived(BatteryLimitFlags)));
}

void RaceModeDashboardView::connectDriverControls(DriverControlsPresenter& driverControlsPresenter)
{
    connect(&driverControlsPresenter, SIGNAL(resetReceived(bool)),
            this, SLOT(resetReceived(bool)));
}

void RaceModeDashboardView::connectKeyMotor(KeyMotorPresenter& keyMotorPresenter)
{
    connect(&keyMotorPresenter, SIGNAL(motorSetCurrentReceived(double)),
            this, SLOT(motorSetCurrentReceived(double)));
    connect(&keyMotorPresenter, SIGNAL(motorActualSpeedReceived(double)),
            this, SLOT(motorActualSpeedReceived(double)));
    connect(&keyMotorPresenter, SIGNAL(motorBusVoltageReceived(double)),
            this, SLOT(motorBusVoltageReceived(double)));
    connect(&keyMotorPresenter, SIGNAL(motorBusCurrentReceived(double)),
            this, SLOT(motorBusCurrentReceived(double)));
}

void RaceModeDashboardView::connectLights(LightsPresenter& lightsPresenter)
{
    connect(&lightsPresenter, SIGNAL(lowBeamsReceived(bool)),
            this, SLOT(lowBeamsReceived(bool)));
    connect(&lightsPresenter, SIGNAL(highBeamsReceived(bool)),
            this, SLOT(highBeamsReceived(bool)));
    connect(&lightsPresenter, SIGNAL(leftSignalReceived(bool)),
            this, SLOT(leftSignalReceived(bool)));
    connect(&lightsPresenter, SIGNAL(rightSignalReceived(bool)),
            this, SLOT(rightSignalReceived(bool)));
    connect(&lightsPresenter, SIGNAL(lightAliveReceived(bool)),
            this, SLOT(lightAliveReceived(bool)));
}

void RaceModeDashboardView::connectMppt(MpptPresenter& mpptPresenter)
{
    connect(&mpptPresenter, SIGNAL(mpptReceived(int, Mppt)),
            this, SLOT(mpptReceived(int, Mppt)));
    connect(&mpptPresenter, SIGNAL(mpptPowerReceived(double)),
            this, SLOT(mpptPowerReceived(double)));
}

void RaceModeDashboardView::connectMotorDetails(MotorDetailsPresenter& motorDetailsPresenter)
{
}

void RaceModeDashboardView::connectMotorFaults(MotorFaultsPresenter& motorFaultsPresenter)
{
    connect(&motorFaultsPresenter, SIGNAL(motorZeroErrorFlagsReceived(ErrorFlags)),
            this, SLOT(motorZeroErrorFlagsReceived(ErrorFlags)));
    connect(&motorFaultsPresenter, SIGNAL(motorZeroLimitFlagsReceived(LimitFlags)),
            this, SLOT(motorZeroLimitFlagsReceived(LimitFlags)));
    connect(&motorFaultsPresenter, SIGNAL(motorOneErrorFlagsReceived(ErrorFlags)),
            this, SLOT(motorOneErrorFlagsReceived(ErrorFlags)));
    connect(&motorFaultsPresenter, SIGNAL(motorOneLimitFlagsReceived(LimitFlags)),
            this, SLOT(motorOneLimitFlagsReceived(LimitFlags)));
}

void RaceModeDashboardView::aliveReceived(bool)
{
}

void RaceModeDashboardView::prechargeStateReceived(QString prechargeState)
{
    ui_.prechargeStateLabel().setText(prechargeState);
}

void RaceModeDashboardView::packNetPowerReceived(double netPower)
{
    ui_.netPowerLabel().setNum(netPower);
    ui_.powerOutLabel().setNum(netPower - ui_.powerInLabel().text().toDouble());
}

void RaceModeDashboardView::errorFlagsReceived(BatteryErrorFlags)
{
    // TODO
}
void RaceModeDashboardView::limitFlagsReceived(BatteryLimitFlags)
{
    // TODO
}
void RaceModeDashboardView::resetReceived(bool reset)
{
    if (reset)
    {
        ui_.motorResetButtonWidget().setStyleSheet("background: url(:/Resources/MotorResetButton.png)");
    }
    else
    {
        ui_.motorResetButtonWidget().setStyleSheet("");
    }
}
void RaceModeDashboardView::motorSetCurrentReceived(double setCurrent)
{
    ui_.setCurrentLabel().setNum(setCurrent);
}
void RaceModeDashboardView::motorActualSpeedReceived(double actualSpeed)
{
    ui_.actualSpeedLabel().setNum(actualSpeed);
}
void RaceModeDashboardView::motorBusVoltageReceived(double busVoltage)
{
    ui_.busVoltageLabel().setNum(busVoltage);
}
void RaceModeDashboardView::motorBusCurrentReceived(double busCurrent)
{
    ui_.busCurrentLabel().setNum(busCurrent);
}

void RaceModeDashboardView::lowBeamsReceived(bool lowBeams)
{
    if (lowBeams)
    {
        ui_.lowHeadlightIndicatorWidget().setStyleSheet("border-image: url(:/Resources/LowHeadlightIndicator.png) 0 0 0 0 stretch stretch");
    }
    else
    {
        ui_.lowHeadlightIndicatorWidget().setStyleSheet("");
    }
}
void RaceModeDashboardView::highBeamsReceived(bool highBeams)
{
    if (highBeams)
    {
        ui_.highHeadlightIndicatorWidget().setStyleSheet("border-image: url(:/Resources/HighHeadlightIndicator.png) 0 0 0 0 stretch stretch");
    }
    else
    {
        ui_.highHeadlightIndicatorWidget().setStyleSheet("");
    }
}
void RaceModeDashboardView::leftSignalReceived(bool leftSignal)
{
    if (leftSignal)
    {
        ui_.leftTurnSignalWidget().setStyleSheet("border-image: url(:/Resources/TurnSignalLeft.png) 0 0 0 0 stretch stretch;");
    }
    else
    {
        ui_.leftTurnSignalWidget().setStyleSheet("");
    }
}
void RaceModeDashboardView::rightSignalReceived(bool rightSignal)
{
    if (rightSignal)
    {
        ui_.rightTurnSignalWidget().setStyleSheet("border-image: url(:/Resources/TurnSignalRight.png) 0 0 0 0 stretch stretch;");
    }
    else
    {
        ui_.rightTurnSignalWidget().setStyleSheet("");
    }
}
void RaceModeDashboardView::lightAliveReceived(bool)
{
    // TODO
}

//TODO
void RaceModeDashboardView::mpptReceived(int i, Mppt mppt)
{
}

void RaceModeDashboardView::mpptPowerReceived(double mpptPower)
{
    ui_.powerInLabel().setNum(mpptPower);
    ui_.powerOutLabel().setNum(ui_.netPowerLabel().text().toDouble() - mpptPower);
}

void RaceModeDashboardView::updateMotorLabel(QLabel& motorLabel, FaultLabel& faultLabel)
{
    if(faultLabel.priority() >= 0)
    {
        motorLabel.setStyleSheet("font: 11pt \"Burlingame Pro\";\n color:" + faultLabel.color() +";");
        motorLabel.setText(faultLabel.text());
    }
    else
    {
        motorLabel.setText("");
    }
}

void RaceModeDashboardView::motorZeroErrorFlagsReceived(ErrorFlags flags)
{
    motorZeroFaultsList_.updateErrors(flags);
    FaultLabel highestPriorityError = motorZeroFaultsList_.getHighestActivePriorityLabel();
    updateMotorLabel(ui_.motorZeroFaultsLabel(), highestPriorityError);
}

void RaceModeDashboardView::motorZeroLimitFlagsReceived(LimitFlags flags)
{
     motorZeroFaultsList_.updateLimits(flags);
     FaultLabel highestPriorityLimit = motorZeroFaultsList_.getHighestActivePriorityLabel();
     updateMotorLabel(ui_.motorZeroFaultsLabel(), highestPriorityLimit);
}

void RaceModeDashboardView::motorOneErrorFlagsReceived(ErrorFlags flags)
{
     motorOneFaultsList_.updateErrors(flags);
     FaultLabel highestPriorityError = motorOneFaultsList_.getHighestActivePriorityLabel();
     updateMotorLabel(ui_.motorOneFaultsLabel(), highestPriorityError);
}

void RaceModeDashboardView::motorOneLimitFlagsReceived(LimitFlags flags)
{
    motorOneFaultsList_.updateLimits(flags);
    FaultLabel highestPriorityLimit = motorOneFaultsList_.getHighestActivePriorityLabel();
    updateMotorLabel(ui_.motorOneFaultsLabel(),highestPriorityLimit);
}

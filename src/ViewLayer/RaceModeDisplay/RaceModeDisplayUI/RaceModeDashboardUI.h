#pragma once

#include "I_RaceModeDashboardUI.h"

class FontLoader;

namespace Ui
{
    class RaceModeDashboardUI;
}
class RaceModeDashboardUI : public I_RaceModeDashboardUI
{
    Q_OBJECT

public:
    explicit RaceModeDashboardUI(bool isWindowed);
    ~RaceModeDashboardUI();


    QLabel& actualSpeedLabel();

    QLabel& auxVoltageLabel();

    QLabel& motorZeroSetCurrentLabel();
    QLabel& motorOneSetCurrentLabel();
    QLabel& motorZeroPowerLabel();
    QLabel& motorOnePowerLabel();

    QLabel& batteryFaultsLabel();
    QLabel& motorZeroFaultsLabel();
    QLabel& motorOneFaultsLabel();

    QWidget& leftTurnSignalWidget();
    QWidget& rightTurnSignalWidget();

    QWidget& motorResetButtonWidget();

    QProgressBar& stateOfChargeCapacityWidget();
    QLabel& prechargeStateLabel();

    QWidget& lowHeadlightIndicatorWidget();
    QWidget& highHeadlightIndicatorWidget();

    QLabel& maxCellTemperatureLabel();
    QLabel& avgCellTemperatureLabel();
    QLabel& lowestCellVoltageLabel();
    QLabel& highCellVoltageLabel();

    QLabel& motorZeroBusVoltageLabel();
    QLabel& motorOneBusVoltageLabel();
    QLabel& motorZeroBusCurrentLabel();
    QLabel& motorOneBusCurrentLabel();

    QLabel& arrayPowerLabel();
    QLabel& batteryPowerLabel();

    QLabel& driveModeValueLabel();
private:
    Ui::RaceModeDashboardUI* ui_;
    QScopedPointer<FontLoader> fontLoader_;
};

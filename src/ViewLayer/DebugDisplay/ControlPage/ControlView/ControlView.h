#pragma once
#include <QObject>
#include <QLabel>

#include "../../../../DataLayer/DriverControlsData/DriverControlsData.h"
#include "../../../../PresenterLayer/CcsPresenter/CcsPresenter.h"
#include "../../../../PresenterLayer/DriverControlsPresenter/DriverControlsPresenter.h"
#include "../../../../PresenterLayer/LightsPresenter/LightsPresenter.h"
#include "../../ControlPage/ControlUi/I_ControlUi.h"

class DriverControlsPresenter;

class ControlView : public QObject
{
    Q_OBJECT
public:
    ControlView(CcsPresenter& CcsPresenter,
                DriverControlsPresenter& driverControlsPresenter,
                LightsPresenter& LightsPresenter,
                I_ControlUi& ui);
    ~ControlView();

private:
    void connectCcs(CcsPresenter&);
    void connectDriverControls(DriverControlsPresenter&);
    void connectLights(LightsPresenter&);

    CcsPresenter& ccsPresenter_;
    DriverControlsPresenter& driverControlsPresenter_;
    LightsPresenter& lightsPresenter_;

    I_ControlUi& ui_;

private slots:
    void aliveReceived(bool);
    void aliveLights(bool);
    void ccsAliveReceived(bool);

    void lowHeadlightsReceived(bool);
    void headlightsOffReceived(bool);
    void lowBeamsReceived(bool);

    void leftSignalReceived(bool);
    void rightSignalReceived(bool);
    void leftLightReceived(bool);
    void rightLightReceived(bool);
    void hazardReceived(bool);

    void interiorReceived(bool);
    void pushToTalkReceived(bool);
    void hornReceived(bool);


    void prevSongReceived(bool);
    void nextSongReceived(bool);
    void volumeUpReceived(bool);
    void volumeDownReceived(bool);

    void brakesReceived(bool);
    void brakesLightReceived(bool);
    void forwardReceived(bool);
    void reverseReceived(bool);
    void auxReceived(bool);
    void bmsStrobeLightReceived(bool);
    void resetReceived(bool);

    void accelerationReceived(double);
    void regenBrakingReceived(double);
};

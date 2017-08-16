﻿
#include "ControlView.h"

namespace
{
  const QString MPPT_ALIVE = "background-color:rgb(93, 234, 140); \
                              border-radius:8px; \
                              border: 1px solid white;";
  const QString MPPT_DEAD = "background-color:rgb(147, 147, 147); \
                             border-radius:8px; \
                             border: 1px solid white;";

}

ControlView:ControlView(DriverControlsPresenter &driverControlsPresenter,
                         I_ControlUi &ui)
    : driverControlsPresenter_(driverControlsPresenter)
    , ui_(ui)
{
    connectDriverControls(driverControlsPresenter_);
}

ControlView::~ControlView()
{
}


void ControlView::connectDriverControls(DriverControlsPresenter& driverControlsPresenter)
{
    connect(&driverControlsPresenter, SIGNAL(aliveReceived(bool)),
            this, SLOT(aliveReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(lowHeadlightsReceived(bool)),
            this, SLOT(lowHeadlightsReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(highHeadlightsReceived(bool)),
            this, SLOT(highHeadlightsReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(leftSignalReceived(bool)),
            this, SLOT(leftSignalReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(rightSignalReceived(bool)),
            this, SLOT(rightsSignalReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(hazardReceived(bool)),
            this, SLOT(hazardReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(interiorReceived(bool)),
            this, SLOT(interiorReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(talkReceived(bool)),
            this, SLOT(talkReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(hornReceived(bool)),
            this, SLOT(hornReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(auxReceived(bool)),
            this, SLOT(auxReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(songReceived(bool)),
            this, SLOT(songReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(volumeReceived(bool)),
            this, SLOT(volumeReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(brakesReceived(bool)),
            this, SLOT(brakesReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(forwardReceived(bool)),
            this, SLOT(forwardReceived(bool)));
    connect(&driverControlsPresenter, SIGNAL(reverseReceived(bool)),
            this, SLOT(reverseReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(resetReceived(bool)),
            this, SLOT(resetReceived(bool)));

    connect(&driverControlsPresenter, SIGNAL(accelerationReceived(double)),
            this, SLOT(accelerationReceived(double)));
    connect(&driverControlsPresenter, SIGNAL(regenBrakingReceived(double)),
            this, SLOT(regenBrakingReceived(double)));
}

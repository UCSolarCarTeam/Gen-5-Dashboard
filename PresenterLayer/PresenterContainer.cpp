#include "BatteryPresenter/BatteryPresenter.h"
#include "BusinessLayer/BusinessContainer.h"
#include "CommunicationLayer/CommunicationContainer.h"
#include "CommunicationPresenter/CommunicationPresenter.h"
#include "DataLayer/DataContainer.h"
#include "FaultsPresenter/FaultsPresenter.h"
#include "MpptPresenter/MpptPresenter.h"
#include "PowerPresenter/PowerPresenter.h"
#include "PresenterContainer.h"
#include "VehiclePresenter/VehiclePresenter.h"

PresenterContainer::PresenterContainer(DataContainer& dataContainer,
      CommunicationContainer& communicationContainer,
      BusinessContainer& businessContainer)
: batteryPresenter_(new BatteryPresenter(dataContainer.batteryData()))
, communicationPresenter_(new CommunicationPresenter(
   communicationContainer.commDevice(),
   businessContainer.communicationsMonitoringService()))
, vehiclePresenter_(new VehiclePresenter(dataContainer.vehicleData()))
, mpptPresenter_(new MpptPresenter(dataContainer.mpptData()))
, powerPresenter_(new PowerPresenter(dataContainer.powerData()))
, faultsPresenter_(new FaultsPresenter(dataContainer.faultsData()))
{
}

PresenterContainer::~PresenterContainer()
{
}

BatteryPresenter& PresenterContainer::batteryPresenter()
{
   return *batteryPresenter_;
}

CommunicationPresenter& PresenterContainer::communicationPresenter()
{
   return *communicationPresenter_;
}

VehiclePresenter& PresenterContainer::vehiclePresenter()
{
   return *vehiclePresenter_;
}

MpptPresenter& PresenterContainer::mpptPresenter()
{
   return *mpptPresenter_;
}

PowerPresenter& PresenterContainer::powerPresenter()
{
   return *powerPresenter_;
}

FaultsPresenter& PresenterContainer::faultsPresenter()
{
   return *faultsPresenter_;
}

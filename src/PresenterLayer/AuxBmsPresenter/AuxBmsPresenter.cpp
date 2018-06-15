#include "AuxBmsPresenter.h"
#include "../../DataLayer/AuxBmsData/I_AuxBmsData.h"

AuxBmsPresenter::AuxBmsPresenter(const I_AuxBmsData& auxBmsData)
    : auxBmsData_(auxBmsData)
{
    relayAuxBmsData();
}

void AuxBmsPresenter::relayAuxBmsData()
{
    connect(&auxBmsData_, SIGNAL(prechargeStateReceived(const QString&)),
            this, SIGNAL(prechargeStateReceived(const QString&)));
    connect(&auxBmsData_, SIGNAL(auxVoltageReceived(const int&)),
            this, SIGNAL(auxVoltageReceived(const int&)));
    connect(&auxBmsData_, SIGNAL(auxBmsAliveReceived(const bool&)),
            this, SIGNAL(auxBmsAliveReceived(bool)));
    connect(&auxBmsData_, SIGNAL(strobeBmsLightReceived(const bool&)),
            this, SIGNAL(strobeBmsLightReceived(bool)));
    connect(&auxBmsData_, SIGNAL(allowChargeReceived(const bool&)),
            this, SIGNAL(allowChargeReceived(bool)));
    connect(&auxBmsData_, SIGNAL(contactorErrorReceived(const bool&)),
            this, SIGNAL(contactorErrorReceived(bool)));
    connect(&auxBmsData_, SIGNAL(highVoltageEnableReceived(const bool&)),
            this, SIGNAL(highVoltageEnableReceived(bool)));
}

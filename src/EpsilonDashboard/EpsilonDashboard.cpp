#include <QCommandLineParser>

#include "../DataLayer/DataContainer.h"
#include "../CommunicationLayer/CommunicationContainer.h"
#include "../BusinessLayer/BusinessContainer.h"
#include "../PresenterLayer/PresenterContainer.h"
#include "../ViewLayer/ViewContainer.h"
#include "../InfrastructureLayer/InfrastructureContainer.h"
#include "EpsilonDashboard.h"

#include <QDebug>
#include <QString>

namespace
{
    const char* RACE_QUEUE = "raceQueue";
    const char* DISPLAY_QUEUE = "displayQueue";
    const char* DEBUG_QUEUE = "debugQueue";
}

EpsilonDashboard::EpsilonDashboard(int& argc, char** argv)
    : QApplication(argc, argv)
    , infrastructureContainer_(new InfrastructureContainer())
    , dataContainer_(new DataContainer())
    , businessContainer_(new BusinessContainer(*dataContainer_))
    , communicationContainer_(new CommunicationContainer(*businessContainer_, *infrastructureContainer_))
    , presenterContainer_(new PresenterContainer(*dataContainer_))
{
    QCommandLineParser parser;
    QCommandLineOption raceModeOption("r");
    QCommandLineOption debugModeOption("d");
    parser.addOption(raceModeOption);
    parser.addOption(debugModeOption);

    parser.process(*this);
    Mode mode = Mode::DISPLAY;

    if (parser.isSet(raceModeOption))
    {
        mode = Mode::RACE;
        infrastructureContainer_->setQueueName(RACE_QUEUE);
    }
    else if (parser.isSet(debugModeOption))
    {
        mode = Mode::DEBUG;
        infrastructureContainer_->setQueueName(DEBUG_QUEUE);
    }
    else
    {
        infrastructureContainer_->setQueueName(DISPLAY_QUEUE);
    }

    viewContainer_.reset(new ViewContainer(*presenterContainer_, mode));
}

EpsilonDashboard::~EpsilonDashboard()
{
}

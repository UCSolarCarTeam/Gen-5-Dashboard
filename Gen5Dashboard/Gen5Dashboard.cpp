#include "DataLayer/DataContainer.h"
#include "CommunicationLayer/CommunicationContainer.h"
#include "BusinessLayer/BusinessContainer.h"
#include "PresenterLayer/PresenterContainer.h"
#include "ViewLayer/ViewContainer.h"

#include "Gen5Dashboard.h"

Gen5Dashboard::Gen5Dashboard(int& argc, char** argv)
    : QApplication(argc, argv)
    , dataContainer_(new DataContainer())
    , communicationContainer_(new CommunicationContainer())
    , businessContainer_(new BusinessContainer(*communicationContainer_, *dataContainer_))
    , presenterContainer_(new PresenterContainer(*dataContainer_))
    , viewContainer_(new ViewContainer(*presenterContainer_))
{
}

Gen5Dashboard::~Gen5Dashboard()
{
}

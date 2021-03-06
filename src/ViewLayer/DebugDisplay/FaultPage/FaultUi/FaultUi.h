#pragma once
#include "I_FaultUi.h"

namespace Ui
{
    class FaultUi;
}
class FaultUi : public I_FaultUi
{
    Q_OBJECT
public:
    explicit FaultUi();
    ~FaultUi();

    QWidget& motor0ContentsWidget();
    QWidget& motor1ContentsWidget();
    QWidget& batteryContentsWidget();

    QScrollArea& motor0ScrollArea();
    QScrollArea& motor1ScrollArea();
    QScrollArea& batteryScrollArea();

private:
    Ui::FaultUi* ui_;
};

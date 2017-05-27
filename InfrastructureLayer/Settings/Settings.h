#pragma once

#include <QSettings>

#include "I_Settings.h"

class Settings : public I_Settings
{
public:
    Settings(QString filepath);
    virtual ~Settings() {}
    QString ipAddress() const;
    quint16 port() const;
    QString packetTitle() const;
    QString exchange() const;

private:
    QSettings settings_ ;
};
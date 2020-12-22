/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "FactGroup.h"
#include "QGCMAVLink.h"

class VehicleSensorFactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehicleSensorFactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* sensorTemp         READ sensorTemp         CONSTANT)
    Q_PROPERTY(Fact* sensorHumi         READ sensorHumi         CONSTANT)
    Q_PROPERTY(Fact* sensorBaro         READ sensorBaro         CONSTANT)
    Q_PROPERTY(Fact* sensorWindDir      READ sensorWindDir      CONSTANT)
    Q_PROPERTY(Fact* sensorWindSpd      READ sensorWindSpd      CONSTANT)

    Fact* sensorTemp                        () { return &_sensorTempFact; }
    Fact* sensorHumi                        () { return &_sensorHumiFact; }
    Fact* sensorBaro                        () { return &_sensorBaroFact; }
    Fact* sensorWindDir                     () { return &_sensorWindDirFact; }
    Fact* sensorWindSpd                     () { return &_sensorWindSpdFact; }

    // Overrides from FactGroup
    void handleMessage(Vehicle* vehicle, mavlink_message_t& message) override;

    static const char* _sensorTempFactName;
    static const char* _sensorHumiFactName;
    static const char* _sensorBaroFactName;
    static const char* _sensorWindDirFactName;
    static const char* _sensorWindSpdFactName;

private:
//    void _handleData16     (mavlink_message_t& message);
    void _handleV2_extension (mavlink_message_t& message);
//    void _initializeSensorData          ();
//    void _writeSensorDataLine           ();
#if !defined(NO_ARDUPILOT_DIALECT)
    //void _handleWind        (mavlink_message_t& message);
#endif

    Fact _sensorTempFact;
    Fact _sensorHumiFact;
    Fact _sensorBaroFact;
    Fact _sensorWindDirFact;
    Fact _sensorWindSpdFact;

//    QTimer              _sensorLogTimer;
//    QFile               _sensorLogFile;

};

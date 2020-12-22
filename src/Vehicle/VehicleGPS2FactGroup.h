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

class VehicleGPS2FactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehicleGPS2FactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* latGps2                READ latGps2                CONSTANT)
    Q_PROPERTY(Fact* lonGps2                READ lonGps2                CONSTANT)
    Q_PROPERTY(Fact* mgrsGps2               READ mgrsGps2               CONSTANT)
    Q_PROPERTY(Fact* hdopGps2               READ hdopGps2               CONSTANT)
    Q_PROPERTY(Fact* vdopGps2               READ vdopGps2               CONSTANT)
    Q_PROPERTY(Fact* courseOverGroundGps2   READ courseOverGroundGps2   CONSTANT)
    Q_PROPERTY(Fact* countGps2              READ countGps2              CONSTANT)
    Q_PROPERTY(Fact* lockGps2               READ lockGps2              CONSTANT)

    Fact* latGps2               () { return &_latGps2Fact; }
    Fact* lonGps2               () { return &_lonGps2Fact; }
    Fact* mgrsGps2              () { return &_mgrsGps2Fact; }
    Fact* hdopGps2              () { return &_hdopGps2Fact; }
    Fact* vdopGps2              () { return &_vdopGps2Fact; }
    Fact* courseOverGroundGps2  () { return &_courseOverGroundGps2Fact; }
    Fact* countGps2             () { return &_countGps2Fact; }
    Fact* lockGps2              () { return &_lockGps2Fact; }

    // Overrides from FactGroup
    void handleMessage(Vehicle* vehicle, mavlink_message_t& message) override;

    static const char* _latGps2FactName;
    static const char* _lonGps2FactName;
    static const char* _mgrsGps2FactName;
    static const char* _hdopGps2FactName;
    static const char* _vdopGps2FactName;
    static const char* _courseOverGroundGps2FactName;
    static const char* _countGps2FactName;
    static const char* _lockGps2FactName;

private:
    void _handleGps2Raw   (mavlink_message_t& message);
//    void _handleHighLatency (mavlink_message_t& message);
//    void _handleHighLatency2(mavlink_message_t& message);

    Fact _latGps2Fact;
    Fact _lonGps2Fact;
    Fact _mgrsGps2Fact;
    Fact _hdopGps2Fact;
    Fact _vdopGps2Fact;
    Fact _courseOverGroundGps2Fact;
    Fact _countGps2Fact;
    Fact _lockGps2Fact;
};

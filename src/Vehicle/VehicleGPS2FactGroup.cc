/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehicleGPS2FactGroup.h"
#include "Vehicle.h"
#include "QGCGeo.h"

const char* VehicleGPS2FactGroup::_latGps2FactName =                 "latGps2";
const char* VehicleGPS2FactGroup::_lonGps2FactName =                 "lonGps2";
const char* VehicleGPS2FactGroup::_mgrsGps2FactName =                "mgrsGps2";
const char* VehicleGPS2FactGroup::_hdopGps2FactName =                "hdopGps2";
const char* VehicleGPS2FactGroup::_vdopGps2FactName =                "vdopGps2";
const char* VehicleGPS2FactGroup::_courseOverGroundGps2FactName =    "courseOverGroundGps2";
const char* VehicleGPS2FactGroup::_countGps2FactName =               "countGps2";
const char* VehicleGPS2FactGroup::_lockGps2FactName =                "lockGps2";

VehicleGPS2FactGroup::VehicleGPS2FactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/GPS2Fact.json", parent)
    , _latGps2Fact              (0, _latGps2FactName,               FactMetaData::valueTypeDouble)
    , _lonGps2Fact              (0, _lonGps2FactName,               FactMetaData::valueTypeDouble)
    , _mgrsGps2Fact             (0, _mgrsGps2FactName,              FactMetaData::valueTypeString)
    , _hdopGps2Fact             (0, _hdopGps2FactName,              FactMetaData::valueTypeDouble)
    , _vdopGps2Fact             (0, _vdopGps2FactName,              FactMetaData::valueTypeDouble)
    , _courseOverGroundGps2Fact (0, _courseOverGroundGps2FactName,  FactMetaData::valueTypeDouble)
    , _countGps2Fact            (0, _countGps2FactName,             FactMetaData::valueTypeInt32)
    , _lockGps2Fact             (0, _lockGps2FactName,              FactMetaData::valueTypeInt32)
{
    _addFact(&_latGps2Fact,                 _latGps2FactName);
    _addFact(&_lonGps2Fact,                 _lonGps2FactName);
    _addFact(&_mgrsGps2Fact,                _mgrsGps2FactName);
    _addFact(&_hdopGps2Fact,                _hdopGps2FactName);
    _addFact(&_vdopGps2Fact,                _vdopGps2FactName);
    _addFact(&_courseOverGroundGps2Fact,    _courseOverGroundGps2FactName);
    _addFact(&_lockGps2Fact,                _lockGps2FactName);
    _addFact(&_countGps2Fact,               _countGps2FactName);

    _latGps2Fact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _lonGps2Fact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _mgrsGps2Fact.setRawValue("");
    _hdopGps2Fact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _vdopGps2Fact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _courseOverGroundGps2Fact.setRawValue(std::numeric_limits<float>::quiet_NaN());
}

void VehicleGPS2FactGroup::handleMessage(Vehicle* /* vehicle */, mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_GPS2_RAW:
        _handleGps2Raw(message);
        break;
//    case MAVLINK_MSG_ID_HIGH_LATENCY:
//        _handleHighLatency(message);
//        break;
//    case MAVLINK_MSG_ID_HIGH_LATENCY2:
//        _handleHighLatency2(message);
//        break;
    default:
        break;
    }
}

void VehicleGPS2FactGroup::_handleGps2Raw(mavlink_message_t& message)
{
    mavlink_gps2_raw_t gps2Raw;
    mavlink_msg_gps2_raw_decode(&message, &gps2Raw);

    latGps2()->setRawValue              (gps2Raw.lat * 1e-7);
    lonGps2()->setRawValue              (gps2Raw.lon * 1e-7);
    mgrsGps2()->setRawValue             (convertGeoToMGRS(QGeoCoordinate(gps2Raw.lat * 1e-7, gps2Raw.lon * 1e-7)));
    countGps2()->setRawValue            (gps2Raw.satellites_visible == 255 ? 0 : gps2Raw.satellites_visible);
    hdopGps2()->setRawValue             (gps2Raw.eph == UINT16_MAX ? qQNaN() : gps2Raw.eph / 100.0);
    vdopGps2()->setRawValue             (gps2Raw.epv == UINT16_MAX ? qQNaN() : gps2Raw.epv / 100.0);
    courseOverGroundGps2()->setRawValue (gps2Raw.cog == UINT16_MAX ? qQNaN() : gps2Raw.cog / 100.0);
    lockGps2()->setRawValue             (gps2Raw.fix_type);
}
/*
void VehicleGPSFactGroup::_handleHighLatency(mavlink_message_t& message)
{
    mavlink_high_latency_t highLatency;
    mavlink_msg_high_latency_decode(&message, &highLatency);

    struct {
        const double latitude;
        const double longitude;
        const double altitude;
    } coordinate {
        highLatency.latitude  / (double)1E7,
                highLatency.longitude  / (double)1E7,
                static_cast<double>(highLatency.altitude_amsl)
    };

    lat()->setRawValue  (coordinate.latitude);
    lon()->setRawValue  (coordinate.longitude);
    mgrs()->setRawValue (convertGeoToMGRS(QGeoCoordinate(coordinate.latitude, coordinate.longitude)));
    count()->setRawValue(0);
}

void VehicleGPSFactGroup::_handleHighLatency2(mavlink_message_t& message)
{
    mavlink_high_latency2_t highLatency2;
    mavlink_msg_high_latency2_decode(&message, &highLatency2);

    lat()->setRawValue  (highLatency2.latitude * 1e-7);
    lon()->setRawValue  (highLatency2.longitude * 1e-7);
    mgrs()->setRawValue (convertGeoToMGRS(QGeoCoordinate(highLatency2.latitude * 1e-7, highLatency2.longitude * 1e-7)));
    count()->setRawValue(0);
    hdop()->setRawValue (highLatency2.eph == UINT8_MAX ? qQNaN() : highLatency2.eph / 10.0);
    vdop()->setRawValue (highLatency2.epv == UINT8_MAX ? qQNaN() : highLatency2.epv / 10.0);
}
*/

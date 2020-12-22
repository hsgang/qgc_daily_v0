/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehicleSensorFactGroup.h"
#include "Vehicle.h"

#include <QtMath>

const char* VehicleSensorFactGroup::_sensorTempFactName =       "sensorTemp";
const char* VehicleSensorFactGroup::_sensorHumiFactName =       "sensorHumi";
const char* VehicleSensorFactGroup::_sensorBaroFactName =       "sensorBaro";
const char* VehicleSensorFactGroup::_sensorWindDirFactName =    "sensorWindDir";
const char* VehicleSensorFactGroup::_sensorWindSpdFactName =    "sensorWindSpd";

struct sensorPayload {
    float sensorTempRaw;
    float sensorHumiRaw;
    float sensorBaroRaw;
    float sensorWindDirRaw;
    float sensorWindSpdRaw;
};

VehicleSensorFactGroup::VehicleSensorFactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/SensorFact.json", parent)
    , _sensorTempFact    (0, _sensorTempFactName,       FactMetaData::valueTypeDouble)
    , _sensorHumiFact    (0, _sensorHumiFactName,       FactMetaData::valueTypeDouble)
    , _sensorBaroFact    (0, _sensorBaroFactName,       FactMetaData::valueTypeDouble)
    , _sensorWindDirFact (0, _sensorWindDirFactName,    FactMetaData::valueTypeDouble)
    , _sensorWindSpdFact (0, _sensorWindSpdFactName,    FactMetaData::valueTypeDouble)
{
    _addFact(&_sensorTempFact,          _sensorTempFactName);
    _addFact(&_sensorHumiFact,          _sensorHumiFactName);
    _addFact(&_sensorBaroFact,          _sensorBaroFactName);
    _addFact(&_sensorWindDirFact,       _sensorWindDirFactName);
    _addFact(&_sensorWindSpdFact,       _sensorWindSpdFactName);

    // Start out as not available "--.--"
    _sensorTempFact.setRawValue      (qQNaN());
    _sensorHumiFact.setRawValue      (qQNaN());
    _sensorBaroFact.setRawValue      (qQNaN());
    _sensorWindDirFact.setRawValue   (qQNaN());
    _sensorWindSpdFact.setRawValue   (qQNaN());
}

void VehicleSensorFactGroup::handleMessage(Vehicle* /* vehicle */, mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_V2_EXTENSION:
        _handleV2_extension(message);
        break;
#if !defined(NO_ARDUPILOT_DIALECT)
    case MAVLINK_MSG_ID_WIND:
//        _handleWind(message);
        break;
#endif
    }
}

void VehicleSensorFactGroup::_handleV2_extension(mavlink_message_t& message)
{
    mavlink_v2_extension_t v2_extension;
    mavlink_msg_v2_extension_decode(&message, &v2_extension);

    struct sensorPayload sP;

    memcpy(&sP, &v2_extension.payload, sizeof (struct sensorPayload));

    float sensorTempRaw = sP.sensorTempRaw;
    float sensorHumiRaw = sP.sensorHumiRaw;
    float sensorBaroRaw = sP.sensorBaroRaw;
    float sensorWindDirRaw = sP.sensorWindDirRaw;
    float sensorWindSpdRaw = sP.sensorWindSpdRaw;

    /*
    double sensorTempRaw = v2_extension.payload[0]+v2_extension.payload[1];
    double sensorHumiRaw = v2_extension.payload[2]+v2_extension.payload[3];
    double sensorBaroRaw = v2_extension.payload[4]+v2_extension.payload[5];
    double sensorWindDirRaw = v2_extension.payload[6]+v2_extension.payload[7];
    double sensorWindSpdRaw = v2_extension.payload[8]+v2_extension.payload[9];
*/
    sensorTemp()->setRawValue(sensorTempRaw);
    sensorHumi()->setRawValue(sensorHumiRaw);
    sensorBaro()->setRawValue(sensorBaroRaw);
    sensorWindDir()->setRawValue(sensorWindDirRaw);
    sensorWindSpd()->setRawValue(sensorWindSpdRaw);

}
/*
void VehicleSensorFactGroup::_initializeSensorData()
{
    if(!_toolbox->settingsManager()->appSettings()->saveSensorLog()->rawValue().toBool()){
        return;
    }
    QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QString fileName = QString("%1 vehicle%2.csv").arg(now).arg(_id);
    QDir saveDir(_toolbox->settingsManager()->appSettings()->sensorSavePath());
    _sensorLogFile.setFileName(saveDir.absoluteFilePath(fileName));

    if (!_sensorLogFile.open(QIODevice::Append)) {
        qCWarning(VehicleLog) << "unable to open file for csv logging, Stopping csv logging!";
        return;
    }

    QTextStream stream(&_sensorLogFile);
    QStringList allFactNames;
    allFactNames << factNames();
    for (const QString& groupName: factGroupNames()) {
        for(const QString& factName: getFactGroup(groupName)->factNames()){
            allFactNames << QString("%1.%2").arg(groupName, factName);
        }
    }
    qCDebug(VehicleLog) << "SensorData logged to csv:" << allFactNames;
    stream << "Timestamp," << allFactNames.join(",") << "\n";
}

void VehicleSensorFactGroup::_writeSensorDataLine()
{
    // Only save the logs after the the vehicle gets armed, unless "Save logs even if vehicle was not armed" is checked
    if(!_sensorLogFile.isOpen() && _armed){
//            (_armed || _toolbox->settingsManager()->appSettings()->telemetrySaveNotArmed()->rawValue().toBool())){
//            (_armed || _toolbox->settingsManager()->appSettings()->telemetrySaveNotArmed()->rawValue().toBool())){

        _initializeSensorData();
    }

    if(!_sensorLogFile.isOpen()){
        return;
    }

    QStringList sensorDataValues;
    QTextStream stream(&_sensorLogFile);

    // Write timestamp to csv file
    sensorDataValues << QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss.zzz"));
    // Write Vehicle's own facts
    for (const QString& factName : factNames()) {
        sensorDataValues << getFact(factName)->cookedValueString();
    }
    // write facts from Vehicle's FactGroups
    for (const QString& groupName: factGroupNames()) {
        for (const QString& factName : getFactGroup(groupName)->factNames()) {
            sensorDataValues << getFactGroup(groupName)->getFact(factName)->cookedValueString();
        }
    }

    stream << sensorDataValues.join(",") << "\n";
}
*/

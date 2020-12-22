/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.12
import QtQuick.Controls         2.4
import QtQuick.Controls.Styles  1.4
import QtQuick.Layouts          1.12

import QGroundControl               1.0
import QGroundControl.Controls      1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.FactSystem    1.0

import QGroundControl.FlightMap     1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.Palette       1.0
import QGroundControl.Vehicle       1.0

ColumnLayout {
    id:         root
    spacing:    ScreenTools.defaultFontPixelHeight / 4

    property real   _innerRadius:           (width - (_topBottomMargin * 3)) / 4
    property real   _outerRadius:           _innerRadius + _topBottomMargin
    property real   _spacing:               ScreenTools.defaultFontPixelHeight * 0.33
    property real   _topBottomMargin:       (width * 0.05) / 2

    //property var    vehicle: null
    property var    _activeVehicle:         QGroundControl.multiVehicleManager.activeVehicle
    property real   _sensorTemp:            _activeVehicle ? _activeVehicle.sensor.sensorTemp.rawValue : 0
    property real   _sensorHumi:            _activeVehicle ? _activeVehicle.sensor.sensorHumi.rawValue : 0
    property real   _sensorBaro:            _activeVehicle ? _activeVehicle.sensor.sensorBaro.rawValue : 0
    property real   _sensorWindDir:         _activeVehicle ? _activeVehicle.sensor.sensorWindDir.rawValue : 0
    property real   _sensorWindSpd:         _activeVehicle ? _activeVehicle.sensor.sensorWindSpd.rawValue : 0

    property real   _valueFontSize:         ScreenTools.defaultFontPointSize

    property var    palette:                QGCPalette { colorGroupEnabled: true }

    QGCPalette { id: qgcPal }

    Rectangle {
        visible:            _sensorWindSpd > 10
        Layout.fillWidth:   true
        height:             ScreenTools.defaultFontPixelHeight * 2
        radius:             3
        anchors.margins:    ScreenTools.defaultFontPixelHeight * 1.5
        color:              palette.alertBackground
        border.color:       palette.alertBorder
        border.width:       1

        Label {
            text:               "Warning! Wind Condition"
            color:              palette.alertText
            font.pointSize:     _valueFontSize * 1.2
            anchors.centerIn:   parent
        }
    }

    Rectangle {
        id:                 testInstrument
        //height:             sensorTitle.height * 11
        height:             mainLayout.height + mainLayout.anchors.margins * 2
        Layout.fillWidth:   true
        //radius:             _outerRadius / 8
        radius:             ScreenTools.defaultFontPixelHeight / 2
        color:              qgcPal.window
        //opacity:            0.65

        ColumnLayout {
            id:                 mainLayout
            anchors.margins:    ScreenTools.defaultFontPixelWidth
            anchors.top:        parent.top
            anchors.horizontalCenter:        parent.horizontalCenter
            spacing:            ScreenTools.defaultFontPixelHeight

            QGCLabel {
                Layout.alignment:   Qt.AlignCenter
                text:               "Mesaurement Value"
                font.family:        ScreenTools.demiboldFantFamily
            }

            RowLayout {
                spacing: ScreenTools.defaultFontPixelWidth

                ColumnLayout {
                    QGCLabel { text: "Temperature"}
                    QGCLabel { text: "Humidity"}
                    QGCLabel { text: "Barometer"}
                    QGCLabel { text: "WindDirection"}
                    QGCLabel { text: "WindSpeed"}
                }
                ColumnLayout {
                    QGCLabel { text: _sensorTemp.toFixed(2) + " 'C"}
                    QGCLabel { text: _sensorHumi.toFixed(2) + " %RH"}
                    QGCLabel { text: _sensorBaro.toFixed(2) + " hPa"}
                    QGCLabel { text: _sensorWindDir.toFixed(1) + " deg"}
                    QGCLabel { text: _sensorWindSpd.toFixed(1) + " m/s"}
                }
            }
        }
/*
        QGCLabel {
            id:                 sensorTitle
            text:               "Measurement Value"
            font.pointSize:     _valueFontSize * 1.3
            color:              qgcPal.text
            font.weight:        Font.Bold
            anchors.topMargin:  sensorTitle.height * 0.8
            anchors.top:        parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        QGCLabel {
            id:                 sensortempvalue
            text:               "Temperature : "+ _sensorTemp.toFixed(2) + " 'C"
            font.pointSize:     _valueFontSize * 1.2
            color:              qgcPal.text
            anchors.topMargin:  sensortempvalue.height * 0.6
            anchors.top:        sensorTitle.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        QGCLabel {
            id:                 sensorhumivalue
            text:               "Humidity : "+ _sensorHumi.toFixed(2) + " %RH"
            font.pointSize:     _valueFontSize * 1.2
            color:              qgcPal.text
            anchors.topMargin:  sensorhumivalue.height * 0.6
            anchors.top:        sensortempvalue.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        QGCLabel {
            id:                 sensorbarovalue
            text:               "Barometer : "+ _sensorBaro.toFixed(2) + " hPa"
            font.pointSize:     _valueFontSize * 1.2
            color:              qgcPal.text
            anchors.topMargin:  sensorbarovalue.height * 0.6
            anchors.top:        sensorhumivalue.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        QGCLabel {
            id:                 sensorwinddirvalue
            text:               "WindDir : "+ _sensorWindDir.toFixed(1) + " deg"
            font.pointSize:     _valueFontSize * 1.2
            color:              qgcPal.text
            anchors.topMargin:  sensorwinddirvalue.height * 0.6
            anchors.top:        sensorbarovalue.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        QGCLabel {
            id:                 sensorwindspdvalue
            text:               "WindSpd : "+ _sensorWindSpd.toFixed(1) + " m/s"
            font.pointSize:     _valueFontSize * 1.2
            color:              qgcPal.text
            anchors.topMargin:  sensorwindspdvalue.height * 0.6
            anchors.top:        sensorwinddirvalue.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
*/
    }

    Rectangle {
        id:                 visualInstrument
        height:             _outerRadius * 2
        Layout.fillWidth:   true
        radius:             _outerRadius
        color:              qgcPal.window
        //opacity:            0.65

        DeadMouseArea { anchors.fill: parent }
/*
        QGCAttitudeWidget {
            id:                     attitude
            anchors.leftMargin:     _topBottomMargin
            anchors.left:           parent.left
            size:                   _innerRadius * 2
            vehicle:                globals.activeVehicle
            anchors.verticalCenter: parent.verticalCenter
        }
*/
        QGCWindVaneWidget {
            id:                     windvane
            anchors.leftMargin:     _spacing
            anchors.left:           parent.left
            size:                   _innerRadius * 2
            vehicle:                globals.activeVehicle
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            anchors.left: windvane.right
            anchors.verticalCenter: windvane.verticalCenter
            anchors.leftMargin:     _spacing
            width: _innerRadius * 2
            height: _innerRadius / 2
            color: qgcPal.window
            border.color: "white"
            border.width: 1
            radius: 10

            QGCLabel {
                text: "WindVane"
                color: qgcPal.text
                anchors.centerIn: parent
            }
        }

    }

}

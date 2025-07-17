import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import OpenHD 1.0

Rectangle {
    id: root
    width: 640
    height: 480
    color: "#1e1e1e"
    
    property alias videoItem: windowsVideoItem
    
    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        
        Text {
            text: "Windows Video Plugin Demo"
            color: "white"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Rectangle {
            width: parent.width - 40
            height: 300
            color: "black"
            border.color: "gray"
            border.width: 2
            
            WindowsVideoItem {
                id: windowsVideoItem
                anchors.fill: parent
                anchors.margins: 2
                source: "test://video_stream"
                playing: true
                opacity: opacitySlider.value
            }
        }
        
        RowLayout {
            width: parent.width
            spacing: 20
            
            Text {
                text: "Opacity:"
                color: "white"
            }
            
            Slider {
                id: opacitySlider
                from: 0.0
                to: 1.0
                value: 1.0
                Layout.fillWidth: true
            }
            
            Text {
                text: opacitySlider.value.toFixed(2)
                color: "white"
                Layout.minimumWidth: 40
            }
        }
        
        RowLayout {
            width: parent.width
            spacing: 10
            
            Button {
                text: "Start"
                onClicked: windowsVideoItem.playing = true
                Layout.fillWidth: true
            }
            
            Button {
                text: "Stop"
                onClicked: windowsVideoItem.playing = false
                Layout.fillWidth: true
            }
        }
        
        RowLayout {
            width: parent.width
            spacing: 10
            
            Text {
                text: "Source:"
                color: "white"
            }
            
            TextField {
                id: sourceField
                text: windowsVideoItem.source
                Layout.fillWidth: true
                onEditingFinished: windowsVideoItem.source = text
            }
        }
        
        Text {
            text: "Status: " + (windowsVideoItem.playing ? "Playing" : "Stopped")
            color: windowsVideoItem.playing ? "green" : "red"
            font.pixelSize: 16
        }
    }
}

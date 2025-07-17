import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

import OpenHD 1.0
import "../../video"

Popup {
    id: root
    width: 700
    height: 550
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    
    anchors.centerIn: Overlay.overlay

    background: Rectangle {
        color: "#2c3e50"
        border.color: "#34495e"
        border.width: 2
        radius: 10
    }

    contentItem: WindowsVideoTest {
        anchors.fill: parent
    }

    onOpened: {
        console.log("WindowsVideo popup opened")
    }
    
    onClosed: {
        console.log("WindowsVideo popup closed")
    }
}

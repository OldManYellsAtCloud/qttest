import QtQuick

Rectangle {
    anchors.left: parent.left
    anchors.right: parent.right
    height: 35
    radius: 4
    color: "lightgrey"
    property alias lineNumber: lineNumber.text
    property alias directionLabel: directionLabel.text
    property alias arrivalLabel: arrivalLabel.text
    property alias delayLabel: delayLabel.text
    Text {
        id: lineNumber
        font.pixelSize: 26
        anchors.verticalCenter: root.verticalCenter
        color: "blue"
        padding: 10
    }

    Text {
        id: directionLabel
        font.pixelSize: 26
        anchors.top: root.top
        anchors.left: lineNumber.right
        color: "black"
    }

    Text {
        id: arrivalLabel
        font.pixelSize: 13
        anchors.top: root.top
        anchors.right: root.right
        color: "darkgreen"
    }

    Text {
        id: delayLabel
        font.pixelSize: 13
        anchors.top: arrivalLabel.bottom
        anchors.right: root.right
        color: "black"
    }

}

import QtQuick

Rectangle {
    id: delegateroot
    anchors.left: parent.left
    anchors.right: parent.right
    height: 35
    radius: 4
    color: "lightgrey"

    property alias lineNumber: lineNumber.text
    property alias directionLabel: directionLabel.text
    property alias arrivalLabel: arrivalLabel.text
    property alias delayLabel: delayLabel.text
    property alias color: lineNumber.color
    border.color: "grey"
    border.width: 1
    Text {
        id: lineNumber
        font.pixelSize: 23
        anchors.verticalCenter: parent.verticalCenter
        padding: 10
    }

    Text {
        id: directionLabel
        font.pixelSize: 18
        anchors.top: root.top
        anchors.left: lineNumber.right
        anchors.verticalCenter: lineNumber.verticalCenter
        color: "black"
    }

    Text {
        id: arrivalLabel
        font.pixelSize: 13
        anchors.right: delegateroot.right
        color: "darkgreen"
    }

    Text {
        id: delayLabel
        font.pixelSize: 13
        anchors.right: arrivalLabel.right
        anchors.top: arrivalLabel.bottom
        color: text == "0" ? "black" : "red"
    }
}

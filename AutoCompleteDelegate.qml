import QtQuick

Rectangle {
    property alias text: textLabel.text

    anchors.left: parent.left
    anchors.right: parent.right
    color: "red"
    Text {
        id: textLabel
        anchors.horizontalCenter: parent.horizontalCenter

    }

}

import QtQuick

Rectangle {
    id: root
    property alias text: textLabel.text
    height: 30
    //width: 100
    anchors.left: parent.left
    anchors.right: parent.right
    color: "red"
    border.color: "blue"
    Text {
        id: textLabel
        anchors.centerIn: parent
        font.pixelSize: 15
        color: "green"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            input.text = textLabel.text
            // autocomplete.visible = false
            autocomplete.clearModel()
            stackView.push("DepartureScreen.qml")
        }
    }
}

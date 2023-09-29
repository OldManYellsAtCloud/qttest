import QtQuick

Rectangle {
    id: root
    property alias text: textLabel.text
    height: 30
    anchors.left: parent.left
    anchors.right: parent.right
    color: "lightsteelblue"
    border.color: "blue"
    Text {
        id: textLabel
        anchors.centerIn: parent
        font.pixelSize: 15
        color: "black"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            autocompletion.clearModel()
            stackView.push("DepartureScreen.qml")
            timetable.fetchData(textLabel.text)
        }
    }
}

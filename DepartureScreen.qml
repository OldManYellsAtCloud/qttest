import QtQuick
import QtQuick.Controls

Item {
    visible: true

    ListView {
        id: departureList
        anchors.top: button.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: timetable
        delegate: TimetableDelegate {
            lineNumber: model.linenumber
            directionLabel: model.terminal
            arrivalLabel: model.arrivaltime
            delayLabel: model.delay
            color: model.color
        }
    }

    Button {
        id: button
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        Text {
            anchors.centerIn: parent
            font.pixelSize: 30
            text: qsTr("Back")
            color: "black"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                stackView.pop()
            }
        }
    }
}

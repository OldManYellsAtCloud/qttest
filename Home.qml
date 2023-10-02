import QtQuick
import QtQuick.Controls
import sgy.pine.bus

Item {
    id: root
    anchors.fill: parent

    Text {
        id: label
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Enter the destination")
        font.pixelSize: 20
        font.bold: true
    }

    Rectangle {
        id: inputroot
        anchors.top: label.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        border.color: "blue"
        border.width: 2
        color: "yellow"
        height: 30
        radius: 6
        TextInput {
            id: input
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            color: "green"
            font.pixelSize: 20
            focus: true
            Text {
                color: "gray"
                font.pixelSize: 20
                text: qsTr("Enter a location...")
                visible: !input.text && !input.activeFocus
            }
            onTextChanged: {
                timer.restart()
            }
        }
    }

    ListView {
        visible: true
        anchors.top: inputroot.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 300
        id: autocomplete
        model: autocompletion

        delegate: AutoCompleteDelegate {
            text: model.display
        }
    }

    Timer {
        id: timer
        interval: 800
        running: false
        repeat: false
        onTriggered: {
            if (input.text) {
                autocompletion.fetchData(input.text)
            }
        }
    }

    Button {
        text: qsTr("Quit")
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        onClicked: {
            Qt.quit()
        }
    }
}

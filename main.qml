import QtQuick

Window {
    id: root
    visible: true
    title: qsTr("Hello World")

    Text {
        id: label
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Enter the destination"
        font.pixelSize: 20
        font.bold: true
    }

    Rectangle {
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
            Text {
                color: "gray"
                font.pixelSize: 20
                text: "Enter a location..."
                visible: !input.text && !input.activeFocus
            }
            onTextChanged: {
                timer.restart()
            }
        }
    }

    Timer {
        id: timer
        interval: 800
        running: false
        repeat: false
        onTriggered: {
            if (input.text) {
                console.log("That's when I should ask the internet for ..." + input.text + "...")
            }
        }
    }

    ListView {
        id: autocomplete
    }
}

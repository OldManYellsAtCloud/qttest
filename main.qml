import QtQuick
import QtQuick.Controls
import sgy.pine.bus

Window {
    id: root
    visible: true
    title: qsTr("Hello World")
    //width: 300
    //height: 600

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Home {}
    }

    AutoCompletionHandler {
        id: autocompletion
    }

    TimetableHandler {
        id: timetable
    }
}

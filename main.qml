import QtQuick
import QtQuick.Controls
import sgy.pine.bus

Window {
    id: root
    visible: true

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

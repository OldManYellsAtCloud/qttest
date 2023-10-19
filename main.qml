import QtQuick
import QtQuick.Controls
import sgy.pine.bus

import QtWayland.Compositor

WaylandCompositor {
    id: waylandCompositor
    useHardwareIntegrationExtension: true

    QtTextInputMethodManager{}

    TextInputManager{}
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

    onSurfaceRequested: {
        var surface = surfaceComponent.createObject(comp, { } );
        surface.initialize(comp, client, id, version);
    }
}

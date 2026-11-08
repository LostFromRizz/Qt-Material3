import Material3
import QtQuick

LoadingIndicator {
    id: control

    property color backgroundColor: Theme.colorScheme.primaryContainer
    color: Theme.colorScheme.onPrimaryContainer

    background: Rectangle {
        radius: Math.min(height, width) / 2
        color: control.backgroundColor
    }
}

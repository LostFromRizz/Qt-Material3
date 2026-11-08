import QtQuick
import Material3

Label {
    id: control

    Theme.backgroundColor: Theme.colorScheme.error
    Theme.contentColor: Theme.colorScheme.onError

    background: Rectangle {
        implicitWidth: 6
        radius: Math.min(height, width) / 2
        color: control.Theme.backgroundColor
    }

    font: Theme.typography.labelSmall
    color: Theme.contentColor
    horizontalAlignment: Text.AlignHCenter

    final property Item target: parent

    x: implicitWidth > 6.0 ? 12.0 : 6.0
    y: 0
}

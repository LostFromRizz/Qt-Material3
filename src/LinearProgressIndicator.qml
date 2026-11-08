pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.ProgressBar {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + leftPadding + rightPadding)

    final property color color: Theme.colorScheme.primary
    final property color trackColor: Theme.colorScheme.secondaryContainer
    final property real gapSize: 4.0
    final property bool flat: false

    final property Component stopIndicator: Rectangle {
        final readonly property real size: Math.min(4.0, control.height)
        implicitHeight: size
        implicitWidth: size
        radius: size / 2
        color: control.color
    }

    contentItem: LinearProgressIndicatorImpl {
        implicitHeight: 4.0
        implicitWidth: 240.0
        color: control.color
        trackColor: control.trackColor
        gapSize: control.gapSize
        flat: control.flat
        visualPosition: control.visualPosition
        indeterminate: control.indeterminate

        Loader {
            sourceComponent: control.stopIndicator
            active: !control.indeterminate
            visible: height <= parent.height && width <= parent.width
            x: parent.width - width - Math.min((control.height - height) / 2, 6.0)
            y: (parent.height - height) / 2
        }
    }
}

import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.Control {
    id: control
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    final property color color: Theme.colorScheme.primary
    final property color trackColor: Theme.colorScheme.secondaryContainer
    final property bool indeterminate: false
    final property real gapSize: 4.0
    final property real strokeWidth: 4.0
    final property real value: 0.0
    final property real from: 0.0
    final property real to: 1.0

    final readonly property real position: MInternals.clamp((value - from) / (to - from), 0.0, 1.0)

    contentItem: CircularProgressIndicatorImpl {
        implicitHeight: 40.0
        implicitWidth: 40.0
        color: control.color
        trackColor: control.trackColor
        gapSize: control.gapSize
        strokeWidth: control.strokeWidth
        progress: control.position
        indeterminate: control.indeterminate
    }
}

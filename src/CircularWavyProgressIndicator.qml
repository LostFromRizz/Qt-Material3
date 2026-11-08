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
    final property real trackStrokeWidth: 4.0
    final property real amplitude: {
        if (control.indeterminate) {
            return 1.6;
        }
        return (position <= 0.1 || position >= 0.95) ? 0.0 : 1.6;
    }
    final property real value: 0.0
    final property real from: 0.0
    final property real to: 1.0

    final readonly property real position: MInternals.clamp((value - from) / (to - from), 0.0, 1.0)

    final property real waveLength: 15.0
    final property real waveSpeed: control.waveLength

    contentItem: CircularWavyProgressIndicatorImpl {
        implicitHeight: 48.0
        implicitWidth: 48.0
        color: control.color
        trackColor: control.trackColor
        gapSize: control.gapSize
        waveLength: control.waveLength
        amplitude: control.amplitude
        waveSpeed: control.waveLength
        strokeWidth: control.strokeWidth
        trackStrokeWidth: control.trackStrokeWidth
        progress: control.position
        indeterminate: control.indeterminate
    }
}

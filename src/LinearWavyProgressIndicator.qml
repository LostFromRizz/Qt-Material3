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
    final property real strokeWidth: 4.0
    final property real trackStrokeWidth: 4.0
    final property real amplitude: {
        if (control.indeterminate) {
            return 1.0;
        }
        return (position <= 0.1 || position >= 0.95) ? 0.0 : 1.0;
    }

    final property real waveLength: control.indeterminate ? 20.0 : 40.0
    final property real waveSpeed: control.waveLength

    final property Component stopIndicator: Rectangle {
        final readonly property real size: Math.min(4.0, control.height)
        implicitHeight: size
        implicitWidth: size
        radius: size / 2
        color: control.color
    }

    contentItem: LinearWavyProgressIndicatorImpl {
        implicitHeight: 10.0
        implicitWidth: 240.0
        color: control.color
        trackColor: control.trackColor
        gapSize: control.gapSize
        waveLength: control.waveLength
        amplitude: control.amplitude
        waveSpeed: control.waveSpeed
        strokeWidth: control.strokeWidth
        trackStrokeWidth: control.trackStrokeWidth
        indeterminate: control.indeterminate
        visualPosition: control.visualPosition

        Loader {
            sourceComponent: control.stopIndicator
            active: !control.indeterminate
            visible: height <= parent.height && width <= parent.width
            readonly property real indicatorSize: Math.min(control.trackStrokeWidth, Math.max(implicitHeight, implicitWidth))
            readonly property real offset: (indicatorSize == control.trackStrokeWidth ? 0 : control.trackStrokeWidth / 4)
            readonly property real progressX: control.position * parent.width + control.gapSize
            readonly property real size: x <= progressX ? Math.max(0, indicatorSize - (progressX - x)) : Math.max(implicitHeight, implicitWidth)

            x: parent.width - indicatorSize - offset
            y: (parent.height - height) / 2
            height: size
            width: size
        }
    }
}

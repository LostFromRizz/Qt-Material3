pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.Popup {
    id: control

    final property color backgroundColor: Theme.colorScheme.surface
    final property real elevation: 4

    final property real radius: 4
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property int outlineWidth
    final property color outlineColor

    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: true

    Theme.backgroundColor: backgroundColor

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding)

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0
    verticalPadding: includeElevation ? shadowElevationSize.height : 0
    horizontalPadding: includeElevation ? shadowElevationSize.width : 0

    final property Component overlay: Rectangle {
        color: control.Theme.colorScheme.surfaceDim
        Behavior on opacity {
            NumberAnimation {
                duration: MotionSpecs.durationShort3
            }
        }
    }

    T.Overlay.modal: overlay

    background: SurfacePrivate {
        shadowElevations: control.__shadows
        enabled: control.enabled
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
        backgroundColor: control.backgroundColor
        outlineWidth: control.outlineWidth
        outlineColor: control.outlineColor
    }
}

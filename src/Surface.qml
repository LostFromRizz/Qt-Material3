import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals as M3

T.Pane {
    id: control

    final property real elevation: 4

    final property real radius: 4
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius
    final property color backgroundColor: Theme.backgroundColor

    final property int outlineWidth
    final property color outlineColor: Theme.colorScheme.outlineVariant

    final property bool includeElevation: false
    final readonly property list<var> __shadows: M3.MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding)

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0
    verticalPadding: includeElevation ? shadowElevationSize.height : 0
    horizontalPadding: includeElevation ? shadowElevationSize.width : 0

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

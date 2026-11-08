import QtQuick
import QtQuick.Templates as T
import Material3

T.ItemDelegate {
    id: control

    final property real radius: 12
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property color backgroundColor: enabled ? Theme.colorScheme.primary : Qt.alpha(Theme.colorScheme.surface, 0.38)
    final property color contentColor: Material.contentColorFor(backgroundColor, Theme.colorScheme)

    final property real elevation
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: false

    Theme.iconSize: Qt.size(24, 24)

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0
    verticalPadding: (includeElevation ? shadowElevationSize.height : 0)
    horizontalPadding: 16 + (includeElevation ? shadowElevationSize.width : 0)

    Theme.contentColor: contentColor
    Theme.backgroundColor: backgroundColor

    background: InteractiveSurface {
        target: control
        shadowElevations: control.__shadows
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
    }
}

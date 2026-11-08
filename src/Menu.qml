import QtQuick
import Material3
import Material3.internals

AbstractStyledMenu {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: MInternals.clamp(Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding), 112.0, 280.0)

    enum Style {
        Vibrant,
        Standard
    }

    final property int style: Menu.Standard

    final property real radius: 4
    final property real elevation: 6
    final property bool includeElevation: false
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))

    final property color backgroundColor: style === Menu.Vibrant ? Theme.colorScheme.tertiaryContainer : Theme.colorScheme.surfaceContainerLow

    Theme.iconSize: Qt.size(24.0, 24.0)
    padding: 4

    delegate: MenuItem {}

    contentItem: ListView {
        implicitHeight: contentHeight
        model: control.contentModel
        interactive: Window.window ? contentHeight + control.topPadding + control.bottomPadding > control.height : false
        clip: true
        currentIndex: control.currentIndex
        spacing: control.spacing
        // T.ScrollIndicator.vertical: ScrollIndicator {}
    }

    background: SurfacePrivate {
        shadowElevations: control.__shadows
        enabled: control.enabled
        topLeftRadius: control.radius
        bottomLeftRadius: control.radius
        topRightRadius: control.radius
        bottomRightRadius: control.radius
        backgroundColor: control.backgroundColor
    }
}

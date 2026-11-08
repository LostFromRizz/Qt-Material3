import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.MenuItem {
    id: control

    final property int colorScheme: control.menu instanceof AbstractFloatingActionButtonMenu ? (control.menu as AbstractFloatingActionButtonMenu).colorScheme : FloatingActionButton.Primary

    final property real iconSize: 24.0
    final property real radius: Math.max(height, width) / 2
    final property real elevation
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: true

    height: implicitHeight
    width: implicitWidth * (control.menu instanceof AbstractFloatingActionButtonMenu ? (control.menu as AbstractFloatingActionButtonMenu).animatedSize : 1)
    opacity: control.menu instanceof AbstractFloatingActionButtonMenu ? (control.menu as AbstractFloatingActionButtonMenu).animatedOpacity : 1
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(56.0, Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding))
    icon.height: iconSize
    icon.width: iconSize
    spacing: 8.0
    horizontalPadding: 24.0 + (includeElevation ? shadowElevationSize.width : 0)
    verticalPadding: includeElevation ? shadowElevationSize.height : 0
    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0

    x: Math.max(0, (control.menu?.width ?? 0) - control.width)
    clip: true

    readonly property bool __hasIcon: icon.name.length > 0 || icon.source.toString().length > 0
    display: {
        if (__hasIcon) {
            if (text.length > 0) {
                return T.AbstractButton.TextBesideIcon;
            }
            return T.AbstractButton.IconOnly;
        } else {
            return T.AbstractButton.TextOnly;
        }
    }

    font: Theme.typography.titleMedium

    Keys.enabled: control.activeFocus
    Keys.onPressed: event => {
        // space is handled by default
        if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            control.click();
            event.accepted = true;
        } else {
            event.accepted = false;
        }
    }

    final property color backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }

        switch (colorScheme) {
        case FloatingActionButton.Secondary:
            return Theme.colorScheme.secondary;
        case FloatingActionButton.Tertiary:
            return Theme.colorScheme.tertiary;
        case FloatingActionButton.TonalPrimary:
            return Theme.colorScheme.primaryContainer;
        case FloatingActionButton.TonalSecondary:
            return Theme.colorScheme.secondaryContainer;
        case FloatingActionButton.TonalTertiary:
            return Theme.colorScheme.tertiaryContainer;
        case FloatingActionButton.Primary:
        default:
            return Theme.colorScheme.primary;
        }
    }

    final property color contentColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }

        switch (colorScheme) {
        case FloatingActionButton.Secondary:
            return Theme.colorScheme.onSecondary;
        case FloatingActionButton.Tertiary:
            return Theme.colorScheme.onTertiary;
        case FloatingActionButton.TonalPrimary:
            return Theme.colorScheme.onPrimaryContainer;
        case FloatingActionButton.TonalSecondary:
            return Theme.colorScheme.onSecondaryContainer;
        case FloatingActionButton.TonalTertiary:
            return Theme.colorScheme.onTertiaryContainer;
        case FloatingActionButton.Primary:
        default:
            return Theme.colorScheme.onPrimary;
        }
    }

    MouseArea {
        id: hoverHandler
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse => mouse.accepted = false
        onReleased: mouse => mouse.accepted = false
        onDoubleClicked: mouse => mouse.accepted = false
        onPressAndHold: mouse => mouse.accepted = false
    }

    background: InteractiveSurface {
        target: control
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
        shadowElevations: control.__shadows
        topLeftRadius: control.radius
        bottomLeftRadius: control.radius
        topRightRadius: control.radius
        bottomRightRadius: control.radius
    }

    contentItem: IconLabel {
        spacing: control.spacing
        text: control.text
        display: control.display
        color: control.contentColor
        iconName: control.icon.name
        iconSource: control.icon.source
        iconSize: Math.max(control.icon.width, control.icon.height)
    }
}

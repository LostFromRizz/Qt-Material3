import QtQuick.Templates as T
import QtQuick
import Material3
import Material3.internals

T.AbstractButton {
    id: control

    final property real elevation

    final property real radius: {
        if (checkable) {
            if (checked || hovered) {
                return Material.buttonSelectedRadius(containerHeight);
            }
            return Math.min(height, width) / 2;
        }

        return Math.min(height, width) / 2;
    }
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property real containerHeight: Material.buttonHeightSmall

    final property color backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.surfaceContainer;
        }
        return Theme.colorScheme.primary;
    }

    final property color contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.onPrimary : Theme.colorScheme.onSurfaceVariant;
        }
        return Theme.colorScheme.onPrimary;
    }

    final property color outlineColor
    final property real outlineWidth

    final property int iconSize: Material.iconButtonIconSize(control.containerHeight)

    final property alias cursorShape: hoverHandler.cursorShape

    final readonly property bool __hasIcon: icon.name.length > 0 || icon.source.toString().length > 0
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: false

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

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, containerHeight + topInset + bottomInset, containerHeight)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0
    verticalPadding: Material.buttonVerticalPadding(containerHeight) + (includeElevation ? shadowElevationSize.height : 0)
    horizontalPadding: Material.buttonHorizontalPadding(containerHeight) + (includeElevation ? shadowElevationSize.width : 0)

    spacing: Material.buttonSpacing(containerHeight)

    icon.color: action?.icon.color ?? contentColor
    icon.height: action?.icon.height ?? control.iconSize
    icon.width: action?.icon.width ?? control.iconSize

    Theme.iconSize: Qt.size(control.icon.width, control.icon.height)

    font: Material.buttonFont(Theme.typography, containerHeight)

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
        shadowElevations: control.__shadows
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
        outlineWidth: control.outlineWidth
        outlineColor: control.outlineColor
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
    }

    Theme.contentColor: control.contentColor

    contentItem: IconLabel {
        icon: control.icon
        text: control.text
        font: control.font
        spacing: control.spacing
        textColor: control.contentColor
        display: control.display
    }
    // contentItem: IconLabel {
    //     spacing: control.spacing
    //     text: control.text
    //     iconName: control.icon.name
    //     iconSource: control.icon.source
    //     iconSize: Math.max(control.icon.width, control.icon.height)
    //     display: control.display
    //     color: control.contentColor
    // }

    Behavior on radius {
        NumberAnimation {
            easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
            duration: MotionSpecs.expressiveFastSpatialDuration
            easing.type: Easing.BezierSpline
        }
    }
}

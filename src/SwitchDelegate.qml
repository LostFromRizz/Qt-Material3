import QtQuick
import QtQuick.Templates as T
import Material3

T.SwitchDelegate {
    id: control

    final property int outlineWidth: 2
    final property color outlineColor: {
        if (!enabled) {
            return Qt.alpha(Theme.colorScheme.onSurface, 0.12);
        }
        if (checked) {
            return Theme.colorScheme.primary;
        } else {
            return Theme.colorScheme.outline;
        }
    }

    final property color backgroundColor: {
        if (!enabled) {
            return Qt.alpha(checked ? Theme.colorScheme.onSurface : Theme.colorScheme.surfaceContainerHighest, 0.12);
        }
        if (checked) {
            return Theme.colorScheme.primary;
        }
        return Theme.colorScheme.surfaceContainerHighest;
    }

    final property color handleColor: {
        if (!enabled) {
            if (checked) {
                return Theme.colorScheme.onSurface;
            }
            return Material.disabledContentColor(Theme.colorScheme.surfaceContainerHighest);
        }

        if (checked) {
            return Theme.colorScheme.onPrimary;
        }
        return Theme.colorScheme.outline;
    }

    final property alias iconColor: control.icon.color
    final property int iconSize: 16.0
    final property alias cursorShape: hoverHandler.cursorShape

    final property bool __hasIcon: control.icon.name.length > 0 || control.icon.source.toString().length > 0

    icon.color: {
        if (!enabled) {
            return Material.disabledContentColor(checked ? Theme.colorScheme.onSurface : Theme.colorScheme.surfaceContainerHighest);
        }
        if (checked) {
            return Theme.colorScheme.primary;
        }
        return Theme.colorScheme.surfaceContainerHighest;
    }

    Theme.contentColor: Theme.colorScheme.onSurface

    Theme.iconSize: Qt.size(icon.width, icon.height)
    icon.height: iconSize
    icon.width: iconSize

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)

    topInset: 7.0
    bottomInset: 7.0

    MouseArea {
        id: hoverHandler
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse => mouse.accepted = false
        onReleased: mouse => mouse.accepted = false
        onDoubleClicked: mouse => mouse.accepted = false
        onPressAndHold: mouse => mouse.accepted = false
    }

    indicator: Rectangle {
        final property real handleSize: {
            if (control.pressed || control.down) {
                return 28.0;
            }
            if (control.checked) {
                return 24.0;
            }

            return control.__hasIcon ? 24.0 : 16.0;
        }
        final property real animatedHandleSize: handleSize

        implicitHeight: animatedHandleSize
        implicitWidth: animatedHandleSize
        radius: animatedHandleSize / 2
        color: control.handleColor

        anchors.verticalCenter: parent.verticalCenter
        // TODO handle control.padding
        final property real padding: (control.availableHeight - control.topInset - control.bottomInset - handleSize) / 2
        x: padding + (control.availableWidth - handleSize - padding * 2) * control.visualPosition

        Behavior on color {
            ColorAnimation {
                easing.bezierCurve: MotionSpecs.expressiveDefaultEffectsBezier
                easing.type: Easing.BezierSpline
                duration: MotionSpecs.expressiveDefaultEffectsDuration
            }
        }

        Behavior on animatedHandleSize {
            NumberAnimation {
                easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
                easing.type: Easing.BezierSpline
                duration: MotionSpecs.expressiveFastSpatialDuration
            }
        }

        Behavior on x {
            NumberAnimation {
                easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
                easing.type: Easing.BezierSpline
                duration: MotionSpecs.expressiveFastSpatialDuration
            }
        }

        // Rectangle {
        //     height: parent.height + parent.padding
        //     width: parent.width + parent.padding
        //     x: -parent.padding / 2
        //     y: -parent.padding / 2
        //     color: Qt.alpha('red', 0.8)
        //
        //     Connections {}
        // }
    }

    contentItem: Icon {
        visible: control.__hasIcon && control.indicator
        name: control.icon.name
        color: control.icon.color
        size: Math.max(control.icon.width, control.icon.height)
        x: (control.indicator?.x ?? 0) + ((control.indicator?.width ?? 0) - width) / 2
        y: (control.indicator?.y ?? 0) + ((control.indicator?.height ?? 0) - height) / 2
    }

    background: Rectangle {
        implicitHeight: 32.0
        implicitWidth: 52.0
        radius: height / 2
        border.width: control.outlineWidth
        border.color: control.outlineColor
        color: control.backgroundColor

        Behavior on color {
            ColorAnimation {
                easing.bezierCurve: MotionSpecs.expressiveDefaultEffectsBezier
                easing.type: Easing.BezierSpline
                duration: MotionSpecs.expressiveDefaultEffectsDuration
            }
        }

        Behavior on border.color {
            ColorAnimation {
                easing.bezierCurve: MotionSpecs.expressiveDefaultEffectsBezier
                easing.type: Easing.BezierSpline
                duration: MotionSpecs.expressiveDefaultEffectsDuration
            }
        }
    }
}

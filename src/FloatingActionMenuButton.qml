import Material3
import QtQuick
import QtQuick.Templates as T

FloatingActionButton {
    id: control

    final property T.Menu menu

    final property icon activeIcon: ({
            name: "add",
            width: Material.fabIconSize(containerHeight),
            color: contentColor
        })
    final property icon closedIcon: MInternals.iconData("close", 20.0, contentColor)

    final readonly property var effectiveIcon: checkable && checked ? closedIcon : activeIcon

    final property real closeButtonSize: 56.0

    iconSize: 0
    icon.name: effectiveIcon.name
    icon.source: effectiveIcon.source
    icon.color: effectiveIcon.color
    icon.width: effectiveIcon.width
    icon.height: effectiveIcon.height
    icon.cache: effectiveIcon.cache
    checkable: true

    radius: checkable && checked ? closeButtonSize / 2 : Material.fabRadius(containerHeight)

    implicitHeight: checkable && checked ? closeButtonSize : Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, containerHeight)
    implicitWidth: checkable && checked ? closeButtonSize : Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding)

    Behavior on implicitHeight {
        NumberAnimation {
            easing.bezierCurve: MotionSpecs.expressiveDefaultSpatialBezier
            easing.type: Easing.BezierSpline
            duration: MotionSpecs.expressiveDefaultSpatialDuration
        }
    }

    Behavior on implicitWidth {
        NumberAnimation {
            easing.bezierCurve: MotionSpecs.expressiveDefaultSpatialBezier
            easing.type: Easing.BezierSpline
            duration: MotionSpecs.expressiveDefaultSpatialDuration
        }
    }

    Binding {
        target: control.menu
        when: control.menu
        property: "parent"
        value: {
            if (control.menu === null) {
                return;
            }
            return control;
        }
    }

    // component ShapeMorphAnimation: SpringAnimation {
    //     damping: 1 - 0.7
    //     spring: 3.8
    // }
}

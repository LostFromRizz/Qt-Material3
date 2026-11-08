pragma ComponentBehavior: Bound
import QtQuick
import Material3
import Material3.internals

AbstractFloatingActionButtonMenu {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, contentHeight + topPadding + bottomPadding)

    margins: 0
    spacing: 4.0
    delegate: FloatingActionButtonMenuItem {}

    readonly property FloatingActionButton __button: parent instanceof FloatingActionButton ? (parent as FloatingActionButton) : null

    override property int colorScheme: parent instanceof FloatingActionButton ? (parent as FloatingActionButton).colorScheme : FloatingActionButton.Primary
    final readonly property real animatedOpacity: menuState.animatedOpacity
    final readonly property real animatedSize: menuState.animatedSize

    rightMargin: {
        if (__button !== null) {
            const margin = (__button.parent instanceof Scaffold) ? (__button.parent as Scaffold).floatingActionButtonHorizontalMargin : 16.0;
            return margin;
        }
        return 16.0;
    }
    bottomMargin: {
        if (__button !== null) {
            const margin = (__button.parent instanceof Scaffold) ? (__button.parent as Scaffold).floatingActionButtonVerticalMargin : 16.0;
            return Math.max(__button.height, __button.containerHeight) + 8.0 + margin;
        }
        return 8.0 + 16.0;
    }

    QtObject {
        id: menuState
        property real animatedOpacity
        property real animatedSize
    }

    contentItem: Column {
        spacing: control.spacing

        Repeater {
            enabled: control.contentModel.count <= 6
            model: control.contentModel
        }
    }

    enter: Transition {
        PropertyAnimation {
            target: menuState
            property: "animatedSize"
            from: 0
            to: 1
            easing.type: Easing.BezierSpline
            easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
            duration: MotionSpecs.expressiveFastSpatialDuration
        }
        PropertyAnimation {
            target: menuState
            property: "animatedOpacity"
            from: 0
            to: 1
            easing.type: Easing.BezierSpline
            easing.bezierCurve: MotionSpecs.expressiveFastEffectsBezier
            duration: MotionSpecs.expressiveFastEffectsDuration
        }
    }
    exit: Transition {
        PropertyAnimation {
            target: menuState
            property: "animatedSize"
            from: 1
            to: 0
            easing.type: Easing.BezierSpline
            easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
            duration: MotionSpecs.expressiveFastSpatialDuration
        }
        PropertyAnimation {
            target: menuState
            property: "animatedOpacity"
            from: 1
            to: 0
            easing.type: Easing.BezierSpline
            easing.bezierCurve: MotionSpecs.expressiveFastEffectsBezier
            duration: MotionSpecs.expressiveFastEffectsDuration
        }
    }
}

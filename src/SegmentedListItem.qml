import QtQuick
import Material3

ListItem {
    final required property int index
    final required property int count

    final property real innerRadius: 4.0
    final property real selectedRadius: 16.0

    radius: 16.0

    final property real effectiveTopRadius: {
        if (count <= 1) {
            return radius;
        }

        if (!checked) {
            if (index === 0) {
                return radius;
            } else if (index === count - 1) {
                return innerRadius;
            }
        }

        if (checked) {
            return selectedRadius;
        }

        return innerRadius;
    }

    final property real effectiveBottomRadius: {
        if (count <= 1) {
            return radius;
        }

        if (!checked) {
            if (index === count - 1) {
                return radius;
            } else if (index === 0) {
                return innerRadius;
            }
        }

        if (checked) {
            return selectedRadius;
        }

        return innerRadius;
    }

    topLeftRadius: effectiveTopRadius
    topRightRadius: effectiveTopRadius
    bottomLeftRadius: effectiveBottomRadius
    bottomRightRadius: effectiveBottomRadius

    Behavior on effectiveTopRadius {
        RadiusAnimation {}
    }

    Behavior on effectiveBottomRadius {
        RadiusAnimation {}
    }

    component RadiusAnimation: NumberAnimation {
        easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
        duration: MotionSpecs.expressiveFastSpatialDuration
        easing.type: Easing.BezierSpline
    }
}

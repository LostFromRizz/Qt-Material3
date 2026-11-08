import QtQuick
import QtQuick.Layouts
import Material3

RowLayout {
    id: control
    final property alias leading: leadingItem.target
    final property alias trailing: trailingItem.target

    spacing: 2

    LayoutItemProxy {
        id: leadingItem
    }
    LayoutItemProxy {
        id: trailingItem
    }

    component LeadingButton: Button {
        final property real startRadius: {
            if (checkable && checked) {
                return Math.min(height, width) / 2;
            }
            return Material.splitButtonInnerRadius(containerHeight);
        }

        radius: Math.min(height, width) / 2
        topRightRadius: startRadius
        bottomRightRadius: startRadius

        Behavior on startRadius {
            NumberAnimation {
                easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
                duration: MotionSpecs.expressiveFastSpatialDuration
                easing.type: Easing.BezierSpline
            }
        }
    }
    component TrailingButton: Button {
        final property real startRadius: {
            if (checkable && checked) {
                return Math.min(height, width) / 2;
            }
            return Material.splitButtonInnerRadius(containerHeight);
        }
        radius: Math.min(height, width) / 2
        topLeftRadius: startRadius
        bottomLeftRadius: startRadius

        Behavior on startRadius {
            NumberAnimation {
                easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
                duration: MotionSpecs.expressiveFastSpatialDuration
                easing.type: Easing.BezierSpline
            }
        }
    }
}

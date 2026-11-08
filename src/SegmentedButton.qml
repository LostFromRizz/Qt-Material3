pragma ComponentBehavior: Bound
import QtQuick
import Material3
import Material3.internals

Button {
    id: control

    enum Style {
        Filled,
        Tonal,
        Elevated,
        Outlined
    }

    final required property int index
    final required property int count
    final property int style: SegmentedButton.Outlined
    final property bool shapeMorph: true
    final property real innerRadius: shapeMorph ? Material.buttonInnerRadius(containerHeight) : 0
    final property real selectedRadius: shapeMorph ? Math.min(height, width) / 2 : 0

    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        switch (style) {
        case SegmentedButton.Elevated:
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.surfaceContainerLow;
        case SegmentedButton.Tonal:
            return checked ? Theme.colorScheme.secondary : Theme.colorScheme.secondaryContainer;
        case SegmentedButton.Filled:
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.surfaceContainer;
        case SegmentedButton.Outlined:
        default:
            return checked ? Theme.colorScheme.secondaryContainer : "transparent";
        }
    }

    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        switch (style) {
        case SegmentedButton.Elevated:
            return checked ? Theme.colorScheme.onPrimary : Theme.colorScheme.primary;
        case SegmentedButton.Tonal:
            return checked ? Theme.colorScheme.onSecondary : Theme.colorScheme.onSecondaryContainer;
        case SegmentedButton.Filled:
            return checked ? Theme.colorScheme.onPrimary : Theme.colorScheme.onSurfaceVariant;
        case SegmentedButton.Outlined:
        default:
            return checked ? Theme.colorScheme.onSecondaryContainer : Theme.colorScheme.onSurface;
        }
    }

    elevation: style === SegmentedButton.Elevated ? 1.0 : 0.0
    outlineWidth: style === SegmentedButton.Outlined ? 1.0 : 0.0
    outlineColor: Theme.colorScheme.outlineVariant
    checkable: true
    radius: 0

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
        shape: control.style === SegmentedButton.Outlined && control.outlineWidth > 0 ? quickShape : simpleRectShape
    }

    final property real effectiveLeftRadius: {
        if (count > 1) {
            if (!checked || !shapeMorph) {
                if (index === 0) {
                    return Math.min(height, width) / 2;
                } else if (index === count - 1) {
                    return innerRadius;
                }
            }
        }

        if (checked && shapeMorph) {
            return selectedRadius;
        }

        return innerRadius;
    }

    final property real effectiveRightRadius: {
        if (count > 1) {
            if (!checked || !shapeMorph) {
                if (index === count - 1) {
                    return Math.min(height, width) / 2;
                } else if (index === 0) {
                    return innerRadius;
                }
            }
        }

        if (checked && shapeMorph) {
            return selectedRadius;
        }

        return innerRadius;
    }

    topLeftRadius: effectiveLeftRadius
    bottomLeftRadius: effectiveLeftRadius
    topRightRadius: effectiveRightRadius
    bottomRightRadius: effectiveRightRadius

    Behavior on effectiveLeftRadius {
        enabled: control.shapeMorph
        NumberAnimation {
            easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
            duration: MotionSpecs.expressiveFastSpatialDuration
            easing.type: Easing.BezierSpline
        }
    }

    Behavior on effectiveRightRadius {
        enabled: control.shapeMorph
        NumberAnimation {
            easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
            duration: MotionSpecs.expressiveFastSpatialDuration
            easing.type: Easing.BezierSpline
        }
    }

    Component {
        id: quickShape
        // Shape made using QtQuick.Shapes api to avoid overlapping outline caused by plain Rectangle
        QuickShapeRect {
            anchors.fill: parent
            topLeftRadius: control.topLeftRadius
            bottomLeftRadius: control.bottomLeftRadius
            topRightRadius: control.topRightRadius
            bottomRightRadius: control.bottomRightRadius
            strokeWidth: control.outlineWidth
            strokeColor: control.outlineColor
            fillColor: control.backgroundColor
        }
    }

    Component {
        id: simpleRectShape
        Rectangle {
            anchors.fill: parent
            topLeftRadius: control.topLeftRadius
            bottomLeftRadius: control.bottomLeftRadius
            topRightRadius: control.topRightRadius
            bottomRightRadius: control.bottomRightRadius
            color: control.backgroundColor
            border.width: control.outlineWidth
            border.color: control.outlineColor
        }
    }
}

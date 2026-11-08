import QtQuick
import Material3
import Material3.internals

TextField {
    id: control

    final property real radius: 8.0
    topLeftRadius: radius
    topRightRadius: radius
    bottomLeftRadius: radius
    bottomRightRadius: radius

    topPadding: containerTopPadding
    bottomPadding: containerBottomPadding + implicitSupportingItemHeight
    rightPadding: containerRightPadding + (implicitTrailingWidth > 0 ? implicitTrailingWidth + spacing : 0)
    leftPadding: containerLeftPadding + (implicitLeadingWidth > 0 ? implicitLeadingWidth + spacing : 0)

    final property color outlineColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (hasError) {
            return Theme.colorScheme.error;
        }
        if (activeFocus) {
            return Theme.colorScheme.primary;
        }
        return Theme.colorScheme.onSurfaceVariant;
    }
    final property real outlineWidth: control.activeFocus ? 2 : 1

    background: OutlinedTextFieldBackgroundImpl {
        height: control.height - control.implicitSupportingItemHeight
        stopX: (label?.x ?? 0) - gap
        hasLabel: control.implicitLabelWidth > 0
        floatingLabel: control.__floating
        labelWidth: control.implicitLabelWidth
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
        outlineWidth: control.outlineWidth
        outlineColor: control.outlineColor
        spacing: gapWidth

        property real gap: 4
        readonly property real gapWidth: control.implicitLabelWidth + gap * 2

        // qmllint disable missing-property
        Binding {
            target: control
            property: "__labelItem"
            value: control.background.label
        }

        readonly property Text label: Text {
            parent: control.background
            text: control.labelText
            font: Material.textFieldLabelFont(Theme.typography, control.activeFocus || control.displayText)
            color: control.labelTextColor

            x: control.__floating ? control.background.gap + (control.leading ? control.containerLeftPadding : control.containerLeftPadding - parent.gap) : control.leftPadding
            y: control.__floating ? -(height / 2) : (control.containerHeight - height) / 2
            visible: control.labelText
            renderType: control.renderType

            Behavior on y {
                NumberAnimation {
                    duration: MotionSpecs.standardDefaultSpatialDuration
                    easing.bezierCurve: MotionSpecs.standardDefaultSpatialBezier
                    easing.type: Easing.BezierSpline
                }
            }
        }

        // qmllint enable missing-property
    }
}

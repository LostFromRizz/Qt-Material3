pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.SearchField {
    id: control

    final property real radius: Math.min(height, width) / 2
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property real elevation: 6
    final property bool includeElevation: false
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))

    final property color backgroundColor: Theme.colorScheme.surfaceContainerHigh

    final property color contentColor: Theme.colorScheme.onSurface

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, 56.0)
    implicitWidth: MInternals.clamp(Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding), 360.0, 720.0)

    leftInset: focusedMargin
    rightInset: focusedMargin

    horizontalPadding: 4 + focusedMargin
    leftPadding: 4 + focusedMargin + (searchIndicator.indicator && searchIndicator.indicator.visible ? searchIndicator.implicitIndicatorWidth : 0)
    rightPadding: 4 + focusedMargin + (clearIndicator.indicator && clearIndicator.indicator.visible ? clearIndicator.implicitIndicatorWidth : 0)

    property real focusedMargin: (activeFocus ? 12 : 24)

    Behavior on focusedMargin {
        NumberAnimation {
            easing.type: Easing.BezierSpline
            easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
            duration: MotionSpecs.expressiveSlowSpatialDuration
        }
    }

    // Behavior on leftInset {
    //     NumberAnimation {
    //         easing.type: Easing.BezierSpline
    //         easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
    //         duration: MotionSpecs.expressiveSlowSpatialDuration
    //     }
    // }
    // Behavior on leftPadding {
    //     NumberAnimation {
    //         easing.type: Easing.BezierSpline
    //         easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
    //         duration: MotionSpecs.expressiveSlowSpatialDuration
    //     }
    // }
    // Behavior on rightPadding {
    //     NumberAnimation {
    //         easing.type: Easing.BezierSpline
    //         easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
    //         duration: MotionSpecs.expressiveSlowSpatialDuration
    //     }
    // }
    // Behavior on rightInset {
    //     NumberAnimation {
    //         easing.type: Easing.BezierSpline
    //         easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
    //         duration: MotionSpecs.expressiveSlowSpatialDuration
    //     }
    // }

    Theme.iconSize: Qt.size(28, 28)

    final property Component leading
    final property Component trailing

    final property TapHandler __tapHandler

    contentItem: SearchBarInputField {
        horizontalPadding: 4
        spacing: 4

        leading: control.leading
        trailing: control.trailing

        Behavior on width {
            NumberAnimation {
                easing.type: Easing.BezierSpline
                easing.bezierCurve: MotionSpecs.expressiveSlowSpatialBezier
                duration: MotionSpecs.expressiveSlowSpatialDuration
            }
        }

        Binding {
            target: control
            property: "__tapHandler"
            value: (control.contentItem as SearchBarInputField).tapHandler
        }
    }

    background: InteractiveSurface {
        target: control.__tapHandler
        shadowElevations: control.__shadows
        hovered: control.hovered
        enabled: control.enabled
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
    }

    delegate: MenuItem {
        id: delegate

        width: ListView.view.width
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled

        contentItem: Text {
            text: delegate.model[control.textRole]
            color: delegate.textColor
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        // backgroundColor: "transparent"

        required property var model
        required property int index
    }

    popup: T.Popup {
        y: control.height + 12
        width: control.width + (control.includeElevation ? control.shadowElevationSize.width : 0)
        height: contentItem.implicitHeight > 0 ? Math.min(contentItem.implicitHeight + verticalPadding * 2, control.Window.height - control.y - control.height - control.padding) : 0
        topMargin: 10
        bottomMargin: 10
        padding: 4

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.delegateModel
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator {}
        }

        background: SurfacePrivate {
            shadowElevations: control.__shadows
            enabled: control.enabled
            topLeftRadius: 6
            bottomLeftRadius: 6
            topRightRadius: 6
            bottomRightRadius: 6
            backgroundColor: control.Theme.colorScheme.surfaceContainerLow
        }
    }
}

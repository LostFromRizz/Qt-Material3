import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.Slider {
    id: control

    enum IconAlignment {
        Start,
        Middle,
        End
    }

    Theme.iconSize: {
        const size = Material.sliderIconSize(control.trackHeight);
        Qt.size(size, size);
    }

    final property icon icon
    icon.height: Theme.iconSize.height
    icon.width: Theme.iconSize.width

    final property int iconAlignment: Slider.End

    final property color activeTrackColor: enabled ? Theme.colorScheme.primary : Qt.alpha(Theme.colorScheme.onSurface, 0.38)
    final property color activeTickColor: enabled ? Theme.colorScheme.onPrimary : Qt.alpha(Theme.colorScheme.onSurface, 0.12)
    final property color inactiveTrackColor: enabled ? Theme.colorScheme.secondaryContainer : Qt.alpha(Theme.colorScheme.onSurface, 0.12)
    final property color inactiveTickColor: enabled ? Theme.colorScheme.onSecondaryContainer : Qt.alpha(Theme.colorScheme.onSurface, 0.38)
    final property color handleColor: enabled ? Theme.colorScheme.primary : Qt.alpha(Theme.colorScheme.onSurface, 0.38)

    final property real trackHeight: Material.sliderHeightSmall

    final property int steps: 0

    final property Component stopIndicator
    final property Component tickItem

    implicitWidth: control.horizontal ? 200 : Math.max(control.implicitBackgroundHeight + leftInset + rightInset, control.implicitHandleWidth + rightPadding + leftPadding)
    implicitHeight: control.vertical ? 200 : Math.max(control.implicitBackgroundHeight + topInset + bottomInset, control.implicitHandleHeight + topPadding + bottomPadding)

    // Effective step count clamped by track aspect ratio
    // Prevents ticks from overlapping when the track is very short
    final readonly property int __steps__: Math.min(steps, Math.max(0, Math.floor(horizontal ? control.availableWidth / control.availableHeight : control.availableHeight / control.availableWidth)))

    final readonly property list<real> __stepsFractions__: steps > 0 ? Array.from({
        length: __steps__ + 2
    }, (_, i) => i / (__steps__ + 1)) : []

    stepSize: steps > 0 ? 1 / (__steps__ + 1) : 0
    snapMode: steps > 0 && (stopIndicator != null || tickItem != null) ? Slider.SnapAlways : Slider.NoSnap

    spacing: 6.0

    hoverEnabled: true

    HoverHandler {
        enabled: control.enabled && control.hoverEnabled
        cursorShape: control.pressed ? Qt.ClosedHandCursor : Qt.PointingHandCursor
    }

    background: SliderTrackImpl {
        x: control.horizontal ? control.leftPadding : (control.width - width) / 2
        y: control.vertical ? control.topPadding : control.topPadding + ((control.height - height) / 2)
        type: SliderTrackImpl.Standard
        implicitHeight: control.vertical ? control.availableHeight : control.trackHeight
        implicitWidth: control.horizontal ? control.availableWidth : control.trackHeight
        stepsFractions: control.__stepsFractions__
        visualPosition: MInternals.clamp(control.visualPosition, 0, 1)
        horizontal: control.horizontal
        trackHeight: control.trackHeight
        spacing: control.spacing
        handleWidth: control.implicitHandleWidth
        activeTrackColor: control.activeTrackColor
        inactiveTrackColor: control.inactiveTrackColor
        activeTickColor: control.activeTickColor
        inactiveTickColor: control.inactiveTickColor
        tickItem: control.tickItem
        stopIndicator: control.stopIndicator
        icon: control.icon
        iconAlignment: control.iconAlignment
    }

    handle: Rectangle {
        readonly property size handleSize: Material.sliderHandleSize(control.trackHeight)
        implicitHeight: control.horizontal ? handleSize.height : handleSize.width
        implicitWidth: control.horizontal ? handleSize.width : handleSize.height
        radius: Math.min(height, width) / 2
        color: control.handleColor
        x: control.horizontal ? control.leftPadding + (control.visualPosition * (control.availableWidth - (width + control.spacing * 2)) + control.spacing) : control.leftPadding + ((control.width - width) / 2)
        y: control.vertical ? control.bottomPadding + (control.visualPosition * (control.availableHeight - (height + control.spacing * 2)) + control.spacing) : control.topPadding + ((control.height - height) / 2)
    }

    component TickItem: Rectangle {
        required property color tickColor
        color: tickColor
        width: 4
        height: 4
        radius: width / 2
    }

    component StopIndiactor: Rectangle {
        required property color indicatorColor
        color: indicatorColor
        width: 4
        height: 4
        radius: width / 2
    }
}

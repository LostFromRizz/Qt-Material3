import QtQuick
import Material3.internals
import QtQuick.Templates as T

T.Control {
    id: control

    final property Component delegate

    final property real minSmallItemSize: 40.0

    final property real maxSmallItemSize: 56.0

    final property real preferredSize: -1

    verticalPadding: 8.0
    horizontalPadding: 16.0
    spacing: 8

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding)

    final property var model

    final readonly property real targetLargeSize: Math.min(control.preferredSize, control.availableWidth)
    final readonly property real targetSmallSize: MInternals.clamp(targetLargeSize / 3.0, control.minSmallItemSize, control.maxSmallItemSize)
    final readonly property real targetMediumSize: (targetLargeSize + targetSmallSize) / 2.0

    final readonly property real minAvailableLargeSpace: control.availableWidth - targetMediumSize - maxSmallItemSize
    final readonly property int minLargeCount: Math.max(1, Math.floor(minAvailableLargeSpace / targetLargeSize))
    final readonly property int maxLargeCount: Math.ceil(control.availableWidth / targetLargeSize)
    final readonly property int largeCounts: maxLargeCount - minLargeCount + 1

    contentItem: ListView {
        implicitWidth: contentWidth
        spacing: control.spacing
        model: control.model
        flickableDirection: Flickable.HorizontalFlick
        delegate: control.delegate
        clip: true
    }
}

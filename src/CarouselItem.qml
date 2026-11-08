import QtQuick
import Material3
import Material3.internals

Rectangle {
    id: control

    implicitWidth: contentItem?.implicitWidth ?? 0.0
    implicitHeight: contentItem?.implicitHeight ?? 0.0

    readonly property CarouselView carousel: parent?.parent instanceof CarouselView ? parent.parent as CarouselView : null

    height: carousel.vertical ? carousel?.preferredHeight ?? implicitHeight : parent?.height ?? implicitHeight
    width: carousel.horizontal ? carousel?.preferredWidth ?? implicitWidth : parent?.width ?? implicitWidth

    color: "#" + Math.floor(Math.random() * 0x1000000).toString(16).padStart(6, "0")

    required property int index
    default final property Item contentItem

    children: contentItem
}

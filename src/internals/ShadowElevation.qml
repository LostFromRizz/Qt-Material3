import QtQuick
import QtQuick.Effects

RectangularShadow {
    required property var shadowElevation
    anchors.fill: parent
    offset.y: shadowElevation.offset
    blur: shadowElevation.blur
    spread: shadowElevation.spread
    color: shadowElevation.color
    visible: enabled || (shadowElevation.blur > 0 && shadowElevation.spread > 0)
}

import Material3
import QtQuick

Card {
    id: control
    elevation: hovered ? 1 : 0
    backgroundColor: enabled ? Theme.colorScheme.surface : "transparent"
    contentColor: Material.contentColorFor(backgroundColor, Theme.colorScheme)

    final property real outlineWidth: 1
    final property color outlineColor: enabled ? Theme.colorScheme.outlineVariant : Qt.alpha(Theme.colorScheme.outline, 0.12)

    background: InteractiveSurface {
        target: control
        shadowElevations: control.__shadows
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
        outlineWidth: control.outlineWidth
        outlineColor: control.outlineColor
    }
}

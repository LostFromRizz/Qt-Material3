import Material3
import QtQuick

Card {
    elevation: hovered ? 3 : 1
    backgroundColor: enabled ? Theme.colorScheme.surfaceContainerLow : Qt.alpha(Theme.colorScheme.surface, 0.38)
    contentColor: Material.contentColorFor(backgroundColor, Theme.colorScheme)
}

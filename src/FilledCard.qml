import Material3
import QtQuick

Card {
    elevation: hovered ? 1 : 0
    backgroundColor: enabled ? Theme.colorScheme.primary : Qt.alpha(Theme.colorScheme.surface, 0.38)
    contentColor: Material.contentColorFor(backgroundColor, Theme.colorScheme)
}

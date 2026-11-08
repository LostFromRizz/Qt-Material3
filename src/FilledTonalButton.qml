import QtQuick
import Material3

Button {
    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.secondary : Theme.colorScheme.secondaryContainer;
        }
        return Theme.colorScheme.secondaryContainer;
    }
    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.onSecondary : Theme.colorScheme.onSecondaryContainer;
        }
        return Theme.colorScheme.onSecondaryContainer;
    }
}

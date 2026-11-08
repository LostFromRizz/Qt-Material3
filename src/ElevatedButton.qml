import QtQuick
import Material3

Button {
    elevation: 1.0

    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.surfaceContainerLow;
        }
        return Theme.colorScheme.surfaceContainerLow;
    }
    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.onPrimary : Theme.colorScheme.primary;
        }
        return Theme.colorScheme.primary;
    }
}

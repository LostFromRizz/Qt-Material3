import QtQuick
import Material3

Button {
    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.surfaceContainer;
        }
        return Theme.colorScheme.primary;
    }
    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.onPrimary : Theme.colorScheme.onSurfaceVariant;
        }
        return Theme.colorScheme.onPrimary;
    }
}

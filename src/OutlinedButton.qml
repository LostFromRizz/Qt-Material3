import QtQuick
import Material3

Button {
    outlineWidth: 1
    outlineColor: Theme.colorScheme.outlineVariant

    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.inverseSurface : Theme.colorScheme.surfaceVariant;
        }
        return "transparent";
    }
    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable) {
            return checked ? Theme.colorScheme.inverseOnSurface : Theme.colorScheme.onSurfaceVariant;
        }
        return Theme.colorScheme.onSurfaceVariant;
    }
}

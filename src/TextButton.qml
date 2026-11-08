import QtQuick
import Material3

Button {
    id: control
    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        return "transparent";
    }
    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        return Theme.colorScheme.primary;
    }

    contentItem: Label {
        text: control.text
        color: control.contentColor
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}

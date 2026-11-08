import Material3
import QtQuick

Button {
    id: control

    containerHeight: Math.max(Material.iconButtonHeightSmall, implicitContentHeight)

    icon.height: iconSize
    icon.width: iconSize
    iconSize: Material.iconButtonIconSize(control.containerHeight)

    verticalPadding: (includeElevation ? shadowElevationSize.height : 0)
    horizontalPadding: Material.iconButtonUniformPadding(containerHeight) + (includeElevation ? shadowElevationSize.width : 0)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(containerHeight, Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding))

    radius: Math.min(height, width) / 2

    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }

        if (checkable) {
            return checked ? "" : "";
        }

        return "transparent";
    }

    contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        if (checkable) {
            return checked ? Theme.colorScheme.primary : Theme.colorScheme.onSurfaceVariant;
        }

        return Theme.colorScheme.onSurfaceVariant;
    }

    spacing: 0
    contentItem: Icon {
        name: control.icon.name
        size: control.iconSize
        color: control.contentColor
    }
}

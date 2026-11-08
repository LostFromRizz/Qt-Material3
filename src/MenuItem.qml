pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.MenuItem {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, 48.0)
    implicitWidth: MInternals.clamp(Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding), 112.0, 280.0)

    final property real radius: 4
    final property icon trailingIcon

    final readonly property int style: menu instanceof AbstractStyledMenu ? (menu as AbstractStyledMenu).style : AbstractStyledMenu.Standard

    final property color backgroundColor: {
        if (style === AbstractStyledMenu.Vibrant) {
            if (checkable && checked) {
                return Theme.colorScheme.tertiary;
            }
            return Theme.colorScheme.tertiaryContainer;
        }

        if (checkable && checked) {
            return Theme.colorScheme.tertiaryContainer;
        }

        return Theme.colorScheme.surfaceContainerLow;
    }

    final property color textColor: {
        if (style === AbstractStyledMenu.Vibrant) {
            if (checkable && checked) {
                return Theme.colorScheme.onTertiary;
            }

            if (!enabled) {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
            return Theme.colorScheme.onTertiaryContainer;
        }

        if (checkable && checked) {
            if (enabled) {
                return Theme.colorScheme.onTertiaryContainer;
            } else {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
        }

        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        return Theme.colorScheme.onSurface;
    }

    icon.color: {
        if (style === AbstractStyledMenu.Vibrant) {
            if (checkable && checked) {
                return Theme.colorScheme.onTertiary;
            }

            if (!enabled) {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
            return Theme.colorScheme.onTertiaryContainer;
        }

        if (checkable && checked) {
            if (enabled) {
                return Theme.colorScheme.onTertiaryContainer;
            } else {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
        }

        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        return Theme.colorScheme.onSurfaceVariant;
    }
    icon.height: Theme.iconSize.height
    icon.width: Theme.iconSize.width

    trailingIcon.color: {
        if (style === AbstractStyledMenu.Vibrant) {
            if (checkable && checked) {
                return Theme.colorScheme.onTertiary;
            }

            if (!enabled) {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
            return Theme.colorScheme.onTertiaryContainer;
        }

        if (checkable && checked) {
            if (enabled) {
                return Theme.colorScheme.onTertiaryContainer;
            } else {
                return Material.disabledContentColor(Theme.colorScheme.onTertiaryContainer);
            }
        }

        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        return Theme.colorScheme.onSurfaceVariant;
    }

    trailingIcon.height: Theme.iconSize.height
    trailingIcon.width: Theme.iconSize.width
    font: Theme.typography.labelLarge
    horizontalPadding: 12
    spacing: 12

    final property alias cursorShape: hoverHandler.cursorShape

    HoverHandler {
        id: hoverHandler
        cursorShape: Qt.PointingHandCursor
    }

    background: InteractiveSurface {
        target: control
        backgroundColor: control.backgroundColor
        contentColor: control.textColor
        topLeftRadius: control.radius
        bottomLeftRadius: control.radius
        topRightRadius: control.radius
        bottomRightRadius: control.radius
    }

    contentItem: MenuItemIconLabel {
        leadingIcon: control.icon
        trailingIcon: control.trailingIcon
        text: control.text
        font: control.font
        spacing: control.spacing
        display: control.display
        textColor: control.textColor
    }

    final property Component overlay: Rectangle {
        color: control.Theme.colorScheme.surfaceDim
        Behavior on opacity {
            NumberAnimation {
                duration: MotionSpecs.durationShort3
            }
        }
    }

    T.Overlay.modal: overlay
}

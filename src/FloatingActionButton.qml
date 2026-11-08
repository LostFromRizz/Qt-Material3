import QtQuick
import Material3

Button {
    id: control
    enum ColorScheme {
        Primary,
        Secondary,
        Tertiary,
        TonalPrimary,
        TonalSecondary,
        TonalTertiary
    }

    containerHeight: Math.max(implicitContentHeight, Material.fabHeightSmall)
    elevation: hovered ? 4 : 3
    radius: Material.fabRadius(containerHeight)
    verticalPadding: 0
    horizontalPadding: Material.fabHorizontalPadding(containerHeight)

    iconSize: Material.fabIconSize(containerHeight)
    property int colorScheme: FloatingActionButton.Primary

    backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }

        switch (colorScheme) {
        case FloatingActionButton.Secondary:
            return Theme.colorScheme.secondary;
        case FloatingActionButton.Tertiary:
            return Theme.colorScheme.tertiary;
        case FloatingActionButton.TonalPrimary:
            return Theme.colorScheme.primaryContainer;
        case FloatingActionButton.TonalSecondary:
            return Theme.colorScheme.secondaryContainer;
        case FloatingActionButton.TonalTertiary:
            return Theme.colorScheme.tertiaryContainer;
        case FloatingActionButton.Primary:
        default:
            return Theme.colorScheme.primary;
        }
    }

    contentColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }

        switch (colorScheme) {
        case FloatingActionButton.Secondary:
            return Theme.colorScheme.onSecondary;
        case FloatingActionButton.Tertiary:
            return Theme.colorScheme.onTertiary;
        case FloatingActionButton.TonalPrimary:
            return Theme.colorScheme.onPrimaryContainer;
        case FloatingActionButton.TonalSecondary:
            return Theme.colorScheme.onSecondaryContainer;
        case FloatingActionButton.TonalTertiary:
            return Theme.colorScheme.onTertiaryContainer;
        case FloatingActionButton.Primary:
        default:
            return Theme.colorScheme.onPrimary;
        }
    }
}

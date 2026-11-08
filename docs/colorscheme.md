# ColorScheme

`ColorScheme` is a value type that defines the color roles used throughout the Material 3 theme. It provides colors for primary, secondary, tertiary, error, surface, and outline roles.

A `ColorScheme` is created from a JavaScript object containing its color properties and can be assigned to `Theme.colorScheme`.

## Basic usage

```qml
import QtQuick
import Material3


Window {
    id: window
    visible: true
    width: 320
    height: 480
    color: Theme.colorScheme.primaryContainer

    Theme.colorScheme: ({
        primary: "#6750A4",
        onPrimary: "#FFFFFF",
        primaryContainer: "#EADDFF",
        onPrimaryContainer: "#21005D",
        // Remaining color properties...
    })
}
```

## Properties

All properties are writable and accept a color value. When constructing a `ColorScheme` from a JavaScript object, all properties must be provided. Any missing properties are initialized to transparent.

### Primary colors

| Property | Description |
|---|---|
| `primary` | Primary accent color. |
| `onPrimary` | Content color used on top of the primary color. |
| `primaryContainer` | Container color for primary elements. |
| `onPrimaryContainer` | Content color used on top of the primary container color. |

### Secondary colors

| Property | Description |
|---|---|
| `secondary` | Secondary accent color. |
| `onSecondary` | Content color used on top of the secondary color. |
| `secondaryContainer` | Container color for secondary elements. |
| `onSecondaryContainer` | Content color used on top of the secondary container color. |

### Tertiary colors

| Property | Description |
|---|---|
| `tertiary` | Tertiary accent color. |
| `onTertiary` | Content color used on top of the tertiary color. |
| `tertiaryContainer` | Container color for tertiary elements. |
| `onTertiaryContainer` | Content color used on top of the tertiary container color. |

### Error colors

| Property | Description |
|---|---|
| `error` | Color used to indicate errors. |
| `onError` | Content color used on top of the error color. |
| `errorContainer` | Container color for error-related elements. |
| `onErrorContainer` | Content color used on top of the error container color. |

### Surface colors

| Property | Description |
|---|---|
| `surface` | Color for surface elements. |
| `onSurface` | Content color used on top of surface elements. |
| `surfaceVariant` | Alternative surface color. |
| `onSurfaceVariant` | Content color used on top of the surface variant color. |
| `surfaceContainerLowest` | Lowest surface container color. |
| `surfaceContainerLow` | Low surface container color. |
| `surfaceContainer` | Default surface container color. |
| `surfaceContainerHigh` | High surface container color. |
| `surfaceContainerHighest` | Highest surface container color. |
| `surfaceBright` | Bright surface color. |
| `surfaceDim` | Dim surface color. |
| `inverseSurface` | Inverse surface color. |
| `inverseOnSurface` | Content color used on top of the inverse surface color. |
| `surfaceTint` | Tint color applied to surfaces. |

### Outline and overlay colors

| Property | Description |
|---|---|
| `outline` | Color used for outlines and borders. |
| `outlineVariant` | Less prominent outline color. |
| `scrim` | Color used for scrim overlays. |
| `shadow` | Color used for shadows. |

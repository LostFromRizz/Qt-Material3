# Theme

`Theme` is an attached property type that provides theme configuration to QML items. Its properties propagate through the attached-property hierarchy, allowing child items to inherit theme settings from their ancestors.

`Theme` cannot be instantiated directly. Access it through an item to configure or read its theme properties.

## Basic usage

```qml
import QtQuick
import Material3

Item {
    height: 100
    width: 100
    Theme.colorScheme: ({
        // Color scheme properties...
    })

    Theme.themeMode: Theme.Dark

    Rectangle {
        // Inherits the parent's theme settings.
        color: Theme.backgroundColor
        anchors.fill:parent
    }
}
```

## Properties

| Property | Description |
|---|---|
| `colorScheme` | Color scheme used by the theme. |
| `typography` | Typography configuration used by the theme. |
| `emphasizedTypography` | Emphasized typography configuration used by the theme. |
| `backgroundColor` | Background color provided by the theme. |
| `contentColor` | Content color provided by the theme. |
| `iconSize` | Default icon size. |
| `themeMode` | Controls whether the theme uses light, dark, or system mode. |

## ThemeMode

`ThemeMode` specifies how the theme determines its color mode.

| Value | Description |
|---|---|
| `Theme.Light` | Uses light mode. |
| `Theme.Dark` | Uses dark mode. |
| `Theme.System` | Follows the system color mode. |

# Button

`Button` is an interactive control for triggering actions. It supports text, icons, checkable states, keyboard interaction, and customizable appearance following Material 3 guidelines.

Buttons are available in different styles:

- `FilledButton.qml`
- `FilledTonalButton.qml`
- `ElevatedButton.qml`
- `OutlinedButton.qml`
- `TextButton.qml`
- `IconButton.qml`

## Basic usage

```qml
RowLayout {
    id: root

    function buttonPressed(text: string): void {
        console.log("Pressed:", text)
    }

    ElevatedButton {
        text: "Elevated button"
        onClicked: root.buttonPressed(text)
    }

    FilledButton {
        text: "Filled button"
        onClicked: root.buttonPressed(text)
    }

    FilledTonalButton {
        text: "Filled tonal button"
        onClicked: root.buttonPressed(text)
    }

    OutlinedButton {
        text: "Outlined button"
        onClicked: root.buttonPressed(text)
    }

    TextButton {
        text: "Text button"
        onClicked: root.buttonPressed(text)
    }
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `backgroundColor` | `color` | Determines the background color based on the button's enabled, checkable, and checked states and the current theme's color scheme. |
| `contentColor` | `color` | Determines the content color based on the button's enabled, checkable, and checked states and the current theme's color scheme. |
| `radius` | `real` | Determines the corner radius based on the button's checkable, checked, and hovered states. |
| `topLeftRadius` | `real` | Controls the top-left corner radius. Defaults to `radius`. |
| `topRightRadius` | `real` | Controls the top-right corner radius. Defaults to `radius`. |
| `bottomLeftRadius` | `real` | Controls the bottom-left corner radius. Defaults to `radius`. |
| `bottomRightRadius` | `real` | Controls the bottom-right corner radius. Defaults to `radius`. |
| `outlineColor` | `color` | Controls the outline color. |
| `outlineWidth` | `real` | Controls the outline width. |
| `iconSize` | `int` | Controls the icon size. Defaults to the value calculated by `Material.iconButtonIconSize(containerHeight)`. |
| `containerHeight` | `real` | Determines the container height used to control button sizes, from `Material.smallButtonHeight` to `Material.extraLargeButtonHeight`. |
| `elevation` | `real` | Controls the button's elevation, up to a maximum of `24.0`. |
| `includeElevation` | `bool` | Determines whether shadow dimensions are included in the button's insets and padding. Defaults to `false`. |
| `shadowElevationSize` | `size` | Defines the space required to accommodate the button's shadows, calculated from their blur, spread, and offset values. |
| `cursorShape` | `Qt.CursorShape` | Controls the cursor shape displayed when the pointer hovers over the button. |

> **Note:** When `includeElevation` is `true`, changes to `elevation` can change `shadowElevationSize`, affecting the card's implicit size and layout. To prevent layout shifts when elevation changes dynamically, reserve space for the maximum expected elevation rather than using the size calculated for the current elevation.

## Inherited properties

`Button` inherits properties from `QtQuick.Templates.AbstractButton`, including:

- `text` — the button's text.
- `icon` — the button's icon configuration.
- `checkable` — whether the button can be checked.
- `checked` — whether the button is checked.
- `enabled` — whether the button is enabled.
- `display` — controls how the icon and text are displayed.

See the [Qt Quick Controls AbstractButton documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-abstractbutton.html) for inherited properties and signals.

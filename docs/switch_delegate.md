# SwitchDelegate

`SwitchDelegate` is a delegate with a switch indicator for toggling an option. It is based on `QtQuick.Templates.SwitchDelegate` and provides the same animated track, handle, and optional icon as `Switch`, along with the text and content support inherited from `ItemDelegate`.

Switch delegates are typically used to select one or more options from a set of options. For smaller sets of options, or for options that need to be uniquely identifiable, consider using [Switch](#switch) instead.

## Basic Usage

```qml
import QtQuick
import Material3

Column {
    SwitchDelegate {
        text: "Wi-Fi"
        checked: true
    }

    SwitchDelegate {
        text: "Bluetooth"
    }

    SwitchDelegate {
        text: "Airplane mode"
    }
}
```

You can also display an icon inside the switch handle:

```qml
SwitchDelegate {
    text: "Wi-Fi"
    checked: true

    icon.name: "check"
}
```

## Properties

| Property | Description |
|---|---|
| `backgroundColor` | The background color of the switch track. Automatically changes according to the enabled and checked states. |
| `handleColor` | The color of the switch handle. Automatically changes according to the enabled and checked states. |
| `outlineColor` | The color of the switch track's outline. Changes according to the enabled and checked states. |
| `outlineWidth` | The width of the track outline. Defaults to `2`. |
| `iconColor` | The color of the optional icon displayed inside the handle. |
| `iconSize` | The size of the optional icon. Defaults to `16`. |
| `cursorShape` | The cursor shape displayed when hovering over the delegate. Defaults to `Qt.PointingHandCursor`. |

## Handle Behavior

The handle size changes according to the switch state:

- `16` when unchecked and without an icon.
- `24` when checked or when an icon is provided.
- `28` while pressed or down.

The handle's position and size are animated using the expressive fast spatial motion specification. Its color and the track's background and outline colors use the expressive default effects motion specification.

## Inherited Properties

`SwitchDelegate` is based on `QtQuick.Templates.SwitchDelegate` and supports inherited delegate and switch properties, including `text`, `enabled`, `checked`, `checkable`, `down`, `pressed`, `highlighted`, `display`, and `icon`.

See the [Qt Quick Controls SwitchDelegate documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-switchdelegate.html) for details.

# Switch

`Switch` is a control for toggling between two states. It is based on `QtQuick.Templates.Switch` and consists of a track and an animated handle.

The handle changes its position, size, and color according to the switch's checked, pressed, and enabled states. An optional icon can be displayed inside the handle.

## Basic Usage

```qml
import QtQuick
import Material3

Switch {
    checked: true
}
```

You can also display an icon inside the switch handle:

```qml
Switch {
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
| `cursorShape` | The cursor shape displayed when hovering over the switch. Defaults to `Qt.PointingHandCursor`. |

## Handle Behavior

The handle size changes according to the switch state:

- `16` when unchecked and without an icon.
- `24` when checked or when an icon is provided.
- `28` while pressed or down.

The handle's position and size are animated using the expressive fast spatial motion specification. Its color and the track's background and outline colors use the expressive default effects motion specification.

## Inherited Properties

`Switch` is based on `QtQuick.Templates.Switch` and supports inherited switch properties, including `checked`, `checkable`, `enabled`, `down`, `pressed`, `hovered`, `text`, and `display`.

See the [Qt Quick Controls Switch documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-switch.html) for details.

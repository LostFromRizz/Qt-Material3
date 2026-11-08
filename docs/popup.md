# Popup

`Popup` displays content in a separate window-like surface above other content. It supports customizable background colors, elevation, corner radii, and outlines. You can also provide a custom overlay for modal popups.

## Basic usage

```qml
import QtQuick
import Material3

FilledButton {
    text: "Open"
    onClicked: popup.open()
}

Popup {
    id: popup
    anchors.centerIn: parent
    width: 200
    height: 300
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `backgroundColor` | `color` | Sets the background color of the popup. |
| `elevation` | `real` | Sets the popup's elevation. Defaults to `4`. |
| `includeElevation` | `bool` | Determines whether space is reserved for the popup's shadow. Defaults to `true`. |
| `shadowElevationSize` | `size` | The size required to accommodate the shadow, calculated from the popup's elevation. |
| `radius` | `real` | Sets the corner radius for all four corners. Defaults to `4`. |
| `topLeftRadius` | `real` | Sets the top-left corner radius. |
| `topRightRadius` | `real` | Sets the top-right corner radius. |
| `bottomLeftRadius` | `real` | Sets the bottom-left corner radius. |
| `bottomRightRadius` | `real` | Sets the bottom-right corner radius. |
| `outlineWidth` | `int` | Sets the width of the popup outline. |
| `outlineColor` | `color` | Sets the color of the popup outline. |
| `overlay` | `Component` | Sets the component used as the modal overlay. |

When `includeElevation` is enabled, the shadow size is used to calculate the popup's insets and padding, reserving space for the shadow around its content. Disable it when the popup should not reserve additional space for elevation.

## Inherited properties

`Popup` is based on `QtQuick.Templates.Popup` and supports inherited popup properties, including `contentItem`, `background`, `contentData`, `contentChildren`, `modal`, `dim`, `visible`, `opened`, `closePolicy`, `focus`, `padding`, and `margins`.

See the [Qt Quick Popup documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-popup.html) for details.

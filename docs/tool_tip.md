# ToolTip

`ToolTip` is a component that displays brief contextual information associated with a control. It is based on `QtQuick.Templates.ToolTip` and follows the Material 3 guidelines for a plain tool tip.

## Basic Usage

```qml
import QtQuick
import Material3

Button {
    id: button
    text: "Button"

    ToolTip {
        visible: button.hovered
        delay: 1000
        timeout: 5000
        y: height + 4.0
        x: button.width / 2 - width / 2
        text: "This tool tip is shown after hovering the button for a second."
    }
}
```

## Properties

| Property | Description |
|---|---|
| `verticalPadding` | The vertical padding inside the tooltip. Defaults to `12`. |
| `horizontalPadding` | The horizontal padding inside the tooltip. Defaults to `16`. |

## Appearance

- **Background:** Uses `Theme.backgroundColor`.
- **Content:** Uses `Theme.contentColor`.
- **Shape:** The background has a fully rounded shape, with its radius calculated as half the smaller of its width and height.
- **Content:** Displays the inherited `text` property using a `Label`.

The implicit dimensions are calculated from the content size and padding. Explicit top, bottom, left, or right padding takes precedence over the corresponding vertical or horizontal padding.

## Inherited Properties

`ToolTip` is based on `QtQuick.Templates.ToolTip` and supports inherited tooltip properties, including `text`, `visible`, `delay`, `timeout`, and `contentItem`.

See the [Qt Quick Controls ToolTip documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-tooltip.html) for details.

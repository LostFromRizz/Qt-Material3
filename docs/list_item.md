# ListItem

`ListItem` displays a single item with a title and optional supporting content, overline, leading content, and trailing content. It is based on `ItemDelegate` and supports its interaction and selection properties.

## Basic Usage

```qml
import Material3

ListItem {
    title: "Wi-Fi"
    subtitleText: "Connected"
}
```

You can also provide overline text and custom leading or trailing content:

```qml
import Material3

ListItem {
    title: "Bluetooth"
    overlineText: "Connections"
    subtitleText: "On"

    leading: Icon {
        name: "bluetooth"
    }

    trailing: Icon {
        name: "chevron_right"
    }
}
```

## Properties

| Property | Description |
|---|---|
| `title` | The primary text displayed in the item. |
| `overlineText` | Text displayed above the title. |
| `subtitleText` | Supporting text displayed below the title. |
| `leading` | An item displayed before the text content. |
| `trailing` | An item displayed after the text content. |
| `backgroundColor` | The background color of the item. |
| `contentColor` | The color of the title. |
| `overlineColor` | The color of the overline text. |
| `subtitleColor` | The color of the subtitle text. |
| `leadingColor` | The color applied to the leading content. |
| `trailingColor` | The color applied to the trailing content. |
| `interactive` | Whether the item accepts pointer interaction. When false, the cursor is set to an arrow and pointer events are not accepted by the item's mouse area. Defaults to `true`. |
| `cursorShape` | The cursor shape displayed when hovering over the item. Defaults to a pointing hand when interactive and an arrow otherwise. |
| `spacing` | The spacing between the item's content elements. Defaults to `12`. |
| `radius` | Sets the corner radius of all four corners. |
| `topLeftRadius` | The radius of the top-left corner. |
| `topRightRadius` | The radius of the top-right corner. |
| `bottomLeftRadius` | The radius of the bottom-left corner. |
| `bottomRightRadius` | The radius of the bottom-right corner. |
| `outlineColor` | The color of the item's outline. |
| `outlineWidth` | The width of the item's outline. |
| `elevation` | The elevation used to determine the item's shadow. Defaults to `0`. |
| `includeElevation` | Whether the shadow is included in the item's layout size. Defaults to `true`. |
| `shadowElevationSize` | The size reserved for the shadow. This affects the item's layout size when `includeElevation` is enabled. |
| `horizontalPadding` | Horizontal padding inside the item. The shadow width is added when `includeElevation` is enabled. Defaults to `16` plus the shadow width. |
| `verticalPadding` | Vertical padding inside the item. The shadow height is added when `includeElevation` is enabled. Defaults to `10` plus the shadow height. |

> **Note:** When `includeElevation` is `true`, changes to `elevation` can change `shadowElevationSize`, affecting the card's implicit size and layout. To prevent layout shifts when elevation changes dynamically, reserve space for the maximum expected elevation rather than using the size calculated for the current elevation.

## Inherited Properties

`ListItem` is based on `QtQuick.Templates.ItemDelegate` and supports inherited delegate properties, including `text`, `enabled`, `checkable`, `checked`, `highlighted`, and `display`.

See the [Qt Quick Controls ItemDelegate documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-itemdelegate.html) for details.

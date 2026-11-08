# TopAppBar

`TopAppBar` provides a top application bar with support for a headline, subtitle, leading content, and trailing actions. Its height and content colors can be customized through properties.

## Basic usage

```qml
import QtQuick
import Material3

TopAppBar {
    anchors.centerIn: parent
    headlineText: "Home"
    subtitleText: "Welcome back"
    width: 420

    leading: IconButton {
        anchors.centerIn: parent
        icon.name: "menu"
    }

    trailing: Row {
        anchors.centerIn: parent
        IconButton {
            icon.name: "search"
        }
        IconButton {
            icon.name: "more_vert"
        }
    }
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `headlineText` | `string` | The main text displayed in the app bar. |
| `subtitleText` | `string` | The secondary text displayed below the headline. |
| `leading` | `Component` | The component displayed before the headline, typically used for navigation or a leading action. |
| `trailing` | `Component` | The component displayed after the headline, typically used for actions. |
| `containerHeight` | `real` | The height of the app bar's content area. Defaults to `Material.appBarHeightSmall`. |
| `actionSpacing` | `real` | The spacing between trailing actions. Defaults to `4`. |
| `backgroundColor` | `color` | The background color of the app bar. |
| `titleContentColor` | `color` | The color of the headline text. |
| `subtitleContentColor` | `color` | The color of the subtitle text. |
| `leadingContentColor` | `color` | The color applied to the leading content. |
| `trailingContentColor` | `color` | The color applied to the trailing content. |
| `font` | `font` | The font used for the headline. Defaults to `Material.appBarFont`. |
| `radius` | `real` | Sets the corner radius of the app bar. |
| `topLeftRadius` | `real` | Sets the top-left corner radius. |
| `topRightRadius` | `real` | Sets the top-right corner radius. |
| `bottomLeftRadius` | `real` | Sets the bottom-left corner radius. |
| `bottomRightRadius` | `real` | Sets the bottom-right corner radius. |

## Inherited properties

`TopAppBar` is based on `QtQuick.Templates.Control` and supports inherited control properties, including `enabled`, `padding`, `topPadding`, `bottomPadding`, `leftPadding`, `rightPadding`, `font`, and `spacing`.

See the [Qt Quick Control documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-control.html) for details.

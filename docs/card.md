# Card

`Card` is a surface component for grouping related content. It follows Material 3 guidelines and supports customizable colors, corner radii, and elevation.

Cards are available in three styles:

- `ElevatedCard.qml`
- `FilledCard.qml`
- `OutlinedCard.qml`

## Basic usage

```qml
ElevatedCard {
    anchors.centerIn: parent
    implicitWidth: 280
    implicitHeight: 160

    contentItem: ColumnLayout {
        spacing: 12

        Label {
            Layout.topMargin: 12
            text: "Material"
            font: Theme.typography.headlineMedium
        }

        Label {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: "Material is a design system - backed by open source code - that helps teams build high-quality digital experiences."
            font: Theme.typography.bodyMedium
            wrapMode: Text.WordWrap
        }
    }
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `backgroundColor` | `color` | Controls the card's background color. Uses the theme's primary color when enabled and a surface color with reduced opacity when disabled. |
| `contentColor` | `color` | Determines the content color based on the background color and the current theme's color scheme. |
| `radius` | `real` | Controls the card's corner radius. Defaults to `12`. |
| `topLeftRadius` | `real` | Controls the top-left corner radius. Defaults to `radius`. |
| `topRightRadius` | `real` | Controls the top-right corner radius. Defaults to `radius`. |
| `bottomLeftRadius` | `real` | Controls the bottom-left corner radius. Defaults to `radius`. |
| `bottomRightRadius` | `real` | Controls the bottom-right corner radius. Defaults to `radius`. |
| `elevation` | `real` | Controls the card's elevation, which determines its shadow. |
| `includeElevation` | `bool` | Determines whether shadow dimensions are included in the card's insets and padding. Defaults to `false`. |
| `shadowElevationSize` | `size` | Defines the space required to accommodate the card's shadows, calculated from their blur, spread, and offset values. |
| `outlineWidth` | `real` | **OutlinedCard only.** Controls the outline width. Defaults to `1`. |
| `outlineColor` | `color` | **OutlinedCard only.** Controls the outline color. |

**Note:** When `includeElevation` is `true`, changes to `elevation` can change `shadowElevationSize`, affecting the card's implicit size and layout. To prevent layout shifts when elevation changes dynamically, reserve space for the maximum expected elevation rather than using the size calculated for the current elevation.

## Inherited properties

`Card` inherits properties from `QtQuick.Templates.ItemDelegate`, including:

- `contentItem` — specifies the item used to display the card's content.

See the [Qt Quick Controls ItemDelegate documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-itemdelegate.html) for inherited properties and signals.

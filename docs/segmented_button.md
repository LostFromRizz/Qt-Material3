# SegmentedButton

`SegmentedButton` is a selectable button designed for use in a group of connected buttons. It is based on `Button` and automatically adjusts its corner radii according to its position in the group and selection state.

It supports four visual styles: Filled, Tonal, Elevated, and Outlined. The default style is Outlined.

## Basic Usage

```qml
import QtQuick
import Material3

Row {
    id: row
    anchors.centerIn: parent
    spacing: 2
    property int activeIndex: 0
    Repeater {
        model: ["Day", "Week", "Month"]

        SegmentedButton {
            required property string modelData
            style: SegmentedButton.Filled
            text: modelData
            count: 3
            checked: index === row.activeIndex
            onToggled: {
                row.activeIndex = index;
            }
        }
    }
}
```

## Properties

| Property | Description |
|---|---|
| `index` | The button's position in the group. Required. |
| `count` | The total number of buttons in the group. Required. |
| `style` | The visual style of the button. Defaults to `SegmentedButton.Outlined`. |
| `shapeMorph` | Whether corner radius changes are animated and selected buttons use a fully rounded shape. Defaults to `true`. |
| `innerRadius` | The corner radius used between adjacent buttons. When `shapeMorph` is enabled, it is calculated using `Material.buttonInnerRadius(containerHeight)`; otherwise, it is `0`. |
| `selectedRadius` | The corner radius used for selected buttons when `shapeMorph` is enabled. Calculated as half the smaller of the button's height and width; otherwise, it is `0`. |
| `effectiveLeftRadius` | The calculated radius applied to both left corners. |
| `effectiveRightRadius` | The calculated radius applied to both right corners. |

## Styles

`SegmentedButton` provides four styles through the `Style` enum:

| Style | Description |
|---|---|
| `SegmentedButton.Filled` | Uses a filled primary container when selected and a surface container when unselected. |
| `SegmentedButton.Tonal` | Uses a secondary container when unselected and a secondary-colored background when selected. |
| `SegmentedButton.Elevated` | Uses an elevated surface when unselected and a primary-colored background when selected. |
| `SegmentedButton.Outlined` | Uses an outline when unselected and a secondary container when selected. |

The button's content color, background color, elevation, and outline are determined by its style and checked state. Disabled buttons use the corresponding disabled theme colors.

## Shape Behavior

- The first button has a rounded outer left edge.
- The last button has a rounded outer right edge.
- The corners between adjacent buttons use `innerRadius`.
- When `shapeMorph` is enabled, selected buttons use `selectedRadius` on all corners.
- When `shapeMorph` is disabled, corner radius changes are not animated, and the selected shape does not morph.
- Corner radius transitions use the expressive fast spatial motion specification.

## Inherited Properties

`SegmentedButton` is based on `Button` and inherits its properties, including `text`, `icon`, `iconSize`, `enabled`, `checkable`, `checked`, `checkable`, and `display`.

See the [Button documentation](#button) for details.

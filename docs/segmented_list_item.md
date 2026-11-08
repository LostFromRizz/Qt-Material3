# SegmentedListItem

`SegmentedListItem` is a specialized `ListItem` designed for use in a group of selectable items. It automatically adjusts its corner radii based on its position in the group and whether it is selected.

The first and last items have rounded outer corners, while the corners between adjacent unselected items use a smaller radius. Selected items use the selected radius on all corners. 

## Basic Usage

```qml
import QtQuick
import Material3

Column {
    anchors.centerIn: parent
    spacing: 2
    width: 120
    Repeater {
        model: ["Wi-Fi", "Bluetooth", "Airplane mode"]

        SegmentedListItem {
            required property string modelData
            title: modelData
            width: parent.width
            count: 3
            checkable: true
        }
    }
}
```

## Properties

| Property | Description |
|---|---|
| `index` | The item's position in the group. Required. |
| `count` | The total number of items in the group. Required. |
| `innerRadius` | The corner radius used between adjacent unselected items. Defaults to `4.0`. |
| `selectedRadius` | The corner radius applied to selected items. Defaults to `16.0`. |
| `effectiveTopRadius` | The calculated radius applied to both top corners. |
| `effectiveBottomRadius` | The calculated radius applied to both bottom corners. |

## Behavior

- When the group contains only one item, all corners use `radius`.
- For multiple unselected items, the first item's top corners and the last item's bottom corners use `radius`.
- Inner corners between unselected items use `innerRadius`.
- Selected items use `selectedRadius` on all corners.
- Changes to the effective top and bottom radii are animated using `MotionSpecs.expressiveFastSpatialBezier` and `MotionSpecs.expressiveFastSpatialDuration`.

## Inherited Properties

`SegmentedListItem` is based on `ListItem` and inherits its properties, including its content, appearance, spacing, padding, outline, and elevation properties.

See the [ListItem documentation](#listitem) for details.

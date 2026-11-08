# Slider

`Slider` is a control for selecting a value within a continuous or stepped range. It is based on `QtQuick.Templates.Slider` and supports horizontal and vertical orientations.

It provides a customizable track, handle, tick marks, stop indicators, and optional icons along the track.

## Basic Usage

```qml
import QtQuick
import Material3

Slider {
    from: 0
    to: 100
    value: 50
}
```

To display tick marks and stop indicators, set `steps` and provide the corresponding components:

```qml
import QtQuick
import Material3

Slider {
    from: 0
    to: 100
    value: 50
    steps: 4

    tickItem: Slider.TickItem {}
    stopIndicator: Slider.StopIndicator {}
}
```

## Properties

| Property | Description |
|---|---|
| `steps` | The number of intervals between the minimum and maximum values. Defaults to `0`, which disables stepping. |
| `activeTrackColor` | The color of the active portion of the track. |
| `inactiveTrackColor` | The color of the inactive portion of the track. |
| `activeTickColor` | The color of tick marks on the active portion of the track. |
| `inactiveTickColor` | The color of tick marks on the inactive portion of the track. |
| `handleColor` | The color of the slider handle. |
| `trackHeight` | The thickness of the slider track. Defaults to `Material.sliderHeightSmall`. |
| `spacing` | The spacing used between the handle and the track's content. Defaults to `6.0`. |
| `stopIndicator` | A component used to display stop indicators along the track. Defaults to `Slider.StopIndicator`. |
| `tickItem` | A component used to display tick marks along the track. Defaults to `Slider.TickItem`. |
| `icon` | The icon data used to display an icon along the track. Its size is calculated from `trackHeight`, and its default alignment is `Slider.End`. |

The effective number of steps is constrained by the available track dimensions to prevent tick marks from overlapping when the track is too short.

When `steps` is greater than `0`, the slider calculates its step size automatically. It snaps to step positions when either `stopIndicator` or `tickItem` is provided; otherwise, snapping is disabled.

## Components

`Slider` provides two default components that can be used or replaced:

- `Slider.TickItem` — a circular tick mark with a required `tickColor` property.
- `Slider.StopIndicator` — a circular stop indicator with a required `indicatorColor` property.

Both components can be customized by supplying your own `tickItem` or `stopIndicator` component.

## Inherited Properties

`Slider` is based on `QtQuick.Templates.Slider` and supports inherited slider properties, including `from`, `to`, `value`, `stepSize`, `orientation`, `horizontal`, `vertical`, `pressed`, `hovered`, `live`, `snapMode`, and `position`.

See the [Qt Quick Controls Slider documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-slider.html) for details.

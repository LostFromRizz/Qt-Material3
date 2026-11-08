# LoadingIndicator

`LoadingIndicator` displays an animated Material 3 loading indicator that morphs between different shapes while rotating. It supports a customizable color and a configurable sequence of shapes through the `polygons` property.

## Basic Usage

```qml
LoadingIndicator {}
```

Control the animation using the `running` property:

```qml
LoadingIndicator {
    running: false
}
```

Using different shapes using the `polygons` property:

Specify a custom list of `RoundedPolygon` shapes to change the shapes used in the animation.

```qml
LoadingIndicator {
    polygons: [
        MaterialShapes.pentagon,
        MaterialShapes.sunny,
        MaterialShapes.pill,
        MaterialShapes.cookie4Sided
    ]
}
```

The indicator morphs between the specified shapes in sequence and repeats the animation while `running` is `true`.

## Properties

| Property | Type | Description |
|---|---|---|
| `color` | color | Controls the color of the indicator. |
| `polygons` | list\<RoundedPolygon\> | Specifies the sequence of shapes used by the indicator. The indicator morphs between consecutive shapes and cycles back to the first shape after reaching the last one. |

## Inherited Properties

`LoadingIndicator` is based on `QtQuick.Templates.BusyIndicator` and supports its inherited properties, including `running`, `enabled`, `padding`, `topPadding`, `bottomPadding`, `leftPadding`, and `rightPadding`.

The `running` property controls whether the indicator's animations are active. It defaults to `true`.

See the [Qt Quick Controls BusyIndicator documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-busyindicator.html) for details.

# CircularProgressIndicator

`CircularProgressIndicator` displays progress in a circular shape, supporting both determinate and indeterminate modes. It provides customizable progress and track colors, stroke width, and the gap between the progress arc and track, following Material 3 guidelines.

## Basic Usage

```qml
CircularProgressIndicator {
    value: 0.65
}
```

To display an indeterminate indicator:

```qml
CircularProgressIndicator {
    indeterminate: true
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `color` | color | Controls the color of the progress arc. |
| `trackColor` | color | Controls the color of the track. |
| `gapSize` | real | Controls the gap between the progress arc and track. |
| `strokeWidth` | real | Controls the stroke width of the progress arc. |
| `value` | real | Specifies the current progress value. |
| `from` | real | Specifies the starting value of the progress range. |
| `to` | real | Specifies the ending value of the progress range. |
| `position` | real | Read-only normalized progress position, calculated from `value`, `from`, and `to`, and clamped to the range from `0.0` to `1.0`. |
| `indeterminate` | bool | Enables indeterminate mode, in which progress is animated without representing a specific value. |

## Inherited Properties

`CircularProgressIndicator` is based on `QtQuick.Templates.Control` and supports its inherited properties, including `enabled`, `padding`, `topPadding`, `bottomPadding`, `leftPadding`, `rightPadding`, `topInset`, `bottomInset`, `leftInset`, and `rightInset`.

See the [Qt Quick Controls Control documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-control.html) for details.

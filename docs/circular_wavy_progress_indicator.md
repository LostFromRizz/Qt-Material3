# CircularWavyProgressIndicator

`CircularWavyProgressIndicator` displays progress using a circular wavy indicator. It supports determinate and indeterminate modes, with customizable progress and track colors, stroke widths, wave amplitude, wavelength, wave speed, and gap size, following Material 3 guidelines.

## Basic Usage

```qml
CircularWavyProgressIndicator {
    value: 0.65
}
```

To display an indeterminate indicator:

```qml
CircularWavyProgressIndicator {
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
| `trackStrokeWidth` | real | Controls the stroke width of the track. |
| `value` | real | Specifies the current progress value. |
| `from` | real | Specifies the starting value of the progress range. |
| `to` | real | Specifies the ending value of the progress range. |
| `position` | real | Read-only normalized progress position, calculated from `value`, `from`, and `to`, and clamped to the range from `0.0` to `1.0`. |
| `indeterminate` | bool | Enables indeterminate mode, in which progress is animated without representing a specific value. |
| `amplitude` | real | Controls the wave amplitude. In indeterminate mode, it is `1.6`. In determinate mode, it is `0.0` when `position` is less than or equal to `0.1` or greater than or equal to `0.95`, and `1.6` otherwise. |
| `waveLength` | real | Controls the wavelength of the progress wave. |
| `waveSpeed` | real | Specifies the wave speed. Its value follows `waveLength`. |

## Inherited Properties

`CircularWavyProgressIndicator` is based on `QtQuick.Templates.Control` and supports its inherited properties, including `enabled`, `padding`, `topPadding`, `bottomPadding`, `leftPadding`, `rightPadding`, `topInset`, `bottomInset`, `leftInset`, and `rightInset`.

See the [Qt Quick Controls Control documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-control.html) for details.

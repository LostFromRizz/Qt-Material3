# LinearWavyProgressIndicator

`LinearWavyProgressIndicator` displays the progress of an ongoing operation using a wavy linear indicator. It supports determinate and indeterminate modes, with customizable wave properties, stroke widths, colors, and stop indicators, following Material 3 guidelines.

## Basic usage

### Determinate

```qml
LinearWavyProgressIndicator {
    value: 0.65
}
```

### Indeterminate

```qml
LinearWavyProgressIndicator {
    indeterminate: true
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `color` | `color` | Controls the color of the progress indicator. |
| `trackColor` | `color` | Controls the color of the track. |
| `gapSize` | `real` | Controls the gap between the progress indicator and the track. |
| `strokeWidth` | `real` | Controls the stroke width of the progress indicator. |
| `trackStrokeWidth` | `real` | Controls the stroke width of the track. |
| `amplitude` | `real` | Controls the wave amplitude. In indeterminate mode, it is `1.0`. In determinate mode, it becomes `0.0` when the progress position is at or below `0.1` or at or above `0.95`, and `1.0` otherwise. |
| `waveLength` | `real` | Controls the wavelength. It is `20.0` in indeterminate mode and `40.0` in determinate mode. |
| `waveSpeed` | `real` | Controls the wave speed. It follows the value of `waveLength`. |
| `stopIndicator` | `Component` | Specifies the component displayed at the end of the track in determinate mode. |

## Inherited properties

`LinearWavyProgressIndicator` inherits properties from `QtQuick.Templates.ProgressBar`, including:

- `value` — the current progress value.
- `from` — the minimum progress value.
- `to` — the maximum progress value.
- `position` — the normalized progress position.
- `visualPosition` — the visual progress position.
- `indeterminate` — whether the indicator displays indeterminate progress.

See the [Qt Quick Controls ProgressBar documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-progressbar.html) for inherited properties and signals.

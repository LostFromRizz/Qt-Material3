# LinearProgressIndicator

`LinearProgressIndicator` displays the progress of an ongoing operation. It supports both determinate and indeterminate modes, with customizable indicator colors, track appearance, gaps, and stop indicators, following Material 3 guidelines.

## Basic usage

### Determinate

```qml
LinearProgressIndicator {
    value: 0.65
}
```

### Indeterminate

```qml
LinearProgressIndicator {
    indeterminate: true
}
```

## Properties

| Property | Type | Description |
|---|---|---|
| `color` | `color` | Controls the indicator color. |
| `trackColor` | `color` | Controls the track color. |
| `gapSize` | `real` | Controls the gap between the indicator and the track. |
| `flat` | `bool` | Determines whether the indicator is rendered with flat ends rather than rounded ends. |
| `stopIndicator` | `Component` | Specifies the component displayed at the end of the track in determinate mode. |

## Inherited properties

`LinearProgressIndicator` inherits properties from `QtQuick.Templates.ProgressBar`, including:

- `value` — the current progress value.
- `from` — the minimum progress value.
- `to` — the maximum progress value.
- `position` — the normalized progress position.
- `visualPosition` — the visual progress position.
- `indeterminate` — whether the indicator displays indeterminate progress.

See the [Qt Quick Controls ProgressBar documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-progressbar.html) for inherited properties and signals.

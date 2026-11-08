# Typography

`Typography` is a value type that defines the font styles used throughout the Material 3 theme. It provides fifteen typography roles grouped into display, headline, title, label, and body styles.

## Basic usage

```qml
import QtQuick
import Material3

Theme.typography: ({
    displayLarge: Qt.font({ pixelSize: 57 })
    headlineMedium: Qt.font({ pixelSize: 28 })
    titleLarge: Qt.font({ pixelSize: 22 })
    bodyMedium: Qt.font({ pixelSize: 14 })
    labelSmall: Qt.font({ pixelSize: 11 })
})
```

## Properties

All properties are writable and accept a `QFont` value.

### Display

| Property | Description |
|---|---|
| `displayLarge` | Large display text style. |
| `displayMedium` | Medium display text style. |
| `displaySmall` | Small display text style. |

### Headline

| Property | Description |
|---|---|
| `headlineLarge` | Large headline text style. |
| `headlineMedium` | Medium headline text style. |
| `headlineSmall` | Small headline text style. |

### Title

| Property | Description |
|---|---|
| `titleLarge` | Large title text style. |
| `titleMedium` | Medium title text style. |
| `titleSmall` | Small title text style. |

### Label

| Property | Description |
|---|---|
| `labelLarge` | Large label text style. |
| `labelMedium` | Medium label text style. |
| `labelSmall` | Small label text style. |

### Body

| Property | Description |
|---|---|
| `bodyLarge` | Large body text style. |
| `bodyMedium` | Medium body text style. |
| `bodySmall` | Small body text style. |

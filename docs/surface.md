# Surface

`Surface` is a container component based on `QtQuick.Templates.Pane`. It provides a background with configurable corner radii, elevation, and outline. It also supports content padding and automatically reserves space for its shadow.

## Basic Usage

```qml
import QtQuick
import Material3

Surface {
    width: 200
    height: 120

    elevation: 4
    radius: 12

    Text {
        anchors.centerIn: parent
        text: "Surface"
    }
}
```

## Properties

| Property | Description |
|---|---|
| `backgroundColor` | The background color of the surface. Defaults to `Theme.backgroundColor`. |
| `radius` | Sets the corner radius of all four corners. Defaults to `4`. |
| `topLeftRadius` | The radius of the top-left corner. Defaults to `radius`. |
| `topRightRadius` | The radius of the top-right corner. Defaults to `radius`. |
| `bottomLeftRadius` | The radius of the bottom-left corner. Defaults to `radius`. |
| `bottomRightRadius` | The radius of the bottom-right corner. Defaults to `radius`. |
| `outlineColor` | The color of the surface outline. Defaults to `Theme.colorScheme.outlineVariant`. |
| `outlineWidth` | The width of the surface outline. |
| `elevation` | The elevation used to calculate the surface shadow. Defaults to `4`. |
| `includeElevation` | Whether shadow space is included in the surface's layout. Defaults to `false`. |
| `shadowElevationSize` | The calculated size reserved for the surface shadow. It is derived from the shadow's blur, spread, and offset. |

> **Note:** When `includeElevation` is `true`, changes to `elevation` can change `shadowElevationSize`, affecting the card's implicit size and layout. To prevent layout shifts when elevation changes dynamically, reserve space for the maximum expected elevation rather than using the size calculated for the current elevation.

## Inherited Properties

`Surface` is based on `QtQuick.Templates.Pane` and supports inherited pane properties, including `contentItem`, `background`, `contentData`, `contentChildren`, `padding`, `topPadding`, `bottomPadding`, `leftPadding`, and `rightPadding`.

See the [Qt Quick Controls Pane documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-pane.html) for details.

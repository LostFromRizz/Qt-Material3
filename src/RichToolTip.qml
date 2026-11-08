import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts
import Material3
import Material3.internals

T.ToolTip {
    id: control

    final property real elevation: 3.0
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: false

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.min(Material.richTooltipWidth, Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding))

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0
    topPadding: 12 + (includeElevation ? shadowElevationSize.height : 0)
    bottomPadding: 8 + (includeElevation ? shadowElevationSize.height : 0)

    verticalPadding: (includeElevation ? shadowElevationSize.height : 0)
    horizontalPadding: 16 + (includeElevation ? shadowElevationSize.width : 0)

    Theme.contentColor: Theme.colorScheme.inverseOnSurface
    Theme.backgroundColor: Theme.colorScheme.inverseSurface

    final property color backgroundColor: Theme.colorScheme.surfaceContainer
    final property color contentColor: Theme.colorScheme.onSurfaceVariant
    final property color titleContentColor: Theme.colorScheme.onSurfaceVariant
    final property color actionContentColor: Theme.colorScheme.primary

    final property string title
    final property real radius: 16

    final readonly property ObjectModel actionsModel: ObjectModel {}

    final property alias actions: control.actionsModel.children

    font: Theme.typography.bodyMedium
    spacing: 0

    contentItem: ColumnLayout {
        spacing: 0
        readonly property bool hasSubtitle: control.text.length > 0
        Text {
            Layout.fillWidth: true
            text: control.title
            color: control.titleContentColor
            font: control.Theme.typography.titleSmall
            visible: control.title.length > 0
            wrapMode: Text.WordWrap
        }
        Text {
            Layout.fillWidth: true
            Layout.topMargin: control.title.length > 0 ? 4 : 0
            text: control.text
            color: control.contentColor
            font: control.font
            visible: control.text.length > 0
            wrapMode: Text.WordWrap
        }
        Item {
            Layout.preferredHeight: 12.0
            visible: control.title.length > 0 || control.text.length > 0
        }
        Row {
            spacing: control.spacing
            Layout.fillWidth: true
            Repeater {
                model: control.actionsModel
            }
        }
    }

    background: SurfacePrivate {
        shadowElevations: control.__shadows
        topLeftRadius: control.radius
        bottomLeftRadius: control.radius
        topRightRadius: control.radius
        bottomRightRadius: control.radius
        backgroundColor: control.backgroundColor
    }
}

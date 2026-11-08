import QtQuick
import QtQuick.Layouts
import QtQuick.Templates as T
import Material3

T.Control {
    id: control

    final property Flickable flickable
    final readonly property bool dragging: flickable?.dragging ?? false
    final property color backgroundColor: dragging ? Theme.colorScheme.surfaceContainer : Theme.colorScheme.surface
    final property color titleContentColor: Theme.colorScheme.onSurface
    final property color subtitleContentColor: Theme.colorScheme.onSurfaceVariant
    final property color leadingContentColor: Theme.colorScheme.onSurface
    final property color trailingContentColor: Theme.colorScheme.onSurfaceVariant

    final property real radius
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property string headlineText
    final property string subtitleText

    final property real actionSpacing: 4

    final property real containerHeight: Material.appBarHeightSmall

    final property Component leading
    final property Component trailing

    implicitHeight: containerHeight + verticalPadding * 2
    implicitWidth: implicitContentWidth + horizontalPadding * 2

    horizontalPadding: 4.0

    font: Material.appBarFont(Theme.typography, control.containerHeight)

    background: Rectangle {
        color: control.backgroundColor
        anchors.fill: parent
        radius: control.radius
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
    }

    spacing: Math.max(control.leftPadding, control.rightPadding)

    contentItem: RowLayout {
        Loader {
            sourceComponent: control.leading
            visible: item instanceof Item && ((item as Item)?.implicitWidth ?? 0) > 0 && ((item as Item)?.implicitHeight ?? 0) > 0
        }
        Column {
            spacing: 0
            Label {
                text: control.headlineText
                color: control.titleContentColor
                font: control.font
                visible: control.headlineText.length > 0
            }
            Label {
                text: control.subtitleText
                color: control.subtitleContentColor
                font: Material.appBarSubtitleFont(Theme.typography, control.containerHeight)
                visible: control.subtitleText.length > 0
            }
            visible: control.headlineText.length || control.subtitleText.length
        }
        Spacer {}
        Loader {
            Theme.contentColor: control.trailingContentColor
            sourceComponent: control.trailing
            visible: item instanceof Item && ((item as Item)?.implicitWidth ?? 0) > 0 && ((item as Item)?.implicitHeight ?? 0) > 0
        }
    }
}

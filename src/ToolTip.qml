import QtQuick
import QtQuick.Templates as T
import Material3

T.ToolTip {
    id: control
    verticalPadding: 12
    horizontalPadding: 16

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.min(Material.plainTooltipWidth, Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding))

    Theme.contentColor: Theme.colorScheme.inverseOnSurface
    Theme.backgroundColor: Theme.colorScheme.inverseSurface
    font: Theme.typography.labelLarge

    contentItem: Label {
        text: control.text
        wrapMode: Text.WordWrap
    }

    background: Rectangle {
        anchors.fill: parent
        color: control.Theme.backgroundColor
        radius: Math.min(height, width) / 2
    }
}

import QtQuick
import QtQuick.Templates as T
import Material3

T.DialogButtonBox {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    alignment: Qt.AlignRight
    buttonLayout: T.DialogButtonBox.AndroidLayout
    topPadding: position == T.DialogButtonBox.Footer ? 16.0 : padding
    horizontalPadding: 24 + __shadowElevationSize.width
    verticalPadding: 24 + __shadowElevationSize.height
    spacing: 8

    font: Theme.typography.labelLarge

    final property size __shadowElevationSize: Qt.size(0.0, 0.0)

    contentItem: ListView {
        implicitWidth: contentWidth
        model: control.contentModel
        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
    }

    delegate: TextButton {}
    visible: count > 0
}

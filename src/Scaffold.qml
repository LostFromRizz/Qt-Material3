import Material3
import QtQuick
import QtQuick.Templates as T

T.Page {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding, implicitHeaderWidth, implicitFooterWidth)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding + implicitHeaderHeight + implicitFooterHeight)

    final property real radius: 0

    final property alias appBar: control.header

    final property alias floatingActionButton: fabLoader.sourceComponent
    final property real floatingActionButtonVerticalMargin: 16
    final property real floatingActionButtonHorizontalMargin: 16

    background: Rectangle {
        radius: control.radius
        color: control.Theme.backgroundColor
    }

    Loader {
        id: fabLoader
        x: control.width - width - control.floatingActionButtonHorizontalMargin
        y: control.height - Math.max(item && item instanceof Item ? (item as Item).height : 0, item instanceof Button ? (item as Button).containerHeight : 0) - control.floatingActionButtonVerticalMargin
    }
}

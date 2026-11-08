import QtQuick.Templates as T

T.Control {
    topPadding: 4.0
    horizontalPadding: 16.0
    implicitWidth: parent.width
    implicitHeight: visible ? implicitContentHeight + topPadding : 0
    x: topPadding
    y: Math.max(0, parent.height - height)
    visible: contentItem !== null && implicitContentHeight > 0
}

import QtQuick
import QtQuick.Templates as T

T.TextField {
    id: control

    final property real horizontalPadding
    final property real spacing
    final readonly property alias tapHandler: __tapHandler

    final property alias leading: leadingLoader.sourceComponent
    final property alias trailing: trailingLoader.sourceComponent

    leftPadding: horizontalPadding + (leadingLoader.implicitWidth > 0 ? leadingLoader.implicitWidth + spacing : 0)
    rightPadding: horizontalPadding + (trailingLoader.implicitWidth > 0 ? trailingLoader.implicitWidth + spacing : 0)

    // final readonly property real implicitLeadingWidth: leadingLoader.implicitWidth
    // final readonly property real implicitLeadingHeight: leadingLoader.implicitHeight
    // final readonly property real implicitTrailingWidth: trailingLoader.implicitWidth
    // final readonly property real implicitTrailingHeight: trailingLoader.implicitHeight

    implicitHeight: contentHeight + topPadding + bottomPadding
    implicitWidth: contentWidth + leftPadding + rightPadding

    verticalAlignment: Text.AlignVCenter

    TapHandler {
        id: __tapHandler
    }

    Loader {
        id: leadingLoader
        x: control.horizontalPadding
        y: (control.height - height) / 2
    }

    Loader {
        id: trailingLoader
        x: control.width - control.horizontalPadding - width
        y: (control.height - height) / 2
    }
}

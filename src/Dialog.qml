pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts
import QtQuick.Templates as T
import Material3
import Material3.internals

T.Dialog {
    id: control

    final property real radius: 16
    final property color backgroundColor: Theme.colorScheme.surfaceContainerHighest
    final property color titleColor: Theme.colorScheme.onSurface
    final property color contentColor: Theme.colorScheme.onSurfaceVariant
    final property color iconColor: Theme.colorScheme.secondary
    final property color actionContentColor: Theme.colorScheme.primary

    final property Component icon

    final property real elevation: 3.0
    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: false

    Theme.iconSize: Qt.size(24.0, 24.0)

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding + (implicitHeaderHeight > 0 ? implicitHeaderHeight + spacing : 0) + (implicitFooterHeight > 0 ? implicitFooterHeight + spacing : 0))
    implicitWidth: MInternals.clamp(Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding, implicitFooterWidth, implicitHeaderWidth), 280.0, 560.0)

    topInset: includeElevation ? shadowElevationSize.height : 0.0
    bottomInset: includeElevation ? shadowElevationSize.height : 0.0
    leftInset: includeElevation ? shadowElevationSize.width : 0.0
    rightInset: includeElevation ? shadowElevationSize.width : 0.0
    verticalPadding: 24.0 + (includeElevation ? shadowElevationSize.height : 0)
    topPadding: implicitHeaderHeight > 0 ? 0.0 : verticalPadding
    bottomPadding: implicitFooterHeight > 0 ? 0.0 : 16.0
    horizontalPadding: 24.0 + (includeElevation ? shadowElevationSize.width : 0)
    spacing: 16.0
    font: Theme.typography.bodyMedium

    header: ColumnLayout {
        spacing: 16.0
        readonly property real elevatedTopPadding: 24.0 + (control.includeElevation ? control.shadowElevationSize.height : 0)
        Loader {
            Theme.contentColor: control.iconColor
            Layout.topMargin: parent.elevatedTopPadding
            Layout.rightMargin: control.rightPadding
            Layout.leftMargin: control.leftPadding
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            sourceComponent: control.icon
            visible: item instanceof Item && (item as Item).implicitHeight > 0 && (item as Item).implicitWidth > 0
        }
        Text {
            Layout.fillWidth: true
            Layout.topMargin: parent.children[0].visible ? 0.0 : parent.elevatedTopPadding
            Layout.rightMargin: control.rightPadding
            Layout.leftMargin: control.leftPadding
            horizontalAlignment: parent.children[0].visible ? Text.AlignHCenter : Text.AlignLeft
            text: control.title
            font: control.Theme.typography.headlineSmall
            color: control.titleColor
            wrapMode: Text.WordWrap
            visible: control.title.length > 0
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

    footer: DialogButtonBox {
        Theme.contentColor: control.actionContentColor
    }

    final property Component overlay: Rectangle {
        color: control.Theme.colorScheme.surfaceDim
        Behavior on opacity {
            NumberAnimation {
                duration: MotionSpecs.durationShort3
            }
        }
    }

    Binding {
        when: control.includeElevation && control.footer instanceof DialogButtonBox
        target: control.footer
        property: "__shadowElevationSize"
        value: control.shadowElevationSize
    }

    T.Overlay.modal: overlay
    T.Overlay.modeless: overlay

    component Title: Text {}
    component SupportingText: Text {}
}

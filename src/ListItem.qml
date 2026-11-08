import QtQuick
import QtQuick.Layouts
import QtQuick.Templates as T
import Material3
import Material3.internals

T.ItemDelegate {
    id: control
    final property string overlineText
    final property string title
    final property string subtitleText

    final property Component leading
    final property Component trailing

    final property real elevation: 0

    final property bool interactive: true

    final property color outlineColor
    final property real outlineWidth

    final property real radius
    final property real topLeftRadius: radius
    final property real bottomLeftRadius: radius
    final property real topRightRadius: radius
    final property real bottomRightRadius: radius

    final property color backgroundColor: {
        if (!enabled) {
            return Material.disabledBackgroundColor(Theme.colorScheme.surface);
        }
        if (checkable && checked) {
            return Theme.colorScheme.secondaryContainer;
        }
        return Theme.colorScheme.surface;
    }

    final property color leadingContentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable && checked) {
            return Theme.colorScheme.onSecondaryContainer;
        }

        return Theme.colorScheme.onSurfaceVariant;
    }
    final property color overlineContentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable && checked) {
            return Theme.colorScheme.onSecondaryContainer;
        }

        return Theme.colorScheme.onSurfaceVariant;
    }
    final property color contentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable && checked) {
            return Theme.colorScheme.onSecondaryContainer;
        }

        return Theme.colorScheme.onSurface;
    }
    final property color subtitleContentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (checkable && checked) {
            return Theme.colorScheme.onSecondaryContainer;
        }

        return Theme.colorScheme.onSurfaceVariant;
    }
    final property color trailingContentColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }

        if (checkable && checked) {
            return Theme.colorScheme.onSecondaryContainer;
        }

        return Theme.colorScheme.onSurfaceVariant;
    }

    property alias cursorShape: mouseArea.cursorShape

    Theme.iconSize: Qt.size(Material.listIconSize, Material.listIconSize)

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: control.interactive ? Qt.PointingHandCursor : Qt.ArrowCursor
        onPressed: mouse => mouse.accepted = !control.interactive
        onReleased: mouse => mouse.accepted = !control.interactive
        onDoubleClicked: mouse => mouse.accepted = !control.interactive
        onPressAndHold: mouse => mouse.accepted = !control.interactive
    }

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + bottomInset, implicitContentWidth + leftPadding + rightPadding)

    verticalPadding: 10.0 + (includeElevation ? shadowElevationSize.height : 0)
    horizontalPadding: 16.0 + (includeElevation ? shadowElevationSize.width : 0)

    spacing: 12.0
    focusPolicy: Qt.TabFocus
    font: Theme.typography.labelMedium

    final readonly property list<var> __shadows: MInternals.shadowsFor(elevation)
    final property size shadowElevationSize: __shadows.reduce(function (max, shadowElevation) {
        return Qt.size(Math.max(max.width, shadowElevation.blur + shadowElevation.spread), Math.max(max.height, shadowElevation.blur + shadowElevation.spread + shadowElevation.offset));
    }, Qt.size(0, 0))
    final property bool includeElevation: true

    topInset: includeElevation ? shadowElevationSize.height : 0
    bottomInset: includeElevation ? shadowElevationSize.height : 0
    leftInset: includeElevation ? shadowElevationSize.width : 0
    rightInset: includeElevation ? shadowElevationSize.width : 0

    background: InteractiveSurface {
        target: control
        shadowElevations: control.__shadows
        backgroundColor: control.backgroundColor
        contentColor: control.contentColor
        outlineWidth: control.outlineWidth
        outlineColor: control.outlineColor
        topLeftRadius: control.topLeftRadius
        bottomLeftRadius: control.bottomLeftRadius
        topRightRadius: control.topRightRadius
        bottomRightRadius: control.bottomRightRadius
    }

    contentItem: RowLayout {
        final readonly property font font: Theme.typography.bodyMedium
        spacing: control.spacing
        DefaultFontProvider {
            Theme.contentColor: control.leadingContentColor
            font: parent.font
            Layout.fillHeight: true
            sourceComponent: control.leading
        }
        ColumnLayout {
            final readonly property font font: parent.font
            spacing: 0
            Text {
                Layout.fillWidth: true
                text: control.overlineText
                color: control.overlineContentColor
                font: parent.font
                visible: control.overlineText.length > 0
                wrapMode: Text.WordWrap
            }
            Text {
                Layout.fillWidth: true
                text: control.title
                color: control.contentColor
                font: control.font
                visible: control.title.length > 0
                wrapMode: Text.WordWrap
            }
            Text {
                Layout.fillWidth: true
                text: control.subtitleText
                color: control.subtitleContentColor
                font: parent.font
                visible: control.subtitleText.length > 0
                wrapMode: Text.WordWrap
            }
        }
        Item {
            Layout.fillWidth: true
        }
        DefaultFontProvider {
            Theme.contentColor: control.trailingContentColor
            font: parent.font
            Layout.fillHeight: true
            sourceComponent: control.trailing
        }
    }
}

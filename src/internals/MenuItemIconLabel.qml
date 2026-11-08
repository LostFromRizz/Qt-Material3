pragma ComponentBehavior: Bound
import QtQuick.Templates as T
import QtQuick
import Material3.internals

Item {
    id: root
    final required property var leadingIcon
    final required property var trailingIcon
    final required property string text
    final required property font font
    final required property real spacing
    final required property color textColor
    final property int display: -1

    final property Item leadingItem

    final readonly property real implicitLeadingWidth: leadingItem && leadingItem.visible ? leadingItem.implicitWidth : 0.0
    final readonly property real implicitLeadingHeight: leadingItem && leadingItem.visible ? leadingItem.implicitHeight : 0.0

    final property Item trailingItem

    final readonly property real implicitTrailingWidth: trailingItem && trailingItem.visible ? trailingItem.implicitWidth : 0.0
    final readonly property real implicitTrailingHeight: trailingItem && trailingItem.visible ? trailingItem.implicitHeight : 0.0

    final property Item labelItem

    final readonly property real implicitLabelWidth: labelItem && labelItem.visible ? labelItem.implicitWidth : 0.0
    final readonly property real implicitLabelHeight: labelItem && labelItem.visible ? labelItem.implicitHeight : 0.0

    implicitWidth: {
        if (display === T.AbstractButton.TextUnderIcon) {
            return Math.max(implicitLeadingHeight, implicitLabelHeight);
        }
        return implicitLeadingWidth + implicitLabelWidth + implicitTrailingWidth + (spacing * Math.max(0, ((implicitLeadingWidth > 0) + (implicitLabelWidth > 0) + (implicitTrailingWidth > 0)) - 1));
    }

    implicitHeight: {
        if (display === T.AbstractButton.TextUnderIcon) {
            return implicitLeadingHeight + implicitLabelHeight + ((implicitLeadingHeight > 0 && implicitLabelHeight > 0) ? spacing : 0.0);
        }

        return Math.max(implicitLeadingHeight, implicitLabelHeight, implicitTrailingHeight);
    }

    onDisplayChanged: {
        switch (root.display) {
        case T.AbstractButton.IconOnly:
            labelItem?.destroy();
            trailingItem?.destroy();
            labelItem = null;
            trailingItem = null;

            createLeadingItem();
            leadingItem.x = Qt.binding(() => (root.width - root.implicitLeadingWidth) / 2);
            leadingItem.y = Qt.binding(() => (root.height - root.implicitLeadingHeight) / 2);
            break;
        case T.AbstractButton.TextOnly:
            leadingItem?.destroy();
            trailingItem?.destroy();
            leadingItem = null;
            trailingItem = null;

            createLabelItem();
            labelItem.x = Qt.binding(() => (root.width - root.implicitLabelWidth) / 2);
            labelItem.y = Qt.binding(() => (root.height - root.implicitLabelHeight) / 2);
            break;
        case T.AbstractButton.TextUnderIcon:
            trailingItem?.destroy();
            trailingItem = null;

            createLeadingItem();
            leadingItem.x = Qt.binding(() => (root.width - root.implicitLeadingWidth) / 2);
            leadingItem.y = Qt.binding(() => (root.height - root.implicitLeadingHeight - (root.implicitLabelHeight > 0 ? root.implicitLabelHeight + root.spacing : 0)) / 2);

            createLabelItem();
            labelItem.x = Qt.binding(() => (root.width - root.implicitLabelWidth) / 2);
            labelItem.y = Qt.binding(function () {
                if (implicitLeadingHeight > 0) {
                    return ((root.height - root.implicitLeadingHeight - root.implicitLabelHeight - root.spacing) / 2) + root.implicitLeadingHeight + root.spacing;
                }
                return (root.height - root.implicitLabelHeight) / 2;
            });
            break;
        case T.AbstractButton.TextBesideIcon:
        default:
            createLeadingItem();
            leadingItem.x = 0;
            leadingItem.y = Qt.binding(() => (root.height - root.implicitLeadingHeight) / 2);

            createLabelItem();
            labelItem.x = Qt.binding(() => root.implicitLeadingWidth > 0 ? root.implicitLeadingWidth + root.spacing : 0);
            labelItem.y = Qt.binding(() => (root.height - root.implicitLabelHeight) / 2);

            createTrailingItem();
            trailingItem.x = Qt.binding(() => root.width - root.implicitTrailingWidth);
            trailingItem.y = Qt.binding(() => (root.height - root.implicitTrailingHeight) / 2);
            break;
        }
    }

    function createLeadingItem(): void {
        if (leadingItem === null) {
            leadingItem = iconDelegate.createObject(root, {
                name: Qt.binding(() => root.leadingIcon.name),
                size: Qt.binding(() => Math.max(root.leadingIcon.height, root.leadingIcon.width)),
                color: Qt.binding(() => root.leadingIcon.color),
                visible: Qt.binding(() => root.leadingIcon.name.length > 0)
            });
        }
    }
    function createLabelItem(): void {
        if (labelItem === null) {
            labelItem = labelDelegate.createObject(root, {
                text: Qt.binding(() => root.text),
                font: Qt.binding(() => root.font),
                color: Qt.binding(() => root.textColor),
                visible: Qt.binding(() => root.text.length > 0)
            });
        }
    }

    function createTrailingItem(): void {
        if (trailingItem === null) {
            trailingItem = iconDelegate.createObject(root, {
                name: Qt.binding(() => root.trailingIcon.name),
                size: Qt.binding(() => Math.max(root.trailingIcon.height, root.trailingIcon.width)),
                color: Qt.binding(() => root.trailingIcon.color),
                visible: Qt.binding(() => root.trailingIcon.name.length > 0)
            });
        }
    }

    Component {
        id: iconDelegate
        Icon {}
    }

    Component {
        id: labelDelegate
        Text {}
    }
}

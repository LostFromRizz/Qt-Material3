pragma ComponentBehavior: Bound
import QtQuick.Templates as T
import QtQuick
import Material3.internals

Item {
    id: root
    final required property var icon // default AbstractButton.icon is qml anonymous
    final required property string text
    final required property font font
    final required property real spacing
    final required property color textColor
    final property int display: -1

    final property Item iconItem

    final readonly property real implicitIconWidth: iconItem && iconItem.visible ? iconItem.implicitWidth : 0.0
    final readonly property real implicitIconHeight: iconItem && iconItem.visible ? iconItem.implicitHeight : 0.0

    final property Item labelItem

    final readonly property real implicitLabelWidth: labelItem && labelItem.visible ? labelItem.implicitWidth : 0.0
    final readonly property real implicitLabelHeight: labelItem && labelItem.visible ? labelItem.implicitHeight : 0.0

    implicitWidth: {
        if (display === T.AbstractButton.TextUnderIcon) {
            return Math.max(implicitIconHeight, implicitLabelHeight);
        }
        return implicitIconWidth + implicitLabelWidth + (spacing * (implicitIconWidth > 0 && implicitLabelWidth > 0));
    }

    implicitHeight: {
        if (display === T.AbstractButton.TextUnderIcon) {
            return implicitIconHeight + implicitLabelHeight + ((implicitIconHeight > 0 && implicitLabelHeight > 0) ? spacing : 0.0);
        }

        return Math.max(implicitIconHeight, implicitLabelHeight);
    }

    onDisplayChanged: {
        switch (root.display) {
        case T.AbstractButton.IconOnly:
            labelItem?.destroy();
            labelItem = null;

            if (!iconItem) {
                iconItem = iconDelegate.createObject(root);
            }
            iconItem.x = Qt.binding(() => (root.width - root.implicitIconWidth) / 2);
            iconItem.y = Qt.binding(() => (root.height - root.implicitIconHeight) / 2);
            break;
        case T.AbstractButton.TextOnly:
            iconItem?.destroy();
            iconItem = null;

            if (!labelItem) {
                labelItem = labelDelegate.createObject(root);
            }
            labelItem.x = Qt.binding(() => (root.width - root.implicitLabelWidth) / 2);
            labelItem.y = Qt.binding(() => (root.height - root.implicitLabelHeight) / 2);
            break;
        case T.AbstractButton.TextUnderIcon:
            if (!iconItem) {
                iconItem = iconDelegate.createObject(root);
            }
            iconItem.x = Qt.binding(() => (root.width - root.implicitIconWidth) / 2);
            iconItem.y = Qt.binding(() => (root.height - root.implicitIconHeight - (root.implicitLabelHeight > 0 ? root.implicitLabelHeight + root.spacing : 0)) / 2);

            if (!labelItem) {
                labelItem = labelDelegate.createObject(root);
            }
            labelItem.x = Qt.binding(() => (root.width - root.implicitLabelWidth) / 2);
            labelItem.y = Qt.binding(function () {
                if (implicitIconHeight > 0) {
                    return ((root.height - root.implicitIconHeight - root.implicitLabelHeight - root.spacing) / 2) + root.implicitIconHeight + root.spacing;
                }
                return (root.height - root.implicitLabelHeight) / 2;
            });
            break;
        case T.AbstractButton.TextBesideIcon:
        default:
            if (!iconItem) {
                iconItem = iconDelegate.createObject(root);
            }
            iconItem.x = 0;
            iconItem.y = Qt.binding(() => (root.height - root.implicitIconHeight) / 2);

            if (!labelItem) {
                labelItem = labelDelegate.createObject(root);
            }

            labelItem.x = Qt.binding(() => root.implicitIconWidth > 0 ? root.implicitIconWidth + root.spacing : 0);
            labelItem.y = Qt.binding(() => (root.height - root.implicitLabelHeight) / 2);

            break;
        }
    }

    Component {
        id: iconDelegate
        Icon {
            name: root.icon.name
            size: Math.max(root.icon.height, root.icon.width)
            visible: root.icon.name.length > 0
            color: root.icon.color
        }
    }

    Component {
        id: labelDelegate
        Text {
            text: root.text
            font: root.font
            visible: root.text.length > 0
            color: root.textColor
        }
    }
}

// pragma ComponentBehavior: Bound
//
// import QtQuick
// import QtQuick.Templates as T
// import Material3.internals
//
// Item {
//     id: root
//
//     final property real spacing
//     final property string text
//     final property string iconName
//     final property string iconSource
//     final property int iconSize
//     final required property int display
//     final required property color color
//     implicitWidth: loader.implicitWidth
//     implicitHeight: loader.implicitHeight
//
//     Loader {
//         id: loader
//         height: root.display == T.AbstractButton.TextBesideIcon ? root.height : implicitHeight
//         width: root.display == T.AbstractButton.TextBesideIcon ? root.width : implicitWidth
//         sourceComponent: {
//             switch (root.display) {
//             case T.AbstractButton.IconOnly:
//                 return iconOnly;
//             case T.AbstractButton.TextOnly:
//                 return textOnly;
//             case T.AbstractButton.TextUnderIcon:
//                 return textUnderIcon;
//             case T.AbstractButton.TextBesideIcon:
//             default:
//                 return textBesideIcon;
//             }
//         }
//
//         anchors.centerIn: parent
//         // x: (root.width - width) / 2
//         // y: (root.height - height) / 2
//     }
//
//     Component {
//         id: iconOnly
//         MFontIcon {}
//     }
//
//     Component {
//         id: textOnly
//         MText {
//             verticalAlignment: Text.AlignVCenter
//             horizontalAlignment: Text.AlignVCenter
//         }
//     }
//
//     Component {
//         id: textBesideIcon
//
//         Item {
//             implicitHeight: Math.max(rowIcon.implicitHeight, rowLabel.implicitHeight)
//             implicitWidth: rowIcon.implicitWidth + root.spacing + rowLabel.implicitWidth
//             MFontIcon {
//                 id: rowIcon
//                 x: (parent.width - rowLabel.width - (rowLabel.width > 0 ? root.spacing : 0) - width) / 2
//                 y: (parent.height - height) / 2
//                 visible: height > 0 && width > 0
//             }
//             MText {
//                 id: rowLabel
//                 x: parent.width > 0 ? rowIcon.x + rowIcon.width + root.spacing : (root.width - width) / 2
//                 y: (parent.height - height) / 2
//                 visible: height > 0 && width > 0
//             }
//         }
//     }
//
//     Component {
//         id: textUnderIcon
//         Item {
//             implicitHeight: columnIcon.implicitHeight + root.spacing + columnLabel.implicitHeight
//             implicitWidth: Math.max(columnIcon.implicitWidth, columnLabel.implicitWidth)
//             MFontIcon {
//                 id: columnIcon
//                 x: (root.width - Math.max(implicitWidth, columnLabel.implicitWidth)) / 2
//                 y: (root.height - columnIcon.implicitHeight - root.spacing - columnLabel.implicitHeight) / 2
//             }
//             MText {
//                 id: columnLabel
//                 x: (root.width - Math.max(implicitWidth, columnIcon.implicitWidth)) / 2
//                 y: columnIcon.y + root.spacing
//             }
//         }
//     }
//
//     component MText: T.Label {
//         text: root.text
//         color: root.color
//     }
//
//     component MFontIcon: Icon {
//         name: root.iconName
//         size: root.iconSize
//         color: root.color
//     }
// }

import QtQuick
import QtQuick.Templates as T
import Material3

T.TextField {
    id: control

    final property string labelText
    final property alias supportingItem: __supportingItem.contentItem

    final property real topLeftRadius: 4.0
    final property real topRightRadius: 4.0
    final property real bottomLeftRadius: 0
    final property real bottomRightRadius: 0

    final property real containerTopPadding: 8.0
    final property real containerBottomPadding: 8.0
    final property real containerLeftPadding: control.leading ? 12.0 : 16.0
    final property real containerRightPadding: control.trailing ? 12.0 : 16.0

    final property real spacing: 16.0

    final property bool hasError: !acceptableInput

    final property Component leading
    final property Component trailing

    final readonly property real implicitLabelHeight: control.__labelItem?.implicitHeight ?? 0
    final readonly property real implicitLabelWidth: control.__labelItem?.implicitWidth ?? 0
    final readonly property real implicitSupportingItemHeight: __supportingItem.implicitHeight
    final readonly property real implicitSupportingItemWidth: __supportingItem.implicitWidth
    final readonly property real implicitLeadingHeight: __leading.implicitHeight
    final readonly property real implicitLeadingWidth: __leading.implicitWidth
    final readonly property real implicitTrailingHeight: __trailing.implicitHeight
    final readonly property real implicitTrailingWidth: __trailing.implicitWidth

    final readonly property real containerHeight: control.height - implicitSupportingItemHeight

    final property color backgroundColor: enabled ? Theme.colorScheme.surfaceContainerHighest : Material.disabledBackgroundColor(Theme.colorScheme.surface)
    final property color indicatorColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (hasError) {
            return Theme.colorScheme.error;
        }
        if (activeFocus) {
            return Theme.colorScheme.primary;
        }
        return Theme.colorScheme.onSurfaceVariant;
    }
    final property color labelTextColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        if (hasError) {
            return Theme.colorScheme.error;
        }
        if (activeFocus) {
            return Theme.colorScheme.primary;
        }
        return Theme.colorScheme.onSurfaceVariant;
    }

    placeholderTextColor: {
        if (!enabled) {
            return Material.disabledContentColor(Theme.colorScheme.onSurface);
        }
        return Theme.colorScheme.onSurfaceVariant;
    }

    final property color supportingTextColor: enabled ? Theme.colorScheme.onSurfaceVariant : Material.disabledContentColor(Theme.colorScheme.onSurface)

    final property color leadingContentColor: enabled ? Qt.alpha(Theme.colorScheme.onSurface, 0.54) : Material.disabledContentColor(Theme.colorScheme.onSurface)

    final property color trailingContentColor: enabled ? Qt.alpha(Theme.colorScheme.onSurface, 0.54) : Material.disabledContentColor(Theme.colorScheme.onSurface)

    implicitWidth: Math.max(Material.textFieldMinimumWidth, implicitBackgroundWidth + leftInset + rightInset, contentWidth + rightPadding + leftPadding)
    implicitHeight: Math.max(Material.textFieldMinimumHeight, contentHeight + containerTopPadding + containerBottomPadding, implicitBackgroundHeight + topInset + bottomInset) + implicitSupportingItemHeight

    topPadding: containerTopPadding + (control.__labelItemVisible && control.__floating ? implicitLabelHeight : 0)
    leftPadding: containerLeftPadding + (__leading.implicitWidth > 0 ? __leading.implicitWidth + spacing : 0)
    bottomPadding: containerBottomPadding + implicitSupportingItemHeight
    rightPadding: containerRightPadding + (__trailing.implicitWidth > 0 ? __trailing.implicitWidth + spacing : 0)

    focusPolicy: Qt.StrongFocus
    verticalAlignment: TextInput.AlignVCenter
    font: Theme.typography.bodyLarge

    Theme.iconSize: Qt.size(Material.textFieldIconSize, Material.textFieldIconSize)

    // leading
    Loader {
        id: __leading
        sourceComponent: control.leading
        x: control.containerLeftPadding
        y: (control.containerHeight - height) / 2
    }

    Loader {
        id: __trailing
        sourceComponent: control.trailing
        x: control.width - width - control.containerRightPadding
        y: (control.containerHeight - height) / 2
        Theme.contentColor: control.trailingContentColor
    }

    // placeHolder
    Text {
        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        x: control.leftPadding
        y: control.topPadding
        height: control.containerHeight - control.topPadding - control.containerBottomPadding
        width: control.width - control.leftPadding - control.rightPadding
        verticalAlignment: control.verticalAlignment
        visible: control.placeholderText.length > 0 && ((control.activeFocus && !control.displayText) || !control.__labelItemVisible && !control.displayText)
        renderType: control.renderType
    }

    TextFieldSupportingText {
        id: __supportingItem
        font: Theme.typography.bodySmall
        Theme.contentColor: control.supportingTextColor
    }

    final readonly property bool __floating: control.displayText || control.activeFocus

    final property Item __labelItem
    final property bool __labelItemVisible: __labelItem?.visible ?? false

    background: Rectangle {
        height: control.height - control.implicitSupportingItemHeight
        topLeftRadius: control.topLeftRadius
        topRightRadius: control.topRightRadius
        bottomLeftRadius: control.bottomLeftRadius
        bottomRightRadius: control.bottomRightRadius
        color: control.backgroundColor

        Binding {
            target: control
            property: "__labelItem"
            // qmllint disable missing-property
            value: control.background.label
            // qmllint enable missing-property
        }

        final property Text label: Text {
            parent: control.background
            text: control.labelText
            font: Material.textFieldLabelFont(Theme.typography, control.__floating)
            color: control.labelTextColor
            x: LayoutMirroring.enabled ? control.rightPadding : control.leftPadding
            y: control.__floating ? Math.max(control.topPadding - implicitHeight, 0) : (control.containerHeight - height) / 2
            visible: control.labelText.length > 0
            renderType: control.renderType

            Behavior on y {
                NumberAnimation {
                    duration: MotionSpecs.standardDefaultSpatialDuration
                    easing.bezierCurve: MotionSpecs.standardDefaultSpatialBezier
                    easing.type: Easing.BezierSpline
                }
            }
        }

        // indicator
        Rectangle {
            anchors.bottom: parent.bottom
            height: control.activeFocus ? 2.0 : 1.0
            Behavior on height {
                NumberAnimation {
                    duration: MotionSpecs.standardFastEffectsDuration
                    easing.bezierCurve: MotionSpecs.standardFastEffectsBezier
                    easing.type: Easing.BezierSpline
                }
            }
            width: parent.width
            color: control.indicatorColor
            bottomLeftRadius: control.bottomLeftRadius
            bottomRightRadius: control.bottomRightRadius
        }
    }
}

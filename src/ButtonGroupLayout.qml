import QtQuick
import QtQml.Models
import QtQuick.Layouts
import QtQuick.Templates as T
import Material3

T.Control {
    id: control

    final property real expandRatio: 0.15
    final property T.AbstractButton overflowIndicator
    final property bool exclusive: false

    final readonly property alias checkedButton: group.checkedButton
    final readonly property alias buttons: group.buttons

    final property real maximumWidth: Number.POSITIVE_INFINITY

    final readonly property real implicitOverflowIndicatorWidth: overflowIndicator?.implicitWidth ?? 0
    final readonly property real implicitOverflowIndicatorHeight: overflowIndicator?.implicitHeight ?? 0

    default final property list<T.Action> actions: []

    final property Component delegate: FilledButton {}

    signal clicked(button: T.AbstractButton)

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + rightPadding + leftPadding)
    hoverEnabled: true
    spacing: exclusive ? 2 : Material.buttonGroupSpacingSmall

    T.ButtonGroup {
        id: group
        buttons: [...contentModel.children, ...(group.hasOverflow && control.overflowIndicator ? [control.overflowIndicator] : [])]
        onClicked: button => control.clicked(button)
        exclusive: control.exclusive

        final readonly property ObjectModel contentModel: ObjectModel {}

        final property bool updating
        final property bool delegateChanged: false
        final property bool updatePending: false
        final property bool updateFull: false
        final property bool hasOverflow: false
        final property real contentWidth: 0
        final property real oldContentWidth: control.implicitContentWidth

        function addItem(index: int, action: T.Action): T.AbstractButton {
            const item = control.delegate.createObject(control.contentItem, {
                action: Qt.binding(() => action)
            });

            if (item instanceof T.AbstractButton) {
                contentModel.insert(index, item);
                return item as T.AbstractButton;
            } else {
                console.error("delegate is not a AbstractButton");
                return null;
            }
        }

        function maybeUpdatePending(): void {
            if (updatePending) {
                updatePending = false;

                if (updateFull) {
                    updateFull = false;
                    updateFullLayout();
                } else {
                    updateLayout();
                }
            }
        }

        property list<int> indexSet: []

        function updateFullLayout(): void {
            if (updating) {
                updatePending = true;
                updateFull = true;
                return;
            }

            try {
                updating = true;

                contentModel.clear();
                addedActions.clear();
                seenActions.clear();

                const actions = control.actions;
                const maximumWidth = control.maximumWidth;
                const spacing = control.spacing;
                const overflowIndicatorWidth = control.implicitOverflowIndicatorWidth;
                let currentWidth = 0;
                let hasOverflow = false;
                let deleteStart = actions.length;

                for (let i = 0; i < actions.length; i++) {
                    const action = actions[i];
                    const item = addItem(i, action);

                    currentWidth += item?.implicitWidth ?? 0;

                    if (i < actions.length - 1 && item) {
                        currentWidth += spacing;
                    }

                    if (currentWidth > maximumWidth) {
                        // try to fit overflowIndicator inside maximumWidth
                        for (let j = i; j > 0; --j) {
                            const button = contentModel.get(j);
                            currentWidth -= ((button as T.AbstractButton).implicitWidth + spacing);
                            if (currentWidth + overflowIndicatorWidth <= maximumWidth) {
                                deleteStart = j;
                                hasOverflow = true;
                                break;
                            }
                        }

                        break;
                    }
                }

                if (deleteStart < contentModel.count) {
                    contentModel.remove(deleteStart, contentModel.count - deleteStart); // remove extras
                }

                group.hasOverflow = hasOverflow;
                group.contentWidth = currentWidth + spacing + (hasOverflow ? overflowIndicatorWidth : 0);
            } finally {
                updating = false;
                Qt.callLater(group.maybeUpdatePending);
            }
        }

        property var seenActions: new Set()
        property var addedActions: new Set()

        function updateLayout(): void {
            if (updating) {
                // everything will already be rebuild
                if (updatePending && updateFull) {
                    return;
                }

                updatePending = true;
                updateFull = false;

                return;
            }

            try {
                updating = true;

                const actions = control.actions;
                const maximumWidth = control.maximumWidth;
                const spacing = control.spacing;
                const overflowIndicatorWidth = control.implicitOverflowIndicatorWidth;
                let currentWidth = 0;

                let deleteStart = actions.length;
                let hasOverflow = false;

                seenActions.clear();

                let modelIndex = 0;
                for (let i = 0; i < actions.length; i++) {
                    const action = actions[i];
                    let button = modelIndex < contentModel.count ? contentModel.get(modelIndex) : null;

                    if (button && button.action !== action) {
                        if (seenActions.has(action)) {
                            // already created
                            // keep the modelIndex unchanged to use it with the next action
                            continue;
                        }

                        // dirty
                        addedActions.delete(button.action);
                        seenActions.delete(button.action);
                        contentModel.remove(modelIndex);
                        button = null;
                    }

                    if (!button && !seenActions.has(action) && !addedActions.has(action)) {
                        button = addItem(modelIndex, action);
                        addedActions.add(action);
                    }

                    seenActions.add(action);
                    modelIndex++;

                    currentWidth += button?.implicitWidth ?? 0; // since we know button will always be a AbstractButton
                    // qmllint enable missing-property

                    if (button && modelIndex < contentModel.count - 1) {
                        currentWidth += spacing;
                    }

                    if (currentWidth > maximumWidth) {
                        // try to fit overflowIndicator inside maximumWidth
                        for (let j = i; j > 0; --j) {
                            const button = contentModel.get(j);
                            currentWidth -= ((button as T.AbstractButton).implicitWidth + spacing);
                            if (currentWidth + overflowIndicatorWidth <= maximumWidth) {
                                deleteStart = j;
                                hasOverflow = true;
                                break;
                            }
                        }

                        break;
                    }
                }

                if (deleteStart < contentModel.count) {
                    for (let i = deleteStart; i < contentModel.count; i++) {
                        addedActions.delete(contentModel.get(i).action);
                    }
                    contentModel.remove(deleteStart, contentModel.count - deleteStart); // remove extras
                }

                group.hasOverflow = hasOverflow;
                group.contentWidth = currentWidth + spacing + (hasOverflow ? overflowIndicatorWidth : 0);
            } finally {
                updating = false;
                Qt.callLater(group.maybeUpdatePending);
            }
        }

        final property real from: 0
        final property real to: 1
        final property real animationValue: 0
        final property real animatedWidth: 0
        final property int currentIndex: -1

        // slot
        final property var animationFinished

        function animateWidth(center: T.AbstractButton, autoReset = false) {
            if (!center) {
                return;
            }

            if (animation.running) {
                group.reset(true);
            }

            // already expanded
            if (group.animatedWidth > 0) {
                return;
            }

            const buttons = group.buttons;
            const index = buttons.indexOf(center);

            if (index === -1) {
                console.error(`Unable to find ${center} in group`);
                return;
            }

            const left = buttons[index - 1];
            const right = buttons[index + 1];

            // capture the widths
            const centerWidth = center.implicitWidth;
            const leftWidth = left?.implicitWidth ?? 0;
            const rightWidth = right?.implicitWidth ?? 0;

            let hasError = false;

            function setWidth(button: T.AbstractButton, binding: var) {
                console.assert(button !== null);
                if (button.Layout?.preferredWidth !== undefined) {
                    button.Layout.preferredWidth = binding;
                } else {
                    console.error("Cannot set button width because Layout.preferredWidth is unavailable. ButtonGroup manages its children using a layout.");
                    hasError = true;
                }
            }

            if (left && right) {
                setWidth(left, Qt.binding(() => leftWidth - Math.floor(group.animatedWidth / 2)));
                setWidth(right, Qt.binding(() => rightWidth - Math.ceil(group.animatedWidth / 2)));
            } else if (left) {
                setWidth(left, Qt.binding(() => leftWidth - group.animatedWidth));
            } else if (right) {
                setWidth(right, Qt.binding(() => rightWidth - group.animatedWidth));
            } else {
                hasError = !control.fillWidth;
            }

            setWidth(center, Qt.binding(() => centerWidth + group.animatedWidth));

            if (hasError) {
                function resetWidth(button: T.AbstractButton) {
                    if (button?.Layout?.preferredWidth !== undefined) {
                        button.Layout.preferredWidth = Qt.binding(() => button.implicitWidth);
                    }
                }

                resetWidth(left);
                resetWidth(right);
                resetWidth(center);
                return;
            }

            group.animatedWidth = Qt.binding(() => Math.round(group.animationValue * control.expandRatio * centerWidth));
            group.currentIndex = index;
            group.from = 0;
            group.to = 1;
            animation.reverse = autoReset;
            animation.start();
        }

        function reset(force = false) {
            animation.complete();

            // We have already expanded, time to shrink back
            if (group.animatedWidth > 0) {
                group.animationFinished = function () {
                    const index = group.currentIndex;
                    const buttons = group.buttons;

                    let center = buttons[index];
                    const left = buttons[index - 1];
                    const right = buttons[index + 1];

                    function resetWidth(button: T.AbstractButton) {
                        if (!button) {
                            return;
                        }
                        if (button?.Layout?.preferredWidth !== undefined) {
                            button.Layout.preferredWidth = Qt.binding(() => button.implicitWidth);
                        }
                    }

                    resetWidth(left);
                    resetWidth(center);
                    resetWidth(right);

                    console.assert(group.animatedWidth === 0 && group.from === 1 && group.to === 0, "ButtonGroup: Bad State");
                    group.currentIndex = -1;
                    group.animationFinished = null;
                };

                if (force) {
                    animation.reverse = false;
                    group.animationFinished();
                } else {
                    group.from = 1;
                    group.to = 0;
                    animation.reverse = false;
                    animation.start();
                }
            }
        }
    }

    NumberAnimation {
        id: animation
        target: group
        from: group.from
        to: group.to
        property: "animationValue"
        property bool reverse: false
        easing.bezierCurve: MotionSpecs.expressiveFastSpatialBezier
        duration: MotionSpecs.expressiveFastSpatialDuration
        easing.type: Easing.BezierSpline
        onFinished: {
            if (reverse) {
                group.reset();
            } else if (group.animationFinished) {
                group.animationFinished();
            }
        }
    }

    onDelegateChanged: group.updateFullLayout()
    onImplicitOverflowIndicatorWidthChanged: group.updateLayout()
    onActionsChanged: group.updateLayout()
    onSpacingChanged: group.updateLayout()
    onMaximumWidthChanged: group.updateLayout()

    contentItem: RowLayout {
        spacing: control.spacing

        Repeater {
            model: group.contentModel
            onItemAdded: function (index, item) {
                item.implicitWidthChanged.connect(() => group.updateLayout());
                item.downChanged.connect(function () {
                    if (group.exclusive) {
                        // button expanded in a exlusive group
                        if (group.animateWidth > 0) {
                            group.reset();
                        }
                    } else {
                        if (item.down) {
                            group.animateWidth(item, false);
                        } else {
                            group.reset();
                        }
                    }
                });
            }
            onItemRemoved: function (index, item) {
                item.destroy();
            }
        }

        LayoutItemProxy {
            target: control.overflowIndicator
            visible: control.overflowIndicator !== null && group.hasOverflow

            Connections {
                target: control.overflowIndicator

                function onDownChanged() {
                    const button = control.overflowIndicator;
                    // just to be safe
                    if (!button) {
                        return;
                    }

                    if (button.down) {
                        group.animateWidth(button, false);
                    } else {
                        group.reset();
                    }
                }
            }
        }
        Spacer {
            visible: group.contentWidth < control.width
        }
    }
}

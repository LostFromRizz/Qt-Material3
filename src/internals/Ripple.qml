pragma ComponentBehavior: Bound
import QtQuick
import Material3.internals

QtObject {
    id: root

    final required property real duration
    final required property list<real> bezierCurve

    required property Item parent
    required property color color

    function showFixed(x: real, y: real, height: real, width: real): void {
        __ripple.createObject(parent, {
            pressX: x,
            pressY: y,
            containerHeight: height ?? parent.height,
            containerWidth: width ?? parent.width,
            color: Qt.alpha(root.color, MInternals.pressedAlpha)
        });
    }

    function show(x: real, y: real): void {
        const projected = __projectAnchor(x, y);
        __ripple.createObject(parent, {
            pressX: projected.x,
            pressY: projected.y,
            containerHeight: parent.height,
            containerWidth: parent.width,
            color: Qt.alpha(root.color, MInternals.pressedAlpha)
        });
    }

    function __projectAnchor(x: real, y: real): point {
        const w = parent.width;
        const h = parent.height;
        const centerX = w / 2;
        const centerY = h / 2;
        const r = Math.sqrt(w * w + h * h) / 2;

        const dx = x - centerX;
        const dy = y - centerY;
        const dist = Math.sqrt(dx * dx + dy * dy);

        // If the press point is inside the circle, use it directly
        if (dist <= r)
            return Qt.point(x, y);

        // Otherwise, project it onto the circle edge
        const angle = Math.atan2(dy, dx);
        const px = centerX + r * Math.cos(angle);
        const py = centerY + r * Math.sin(angle);
        return Qt.point(px, py);
    }

    property Component __ripple: Component {
        Rectangle {
            id: rect
            property real containerHeight
            property real containerWidth
            property real pressX: width / 2
            property real pressY: height / 2
            property real value: 0
            property var endCallback
            readonly property real diameter: {
                const h = containerHeight;
                const w = containerWidth;
                return Math.sqrt(w * w + h * h);
            }

            property real p: value / diameter
            x: (containerWidth - value) / 2 + (1 - p) * (pressX - containerWidth / 2)
            y: (containerHeight - value) / 2 + (1 - p) * (pressY - containerHeight / 2)
            width: value
            height: value
            radius: value / 2

            ParallelAnimation {
                id: ani
                running: true

                NumberAnimation {
                    target: rect
                    duration: root.duration
                    easing.type: Easing.BezierSpline
                    easing.bezierCurve: root.bezierCurve
                    property: "opacity"
                    from: 1
                    to: 0
                }

                NumberAnimation {
                    target: rect
                    duration: root.duration
                    easing.type: Easing.BezierSpline
                    easing.bezierCurve: root.bezierCurve
                    property: "value"
                    from: 0
                    to: rect.diameter
                }

                onFinished: {
                    rect.destroy();
                }
            }
        }
    }
}

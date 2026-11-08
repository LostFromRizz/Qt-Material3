pragma ComponentBehavior: Bound

import Material3.internals
import QtQuick
import QtQuick.Effects

SurfacePrivate {
    id: surface
    final property QtObject target // AbstractButton or MouseArea
    final property color contentColor
    final property color hoveredColor: Qt.alpha(surface.contentColor, MInternals.hoveredAlpha)
    final property color rippleColor: surface.contentColor
    final property bool hovered: target?.hovered ?? false

    DefaultShape {
        anchors.fill: parent
        color: surface.hovered ? surface.hoveredColor : "transparent"
        visible: surface.enabled
        z: 1
    }

    Item {
        id: clip
        anchors.fill: parent
        layer.enabled: true
        layer.effect: MultiEffect {
            maskSource: __mask
            maskEnabled: true
            maskThresholdMin: 0.5
            maskSpreadAtMin: 1
        }
        z: 2
    }

    Item {
        id: __mask
        anchors.fill: parent
        layer.enabled: true
        visible: false
        DefaultShape {
            anchors.fill: parent
        }
    }

    Ripple {
        id: ripple
        parent: clip
        color: surface.rippleColor
        duration: 1000
        bezierCurve: [0.05, 0.7, 0.1, 1.0, 1.0, 1.0]
    }

    function addRipple(x: real, y: real) {
        ripple.show(x, y);
    }

    component DefaultShape: Rectangle {
        topLeftRadius: surface.topLeftRadius
        bottomLeftRadius: surface.bottomLeftRadius
        topRightRadius: surface.topRightRadius
        bottomRightRadius: surface.bottomRightRadius
        border.width: surface.outlineWidth
        border.color: "transparent"
    }

    Connections {
        target: surface.target
        function onClicked(): void {
            surface.addRipple(surface.target.pressX, surface.target.pressY);
        }
        function onTapped(event): void {
            surface.addRipple(event.position.x, event.position.y);
        }
        ignoreUnknownSignals: true
    }
}

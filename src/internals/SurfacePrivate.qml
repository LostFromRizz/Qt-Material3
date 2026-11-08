pragma ComponentBehavior: Bound
import QtQuick
import Material3.internals

Item {
    id: surface

    final property list<var> shadowElevations
    final property real topLeftRadius
    final property real bottomLeftRadius
    final property real topRightRadius
    final property real bottomRightRadius
    final property color backgroundColor
    final property int outlineWidth
    final property color outlineColor

    Repeater {
        enabled: surface.background !== null
        model: surface.shadowElevations
        delegate: ShadowElevationDelegate {
            required property var modelData
            shadowElevation: modelData
        }
    }

    final property Item background

    final property bool explicitShape: false

    final property Component shape: Rectangle {
        anchors.fill: parent
        enabled: surface.enabled
        topLeftRadius: surface.topLeftRadius
        bottomLeftRadius: surface.bottomLeftRadius
        topRightRadius: surface.topRightRadius
        color: surface.backgroundColor
        bottomRightRadius: surface.bottomRightRadius
        border.width: surface.outlineWidth
        border.color: surface.outlineColor
    }

    onShapeChanged: {
        explicitShape = true;
        Qt.callLater(surface.constructShape);
    }

    function constructShape(): void {
        if (surface.background !== null) {
            surface.background.destroy();
            surface.background = null;
        }

        if (surface.shape) {
            surface.background = surface.shape.createObject(surface);
        }
    }

    Component.onCompleted: {
        if (!explicitShape) {
            surface.constructShape();
        }
    }

    component ShadowElevationDelegate: ShadowElevation {
        anchors.fill: surface.background ?? undefined
        enabled: surface.enabled
        topLeftRadius: surface.topLeftRadius
        bottomLeftRadius: surface.bottomLeftRadius
        topRightRadius: surface.topRightRadius
        bottomRightRadius: surface.bottomRightRadius
    }
}

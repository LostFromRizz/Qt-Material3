import QtQuick
import QtQuick.Shapes

Shape {
    id: root
    final property int radius: 0
    final property int topLeftRadius: root.radius
    final property int bottomLeftRadius: root.radius
    final property int topRightRadius: root.radius
    final property int bottomRightRadius: root.radius

    final property alias strokeWidth: path.strokeWidth
    final property alias strokeColor: path.strokeColor
    final property alias fillColor: path.fillColor

    final property int joinStyle: ShapePath.MiterJoin
    final property int capStyle: ShapePath.SquareCap
    final property int strokeStyle: ShapePath.SolidLine

    final readonly property bool __preferredRendererTypeAvailable: root.preferredRendererType !== undefined
    final readonly property bool __curveRendererActive: root.__preferredRendererTypeAvailable && root.rendererType === Shape.CurveRenderer

    antialiasing: true

    layer.enabled: root.antialiasing && !root.__curveRendererActive
    layer.smooth: root.antialiasing && !root.__curveRendererActive
    layer.samples: root.antialiasing && !root.__curveRendererActive ? 4 : 0

    final property real borderOffset: root.strokeWidth * 0.5

    onRadiusChanged: Qt.callLater(root.calculateIndependentRadii)
    onTopLeftRadiusChanged: Qt.callLater(root.calculateIndependentRadii)
    onTopRightRadiusChanged: Qt.callLater(root.calculateIndependentRadii)
    onBottomLeftRadiusChanged: Qt.callLater(root.calculateIndependentRadii)
    onBottomRightRadiusChanged: Qt.callLater(root.calculateIndependentRadii)
    onWidthChanged: Qt.callLater(root.calculateIndependentRadii)
    onHeightChanged: Qt.callLater(root.calculateIndependentRadii)

    function calculateIndependentRadii(): void {
        let minDimension = Math.min(root.width, root.height);
        let maxRadius = Math.floor(minDimension / 2);
        let mixed = !(root.radius === root.topLeftRadius && root.radius === root.topRightRadius && root.radius === root.bottomLeftRadius && root.radius === root.bottomRightRadius);

        // Uniform radii
        if (!mixed) {
            path.__topLeftRadius = Math.min(root.topLeftRadius, maxRadius);
            path.__topRightRadius = Math.min(root.topRightRadius, maxRadius);
            path.__bottomRightRadius = Math.min(root.bottomRightRadius, maxRadius);
            path.__bottomLeftRadius = Math.min(root.bottomLeftRadius, maxRadius);
            return;
        }

        // Mixed radii
        let topLeftRadiusMin = Math.min(minDimension, root.topLeftRadius);
        let topRightRadiusMin = Math.min(minDimension, root.topRightRadius);
        let bottomLeftRadiusMin = Math.min(minDimension, root.bottomLeftRadius);
        let bottomRightRadiusMin = Math.min(minDimension, root.bottomRightRadius);

        // Top radii
        let topRadii = root.topLeftRadius + root.topRightRadius;

        if (topRadii > root.width) {
            let topLeftRadiusFactor = root.topLeftRadius / topRadii;
            let tlr = Math.round(root.width * topLeftRadiusFactor);

            topLeftRadiusMin = Math.min(topLeftRadiusMin, tlr);
            topRightRadiusMin = Math.min(topRightRadiusMin, root.width - tlr);
        }

        // Right radii
        let rightRadii = root.topRightRadius + root.bottomRightRadius;

        if (rightRadii > root.height) {
            let topRightRadiusFactor = root.topRightRadius / rightRadii;
            let trr = Math.round(root.height * topRightRadiusFactor);

            topRightRadiusMin = Math.min(topRightRadiusMin, trr);
            bottomRightRadiusMin = Math.min(bottomRightRadiusMin, root.height - trr);
        }

        // Bottom radii
        let bottomRadii = root.bottomRightRadius + root.bottomLeftRadius;

        if (bottomRadii > root.width) {
            let bottomRightRadiusFactor = root.bottomRightRadius / bottomRadii;
            let brr = Math.round(root.width * bottomRightRadiusFactor);

            bottomRightRadiusMin = Math.min(bottomRightRadiusMin, brr);
            bottomLeftRadiusMin = Math.min(bottomLeftRadiusMin, root.width - brr);
        }

        // Left radii
        let leftRadii = root.bottomLeftRadius + root.topLeftRadius;

        if (leftRadii > root.height) {
            let bottomLeftRadiusFactor = root.bottomLeftRadius / leftRadii;
            let blr = Math.round(root.height * bottomLeftRadiusFactor);

            bottomLeftRadiusMin = Math.min(bottomLeftRadiusMin, blr);
            topLeftRadiusMin = Math.min(topLeftRadiusMin, root.height - blr);
        }

        path.__topLeftRadius = topLeftRadiusMin;
        path.__topRightRadius = topRightRadiusMin;
        path.__bottomLeftRadius = bottomLeftRadiusMin;
        path.__bottomRightRadius = bottomRightRadiusMin;
    }

    ShapePath {
        id: path

        property int __topLeftRadius: 0
        property int __topRightRadius: 0
        property int __bottomRightRadius: 0
        property int __bottomLeftRadius: 0

        capStyle: root.capStyle
        strokeStyle: root.strokeStyle
        joinStyle: root.joinStyle

        strokeWidth: 1

        startX: path.__topLeftRadius + root.borderOffset
        startY: root.borderOffset

        PathRectangle {
            width: root.width
            height: root.height
            topLeftRadius: path.__topLeftRadius
            bottomLeftRadius: path.__bottomLeftRadius
            topRightRadius: path.__topRightRadius
            bottomRightRadius: path.__bottomRightRadius
        }
    }

    Component.onCompleted: {
        // If preferredRendererType wasn't set initially make CurveRenderer the default
        if (root.__preferredRendererTypeAvailable && root.preferredRendererType === Shape.UnknownRenderer)
            root.preferredRendererType = Shape.CurveRenderer;

        root.calculateIndependentRadii();
    }
}

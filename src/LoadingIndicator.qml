import QtQuick
import QtQuick.Templates as T
import Material3

T.BusyIndicator {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentWidth + leftPadding + rightPadding)
    running: true

    final property color color: Theme.colorScheme.primary
    final property list<RoundedPolygon> polygons: [MaterialShapes.softBurst, MaterialShapes.cookie9Sided, MaterialShapes.pentagon, MaterialShapes.pill, MaterialShapes.sunny, MaterialShapes.cookie4Sided, MaterialShapes.oval]

    contentItem: Canvas {
        final readonly property alias color: control.color
        final readonly property real scaleFactor: MaterialShapes.calculateScaleFactor(control.polygons) * (38 / 48) // (indicatorSize / containerSize)

        final property int activeIndex: 0
        final property real progress: 0
        final property real rotationAngle: 0
        final property real continuousRotation

        // qmllint disable missing-property
        final readonly property Morph morph: Morph {
            start: control.polygons[control.contentItem.activeIndex]
            end: control.polygons[(control.contentItem.activeIndex + 1) % control.polygons.length]
        }

        implicitWidth: 48.0
        implicitHeight: 48.0

        onColorChanged: requestPaint()
        onMorphChanged: requestPaint()
        onProgressChanged: requestPaint()
        onScaleFactorChanged: requestPaint()

        rotation: (progress * 90.0) + rotationAngle + continuousRotation

        PropertyAnimation on continuousRotation {
            running: control.running
            loops: Animation.Infinite
            from: 0.0
            to: 360.0
            duration: 4666
        }

        SequentialAnimation {
            running: control.running
            loops: Animation.Infinite
            NumberAnimation {
                target: control.contentItem
                property: "progress"
                from: 0.0
                to: 1.0
                duration: 650
                easing.type: Easing.InOutCubic
            }
            ScriptAction {
                script: {
                    control.contentItem.activeIndex = (control.contentItem.activeIndex + 1) % control.polygons.length;
                    control.contentItem.rotationAngle = (control.contentItem.rotationAngle + 90.0) % 360.0;
                }
            }
        }
        // qmllint enable missing-property

        onPaint: {
            const cubics = morph.asCubics(progress);

            const ctx = getContext("2d");
            ctx.resetTransform();
            ctx.clearRect(0, 0, width, height);

            const size = Math.min(width, height);
            const scale = size * scaleFactor;

            ctx.translate((width - scale) / 2, (height - scale) / 2);
            ctx.scale(scale, scale);
            console.log(width, scale);

            ctx.fillStyle = color;

            ctx.beginPath();

            ctx.moveTo(cubics[0].anchor0X, cubics[0].anchor0Y);

            for (const cubic of cubics) {
                ctx.bezierCurveTo(cubic.control0X, cubic.control0Y, cubic.control1X, cubic.control1Y, cubic.anchor1X, cubic.anchor1Y);
            }

            ctx.closePath();

            ctx.fill();
        }
    }
}

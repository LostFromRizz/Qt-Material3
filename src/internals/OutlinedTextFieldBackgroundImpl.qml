pragma ComponentBehavior: Bound
import QtQuick

Rectangle {
    id: background
    required property real stopX
    required property bool hasLabel
    required property bool floatingLabel

    required property real labelWidth

    required property real outlineWidth
    required property color outlineColor
    required property real spacing

    border.color: outlineColor
    border.width: !hasLabel ? outlineWidth : -1

    Loader {
        anchors.fill: parent
        active: background.hasLabel
        Canvas {
            id: outline
            anchors.fill: parent

            property alias radius: background.radius
            property alias topLeftRadius: background.topLeftRadius
            property alias bottomLeftRadius: background.bottomLeftRadius
            property alias topRightRadius: background.topRightRadius
            property alias bottomRightRadius: background.bottomRightRadius

            property alias outlineWidth: background.outlineWidth
            property alias outlineColor: background.outlineColor

            property alias gapX: background.stopX
            property alias gapWidth: background.spacing
            property alias addGap: background.floatingLabel

            onRadiusChanged: requestPaint()
            onTopLeftRadiusChanged: requestPaint()
            onBottomLeftRadiusChanged: requestPaint()
            onTopRightRadiusChanged: requestPaint()
            onBottomRightRadiusChanged: requestPaint()
            onOutlineWidthChanged: requestPaint()
            onOutlineColorChanged: requestPaint()
            onGapXChanged: requestPaint()
            onGapWidthChanged: requestPaint()
            onAddGapChanged: requestPaint()
            onWidthChanged: requestPaint()
            onHeightChanged: requestPaint()

            onPaint: {
                let ctx = getContext("2d");

                ctx.clearRect(0, 0, width, height);

                let halfBorderWidth = outlineWidth / 2;

                let x = halfBorderWidth;
                let y = halfBorderWidth;

                let w = width - outlineWidth;
                let h = height - outlineWidth;

                ctx.strokeStyle = outlineColor;
                ctx.lineWidth = outlineWidth;
                ctx.lineCap = "round";

                ctx.beginPath();

                if (addGap) {
                    let gapEnd = gapX + gapWidth;

                    let arcEndX = x + topLeftRadius;
                    let startX = Math.max(gapEnd, arcEndX);
                    ctx.moveTo(startX, y);

                    drawCorners(ctx, w, h, x, y);

                    let endX = Math.min(gapX, x + w - topRightRadius);

                    if (endX > arcEndX) {
                        ctx.lineTo(endX, y);
                    }
                } else {
                    //draw outline normally
                    ctx.moveTo(x + topLeftRadius, y);
                    drawCorners(ctx, w, h, x, y);
                }
                ctx.stroke();
            }

            function drawCorners(ctx, w, h, x, y) {
                // top right corner
                ctx.lineTo(x + w - topRightRadius, y);
                ctx.arcTo(x + w, y, x + w, y + topRightRadius, topRightRadius);

                // bottom right corner
                ctx.lineTo(x + w, y + h - bottomRightRadius);
                ctx.arcTo(x + w, y + h, x + w - bottomRightRadius, y + h, bottomRightRadius);

                // bottom left corner
                ctx.lineTo(x + bottomLeftRadius, y + h);
                ctx.arcTo(x, y + h, x, y + h - bottomLeftRadius, bottomLeftRadius);

                // top left corner
                ctx.lineTo(x, y + topLeftRadius);
                ctx.arcTo(x, y, x + topLeftRadius, y, topLeftRadius);
            }
        }
    }

    // Text {
    //     id: label
    //     text: background.labelText
    //     font: background.labelFont
    //     color: background.labelColor
    //     x: background.shrinkLabel ? ((outline.gapWidth - implicitWidth) / 2) + background.horizontalPadding : background.horizontalPadding
    //     y: background.shrinkLabel ? -(implicitHeight / 2) : (background.height - implicitHeight) / 2
    //
    //     Binding {
    //         background {
    //             implicitLabelHeight: label.implicitHeight
    //             implicitLabelWidth: label.implicitWidth
    //         }
    //     }
    //
    //     Behavior on y {
    //         id: __labelAnimation__
    //     }
    // }
}

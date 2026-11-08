import QtQuick

Text {
    id: icon

    enum Align {
        Center,
        TopCenter,
        TopLeft,
        BottomLeft,
        BottomRight,
        BottomCenter,
        TopRight
    }

    property int fill
    property real grade
    property alias name: icon.text
    property alias fontWeight: icon.font.weight
    property alias size: icon.font.pixelSize
    property alias family: icon.font.family

    property int alignment: Icon.Align.Center

    verticalAlignment: switch (alignment) {
    case Icon.Align.TopLeft:
    case Icon.Align.TopRight:
    case Icon.Align.TopCenter:
        return Text.AlignTop;
    case Icon.Align.BottomLeft:
    case Icon.Align.BottomRight:
    case Icon.Align.BottomCenter:
        return Text.AlignBottom;
    case Icon.Align.Center:
    default:
        return Text.AlignVCenter;
    }

    horizontalAlignment: switch (alignment) {
    case Icon.Align.TopLeft:
    case Icon.Align.BottomLeft:
        return Text.AlignLeft;
    case Icon.Align.TopRight:
    case Icon.Align.BottomRight:
        return Text.AlignRight;
    case Icon.Align.TopCenter:
    case Icon.Align.BottomCenter:
    case Icon.Align.Center:
    default:
        return Text.AlignHCenter;
    }

    font.pixelSize: 20
    font.family: "Material Symbols Rounded"
    font.variableAxes: ({
            FILL: icon.fill,
            GRAD: icon.grade,
            opsz: fontInfo.pixelSize,
            wght: fontInfo.weight
        })
}

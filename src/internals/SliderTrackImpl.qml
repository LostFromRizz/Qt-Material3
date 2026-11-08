pragma ComponentBehavior: Bound

import QtQuick
import QtQml.Models
import Material3

Item {
    id: track
    enum Type {
        Standard,
        Ranged,
        Centered
    }

    enum IconAlignment {
        Start,
        Middle,
        End
    }

    final required property int type
    final required property Component tickItem
    final required property Component stopIndicator
    final required property list<real> stepsFractions

    final required property real visualPosition
    final required property bool horizontal
    final required property real spacing
    final required property real handleWidth
    final required property var icon
    final required property real trackHeight

    final property alias activeTrackColor: activeTrack.color
    final property alias inactiveTrackColor: inactiveTrack.color
    final property color activeTickColor
    final property color inactiveTickColor

    final property int iconAlignment: SliderTrackImpl.End

    final readonly property real handleStart: horizontal ? visualPosition * (width - handleWidth - spacing * 2) : visualPosition * (height - handleWidth - spacing * 2)
    final readonly property real handleEnd: handleStart + handleWidth + spacing * 2
    final readonly property real handleCenter: (handleWidth / 2) + spacing

    final readonly property real sliderLength: horizontal ? width : height
    final readonly property real centerAxis: sliderLength / 2

    final readonly property real innerRadius: 2.0
    final readonly property real radius: Material.sliderCornerRadius(trackHeight)

    Rectangle {
        id: inactiveTrack
        x: track.horizontal ? track.handleEnd : 0
        y: track.horizontal ? (track.height - height) / 2 : 0
        width: track.horizontal ? track.width - x : track.trackHeight
        height: track.horizontal ? track.trackHeight : track.handleStart
        topLeftRadius: track.horizontal ? track.innerRadius : track.radius
        bottomRightRadius: track.horizontal ? track.radius : track.innerRadius
        topRightRadius: track.radius
    }

    Rectangle {
        id: activeTrack
        y: track.horizontal ? (track.height - height) / 2 : track.handleEnd
        width: track.horizontal ? track.handleStart : track.trackHeight
        height: track.horizontal ? track.trackHeight : track.height - y
        topRightRadius: track.innerRadius
        bottomRightRadius: track.horizontal ? track.innerRadius : track.radius
        topLeftRadius: track.horizontal ? track.radius : track.innerRadius
        bottomLeftRadius: track.radius
    }

    Repeater {
        id: repeater

        model: ListModel {
            id: ticks

            function calculateTicks(forEach: var): void {
                for (let index = 0; index < track.stepsFractions.length; index++) {
                    const fraction = track.stepsFractions[index];

                    const isCentered = track.type == SliderTrackImpl.Type.Centered;
                    const isRanged = track.type == SliderTrackImpl.Type.Ranged;

                    // Skip endpoints
                    if (track.stopIndicator !== null) {
                        const isStopIndicatorAtStart = (isCentered || isRanged) && index == 0;
                        if (isStopIndicatorAtStart || index === track.stepsFractions.length - 1)
                            continue;
                    }

                    const first = track.stepsFractions[0];
                    const last = track.stepsFractions[track.stepsFractions.length - 1];

                    const isStartEdge = first === 0 || first === last;
                    const isEndEdge = track.visualPosition === first || track.visualPosition === last;

                    const activeEndPx = MInternals.lerp(track.radius, track.sliderLength - track.radius, track.visualPosition);

                    const tickCenterPx = MInternals.lerp(track.radius, track.sliderLength - track.radius, fraction);

                    const centerGap = {
                        min: track.centerAxis - track.handleCenter,
                        max: track.centerAxis + track.handleCenter
                    };

                    const endGap = {
                        min: activeEndPx - track.handleCenter,
                        max: activeEndPx + track.handleCenter
                    };

                    if (isCentered && tickCenterPx >= centerGap.min && tickCenterPx <= centerGap.max) {
                        continue;
                    }

                    if (tickCenterPx >= endGap.min && tickCenterPx <= endGap.max) {
                        continue;
                    }

                    const isActive = track.horizontal ? tickCenterPx >= 0 && tickCenterPx <= (activeEndPx - track.handleCenter) : activeEndPx <= tickCenterPx;
                    // ticks.append();
                    forEach({
                        position: tickCenterPx,
                        tickColor: isActive ? track.activeTickColor : track.inactiveTickColor
                    });
                }
            }

            readonly property Connections __connections__: Connections {
                target: track
                property bool updating: false
                function onStepsFractionsChanged(): void {
                    ticks.clear();
                    ticks.calculateTicks((_, data) => ticks.append(data));
                }
                function onHeightChanged(): void {
                    ticks.calculateTicks((index, data) => ticks.set(index, data));
                }
                function onWidthChanged(): void {
                    ticks.calculateTicks((index, data) => ticks.set(index, data));
                }
                function onVisualPositionChanged(): void {
                    ticks.calculateTicks((index, data) => ticks.set(index, data));
                }
            }

            Component.onCompleted: {
                if (ticks.count === 0) {
                    ticks.calculateTicks((_, data) => ticks.append(data));
                }
            }
        }
        onItemAdded: function (index, item): void {
            const pos = ticks.get(index).position ?? 0;
            item.x = Qt.binding(() => track.horizontal ? pos : (track.width - item.width) / 2);
            item.y = Qt.binding(() => track.horizontal ? (track.height - item.height) / 2 : pos);
        }
        delegate: track.tickItem
    }

    Instantiator {
        id: stopIndicator
        property bool isActive: {
            const item = object ? object as Item : null;
            return track.horizontal ? (item?.x ?? 0) <= track.handleStart : (item?.y ?? 0) >= track.handleStart;
        }
        onIsActiveChanged: setTickColor()
        function setTickColor(): void {
            model.setProperty(0, "indicatorColor", isActive ? track.activeTickColor.toString() : track.inactiveTickColor.toString());
        }
        model: ListModel {
            ListElement {
                tickColor: "transparent"
            }
        }
        delegate: track.stopIndicator
        onObjectAdded: function (_, item): void {
            setTickColor();
            item.parent = track;
            item.x = Qt.binding(() => track.horizontal ? track.width - track.radius : (track.center.x - item.width) / 2);
            item.y = Qt.binding(() => track.horizontal ? (track.center.y - item.height) / 2 : track.radius);
            item.visible = Qt.binding(() => !(track.horizontal ? item.x >= track.handleStart && item.x <= track.handleEnd : item.y <= track.handleStart && item.y >= track.handleEnd));
        }
    }

    final readonly property point center: Qt.point(track.width - ((track.width - track.trackHeight) / 2), track.height - ((track.height - track.trackHeight) / 2))

    final readonly property bool iconActive: _icon.info.inActiveTrack

    Icon {
        id: _icon
        readonly property real margin: Material.sliderIconMargin(track.trackHeight)

        readonly property var info: {
            let x, y, inActiveTrack;

            const height = track.icon.height;
            const width = track.icon.width;
            const radius = track.radius;
            const handleWidthWithGap = track.handleWidth + track.spacing * 2;
            const handleEnd = track.handleEnd;

            if (track.horizontal) {
                y = (track.center.y - track.icon.height) / 2;

                const startLimit = radius + width + (margin * 2) + handleWidthWithGap;
                const endLimit = track.width - radius - width - (margin * 2);

                switch (track.icon.alignment) {
                case SliderTrackImpl.Start:
                    inActiveTrack = handleEnd > startLimit;
                    x = inActiveTrack ? radius + margin : handleEnd + margin;
                    break;
                case SliderTrackImpl.Middle:
                    inActiveTrack = handleEnd > startLimit;
                    x = inActiveTrack ? handleEnd - handleWidthWithGap - margin - width : handleEnd + margin;
                    break;
                case SliderTrackImpl.End:
                default:
                    inActiveTrack = handleEnd > endLimit;
                    x = inActiveTrack ? handleEnd - handleWidthWithGap - margin - width : track.width - radius - width - margin;
                    break;
                }
            } else {
                x = (track.center.x - track.icon.width) / 2;

                const startLimit = track.height - radius - height - (margin * 2);
                const endLimit = radius + height + (margin * 2);

                switch (track.iconAlignment) {
                case SliderTrackImpl.Start:
                    inActiveTrack = handleEnd < startLimit;
                    y = inActiveTrack ? track.height - radius - margin - height : handleEnd - handleWidthWithGap - margin - height;
                    break;
                case SliderTrackImpl.Middle:
                    inActiveTrack = handleEnd < startLimit;
                    y = inActiveTrack ? handleEnd + margin : handleEnd - handleWidthWithGap - margin - height;
                    break;
                case SliderTrackImpl.End:
                default:
                    inActiveTrack = handleEnd - handleWidthWithGap < endLimit;
                    y = inActiveTrack ? handleEnd + margin : track.radius + margin;
                    break;
                }
            }

            return {
                x: x,
                y: y,
                inActiveTrack: inActiveTrack
            };
        }

        x: info.x
        y: info.y
        size: Math.max(track.icon.height, track.icon.width)
        name: track.icon.name
        color: MInternals.iconColorResolved(track.icon) ? track.icon.color : info.inActiveTrack ? track.activeTickColor : track.inactiveTickColor
        visible: {
            if (track.icon.name.length <= 0 || track.icon.size <= 0) {
                return false;
            }

            if (track.horizontal) {
                return (track.width >= track.icon.width + (margin * 2) + track.handleCenter) && track.trackHeight >= track.icon.height;
            } else {
                return (track.height >= track.icon.height + (margin * 2) + track.handleCenter) && track.trackHeight >= track.icon.width;
            }
        }
    }
}

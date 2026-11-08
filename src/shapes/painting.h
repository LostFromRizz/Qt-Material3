#ifndef MATERIAL_SHAPES_PAINTING_H
#define MATERIAL_SHAPES_PAINTING_H

#include "rounded_polygon.h"
#include <QPainterPath>

namespace material::shapes {

QPainterPath pathFromCubics(QPainterPath &path,
                            const std::span<const shapes::Cubic> &cubics,
                            int startAngle = 270, bool repeatPath = false,
                            qreal rotationPivotX = 0, qreal rotationPivotY = 0

);

QPainterPath roundedPolygonPath(QPainterPath &path,
                                const RoundedPolygon &polygon,
                                int startAngle = 270, bool repeatPath = false);

void context2DPathFromCubics(QJSValue ctx,
                             const std::span<const shapes::Cubic> &cubics,
                             int startAngle = 270, bool repeatPath = false,
                             qreal rotationPivotX = 0,
                             qreal rotationPivotY = 0);

} // namespace material::shapes

#endif // MATERIAL_SHAPES_PAINTING_H

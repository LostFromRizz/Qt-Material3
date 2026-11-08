#include "painting.h"
#include <qjslist.h>
#include <qjsvalue.h>

using namespace material;

namespace {
inline float radiansToDegrees(float radians) {
  return radians * 180.0 / std::numbers::pi_v<float>;
}

} // namespace

QPainterPath shapes::pathFromCubics(
    QPainterPath &path, const std::span<const shapes::Cubic> &cubics,
    int startAngle, bool repeatPath, qreal rotationPivotX, qreal rotationPivotY

) {

  path.clear();

  for (int i = 0; i < 1 + static_cast<int>(repeatPath); ++i) {
    bool first = true;
    for (const auto &cubic : cubics) {
      if (first) {
        path.moveTo(cubic.anchor0X(), cubic.anchor0Y());
        first = false;
      }
      path.cubicTo(cubic.control0X(), cubic.control0Y(), cubic.control1X(),
                   cubic.control1Y(), cubic.anchor1X(), cubic.anchor1Y());
    }
  }

  if (startAngle != 0 && !cubics.empty()) {
    float angleToFirstCubic =
        radiansToDegrees(std::atan2(cubics[0].anchor0Y() - rotationPivotY,
                                    cubics[0].anchor0X() - rotationPivotX));

    // Rotate the path to start from the given angle.
    QTransform rotation;
    rotation.rotate(-angleToFirstCubic + startAngle);
    return rotation.map(path);
    return path;
  }
  return path;
}

QPainterPath shapes::roundedPolygonPath(QPainterPath &path,
                                        const RoundedPolygon &polygon,
                                        int startAngle, bool repeatPath) {
  return pathFromCubics(path, polygon.cubics(), startAngle, repeatPath,
                        polygon.centerX(), polygon.centerY());
}

void shapes::context2DPathFromCubics(
    QJSValue ctx, const std::span<const shapes::Cubic> &cubics, int startAngle,
    bool repeatPath, qreal rotationPivotX, qreal rotationPivotY) {

  if (cubics.size() == 0) {
    return;
  }

  QJSValueList args;
  args.reserve(6);

  QJSValue result;
  ctx.property("beginPath").callWithInstance(ctx);

  for (int i = 0; i < 1 + static_cast<int>(repeatPath); ++i) {
    bool first = true;
    for (const auto &cubic : cubics) {
      if (first) {
        args.clear();
        args.append(cubic.anchor0X());
        args.append(cubic.anchor0Y());

        ctx.property("moveTo").callWithInstance(ctx, args);
        first = false;
      }

      args.clear();
      args.append(cubic.control0X());
      args.append(cubic.control0Y());
      args.append(cubic.control1X());

      args.append(cubic.control1Y());
      args.append(cubic.anchor1X());
      args.append(cubic.anchor1Y());

      ctx.property("bezierCurveTo").callWithInstance(ctx, args);
    }
  }

  if (startAngle != 0) {
    float angleToFirstCubic =
        radiansToDegrees(std::atan2(cubics[0].anchor0Y() - rotationPivotY,
                                    cubics[0].anchor0X() - rotationPivotX));

    args.clear();
    args.append(-angleToFirstCubic + startAngle);

    ctx.property("rotate").call(args);
  }

  ctx.property("closePath").callWithInstance(ctx);
}

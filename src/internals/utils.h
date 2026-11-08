#ifndef MATERIAL_INTERNALS_UTILS_H
#define MATERIAL_INTERNALS_UTILS_H

#include <QtCore/qeasingcurve.h>
#include <qassert.h>
#include <qfloat16.h>
#include <qmath.h>
#include <qpoint.h>

namespace material::internals::utils {
struct AnimSpec {
  QEasingCurve curve;
  int duration;
};

constexpr inline int roundToInt(double x) {
  if (std::isnan(x)) {
    return 0;
  }

  if (x <= std::numeric_limits<int>::min()) {
    return std::numeric_limits<int>::min();
  }

  if (x >= std::numeric_limits<int>::max()) {
    return std::numeric_limits<int>::max();
  }

  return static_cast<int>(std::floor(x + 0.5));
}

const QEasingCurve inline cubicBezierCurve(const QPointF &c1, const QPointF &c2,
                                           const QPointF &endPoint) {
  auto easingCurve = QEasingCurve(QEasingCurve::BezierSpline);
  easingCurve.addCubicBezierSegment(c1, c2, endPoint);
  return easingCurve;
}

constexpr inline qreal lerp(qreal start, qreal stop, qreal value) {
  return (1 - value) * start + value * stop;
}

static constexpr qreal
evaluateIndeterminateSegment(qreal value, int delayMs, int durationMs,
                             int totalDurationMs, const QEasingCurve &easing) {
  auto start = static_cast<qreal>(delayMs) / totalDurationMs;
  auto end = static_cast<qreal>((delayMs + durationMs)) / totalDurationMs;
  if (value < start)
    return 0.0;
  if (value > end)
    return 1.0;

  auto currentProgress = (value - start) / (end - start);
  return easing.valueForProgress(currentProgress);
}

} // namespace material::internals::utils

#endif // MATERIAL_INTERNALS_UTILS_H

#include "cubic.h"
#include "utils.h"

using namespace material::shapes;

// QDebug Cubic::operator<<(QDebug debug, const Cubic &cubic) {
//   QDebugStateSaver saver(debug);
//   debug.nospace() << "Cubic { points: " << cubic.m_points << " }";
//   return debug;
// }

Point Cubic::pointOnCurve(float t) const noexcept {
  auto u = 1.0f - t;
  return Point(anchor0X() * (u * u * u) + control0X() * (3.0f * t * u * u) +
                   control1X() * (3.0f * t * t * u) + anchor1X() * (t * t * t),
               anchor0Y() * (u * u * u) + control0Y() * (3.0f * t * u * u) +
                   control1Y() * (3.0f * t * t * u) + anchor1Y() * (t * t * t));
}

std::pair<Cubic, Cubic> Cubic::split(float t) const noexcept {
  float u = 1.0f - t;
  auto pointOnCurve = this->pointOnCurve(t);
  return std::make_pair(
      Cubic(anchor0X(), anchor0Y(), anchor0X() * u + control0X() * t,
            anchor0Y() * u + control0Y() * t,
            anchor0X() * (u * u) + control0X() * (2.0f * u * t) +
                control1X() * (t * t),
            anchor0Y() * (u * u) + control0Y() * (2.0f * u * t) +
                control1Y() * (t * t),
            pointOnCurve.x(), pointOnCurve.y()),
      Cubic(pointOnCurve.x(), pointOnCurve.y(),
            control0X() * (u * u) + control1X() * (2.0f * u * t) +
                anchor1X() * (t * t),
            control0Y() * (u * u) + control1Y() * (2.0f * u * t) +
                anchor1Y() * (t * t),
            control1X() * u + anchor1X() * t, control1Y() * u + anchor1Y() * t,
            anchor1X(), anchor1Y()));
}

void Cubic::lerp(const Cubic &c1, const Cubic &c2, float progress) noexcept {
  for (size_t i = 0; i < m_points.size(); ++i) {
    m_points[i] = shape_utils::lerp(c1.m_points[i], c2.m_points[i], progress);
  }
}

void Cubic::calculateBounds(Cubic::BoundsArray &bounds,
                            bool approx) const noexcept {
  if (zeroLength()) {
    bounds[0] = anchor0X();
    bounds[1] = anchor0Y();
    bounds[2] = anchor0X();
    bounds[3] = anchor0Y();
    return;
  }

  float minX = std::min(anchor0X(), anchor1X());
  float minY = std::min(anchor0Y(), anchor1Y());
  float maxX = std::max(anchor0X(), anchor1X());
  float maxY = std::max(anchor0Y(), anchor1Y());

  if (approx) {
    // Approximate bounds use the bounding box of all anchors and controls
    bounds[0] = std::min(minX, std::min(control0X(), control1X()));
    bounds[1] = std::min(minY, std::min(control0Y(), control1Y()));
    bounds[2] = std::max(maxX, std::max(control0X(), control1X()));
    bounds[3] = std::max(maxY, std::max(control0Y(), control1Y()));
    return;
  }

  {
    // Find the derivative, which is a quadratic Bezier. Then we can solve for t
    // using the quadratic formula
    float xa = -anchor0X() + 3 * control0X() - 3 * control1X() + anchor1X();
    float xb = 2 * anchor0X() - 4 * control0X() + 2 * control1X();
    float xc = -anchor0X() + control0X();

    auto updateMinAndMaxX = [minX, maxX, this](float t) mutable {
      if (t >= 0.0 && t <= 1.0) {
        const float x = pointOnCurve(t).x();

        if (x < minX) {
          minX = x;
        } else if (x > maxX) {
          maxX = x;
        }
      }
    };

    if (zeroIsh(xa)) {
      // Try Muller's method instead; it can find a single root when a is 0
      if (xb != 0.0) {
        float t = 2.0 * xc / (-2.0 * xb);
        updateMinAndMaxX(t);
      }
    } else {
      float xs = xb * xb - 4.0 * xa * xc;
      if (xs >= 0) {
        float t1 = (-xb + std::sqrt(xs)) / (2.0 * xa);
        updateMinAndMaxX(t1);

        float t2 = (-xb - std::sqrt(xs)) / (2.0 * xa);
        updateMinAndMaxX(t2);
      }
    }
  }

  {
    // Repeat the above for y coordinate
    float ya = -anchor0Y() + 3.0 * control0Y() - 3.0 * control1Y() + anchor1Y();
    float yb = 2.0 * anchor0Y() - 4.0 * control0Y() + 2.0 * control1Y();
    float yc = -anchor0Y() + control0Y();

    auto updateMinAndMaxY = [minY, maxY, this](float t) mutable {
      if (t >= 0.0 && t <= 1.0) {
        const float y = pointOnCurve(t).y();

        if (y < minY) {
          minY = y;
        } else if (y > maxY) {
          maxY = y;
        }
      }
    };
    if (zeroIsh(ya)) {
      // Try Muller's method instead; it can find a single root when a is 0
      if (yb != 0.0) {
        float t = 2.0 * yc / (-2.0 * yb);
        updateMinAndMaxY(t);
      }
    } else {
      float ys = yb * yb - 4.0 * ya * yc;
      if (ys >= 0) {
        float t1 = (-yb + std::sqrt(ys)) / (2.0 * ya);
        updateMinAndMaxY(t1);

        float t2 = (-yb - std::sqrt(ys)) / (2.0 * ya);
        updateMinAndMaxY(t2);
      }
    }
  }

  bounds[0] = minX;
  bounds[1] = minY;
  bounds[2] = maxX;
  bounds[3] = maxY;
}

Cubic Cubic::transformed(const PointTransformer &f) const {
  Cubic newCubic = *this;
  newCubic.transform(f);
  return newCubic;
}

void Cubic::transform(const PointTransformer &f) {
  for (float ix : {0, 2, 4, 6}) {
    auto result = f(m_points[ix], m_points[ix + 1]);
    m_points[ix] = result.first;
    m_points[ix + 1] = result.second;
  }
}

Cubic Cubic::straightLine(float x0, float y0, float x1, float y1) noexcept {
  return Cubic(x0, y0, shape_utils::lerp(x0, x1, 1.0f / 3.0f),
               shape_utils::lerp(y0, y1, 1.0f / 3.0f),
               shape_utils::lerp(x0, x1, 2.0f / 3.0f),
               shape_utils::lerp(y0, y1, 2.0f / 3.0f), x1, y1);
}

Cubic Cubic::circularArc(float centerX, float centerY, float x0, float y0,
                         float x1, float y1) noexcept {
  Point p0d = Point::directionVector(x0 - centerX, y0 - centerY);
  Point p1d = Point::directionVector(x1 - centerX, y1 - centerY);
  Point rotatedP0 = p0d.rotate90();
  Point rotatedP1 = p1d.rotate90();
  bool clockwise = rotatedP0.dotProduct(Point(x1 - centerX, y1 - centerY)) >= 0;
  float cosa = p0d.dotProduct(p1d);
  if (cosa > 0.999f) /* p0 ~= p1 */
    return straightLine(x0, y0, x1, y1);
  float k = shape_utils::distance(x0 - centerX, y0 - centerY) * 4.0f / 3.0f *
            (std::sqrt(2.0f * (1.0f - cosa)) - std::sqrt(1.0f - cosa * cosa)) /
            (1.0f - cosa) * (clockwise ? 1.0f : -1.0f);
  return Cubic(x0, y0, x0 + rotatedP0.x() * k, y0 + rotatedP0.y() * k,
               x1 - rotatedP1.x() * k, y1 - rotatedP1.y() * k, x1, y1);
}

Cubic Cubic::empty(float x0, float y0) noexcept {
  return Cubic(x0, y0, x0, y0, x0, y0, x0, y0);
}

QString Cubic::toString() const {
  return QString("Cubic("
                 "anchor0: (%1, %2), "
                 "control0: (%3, %4), "
                 "control1: (%5, %6), "
                 "anchor1: (%7, %8))")
      .arg(anchor0X(), 0, 'g', 8)
      .arg(anchor0Y(), 0, 'g', 8)
      .arg(control0X(), 0, 'g', 8)
      .arg(control0Y(), 0, 'g', 8)
      .arg(control1X(), 0, 'g', 8)
      .arg(control1Y(), 0, 'g', 8)
      .arg(anchor1X(), 0, 'g', 8)
      .arg(anchor1Y(), 0, 'g', 8);
}

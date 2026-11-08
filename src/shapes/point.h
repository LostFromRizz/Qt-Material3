#ifndef MATERIAL_SHAPES_POINT_H
#define MATERIAL_SHAPES_POINT_H

#include "utils.h"
#include <cmath>
#include <qassert.h>
#include <qdebug.h>

namespace material::shapes {
class Point {
public:
  constexpr explicit Point() : m_x(0.0f), m_y(0.0f) {}
  constexpr explicit Point(float x, float y) : m_x(x), m_y(y) {}

  constexpr inline float x() const noexcept { return m_x; }
  constexpr inline float y() const noexcept { return m_y; }

  friend constexpr inline Point operator+(const Point &p1,
                                          const Point &p2) noexcept {
    return Point(p1.x() + p2.x(), p1.y() + p2.y());
  }
  friend constexpr inline Point operator-(const Point &p1,
                                          const Point &p2) noexcept {
    return Point(p1.x() - p2.x(), p1.y() - p2.y());
  }
  friend constexpr inline Point operator-(const Point &p) noexcept {
    return Point(-p.x(), -p.y());
  }

  friend constexpr inline Point operator*(const Point &p,
                                          float factor) noexcept {
    return Point(p.x() * factor, p.y() * factor);
  }

  friend constexpr inline Point operator/(const Point &p,
                                          float operand) noexcept {
    return Point(p.x() / operand, p.y() / operand);
  }

  friend constexpr inline Point operator%(const Point &p,
                                          float operand) noexcept {
    return Point(std::fmod(p.x(), operand), std::fmod(p.y(), operand));
  }
  friend constexpr inline Point operator*(float factor,
                                          const Point &p) noexcept {
    return Point(p.x() * factor, p.y() * factor);
  }

  friend constexpr inline Point operator/(float operand,
                                          const Point &p) noexcept {
    return Point(p.x() / operand, p.y() / operand);
  }

  friend constexpr inline Point operator%(float operand,
                                          const Point &p) noexcept {
    return Point(std::fmod(p.x(), operand), std::fmod(p.y(), operand));
  }

  friend constexpr inline bool operator==(const Point &lhs,
                                          const Point &rhs) noexcept {
    return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
  }

  friend constexpr inline bool operator!=(const Point &lhs,
                                          const Point &rhs) noexcept {
    return lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y;
  }

  constexpr inline const Point rotate90() const noexcept {
    return Point(-m_y, m_x);
  }

  constexpr inline const Point
  rotateDegress(float angle, const Point &center) const noexcept {
    const float a = shape_utils::toRadians(angle);
    const auto p = *this - center;
    return Point((p.m_x * std::cos(a) - p.m_y * std::sin(a)) + center.m_x,
                 (p.m_x * std::sin(a) + p.m_y * std::cos(a)) + center.m_y);
  }

  constexpr inline float distance() const noexcept {
    return shape_utils::distance(m_x, m_y);
  }

  constexpr inline float distanceSquared() const noexcept {
    return shape_utils::distanceSquared(m_x, m_y);
  }

  constexpr inline Point direction() const noexcept {
    float d = distance();
    Q_ASSERT_X(d > 0.0, "material::internals::shpaes::::Point::distancePoint",
               "Can't get the direction of a 0-length vector");
    return *this / d;
  }

  constexpr inline float dotProduct(const Point &other) const noexcept {
    return m_x * other.x() + m_y * other.m_y;
  }
  constexpr inline float dotProduct(const float otherX,
                                    const float otherY) const noexcept {
    return m_x * otherX + m_y * otherY;
  }

  constexpr inline bool clockwise(const Point &other) noexcept {
    return m_x * other.y() - m_y * other.x() > 0;
  }

  constexpr inline static Point lerp(const Point &p1, const Point &p2,
                                     float fraction) noexcept {
    return Point(shape_utils::lerp(p1.x(), p2.x(), fraction),
                 shape_utils::lerp(p1.y(), p1.y(), fraction));
  }

  constexpr inline static Point directionVector(float x, float y) noexcept {
    const auto d = shape_utils::distance(x, y);
    Q_ASSERT_X(d > 0, "material::shapes::Point::directionVector",
               "Requires distance greater than zero");
    return Point(x / d, y / d);
  }

  constexpr inline static Point directionVector(float angleRadians) noexcept {
    return Point(std::cos(angleRadians), std::sin(angleRadians));
  }

  constexpr inline static Point
  radialToCartesian(float radius, float angleRadians,
                    const Point &center = Point()) noexcept {

    return directionVector(angleRadians) * radius + center;
  }

  constexpr inline static bool convex(Point previous, Point current,
                                      Point next) {
    return (current - previous).clockwise(next - current);
  }

  inline friend QDebug operator<<(QDebug debug, const Point &point) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "Point(" << std::bit_cast<uint32_t>(point.m_x) << ", "
                    << std::bit_cast<uint32_t>(point.m_y) << ")";
    return debug;
  }

  inline QString toString() const {
    return QString("Cubic(x: %1, y: %2)")
        .arg(m_x, 0, 'g', 8)
        .arg(m_y, 0, 'g', 8);
  }

private:
  float m_x;
  float m_y;
};
} // namespace material::shapes

#endif // POINT_H

#ifndef MATERIAL_SHAPES_CUBIC_H
#define MATERIAL_SHAPES_CUBIC_H

#include "point.h"
#include "qdebug.h"
#include <QtQmlIntegration/QtQmlIntegration>
#include <array>

namespace material::shapes {
class Cubic final {
  Q_GADGET
  Q_PROPERTY(float anchor0X READ anchor0X WRITE setAnchor0X FINAL)
  Q_PROPERTY(float anchor0Y READ anchor0Y WRITE setAnchor0Y FINAL)
  Q_PROPERTY(float control0X READ control0X WRITE setControl0X FINAL)
  Q_PROPERTY(float control0Y READ control0Y WRITE setControl0Y FINAL)
  Q_PROPERTY(float control1X READ control1X WRITE setControl1X FINAL)
  Q_PROPERTY(float control1Y READ control1Y WRITE setControl1Y FINAL)
  Q_PROPERTY(float anchor1X READ anchor1X WRITE setAnchor1X FINAL)
  Q_PROPERTY(float anchor1Y READ anchor1Y WRITE setAnchor1Y FINAL)
  QML_VALUE_TYPE(cubic)
public:
  using BoundsArray = std::array<float, 4>;
  using FloatArray8 = std::array<float, 8>;
  using PointTransformer =
      std::function<std::pair<float, float>(float x, float y)>;

  constexpr inline explicit Cubic() : m_points(FloatArray8()) {}

  constexpr inline explicit Cubic(Point anchor0, Point control0, Point control1,
                                  Point anchor1)
      : m_points(FloatArray8{
            anchor0.x(),
            anchor0.y(),
            control0.x(),
            control0.y(),
            control1.x(),
            control1.y(),
            anchor1.x(),
            anchor1.y(),
        }) {}

  constexpr explicit Cubic(float anchor0X, float anchor0Y, float control0X,
                           float control0Y, float control1X, float control1Y,
                           float anchor1X, float anchor1Y

                           )
      : m_points(FloatArray8{
            anchor0X,
            anchor0Y,
            control0X,
            control0Y,
            control1X,
            control1Y,
            anchor1X,
            anchor1Y,
        }) {}

  constexpr inline explicit Cubic(FloatArray8 points) : m_points(points) {}

  static Cubic straightLine(float x0, float y0, float x1, float y1) noexcept;
  static Cubic circularArc(float centerX, float centerY, float x0, float y0,
                           float x1, float y1) noexcept;
  static Cubic empty(float x0, float y0) noexcept;

  constexpr inline const FloatArray8 &points() const noexcept {
    return m_points;
  }
  constexpr inline float anchor0X() const noexcept { return m_points[0]; }
  constexpr inline void setAnchor0X(float v) noexcept { m_points[0] = v; }
  constexpr inline float anchor0Y() const noexcept { return m_points[1]; }
  constexpr inline void setAnchor0Y(float v) noexcept { m_points[1] = v; }
  constexpr inline float control0X() const noexcept { return m_points[2]; }
  constexpr inline void setControl0X(float v) noexcept { m_points[2] = v; }
  constexpr inline float control0Y() const noexcept { return m_points[3]; }
  constexpr inline void setControl0Y(float v) noexcept { m_points[3] = v; }
  constexpr inline float control1X() const noexcept { return m_points[4]; }
  constexpr inline void setControl1X(float v) noexcept { m_points[4] = v; }
  constexpr inline float control1Y() const noexcept { return m_points[5]; }
  constexpr inline void setControl1Y(float v) noexcept { m_points[5] = v; }
  constexpr inline float anchor1X() const noexcept { return m_points[6]; }
  constexpr inline void setAnchor1X(float v) noexcept { m_points[6] = v; }
  constexpr inline float anchor1Y() const noexcept { return m_points[7]; }
  constexpr inline void setAnchor1Y(float v) noexcept { m_points[7] = v; }
  constexpr inline Cubic reverse() const noexcept {
    return Cubic(anchor1X(), anchor1Y(), control1X(), control1Y(),

                 control0X(), control0Y(), anchor0X(), anchor0Y());
  }
  constexpr friend Cubic operator+(const Cubic &lhs,
                                   const Cubic &rhs) noexcept {
    return mapIndexed(lhs,
                      [rhs](size_t i, float v) { return v + rhs.m_points[i]; });
  }
  constexpr inline friend Cubic operator*(const Cubic &cubic,
                                          float x) noexcept {
    return map(cubic, [x](float v) { return v * x; });
  }
  constexpr inline friend Cubic operator*(const Cubic &cubic, int x) noexcept {
    return map(cubic, [x](float v) { return v * x; });
  }
  constexpr inline friend Cubic operator/(const Cubic &cubic,
                                          float y) noexcept {
    return map(cubic, [y](float v) { return v / y; });
  }
  constexpr inline friend Cubic operator/(const Cubic &cubic, int y) noexcept {
    return map(cubic, [y](float v) { return v / y; });
  }
  constexpr inline friend bool operator==(const Cubic &lhs,
                                          const Cubic &rhs) noexcept {
    return lhs.m_points == rhs.m_points;
  }
  constexpr inline friend bool operator!=(const Cubic &lhs,
                                          const Cubic &rhs) noexcept {
    return lhs.m_points != rhs.m_points;
  }

  constexpr inline bool zeroLength() const noexcept {
    return std::abs(anchor0X() - anchor1X()) < shape_utils::DISTANCE_EPSILON &&
           std::abs(anchor0Y() - anchor1Y()) < shape_utils::DISTANCE_EPSILON;
  }

  Point pointOnCurve(float t) const noexcept;
  std::pair<Cubic, Cubic> split(float t) const noexcept;
  void calculateBounds(BoundsArray &bounds, bool approx = false) const noexcept;
  Cubic transformed(const PointTransformer &) const;
  void transform(const PointTransformer &);
  void lerp(const Cubic &c1, const Cubic &c2, float progress) noexcept;

  inline friend QDebug operator<<(QDebug debug, const Cubic &cubic) {
    QDebugStateSaver saver(debug);
    // clang-format off
    debug.nospace() << "Cubic(" <<
    "anchor0: (" << std::bit_cast<uint32_t>(cubic.anchor0X()) << ", " << std::bit_cast<uint32_t>(cubic.anchor0Y()) << "), "
    "control0: (" << std::bit_cast<uint32_t>(cubic.control0X()) << ", " << std::bit_cast<uint32_t>(cubic.control0Y()) << "), " 
    "control1: (" << std::bit_cast<uint32_t>(cubic.control1X()) << ", " << std::bit_cast<uint32_t>(cubic.control1Y()) << "), " 
    "anchor1: (" << std::bit_cast<uint32_t>(cubic.anchor1X()) << ", " << std::bit_cast<uint32_t>(cubic.anchor1Y()) << ")"
     << ")";
    // clang-format on
    return debug;
  }

  QString toString() const;

private:
  template <typename Func>
  constexpr friend inline Cubic map(const Cubic &cubic, Func func) {
    auto result = FloatArray8();
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = func(cubic.m_points[i]);
    }
    return Cubic(result);
  }

  template <typename Func>
  constexpr friend inline Cubic mapIndexed(const Cubic &cubic, Func func) {
    auto result = FloatArray8();
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = func(i, cubic.m_points[i]);
    }
    return Cubic(result);
  }

  constexpr inline bool zeroIsh(float value) const noexcept {
    return std::abs(value) < shape_utils::DISTANCE_EPSILON;
  }

  FloatArray8 m_points;
};
} // namespace material::shapes

#endif // MATERIAL_SHAPES_CUBIC_H

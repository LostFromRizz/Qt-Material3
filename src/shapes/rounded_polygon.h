#ifndef MATERIAL_SHAPES_ROUNDED_POLYGON_H
#define MATERIAL_SHAPES_ROUNDED_POLYGON_H

#include "corner_rounding.h"
#include "matrix.h"
#include "shapes_features.h"
#include <QtQml/qqml.h>
#include <array>
#include <internals/collections/slice.h>
#include <optional>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#include <vector>

namespace material::shapes {
class RoundedPolygon final : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("")
public:
  static RoundedPolygon *
  Create(internals::collections::Slice<Feature> &&features, float centerX,
         float centerY) noexcept;

  static RoundedPolygon *
  Create(const std::span<const float> &vertices,
         const CornerRounding &rounding = CornerRounding::Unbounded,
         std::optional<std::span<const CornerRounding>> perVertexRounding =
             std::nullopt,
         const float centerX = std::numeric_limits<float>::min(),
         const float centerY = std::numeric_limits<float>::min()) noexcept;

  static RoundedPolygon *
  Create(int verticesNum = 3,
         const CornerRounding &rounding = CornerRounding::Unbounded,
         std::optional<std::span<const CornerRounding>> perVertexRounding =
             std::nullopt,
         const float radius = 1.0, const float centerX = 0.0,
         const float centerY = 0.0) noexcept;

  static RoundedPolygon *Circle(int verticesNum = 8, const float radius = 1.0,
                                const float centerX = 0.0,
                                const float centerY = 0.0) noexcept;

  static RoundedPolygon *
  Rectangle(float width = 2.0, float height = 2.0,
            const CornerRounding &rounding = CornerRounding::Unbounded,
            std::optional<std::span<const CornerRounding>> perVertexRounding =
                std::nullopt,
            const float centerX = 0.0, const float centerY = 0.0) noexcept;

  static RoundedPolygon *
  Star(int verticesPerRadius, float radius = 1.0f, float innerRadius = 0.5f,
       const CornerRounding &rounding = CornerRounding::Unbounded,
       const std::optional<CornerRounding> &innerRounding = std::nullopt,
       std::optional<std::span<const CornerRounding>> perVertexRounding =
           std::nullopt,
       const float centerX = 0.0, const float centerY = 0.0);

  static RoundedPolygon *
  PillStar(float width = 2.0f, float height = 1.0f, int verticesPerRadius = 8,
           float innerRadius = 0.5f,
           const CornerRounding &rounding = CornerRounding::Unbounded,
           const std::optional<CornerRounding> &innerRounding = std::nullopt,
           std::optional<std::span<const CornerRounding>> perVertexRounding =
               std::nullopt,
           float vertexSpacing = 0.5f, float startLocation = 0.0f,
           float centerX = 0.0f, float centerY = 0.0f);

  RoundedPolygon(const RoundedPolygon &) = delete;
  RoundedPolygon &operator=(const RoundedPolygon &) = delete;

  RoundedPolygon(RoundedPolygon &&) = delete;
  RoundedPolygon &operator=(RoundedPolygon &&) = delete;

  inline friend bool operator==(const RoundedPolygon &lhs,
                                const RoundedPolygon &rhs) noexcept {
    return lhs.m_center == rhs.m_center && lhs.m_features == rhs.m_features;
  }

  inline friend bool operator!=(const RoundedPolygon &lhs,
                                const RoundedPolygon &rhs) noexcept {
    return !(lhs == rhs);
  }

  inline Point center() const noexcept { return m_center; }
  inline float centerX() const noexcept { return m_center.x(); }
  inline float centerY() const noexcept { return m_center.y(); }

  inline const std::vector<Cubic> &cubics() const noexcept { return m_cubics; }
  inline const internals::collections::Slice<Feature> &
  features() const noexcept {
    return m_features;
  }

  inline RoundedPolygon clone() const {
    auto cubicsClone = m_cubics;
    auto featuresClone =
        internals::collections::Slice<Feature>(m_features.size());
    for (std::size_t i = 0; i < m_features.size(); ++i) {
      featuresClone[i] = m_features[i].clone();
    }
    return RoundedPolygon(std::move(cubicsClone), std::move(featuresClone),
                          m_center);
  }

  void calculateMaxBounds(Cubic::BoundsArray &bounds) const noexcept;
  void calculateBounds(Cubic::BoundsArray &bounds,
                       bool approx = true) const noexcept;

  Q_INVOKABLE void toContext2DPath(QJSValue ctx, qreal width, qreal height);

  Q_INVOKABLE QList<qreal> inline qcalculateMaxBounds() const noexcept;

  Q_INVOKABLE
  QList<qreal> inline qcalculateBounds(bool approx = true) const noexcept;

  Q_INVOKABLE void normalize();

  RoundedPolygon *normalized() const;

  inline void transform(const Matrix &matrix);
  void transform(const Cubic::PointTransformer &);

  inline RoundedPolygon *transformed(const Matrix &matrix) const;
  RoundedPolygon *transformed(const Cubic::PointTransformer &) const;

  inline friend QDebug operator<<(QDebug debug, const RoundedPolygon &polygon) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "RoundedPolygon(features: " << polygon.m_features
                    << ", cubics: " << polygon.m_cubics
                    << ", center: " << polygon.m_center << ")";
    return debug;
  }

  Q_INVOKABLE QString toString() const;

private:
  explicit RoundedPolygon(const std::vector<Cubic> &&cubics,
                          internals::collections::Slice<Feature> &&features,
                          const Point &point);

  class RoundedCorner final {
  public:
    explicit RoundedCorner(Point p0 = Point(), Point p1 = Point(),
                           Point p2 = Point(),
                           std::optional<CornerRounding> rounding = std::nullopt

    );

    inline float expectedRoundCut() const noexcept {
      return m_expectedRoundCut;
    }
    inline float expectedCut() const noexcept {
      return ((1.0f + m_smoothing) * m_expectedRoundCut);
    }

    internals::collections::Slice<Cubic> getCubics(float allowedCut0,
                                                   float allowedCut1);

    float calculateActualSmoothingValue(float allowedCut) const noexcept;

    Cubic computeFlankingCurve(float actualRoundCut,
                               float actualSmoothingValues, const Point &corner,
                               const Point &sideStart,
                               const Point &circleSegmentIntersection,
                               const Point &otherCircleSegmentIntersection,
                               const Point &circleCenter,
                               float actualR) const noexcept;

    std::optional<Point> lineIntersection(const Point &p0, const Point &d0,
                                          const Point &p1,
                                          const Point &d1) const noexcept;

    Point p0;
    Point p1;
    Point p2;
    std::optional<CornerRounding> rounding;

    Point m_d1;
    Point m_d2;
    Point m_center;
    float m_cornerRadius = 0.0f;
    float m_smoothing = 0.0f;
    float m_cosAngle = 0.0f;
    float m_sinAngle = 0.0f;
    float m_expectedRoundCut = 0.0f;
  };

  inline static auto matrixTransform(const Matrix &matrix) {
    return [matrix](float x, float y) {
      const auto p = matrix.map(Point(x, y));
      return std::pair{p.x(), p.y()};
    };
  }

  std::vector<Cubic> m_cubics;
  internals::collections::Slice<Feature> m_features;
  Point m_center;
};

void material::shapes::RoundedPolygon::transform(const Matrix &matrix) {
  transform(matrixTransform(matrix));
}

material::shapes::RoundedPolygon *
material::shapes::RoundedPolygon::transformed(const Matrix &matrix) const {
  return transformed(matrixTransform(matrix));
}

QList<qreal>
material::shapes::RoundedPolygon::qcalculateMaxBounds() const noexcept {
  auto bounds = Cubic::BoundsArray{};
  calculateMaxBounds(bounds);
  auto ret = QList<qreal>(bounds.size());
  std::ranges::copy(bounds, ret.begin());
  return ret;
}

QList<qreal>
material::shapes::RoundedPolygon::qcalculateBounds(bool approx) const noexcept {
  auto bounds = Cubic::BoundsArray{};
  calculateBounds(bounds, approx);
  auto ret = QList<qreal>(bounds.size());
  std::ranges::copy(bounds, ret.begin());
  return ret;
}

} // namespace material::shapes

#endif // MATERIAL_SHAPES_ROUNDED_POLYGON_H
//
//
//
//  //endif // MATERIAL_SHAPES_ROUNDED_POLYGON_H

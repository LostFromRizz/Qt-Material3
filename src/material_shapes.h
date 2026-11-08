#ifndef MATERIAL_SHAPES_SHAPES_H
#define MATERIAL_SHAPES_SHAPES_H

#include "painting.h"
#include "shapes/painting.h"
#include "shapes/point.h"
#include <QPointF>
#include <QtQml/qqml.h>
#include <qtmetamacros.h>
#include <shapes/corner_rounding.h>
#include <shapes/rounded_polygon.h>

namespace material {

struct QPointNRound {
  Q_GADGET
  QML_VALUE_TYPE(roundpoint)
  QML_STRUCTURED_VALUE
  Q_PROPERTY(QPointF point READ point WRITE setPoint FINAL)
  Q_PROPERTY(qreal radius READ radius WRITE setRadius FINAL)
  Q_PROPERTY(qreal smoothing READ smoothing WRITE setSmoothing FINAL)
public:
  explicit QPointNRound();
  friend class MaterialShapes;

  inline QPointF point() const noexcept;
  inline void setPoint(QPointF point) noexcept;

  inline qreal radius() const noexcept;
  inline void setRadius(qreal radius) noexcept;

  inline qreal smoothing() const noexcept;
  inline void setSmoothing(qreal smoothing) noexcept;

private:
  explicit QPointNRound(shapes::Point, shapes::CornerRounding =
                                           shapes::CornerRounding::Unbounded);

  shapes::Point p;
  shapes::CornerRounding r;
};

class MaterialShapes : public QObject {
  Q_OBJECT
  Q_PROPERTY(material::shapes::RoundedPolygon *circle READ circle CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *square READ square CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *slanted READ slanted CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *arch READ arch CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *fan READ fan CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *arrow READ arrow CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *semiCircle READ semiCircle CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *oval READ oval CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *pill READ pill CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *triangle READ triangle CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *diamond READ diamond CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *clamShell READ clamShell CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *pentagon READ pentagon CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *gem READ gem CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *verySunny READ verySunny CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *sunny READ sunny CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *cookie4Sided READ cookie4Sided CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *cookie6Sided READ cookie6Sided CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *cookie7Sided READ cookie7Sided CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *cookie9Sided READ cookie9Sided CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *cookie12Sided READ cookie12Sided
                 CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *ghostish READ ghostish CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *clover4Leaf READ clover4Leaf CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *clover8Leaf READ clover8Leaf CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *burst READ burst CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *softBurst READ softBurst CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *boom READ boom CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *softBoom READ softBoom CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *flower READ flower CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *puffy READ puffy CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *puffyDiamond READ puffyDiamond CONSTANT)
  Q_PROPERTY(
      material::shapes::RoundedPolygon *pixelCircle READ pixelCircle CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *pixelTriangle READ pixelTriangle
                 CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *bun READ bun CONSTANT)
  Q_PROPERTY(material::shapes::RoundedPolygon *heart READ heart CONSTANT)
  QML_ELEMENT
  QML_SINGLETON
public:
  explicit MaterialShapes(QObject *parent = nullptr);

  inline shapes::RoundedPolygon *circle();
  inline shapes::RoundedPolygon *square();
  inline shapes::RoundedPolygon *slanted();
  inline shapes::RoundedPolygon *arch();
  inline shapes::RoundedPolygon *fan();
  inline shapes::RoundedPolygon *arrow();
  inline shapes::RoundedPolygon *semiCircle();
  inline shapes::RoundedPolygon *oval();
  inline shapes::RoundedPolygon *pill();
  inline shapes::RoundedPolygon *triangle();
  inline shapes::RoundedPolygon *diamond();
  inline shapes::RoundedPolygon *clamShell();
  inline shapes::RoundedPolygon *pentagon();
  inline shapes::RoundedPolygon *gem();
  inline shapes::RoundedPolygon *verySunny();
  inline shapes::RoundedPolygon *sunny();
  inline shapes::RoundedPolygon *cookie4Sided();
  inline shapes::RoundedPolygon *cookie6Sided();
  inline shapes::RoundedPolygon *cookie7Sided();
  inline shapes::RoundedPolygon *cookie9Sided();
  inline shapes::RoundedPolygon *cookie12Sided();
  inline shapes::RoundedPolygon *ghostish();
  inline shapes::RoundedPolygon *clover4Leaf();
  inline shapes::RoundedPolygon *clover8Leaf();
  inline shapes::RoundedPolygon *burst();
  inline shapes::RoundedPolygon *softBurst();
  inline shapes::RoundedPolygon *boom();
  inline shapes::RoundedPolygon *softBoom();
  inline shapes::RoundedPolygon *flower();
  inline shapes::RoundedPolygon *puffy();
  inline shapes::RoundedPolygon *puffyDiamond();
  inline shapes::RoundedPolygon *pixelCircle();
  inline shapes::RoundedPolygon *pixelTriangle();
  inline shapes::RoundedPolygon *bun();
  inline shapes::RoundedPolygon *heart();

  Q_INVOKABLE shapes::RoundedPolygon *
  customPolygon(const QList<QPointNRound> &points, int reps,
                bool mirroring = false, QPointF center = QPointF(0.5, 0.5));

  Q_INVOKABLE
  inline qreal calculateScaleFactor(shapes::RoundedPolygon *polygon) {
    auto bounds = shapes::Cubic::BoundsArray();
    auto maxBounds = shapes::Cubic::BoundsArray();

    polygon->calculateBounds(bounds);
    polygon->calculateMaxBounds(maxBounds);
    auto scaleX = width(bounds) / width(maxBounds);
    auto scaleY = height(bounds) / height(maxBounds);
    return static_cast<qreal>(std::max(scaleX, scaleY));
  }

  Q_INVOKABLE
  inline qreal
  calculateScaleFactor(const QList<shapes::RoundedPolygon *> polygons) {
    float scaleFactor = 1.0f;
    // Axis-aligned max bounding box for this object, where the rectangles
    // left, top, right, and bottom values will be stored in entries 0, 1, 2,
    // and 3, in that order.
    auto bounds = shapes::Cubic::BoundsArray();
    auto maxBounds = shapes::Cubic::BoundsArray();

    for (const auto *polygon : polygons) {
      if (!polygon) {
        continue;
      }
      polygon->calculateBounds(bounds);
      polygon->calculateMaxBounds(maxBounds);
      auto scaleX = width(bounds) / width(maxBounds);
      auto scaleY = height(bounds) / height(maxBounds);
      scaleFactor = std::min(scaleFactor, std::max(scaleX, scaleY));
    }
    return static_cast<qreal>(scaleFactor);
  }

  Q_INVOKABLE inline void
  polygonToContext2DPath(QJSValue ctx, const shapes::RoundedPolygon *polygon) {
    return shapes::context2DPathFromCubics(ctx, polygon->cubics(), 0);
  }

  Q_INVOKABLE inline void
  cubicsToContext2DPath(QJSValue ctx, const QList<shapes::Cubic> &cubics) {
    return shapes::context2DPathFromCubics(ctx, cubics, 0);
  }

private:
  inline static constexpr shapes::Point kCenter = shapes::Point(0.5, 0.5);

  inline float height(const shapes::Cubic::BoundsArray &bounds) {
    return bounds[3] - bounds[1];
  }

  inline float width(const shapes::Cubic::BoundsArray &bounds) {
    return bounds[2] - bounds[0];
  }

  inline static shapes::RoundedPolygon *
  customPolygon(const std::span<const QPointNRound> &points, int reps,
                bool mirroring = false, shapes::Point center = kCenter) {
    std::vector<float> vertices;
    std::vector<shapes::CornerRounding> perCornerRounding;
    doRepeat(points, reps, center, mirroring, vertices, perCornerRounding);

    return shapes::RoundedPolygon::Create(
        vertices, shapes::CornerRounding::Unbounded, perCornerRounding,
        center.x(), center.y());
  }

  inline static void
  doRepeat(const std::span<const QPointNRound> &points, int reps,
           const shapes::Point &center, bool mirroring,
           std::vector<float> &outVertices,
           std::vector<shapes::CornerRounding> &outRounding) {

    const std::size_t n = points.size();
    if (mirroring) {
      // Per-input-point angle/distance cache — O(n), not O(reps*n).
      // This mirrors the Kotlin `angles`/`distances` fastMap calls
      // and is cheap since n is the small "shape definition" size.
      std::vector<std::pair<float, float>> anglesAndDist;
      anglesAndDist.reserve(n);
      for (std::size_t k = 0; k < n; ++k) {
        const shapes::Point rel = points[k].p - center;
        const auto angle =
            std::atan2(rel.y(), rel.x()) * 180.0f / std::numbers::pi_v<float>;

        anglesAndDist.emplace_back(angle, rel.distance());
      }

      const int actualReps = reps * 2;
      const float sectionAngle = 360.0f / actualReps;
      const std::size_t lastIndex = n - 1;

      outVertices.reserve(outVertices.size() +
                          static_cast<std::size_t>(actualReps) * n * 2);
      outRounding.reserve(outRounding.size() +
                          static_cast<std::size_t>(actualReps) * n);

      for (int rep = 0; rep < actualReps; ++rep) {
        for (std::size_t index = 0; index < n; ++index) {
          const std::size_t i = (rep % 2 == 0) ? index : (lastIndex - index);

          if (i > 0 || rep % 2 == 0) {
            const auto angleAndDist = anglesAndDist[i];
            const float a =
                sectionAngle * static_cast<float>(rep) +
                ((rep % 2 == 0) ? angleAndDist.first
                                : sectionAngle - angleAndDist.first +
                                      2.0f * anglesAndDist[0].first);
            const float ar = shapes::shape_utils::toRadians(a);

            outVertices.push_back(std::cos(ar) * angleAndDist.second +
                                  center.x());
            outVertices.push_back(std::sin(ar) * angleAndDist.second +
                                  center.y());
            outRounding.push_back(points[i].r);
          }
        }
      }
    } else {
      const std::size_t np = n;
      const std::size_t total = np * static_cast<std::size_t>(reps);

      outVertices.reserve(outVertices.size() + total * 2);
      outRounding.reserve(outRounding.size() + total);

      for (std::size_t i = 0; i < total; ++i) {
        const std::size_t pointIdx = i % np;
        const float angle =
            static_cast<float>(static_cast<int>(i / np)) * 360.0f / reps;

        const shapes::Point rotated =
            points[pointIdx].p.rotateDegress(angle, center);

        outVertices.push_back(rotated.x());
        outVertices.push_back(rotated.y());
        outRounding.push_back(points[pointIdx].r);
      }
    }
  }

  shapes::RoundedPolygon *createCircle(int vertices = 10);
  shapes::RoundedPolygon *createSquare();
  shapes::RoundedPolygon *createSlanted();
  shapes::RoundedPolygon *createArch();
  shapes::RoundedPolygon *createFan();
  shapes::RoundedPolygon *createArrow();
  shapes::RoundedPolygon *createSemiCircle();
  shapes::RoundedPolygon *createOval();
  shapes::RoundedPolygon *createPill();
  shapes::RoundedPolygon *createTriangle();
  shapes::RoundedPolygon *createDiamond();
  shapes::RoundedPolygon *createClamShell();
  shapes::RoundedPolygon *createPentagon();
  shapes::RoundedPolygon *createGem();
  shapes::RoundedPolygon *createSunny();
  shapes::RoundedPolygon *createVerySunny();
  shapes::RoundedPolygon *createCookie4Sided();
  shapes::RoundedPolygon *createCookie6Sided();
  shapes::RoundedPolygon *createCookie7Sided();
  shapes::RoundedPolygon *createCookie9Sided();
  shapes::RoundedPolygon *createCookie12Sided();
  shapes::RoundedPolygon *createGhostish();
  shapes::RoundedPolygon *createClover4Leaf();
  shapes::RoundedPolygon *createClover8Leaf();
  shapes::RoundedPolygon *createBurst();
  shapes::RoundedPolygon *createSoftBurst();
  shapes::RoundedPolygon *createBoom();
  shapes::RoundedPolygon *createSoftBoom();
  shapes::RoundedPolygon *createFlower();
  shapes::RoundedPolygon *createPuffy();
  shapes::RoundedPolygon *createPuffyDiamond();
  shapes::RoundedPolygon *createPixelCircle();
  shapes::RoundedPolygon *createPixelTriangle();
  shapes::RoundedPolygon *createBun();
  shapes::RoundedPolygon *createHeart();

  shapes::RoundedPolygon *m_circle = nullptr;
  shapes::RoundedPolygon *m_square = nullptr;
  shapes::RoundedPolygon *m_slanted = nullptr;
  shapes::RoundedPolygon *m_arch = nullptr;
  shapes::RoundedPolygon *m_fan = nullptr;
  shapes::RoundedPolygon *m_arrow = nullptr;
  shapes::RoundedPolygon *m_semiCircle = nullptr;
  shapes::RoundedPolygon *m_oval = nullptr;
  shapes::RoundedPolygon *m_pill = nullptr;
  shapes::RoundedPolygon *m_triangle = nullptr;
  shapes::RoundedPolygon *m_diamond = nullptr;
  shapes::RoundedPolygon *m_clamShell = nullptr;
  shapes::RoundedPolygon *m_pentagon = nullptr;
  shapes::RoundedPolygon *m_gem = nullptr;
  shapes::RoundedPolygon *m_verySunny = nullptr;
  shapes::RoundedPolygon *m_sunny = nullptr;
  shapes::RoundedPolygon *m_cookie4Sided = nullptr;
  shapes::RoundedPolygon *m_cookie6Sided = nullptr;
  shapes::RoundedPolygon *m_cookie7Sided = nullptr;
  shapes::RoundedPolygon *m_cookie9Sided = nullptr;
  shapes::RoundedPolygon *m_cookie12Sided = nullptr;
  shapes::RoundedPolygon *m_ghostish = nullptr;
  shapes::RoundedPolygon *m_clover4Leaf = nullptr;
  shapes::RoundedPolygon *m_clover8Leaf = nullptr;
  shapes::RoundedPolygon *m_burst = nullptr;
  shapes::RoundedPolygon *m_softBurst = nullptr;
  shapes::RoundedPolygon *m_boom = nullptr;
  shapes::RoundedPolygon *m_softBoom = nullptr;
  shapes::RoundedPolygon *m_flower = nullptr;
  shapes::RoundedPolygon *m_puffy = nullptr;
  shapes::RoundedPolygon *m_puffyDiamond = nullptr;
  shapes::RoundedPolygon *m_pixelCircle = nullptr;
  shapes::RoundedPolygon *m_pixelTriangle = nullptr;
  shapes::RoundedPolygon *m_bun = nullptr;
  shapes::RoundedPolygon *m_heart = nullptr;
};
} // namespace material

QPointF material::QPointNRound::point() const noexcept {
  return QPointF(static_cast<qreal>(p.x()), static_cast<qreal>(p.y()));
}

void material::QPointNRound::setPoint(QPointF point) noexcept {
  auto xF = static_cast<float>(point.x());
  auto yF = static_cast<float>(point.y());

  if (xF == p.x() && yF == p.y()) {
    return;
  }

  p = shapes::Point(xF, yF);
}

qreal material::QPointNRound::radius() const noexcept {
  return static_cast<qreal>(r.radius());
}
void material::QPointNRound::setRadius(qreal radius) noexcept {
  auto radiusF = static_cast<float>(radius);
  if (radiusF == r.radius()) {
    return;
  }
  r = shapes::CornerRounding(radiusF, r.smoothing());
}

qreal material::QPointNRound::smoothing() const noexcept {
  return static_cast<qreal>(r.smoothing());
}

void material::QPointNRound::setSmoothing(qreal smoothing) noexcept {
  auto smoothingF = static_cast<float>(smoothing);
  if (smoothingF == r.smoothing()) {
    return;
  }
  r = shapes::CornerRounding(r.radius(), smoothingF);
}

#define GETTER_IMPL(name, create)                                              \
  material::shapes::RoundedPolygon *material::MaterialShapes::name() {         \
    if (m_##name != nullptr) {                                                 \
      return m_##name;                                                         \
    }                                                                          \
    auto *created = create();                                                  \
    created->normalize();                                                      \
    created->setParent(this);                                                  \
    m_##name = created;                                                        \
    return m_##name;                                                           \
  }

GETTER_IMPL(circle, createCircle)
GETTER_IMPL(square, createSquare);
GETTER_IMPL(slanted, createSlanted);
GETTER_IMPL(arch, createArch);
GETTER_IMPL(fan, createFan);
GETTER_IMPL(arrow, createArrow);
GETTER_IMPL(semiCircle, createSemiCircle);
GETTER_IMPL(oval, createOval);
GETTER_IMPL(pill, createPill);
GETTER_IMPL(triangle, createTriangle);
GETTER_IMPL(diamond, createDiamond);
GETTER_IMPL(clamShell, createClamShell);
GETTER_IMPL(pentagon, createPentagon);
GETTER_IMPL(gem, createGem);
GETTER_IMPL(verySunny, createVerySunny);
GETTER_IMPL(sunny, createSunny);
GETTER_IMPL(cookie4Sided, createCookie4Sided);
GETTER_IMPL(cookie6Sided, createCookie6Sided);
GETTER_IMPL(cookie7Sided, createCookie7Sided);
GETTER_IMPL(cookie9Sided, createCookie9Sided);
GETTER_IMPL(cookie12Sided, createCookie12Sided);
GETTER_IMPL(ghostish, createGhostish);
GETTER_IMPL(clover4Leaf, createClover4Leaf);
GETTER_IMPL(clover8Leaf, createClover8Leaf);
GETTER_IMPL(burst, createBurst);
GETTER_IMPL(softBurst, createSoftBurst);
GETTER_IMPL(boom, createBoom);
GETTER_IMPL(softBoom, createSoftBoom);
GETTER_IMPL(flower, createFlower);
GETTER_IMPL(puffy, createPuffy);
GETTER_IMPL(puffyDiamond, createPuffyDiamond);
GETTER_IMPL(pixelCircle, createPixelCircle);
GETTER_IMPL(pixelTriangle, createPixelTriangle);
GETTER_IMPL(bun, createBun);
GETTER_IMPL(heart, createHeart);

#undef GETTER_IMPL

#endif // MATERIAL_SHAPES_SHAPES_H

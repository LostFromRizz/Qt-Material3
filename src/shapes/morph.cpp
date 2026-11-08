#include "morph.h"
#include "feature_mapping.h"
#include "polygon_measure.h"
#include "rounded_polygon.h"
#include "utils.h"

using namespace material::shapes;

Morph::Morph(QObject *parent)
    : QObject(parent), m_extraCubics{}, m_matches{}, m_polygons{}, m_cubics{},
      m_dirty(true) {}

// Morph::Morph(std::array<RoundedPolygon *, 2> &&polygons,
//              std::vector<Cubic> &&extraCubics,
//              std::vector<std::pair<Morph::CubicLocationWrapper,
//                                    Morph::CubicLocationWrapper>> &&matches)
//     : m_extraCubics(std::move(extraCubics)), m_matches(std::move(matches)),
//       m_polygons(std::move(polygons)) {}

Morph::CubicLocationWrapper::CubicLocationWrapper(CubicLocation location)
    : polygon(0), location(location) {}

Morph::CubicLocationWrapper::CubicLocationWrapper(uint32_t polygonIndex,
                                                  CubicLocation location)
    : polygon(polygonIndex), location(location) {}

// Morph Morph::Create(const RoundedPolygon &start, const RoundedPolygon &end) {
//   std::vector<Cubic> extraCubics;
//   auto matches = match(start, end, extraCubics);
//   return Morph(std::array<const RoundedPolygon *, 2>{&start, &end},
//                std::move(extraCubics), std::move(matches));
// }

std::vector<std::pair<Morph::CubicLocationWrapper, Morph::CubicLocationWrapper>>
Morph::match(const RoundedPolygon &p1, const RoundedPolygon &p2,
             std::vector<Cubic> &extraCubicsStorage) {
  extraCubicsStorage.clear(); // remove dirty cubics

  auto measurer = LengthMeasurer();
  auto measuredPolygon1 =
      MeasuredPolygon::measurePolygon(&measurer, p1, extraCubicsStorage);
  auto measuredPolygon2 =
      MeasuredPolygon::measurePolygon(&measurer, p2, extraCubicsStorage);

  auto doubleMapper =
      feature_mapping::featureMapper(measuredPolygon1, measuredPolygon2);

  const auto polygon2CutPoint = doubleMapper.map(0.0f);

  // qDebug() << "polygon2CutPoint: " <<
  // std::bit_cast<uint32_t>(polygon2CutPoint);

  auto measuredPolygon3 = measuredPolygon2.cutAndShift(polygon2CutPoint);
  auto &bs1 = measuredPolygon1;
  auto &bs2 = measuredPolygon3.has_value() ? measuredPolygon3.value()
                                           : measuredPolygon2;

  // Match
  // Now we can compare the two lists of measured cubics and create a list of
  // pairs of cubics [ret], which are the start/end curves that represent the
  // Morph object and the start and end shapes, and which can be interpolated to
  // animate the between those shapes.

  std::vector<
      std::pair<Morph::CubicLocationWrapper, Morph::CubicLocationWrapper>>
      ret;

  ret.reserve(bs1.cubics().size());

  // i1/i2 are the indices of the current cubic on the start (1) and end (2)
  // shapes
  std::size_t i1 = 0, i2 = 0;
  // b1, b2 are the current measured cubic for each polygon
  auto b1 = bs1.getCubicOpt(i1++);
  auto b2 = bs2.getCubicOpt(i2++);

  while (b1.has_value() && b2.has_value()) {
    const auto b1a =
        (i1 == bs1.size()) ? 1.0f : b1.value().endOutlineProgress();
    const float b2a =
        (i2 == bs2.size())
            ? 1.0f
            : doubleMapper.mapBack(shape_utils::positiveModulo(
                  b2.value().endOutlineProgress() + polygon2CutPoint, 1.0f));

    const auto minb = std::min(b1a, b2a);

    MeasuredPolygon::MeasuredCubic seg1 = b1.value();
    std::optional<MeasuredPolygon::MeasuredCubic> newb1 = bs1.getCubicOpt(i1++);

    if (b1a > minb + shape_utils::ANGLE_EPSILON) {
      // qDebug() << "Cut 1";
      const auto p = b1.value().cutAtProgress(bs1, minb);
      seg1 = p.first;
      newb1 = std::make_optional(p.second);
      i1--;
    }

    MeasuredPolygon::MeasuredCubic seg2 = b2.value();
    std::optional<MeasuredPolygon::MeasuredCubic> newb2 = bs2.getCubicOpt(i2++);

    if (b2a > minb + shape_utils::ANGLE_EPSILON) {
      // qDebug() << "Cut 2";
      const auto p = b2.value().cutAtProgress(
          bs2, shape_utils::positiveModulo(
                   doubleMapper.map(minb) - polygon2CutPoint, 1.0f));

      seg2 = p.first;
      newb2 = std::make_optional(p.second);
      i2--;
    }

    auto getCubicLocationWrapper =
        [&](const uint8_t startOrEnd,
            const MeasuredPolygon::MeasuredCubic &mcubic) {
          if (mcubic.isExtra()) {
            return Morph::CubicLocationWrapper(mcubic.location());
          } else {
            return Morph::CubicLocationWrapper(startOrEnd, mcubic.location());
          }
        };

    ret.emplace_back(getCubicLocationWrapper(0, seg1),
                     getCubicLocationWrapper(1, seg2));
    b1 = newb1;
    b2 = newb2;
  }

  Q_ASSERT_X(!b1.has_value() && !b2.has_value(),
             "material::shapes::Morph::match",
             "Expected both Polygon's Cubic to be fully matched");

  return ret;
}

Cubic::BoundsArray
Morph::calculateMaxBounds(Cubic::BoundsArray &&bounds) const {
  const auto minX = bounds[0];
  const auto minY = bounds[1];
  const auto maxX = bounds[2];
  const auto maxY = bounds[3];

  m_polygons.back()->calculateMaxBounds(bounds);

  bounds[0] = std::min(minX, bounds[0]);
  bounds[1] = std::min(minY, bounds[1]);
  bounds[2] = std::max(maxX, bounds[2]);
  bounds[3] = std::max(maxY, bounds[3]);

  return bounds;
}

Cubic::BoundsArray Morph::calculateBounds(Cubic::BoundsArray &&bounds,
                                          bool approx) const {
  const auto minX = bounds[0];
  const auto minY = bounds[1];
  const auto maxX = bounds[2];
  const auto maxY = bounds[3];

  m_polygons.back()->calculateBounds(bounds, approx);

  bounds[0] = std::min(minX, bounds[0]);
  bounds[1] = std::min(minY, bounds[1]);
  bounds[2] = std::max(maxX, bounds[2]);
  bounds[3] = std::max(maxY, bounds[3]);

  return bounds;
}

QList<Cubic> Morph::asCubics(float progress) {
  m_cubics.clear();
  if (m_dirty) {
    if (std::all_of(m_polygons.begin(), m_polygons.end(),
                    [](const auto *ptr) { return ptr != nullptr; })) {
      m_matches = match(*m_polygons[0], *m_polygons[1], m_extraCubics);
      m_dirty = false;
    } else {
      return m_cubics;
    }
  }

  m_cubics.reserve(m_matches.size() + 1);

  // The first/last mechanism here ensures that the final anchor point
  // in the shape exactly matches the first anchor point. There can be
  // rendering artifacts introduced by those points being slightly off,
  // even by much less than a pixel.
  std::optional<Cubic> firstCubic;
  std::optional<Cubic> lastCubic;

  for (std::size_t i = 0; i < m_matches.size(); ++i) {
    const auto &match = m_matches[i];

    // copy it
    Cubic cubic = Cubic();
    cubic.lerp(getCubic(match.first), getCubic(match.second), progress);

    if (!firstCubic.has_value())
      firstCubic = cubic;

    if (lastCubic.has_value())
      m_cubics.append(lastCubic.value());

    lastCubic = cubic;
  }

  if (lastCubic.has_value() && firstCubic.has_value()) {
    m_cubics.emplaceBack(lastCubic->anchor0X(), lastCubic->anchor0Y(),
                         lastCubic->control0X(), lastCubic->control0Y(),
                         lastCubic->control1X(), lastCubic->control1Y(),
                         firstCubic->anchor0X(), firstCubic->anchor0Y());
  }

  return m_cubics;
}

RoundedPolygon *Morph::start() const { return m_polygons[0]; }
void Morph::setStart(RoundedPolygon *value) {
  auto *old = m_polygons[0];

  if (value == old) {
    return;
  }

  if (old != nullptr && old->parent() == this) {
    old->deleteLater();
  }

  if (value != nullptr && value->parent() == nullptr) {
    value->setParent(this);
  }

  m_dirty = true;
  m_polygons[0] = value;
  emit startChanged();
}

RoundedPolygon *Morph::end() const { return m_polygons[1]; }
void Morph::setEnd(RoundedPolygon *value) {
  auto *old = m_polygons[1];

  if (value == old) {
    return;
  }

  if (old != nullptr && old->parent() == this) {
    old->deleteLater();
  }

  if (value != nullptr && value->parent() == nullptr) {
    value->setParent(this);
  }

  m_dirty = true;
  m_polygons[1] = value;
  emit endChanged();
}

Q_INVOKABLE void Morph::setPolygons(RoundedPolygon *start,
                                    RoundedPolygon *end) {

  auto *startOld = m_polygons[0];
  auto *endOld = m_polygons[1];

  if (start == startOld && end == endOld) {
    return;
  }

  if (startOld != nullptr && startOld->parent() == this) {
    startOld->deleteLater();
  }
  if (endOld != nullptr && endOld->parent() == this) {
    endOld->deleteLater();
  }

  if (start != nullptr && start->parent() == nullptr) {
    start->setParent(this);
  }
  if (end != nullptr && end->parent() == nullptr) {
    end->setParent(this);
  }

  m_dirty = true;
  m_polygons[0] = start;
  m_polygons[1] = end;
  emit polygonsChanged();
}

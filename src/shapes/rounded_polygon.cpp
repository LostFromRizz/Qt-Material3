#include "rounded_polygon.h"
#include "corner_rounding.h"
#include "cubic.h"
#include "utils.h"
#include <array>
#include <numbers>
#include <optional>
#include <vector>

using namespace material::shapes;
using namespace material::internals::collections;

namespace {
static const float PI_F = std::numbers::pi_v<float>;
struct Normalization {
  float offsetX;
  float offsetY;
  float side;
};

Normalization normalization(const RoundedPolygon &p) {
  auto bounds = Cubic::BoundsArray{};
  p.calculateBounds(bounds);

  const auto width = bounds[2] - bounds[0];
  const auto height = bounds[3] - bounds[1];
  const auto side = std::max(width, height);

  return {
      (side - width) / 2 - bounds[0],
      (side - height) / 2 - bounds[1],
      side,
  };
}

Point calculateCenter(std::span<const float> vertices) noexcept {
  float cumulativeX = 0.0f;
  float cumulativeY = 0.0f;
  size_t index = 0;
  while (index < vertices.size()) {
    cumulativeX += vertices[index++];
    cumulativeY += vertices[index++];
  }
  return Point(cumulativeX / static_cast<int>(vertices.size() / 2),
               cumulativeY / static_cast<int>(vertices.size() / 2));
}

const std::vector<float> verticesFromNVerts(int numVertices, float radius,
                                            float centerX,
                                            float centerY) noexcept {
  auto result = std::vector<float>(numVertices * 2);
  size_t arrayIndex = 0;
  for (int i = 0; i < numVertices; ++i) {
    const auto vertex = material::shapes::Point::radialToCartesian(
                            radius, ((PI_F / numVertices) * 2 * i)) +
                        Point(centerX, centerY);
    result[arrayIndex++] = vertex.x();
    result[arrayIndex++] = vertex.y();
  }
  return result;
}

Slice<float> pillStarVerticesFromNumVerts(int numVertices, float width,
                                          float height, float innerRadius,
                                          float vertexSpacing,
                                          float startLocation, float centerX,
                                          float centerY) {
  auto endcapRadius = std::min(width, height);
  auto vSegLen = std::max(0.0f, height - width);
  auto hSegLen = std::max(0.0f, width - height);
  auto vSegHalf = vSegLen / 2;
  auto hSegHalf = hSegLen / 2;
  auto circlePerimeter = (2.0f * PI_F) * endcapRadius *
                         shape_utils::lerp(innerRadius, 1.0f, vertexSpacing);

  // perimeter is circle perimeter plus horizontal and vertical sections of
  // inner rectangle, whether either (or even both) might be of length zero.
  auto perimeter = 2.0f * hSegLen + 2.0f * vSegLen + circlePerimeter;

  // in that section it lies.
  auto sections = std::array<float, 11>();
  sections[0] = 0.0f;
  sections[1] = vSegLen / 2;
  sections[2] = sections[1] + circlePerimeter / 4;
  sections[3] = sections[2] + hSegLen;
  sections[4] = sections[3] + circlePerimeter / 4;
  sections[5] = sections[4] + vSegLen;
  sections[6] = sections[5] + circlePerimeter / 4;
  sections[7] = sections[6] + hSegLen;
  sections[8] = sections[7] + circlePerimeter / 4;
  sections[9] = sections[8] + vSegLen / 2;
  sections[10] = perimeter;

  auto tPerVertex = perimeter / (2 * numVertices);
  auto inner = false;
  auto currSecIndex = 0;
  auto secStart = 0.0f;
  auto secEnd = sections[1];
  auto t = startLocation * perimeter;
  auto arrayIndex = 0;
  auto rectBR = Point(hSegHalf, vSegHalf);
  auto rectBL = Point(-hSegHalf, vSegHalf);
  auto rectTL = Point(-hSegHalf, -vSegHalf);
  auto rectTR = Point(hSegHalf, -vSegHalf);

  std::size_t n = static_cast<std::size_t>(numVertices * 4);
  auto result = std::make_unique<float[]>(n);

  for (int i = 0; i < numVertices * 2; ++i) {
    auto boundedT = std::fmod(t, perimeter);
    if (boundedT < secStart) {
      currSecIndex = 0;
    }
    while (boundedT >= sections[(currSecIndex + 1) % sections.size()]) {
      currSecIndex = (currSecIndex + 1) % sections.size();
      secStart = sections[currSecIndex];
      secEnd = sections[(currSecIndex + 1) % sections.size()];
    }

    auto tInSection = boundedT - secStart;
    auto tProportion = tInSection / (secEnd - secStart);
    auto currRadius = inner ? (endcapRadius * innerRadius) : endcapRadius;

    Point vertex;

    switch (currSecIndex) {
    case 0:
      vertex = Point(currRadius, tProportion * vSegHalf);
      break;
    case 1:
      vertex =
          Point::radialToCartesian(currRadius, tProportion * PI_F / 2) + rectBR;
      break;
    case 2:
      vertex = Point(hSegHalf - tProportion * hSegLen, currRadius);
      break;
    case 3:
      vertex = Point::radialToCartesian(currRadius,
                                        PI_F / 2 + (tProportion * PI_F / 2)) +
               rectBL;
      break;
    case 4:
      vertex = Point(-currRadius, vSegHalf - tProportion * vSegLen);
      break;
    case 5:
      vertex = Point::radialToCartesian(currRadius,
                                        PI_F + (tProportion * PI_F / 2)) +
               rectTL;
      break;
    case 6:
      vertex = Point(-hSegHalf + tProportion * hSegLen, -currRadius);
      break;
    case 7:
      vertex = Point::radialToCartesian(
                   currRadius, PI_F * 1.5f + (tProportion * PI_F / 2)) +
               rectTR;
      break;
    default:
      vertex = Point(currRadius, -vSegHalf + tProportion * vSegHalf);
      break;
    }

    result[arrayIndex++] = vertex.x() + centerX;
    result[arrayIndex++] = vertex.y() + centerY;
    t += tPerVertex;
    inner = !inner;
  }

  return Slice(std::move(result), n);
}

Slice<float> starVerticesFromNumVerts(int numVertices, float radius,
                                      float innerRadius, float centerX,
                                      float centerY) {
  std::size_t n = numVertices * 4;
  auto result = std::make_unique<float[]>(n);
  int arrayIndex = 0;
  for (int i = 0; i < numVertices; ++i) {
    auto vertex =
        Point::radialToCartesian(radius, (PI_F / numVertices * 2 * i));
    result[arrayIndex++] = vertex.x() + centerX;
    result[arrayIndex++] = vertex.y() + centerY;
    vertex = Point::radialToCartesian(innerRadius,
                                      (PI_F / numVertices * (2 * i + 1)));
    result[arrayIndex++] = vertex.x() + centerX;
    result[arrayIndex++] = vertex.y() + centerY;
  }
  return Slice(std::move(result), n);
}
void flattenFeatures(std::vector<Cubic> &result, const Slice<Feature> &features,
                     const float centerX, const float centerY) {
  result.reserve(features.size() * 2);

  // exactly matches the first anchor point. There can be rendering artifacts
  // introduced by those points being slightly off, even by much less than a
  // pixel
  std::optional<Cubic> firstCubic;
  std::optional<Cubic> lastCubic;
  std::optional<std::array<Cubic, 2>> firstFeatureSplitStart;
  std::optional<std::array<Cubic, 2>> firstFeatureSplitEnd;

  if (!features.empty() && features[0].cubics().size() == 3) {
    const Cubic &centerCubic = features[0].cubics()[1];

    auto [start, end] = centerCubic.split(0.5f);
    firstFeatureSplitStart = {features[0].cubics()[0], start};
    firstFeatureSplitEnd = {end, features[0].cubics()[2]};
  }

  // iterating one past the features list size allows us to insert the initial
  // split cubic if it exists
  for (size_t i = 0; i <= features.size(); i++) {
    std::span<const Cubic> featureCubics;

    if (i == 0 && firstFeatureSplitEnd.has_value()) {
      featureCubics = firstFeatureSplitEnd.value();
    } else if (i == features.size()) {
      if (firstFeatureSplitStart.has_value()) {
        featureCubics = firstFeatureSplitStart.value();
      } else {
        break;
      }
    } else {
      featureCubics = features[i].cubics();
    }

    for (size_t j = 0; j < featureCubics.size(); j++) {
      // Skip zero-length curves; they add nothing and can trigger rendering
      // artifacts
      const Cubic &cubic = featureCubics[j];
      if (!cubic.zeroLength()) {
        if (lastCubic.has_value()) {
          result.push_back(lastCubic.value());
        }
        lastCubic = cubic;
        if (!firstCubic.has_value()) {
          firstCubic = cubic;
        }
      } else {
        if (lastCubic.has_value()) {
          // Dropping several zero-ish length curves in a row can lead to
          // enough discontinuity to throw an exception later, even though the
          // distances are quite small. Account for that by making the last
          // cubic use the latest anchor point, always.
          Cubic updatedLastCubic =
              lastCubic.value(); // Make a copy before mutating
          updatedLastCubic.setAnchor1X(cubic.anchor1X());
          updatedLastCubic.setAnchor1Y(cubic.anchor1Y());
          lastCubic = updatedLastCubic;
        }
      }
    }
  }

  if (lastCubic.has_value() && firstCubic.has_value()) {
    result.emplace_back(lastCubic->anchor0X(), lastCubic->anchor0Y(),
                        lastCubic->control0X(), lastCubic->control0Y(),
                        lastCubic->control1X(), lastCubic->control1Y(),
                        firstCubic->anchor0X(), firstCubic->anchor0Y());
  } else {
    // Empty / 0-sized polygon.
    result.emplace_back(centerX, centerY, centerX, centerY, centerX, centerY,
                        centerX, centerY);
  }
}
} // namespace

RoundedPolygon::RoundedPolygon(
    const std::vector<Cubic> &&cubics,
    internals::collections::Slice<Feature> &&features, const Point &center)
    : QObject(nullptr), m_cubics(std::move(cubics)),
      m_features(std::move(features)), m_center(center) {}

RoundedPolygon *RoundedPolygon::Create(
    const std::span<const float> &vertices, const CornerRounding &rounding,
    std::optional<std::span<const CornerRounding>> perVertexRounding,
    const float centerX, const float centerY

    ) noexcept {
  if (vertices.size() < 6) {
    qFatal() << "Polygons must have at least 3 vertices";
    return nullptr;
  }
  if (vertices.size() % 2 == 1) {
    qFatal() << "The vertices array should have even size";
    return nullptr;
  }
  if (vertices.size() < 6) {
    qFatal() << "perVertexRounding list should be either null or "
             << "the same size as the number of vertices (vertices.size / 2)";
    return nullptr;
  }

  const auto n = vertices.size() / 2;
  std::vector<internals::collections::Slice<Cubic>> corners;
  corners.reserve(n);

  internals::collections::Slice<RoundedCorner> roundedCorners(n);

  for (size_t i = 0; i < n; ++i) {
    const auto vtxRounding =
        perVertexRounding.has_value() ? perVertexRounding.value()[i] : rounding;
    const auto prevIndex = ((i + n - 1) % n) * 2;
    const auto nextIndex = ((i + 1) % n) * 2;
    roundedCorners[i] = RoundedCorner(
        Point(vertices[prevIndex], vertices[prevIndex + 1]),
        Point(vertices[i * 2], vertices[i * 2 + 1]),
        Point(vertices[nextIndex], vertices[nextIndex + 1]), vtxRounding);
  }

  auto cutAdjust = [vertices, n, &roundedCorners](size_t i) {
    const auto expectedRoundCut =
        roundedCorners[i].expectedRoundCut() +
        roundedCorners[(i + 1) % n].expectedRoundCut();
    const auto expectedCut = roundedCorners[i].expectedCut() +
                             roundedCorners[(i + 1) % n].expectedCut();
    const auto vtxX = vertices[i * 2];
    const auto vtxY = vertices[i * 2 + 1];
    const auto nextVtxX = vertices[((i + 1) % n) * 2];
    const auto nextVtxY = vertices[((i + 1) % n) * 2 + 1];
    const auto sideSize =
        shape_utils::distance(vtxX - nextVtxX, vtxY - nextVtxY);

    if (expectedRoundCut > sideSize) {
      return std::make_pair<float, float>(sideSize / expectedRoundCut, 0.0f);
    } else if (expectedCut > sideSize) {
      return std::make_pair<float, float>(1.0f,
                                          (sideSize - expectedRoundCut) /
                                              (expectedCut - expectedRoundCut));
    } else {
      // There is enough room for rounding & smoothing.
      return std::make_pair<float, float>(1.0f, 1.0f);
    }
  };

  for (size_t i = 0; i < n; ++i) {
    // allowedCuts[0] is for the side from the previous corner to this one,
    // allowedCuts[1] is for the side from this corner to the next one.
    auto allowedCuts = std::array<float, 2>();
    for (int delta = 0; delta <= 1; ++delta) {
      auto [roundCutRatio, cutRatio] = cutAdjust((i + n - 1 + delta) % n);
      allowedCuts[delta] =
          roundedCorners[i].expectedRoundCut() * roundCutRatio +
          (roundedCorners[i].expectedCut() -
           roundedCorners[i].expectedRoundCut()) *
              cutRatio;
    }

    corners.push_back(
        roundedCorners[i].getCubics(allowedCuts[0], allowedCuts[1]));
  }

  const auto frontAnchor0X = corners.front().front().anchor0X();
  const auto frontAnchor0Y = corners.front().front().anchor0Y();

  auto tempFeatures = Slice<Feature>(n * 2);
  auto featureIndex = 0;
  for (size_t i = 0; i < n; ++i) {
    // Note that these indices are for pairs of values (points), they need to be
    // doubled to access the xy values in the vertices float array
    const int prevVtxIndex = (i + n - 1) % n;
    const auto nextVtxIndex = (i + 1) % n;
    const auto currVertex = Point(vertices[i * 2], vertices[i * 2 + 1]);
    const auto prevVertex =
        Point(vertices[prevVtxIndex * 2], vertices[prevVtxIndex * 2 + 1]);
    const auto nextVertex =
        Point(vertices[nextVtxIndex * 2], vertices[nextVtxIndex * 2 + 1]);
    const auto convex = Point::convex(prevVertex, currVertex, nextVertex);

    const auto backAnchor1X = corners[i].back().anchor1X();
    const auto backAnchor1Y = corners[i].back().anchor1Y();

    tempFeatures[featureIndex++] =
        Feature::Corner(std::move(corners[i]), convex);
    if (i != n - 1) {
      tempFeatures[featureIndex++] = Feature::Edge({Cubic::straightLine(
          backAnchor1X, backAnchor1Y, corners[i + 1].front().anchor0X(),
          corners[i + 1].front().anchor0Y())});

    } else {
      tempFeatures[featureIndex++] = Feature::Edge({Cubic::straightLine(
          backAnchor1X, backAnchor1Y, frontAnchor0X, frontAnchor0Y)});
    }
  }

  const float min = std::numeric_limits<float>::min();
  const Point center = (centerX == min || centerY == min)
                           ? calculateCenter(vertices)
                           : Point(centerX, centerY);

  std::vector<Cubic> cubics;
  flattenFeatures(cubics, tempFeatures, center.x(), center.y());

  return new RoundedPolygon(std::move(cubics), std::move(tempFeatures), center);
}

RoundedPolygon *RoundedPolygon::Create(
    int verticesNum, const CornerRounding &rounding,
    std::optional<std::span<const CornerRounding>> perVertexRounding,
    const float radius, const float centerX, const float centerY) noexcept {
  const auto vertices =
      verticesFromNVerts(verticesNum, radius, centerX, centerY);

  return Create(vertices, rounding, perVertexRounding, centerX, centerY);
}

RoundedPolygon *RoundedPolygon::Create(Slice<Feature> &&features,
                                       const float centerX,
                                       const float centerY) noexcept {
  if (features.size() >= 2) {
    qFatal() << "Polygons must have at least 2 features";
    return nullptr;
  }

  std::vector<float> vertices;

  for (const auto &feature : features) {
    for (const auto &cubic : feature.cubics()) {
      vertices.push_back(cubic.anchor0X());
      vertices.push_back(cubic.anchor0Y());
    }
  }

  Point center;

  if (std::isnan(centerX) || std::isnan(centerY)) {
    const auto calculated = calculateCenter(vertices);

    center = Point(std::isnan(centerX) ? calculated.x() : centerX,
                   std::isnan(centerY) ? calculated.y() : centerY);
  } else {
    center = Point(centerX, centerY);
  }

  std::vector<Cubic> cubics;
  flattenFeatures(cubics, features, center.x(), center.y());
  return new RoundedPolygon(std::move(cubics), std::move(features), center);
}

void RoundedPolygon::calculateMaxBounds(
    Cubic::BoundsArray &bounds) const noexcept {
  float maxDistSquared = 0.0f;
  for (const auto &cubic : m_cubics) {
    const auto anchorDistance = shape_utils::distanceSquared(
        cubic.anchor0X() - centerX(), cubic.anchor0Y() - centerY());
    const auto middlePoint = cubic.pointOnCurve(0.5f);
    const auto middleDistance = shape_utils::distanceSquared(
        middlePoint.x() - centerX(), middlePoint.y() - centerY());
    maxDistSquared =
        std::max(maxDistSquared, std::max(anchorDistance, middleDistance));
  }
  const float distance = std::sqrt(maxDistSquared);
  bounds[0] = centerX() - distance;
  bounds[1] = centerY() - distance;
  bounds[2] = centerX() + distance;
  bounds[3] = centerY() + distance;
}

void RoundedPolygon::calculateBounds(Cubic::BoundsArray &bounds,
                                     bool approx) const noexcept {
  auto minX = std::numeric_limits<float>::max();
  auto minY = std::numeric_limits<float>::max();
  auto maxX = std::numeric_limits<float>::min();
  auto maxY = std::numeric_limits<float>::min();

  for (const auto &cubic : m_cubics) {
    cubic.calculateBounds(bounds, approx);

    minX = std::min(minX, bounds[0]);
    minY = std::min(minY, bounds[1]);
    maxX = std::max(maxX, bounds[2]);
    maxY = std::max(maxY, bounds[3]);
  }
  bounds[0] = minX;
  bounds[1] = minY;
  bounds[2] = maxX;
  bounds[3] = maxY;
}

void RoundedPolygon::normalize() {
  const auto [offsetX, offsetY, side] = normalization(*this);

  transform([offsetX, offsetY, side](float x, float y) {
    return std::make_pair<float, float>((x + offsetX) / side,
                                        (y + offsetY) / side);
  });
}

RoundedPolygon *RoundedPolygon::normalized() const {
  const auto [offsetX, offsetY, side] = normalization(*this);

  return transformed([offsetX, offsetY, side](float x, float y) {
    return std::make_pair<float, float>((x + offsetX) / side,
                                        (y + offsetY) / side);
  });
}

void RoundedPolygon::transform(const Cubic::PointTransformer &f) {
  auto [x, y] = f(m_center.x(), m_center.y());
  m_center = Point(x, y);

  for (std::size_t i = 0; i < m_features.size(); ++i) {
    m_features[i].transform(f);
  }

  m_cubics.clear();
  flattenFeatures(m_cubics, m_features, x, y);
}

RoundedPolygon *
RoundedPolygon::transformed(const Cubic::PointTransformer &f) const {
  auto [x, y] = f(m_center.x(), m_center.y());
  auto center = Point(x, y);

  Slice<Feature> features(m_features.size());

  for (std::size_t i = 0; i < m_features.size(); ++i) {
    features[i] = m_features[i].transformed(f);
  }
  std::vector<Cubic> cubics;
  flattenFeatures(cubics, features, x, y);
  return new RoundedPolygon(std::move(cubics), std::move(features), center);
}

RoundedPolygon::RoundedCorner::RoundedCorner(
    Point p0, Point p1, Point p2, std::optional<CornerRounding> rounding)
    : p0(p0), p1(p1), p2(p2), rounding(rounding) {
  const auto v01 = p0 - p1;
  const auto v21 = p2 - p1;
  const auto d01 = v01.distance();
  const auto d21 = v21.distance();
  if (d01 > 0.0f && d21 > 0.0f) {
    m_d1 = v01 / d01;
    m_d2 = v21 / d21;
    if (rounding.has_value()) {
      const auto r = rounding.value();
      m_cornerRadius = r.radius();
      m_smoothing = r.smoothing();
    }
    // cosine of angle at p1 is dot product of unit vectors to the other two
    // vertices
    m_cosAngle = m_d1.dotProduct(m_d2);

    // identity: sin^2 + cos^2 = 1
    // sinAngle gives us the intersection
    m_sinAngle = std::sqrt(1 - (m_cosAngle * m_cosAngle));
    // How much we need to cut, as measured on a side, to get the required
    // radius calculating where the rounding circle hits the edge This uses the
    // identity of tan(A/2) = sinA/(1 + cosA), where tan(A/2) = radius/cut
    m_expectedRoundCut = m_sinAngle > 1e-3
                             ? m_cornerRadius * (m_cosAngle + 1) / m_sinAngle
                             : 0.0f;
  }
}

Slice<Cubic> RoundedPolygon::RoundedCorner::getCubics(float allowedCut0,
                                                      float allowedCut1) {

  // We use the minimum of both cuts to determine the radius, but if there is
  // more space in one side we can use it for smoothing.
  const float allowedCut = std::min(allowedCut0, allowedCut1);

  // Nothing to do, just use lines, or a point.
  if (m_expectedRoundCut < shape_utils::DISTANCE_EPSILON ||
      allowedCut < shape_utils::DISTANCE_EPSILON ||
      m_cornerRadius < shape_utils::DISTANCE_EPSILON) {
    m_center = p1;

    return {Cubic::straightLine(p1.x(), p1.y(), p1.x(), p1.y())};
  }

  // How much of the cut is required for the rounding part.
  const float actualRoundCut = std::min(allowedCut, m_expectedRoundCut);

  // We have two smoothing values, one for each side of the vertex.
  //
  // Space is used for rounding values first. If there is space left over,
  // then we apply smoothing, if it was requested.
  const float actualSmoothing0 = calculateActualSmoothingValue(allowedCut0);

  const float actualSmoothing1 = calculateActualSmoothingValue(allowedCut1);

  // Scale the radius if needed.
  const float actualR = m_cornerRadius * actualRoundCut / m_expectedRoundCut;

  // Distance from the corner (p1) to the center.
  const float centerDistance =
      std::sqrt((actualR * actualR) + (actualRoundCut * actualRoundCut));

  // Center of the arc we will use for rounding.
  m_center = p1 + ((m_d1 + m_d2) / 2.0f).direction() * centerDistance;

  const Point circleIntersection0 = p1 + m_d1 * actualRoundCut;

  const Point circleIntersection2 = p1 + m_d2 * actualRoundCut;

  const Cubic flanking0 = computeFlankingCurve(
      actualRoundCut, actualSmoothing0, p1, p0, circleIntersection0,
      circleIntersection2, m_center, actualR);

  const Cubic flanking2 =
      computeFlankingCurve(actualRoundCut, actualSmoothing1, p1, p2,
                           circleIntersection2, circleIntersection0, m_center,
                           actualR)
          .reverse();

  return {flanking0,
          Cubic::circularArc(m_center.x(), m_center.y(), flanking0.anchor1X(),
                             flanking0.anchor1Y(), flanking2.anchor0X(),
                             flanking2.anchor0Y()),

          flanking2};
}

float RoundedPolygon::RoundedCorner::calculateActualSmoothingValue(
    float allowedCut) const noexcept {
  if (allowedCut > expectedCut()) {
    return m_smoothing;
  } else if (allowedCut > m_expectedRoundCut) {
    return m_smoothing * (allowedCut - m_expectedRoundCut) /
           (expectedCut() - m_expectedRoundCut);
  } else {
    return 0.0;
  }
}

Cubic RoundedPolygon::RoundedCorner::computeFlankingCurve(
    float actualRoundCut, float actualSmoothingValues, const Point &corner,
    const Point &sideStart, const Point &circleSegmentIntersection,
    const Point &otherCircleSegmentIntersection, const Point &circleCenter,
    float actualR) const noexcept

{
  // sideStart is the anchor, 'anchor' is actual control point
  const Point sideDirection = (sideStart - corner).direction();

  const Point curveStart =
      corner + sideDirection * actualRoundCut * (1.0 + actualSmoothingValues);

  // We use an approximation to cut a part of the circle section
  // proportional to 1 - smooth.
  //
  // When smooth = 0, we take the full section,
  // when smooth = 1, we take nothing.
  //
  const Point p = Point::lerp(
      circleSegmentIntersection,
      circleSegmentIntersection +
          (circleSegmentIntersection + otherCircleSegmentIntersection) / 2.0f,
      actualSmoothingValues);

  // The flanking curve ends on the circle.
  const Point curveEnd =
      circleCenter + Point::directionVector(p.x() - circleCenter.x(),
                                            p.y() - circleCenter.y()) *
                         actualR;

  // The anchor on the circle segment side is in the intersection
  // between the tangent to the circle in the circle/flanking curve
  // boundary and the linear segment.
  const Point circleTangent = (curveEnd - circleCenter).rotate90();

  const std::optional<Point> anchorEnd =
      lineIntersection(sideStart, sideDirection, curveEnd, circleTangent);

  // From what remains, we pick a point for the start anchor.
  // 2/3 seems to come from design tools?
  const Point anchorStart =
      (curveStart + anchorEnd.value_or(circleSegmentIntersection) * 2.0f) /
      3.0f;

  return Cubic(curveStart, anchorStart,
               anchorEnd.value_or(circleSegmentIntersection), curveEnd);
}

std::optional<Point> RoundedPolygon::RoundedCorner::lineIntersection(
    const Point &p0, const Point &d0, const Point &p1,
    const Point &d1) const noexcept {
  const Point rotatedD1 = d1.rotate90();

  const float den = d0.dotProduct(rotatedD1);

  if (std::abs(den) < shape_utils::DISTANCE_EPSILON) {
    return std::nullopt;
  }

  const float num = (p1 - p0).dotProduct(rotatedD1);

  // Also check the relative value. This is equivalent to
  // abs(den / num) < shape_utils::DISTANCE_EPSILON, but avoid doing a division.
  if (std::abs(den) < shape_utils::DISTANCE_EPSILON * std::abs(num)) {
    return std::nullopt;
  }

  const float k = num / den;

  return p0 + d0 * k;
}

RoundedPolygon *RoundedPolygon::Circle(int verticesNum, const float radius,
                                       const float centerX,
                                       const float centerY) noexcept {
  // Half of the angle between two adjacent vertices on the polygon
  const float theta = PI_F / verticesNum;
  // Radius of the underlying RoundedPolygon object given the desired radius of
  // the circle
  const float polygonRadius = radius / std::cos(theta);
  return Create(verticesNum, CornerRounding(radius), std::nullopt,
                polygonRadius, centerX, centerY);
}

RoundedPolygon *RoundedPolygon::Rectangle(
    float width, float height, const CornerRounding &rounding,
    std::optional<std::span<const CornerRounding>> perVertexRounding,
    const float centerX, const float centerY) noexcept {

  const auto left = centerX - width / 2;    // left
  const auto top = centerY - height / 2;    // top
  const auto right = centerX + width / 2;   // right
  const auto bottom = centerY + height / 2; // bottom

  const auto vertices =
      std::array<float, 8>{right, bottom, left, bottom, left, top, right, top};

  return Create(vertices, rounding, perVertexRounding, centerX, centerY);
}

RoundedPolygon *RoundedPolygon::Star(
    int verticesPerRadius, float radius, float innerRadius,
    const CornerRounding &rounding,
    const std::optional<CornerRounding> &innerRounding,
    std::optional<std::span<const CornerRounding>> perVertexRounding,
    const float centerX, const float centerY) {
  if (radius <= 0.0f || innerRadius <= 0.0f) {
    qFatal() << "Star radii must both be greater than 0";
    return nullptr;
  }
  if (innerRadius >= radius) {
    qFatal() << "innerRadius must be less than radius";
    return nullptr;
  }

  auto slice = starVerticesFromNumVerts(verticesPerRadius, radius, innerRadius,
                                        centerX, centerY);

  if (!perVertexRounding.has_value() && innerRounding.has_value()) {
    auto innerR = innerRounding.value();
    std::size_t pvRoundingSize = verticesPerRadius * 2;
    auto pvRounding = std::make_unique<CornerRounding[]>(pvRoundingSize);
    int offset = 0;
    for (int i = 0; i < verticesPerRadius; ++i) {
      pvRounding[offset++] = rounding;
      pvRounding[offset++] = innerR;
    }

    return Create(slice, rounding, std::span(pvRounding.get(), pvRoundingSize),
                  centerX, centerY);
  }

  return Create(slice, rounding, perVertexRounding, centerX, centerY);
}

RoundedPolygon *RoundedPolygon::PillStar(
    float width, float height, int verticesPerRadius, float innerRadius,
    const CornerRounding &rounding,
    const std::optional<CornerRounding> &innerRounding,

    std::optional<std::span<const CornerRounding>> perVertexRounding,
    float vertexSpacing, float startLocation, float centerX, float centerY) {
  if (width < 0.0f || height < 0.0f) {
    qFatal() << "Pill shapes must have positive width and height";
    return nullptr;
  }
  if (innerRadius < 0 || innerRadius > 1) {
    qFatal() << "innerRadius must be between 0 and 1";
    return nullptr;
  }

  auto slice = pillStarVerticesFromNumVerts(verticesPerRadius, width, height,
                                            innerRadius, vertexSpacing,
                                            startLocation, centerX, centerY);

  if (!perVertexRounding.has_value() && innerRounding.has_value()) {
    auto innerR = innerRounding.value();
    std::size_t pvRoundingSize = verticesPerRadius * 2;
    auto pvRounding = std::make_unique<CornerRounding[]>(pvRoundingSize);
    int offset = 0;
    for (int i = 0; i < verticesPerRadius; ++i) {
      pvRounding[offset++] = rounding;
      pvRounding[offset++] = innerR;
    }

    return Create(slice, rounding, std::span(pvRounding.get(), pvRoundingSize),
                  centerX, centerY);
  }

  return Create(slice, rounding, perVertexRounding, centerX, centerY);
}

QString RoundedPolygon::toString() const {
  QString result = QStringLiteral("RoundedPolygon(features: [");

  for (size_t i = 0; i < m_features.size(); ++i) {
    if (i > 0)
      result += QStringLiteral(", ");

    result += m_features[i].toString();
  }

  result += QStringLiteral("], cubics: [");

  for (size_t i = 0; i < m_cubics.size(); ++i) {
    if (i > 0)
      result += QStringLiteral(", ");

    result += m_cubics[i].toString();
  }

  result += QStringLiteral("], center: ");
  result += m_center.toString();
  result += QLatin1Char(')');

  return result;
}

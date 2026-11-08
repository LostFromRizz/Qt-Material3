#include "polygon_measure.h"
#include "progressable_feature.h"
#include "utils.h"
#include <vector>

using namespace material::shapes;

namespace {
struct MeasuredData {
public:
  uint32_t featureIdx;
  uint32_t cubicIdx;
  float measurement;
  float size;
  bool isProgressableFeature;
};
} // namespace

MeasuredPolygon::MeasuredPolygon(
    Measurer *measurer, const RoundedPolygon *polygon,
    const std::vector<MeasuredCubic> &&cubics,
    const std::vector<ProgressableFeature> &&features,
    std::vector<Cubic> *sharedCubics)
    : m_measurer(measurer), m_polygon(polygon), m_cubics(std::move(cubics)),
      m_features(std::move(features)), m_extraCubics(sharedCubics) {
  Q_ASSERT_X(sharedCubics != nullptr, "Received nullptr from sharedCubics",
             "material::shapes::MeasuredPolygon");
}

std::optional<MeasuredPolygon>
MeasuredPolygon::cutAndShift(float cuttingPoint) {
  Q_ASSERT_X(cuttingPoint >= 0.0f && cuttingPoint <= 1.0f,
             "material::shapes::MeasuredPolygon::cutAndShift",
             "Cutting point is expected to be between 0 and 1");

  if (cuttingPoint < shape_utils::DISTANCE_EPSILON) {
    return std::nullopt;
  }

  auto it =
      std::find_if(cbegin(), cend(), [cuttingPoint](const MeasuredCubic &c) {
        return cuttingPoint >= c.m_startOtlProgress &&
               cuttingPoint <= c.m_endOtlProgress;
      });
  Q_ASSERT_X(it != cend(), "material::shapes::MeasuredPolygon::cutAndShift",
             "could not find target index");

  const MeasuredCubic &target = *it;

  const size_t targetIndex = std::distance(cbegin(), it);
  auto [b1, b2] = target.cutAtProgress(*this, cuttingPoint);

  std::vector<MeasuredCubic> retCubics;
  retCubics.reserve(m_cubics.size() + 1);

  float startOutlineProgress = 0.0f;
  bool addedB2 = false;
  const auto n = m_cubics.size() + 1;
  for (size_t i = 0; i < n; ++i) {
    if (i == 0) {
      const auto idx = (i + targetIndex) % m_cubics.size();
      const auto endProgress = shape_utils::positiveModulo(
          m_cubics[idx].m_endOtlProgress - cuttingPoint, 1.0f);

      if (endProgress > shape_utils::DISTANCE_EPSILON) {
        b2.m_startOtlProgress = 0.0f;
        b2.m_endOtlProgress = endProgress;
        startOutlineProgress = endProgress;
        retCubics.push_back(b2);
        addedB2 = true;
      } else {
        // removed b2 from ownedCubics
        m_extraCubics->pop_back();
      }

    } else if (i == n - 1) {
      if ((1.0f - startOutlineProgress) > shape_utils::DISTANCE_EPSILON) {
        b1.m_startOtlProgress = startOutlineProgress;
        b1.m_endOtlProgress = 1.0f;
        startOutlineProgress = 1.0f;
        retCubics.push_back(b1);
      } else {
        // removed b1 from ownedCubics
        m_extraCubics->erase(m_extraCubics->end() - 2);

        // since size is changed update b2 index if pushed
        if (addedB2) {
          retCubics[0].m_location = CubicLocation(static_cast<uint32_t>(
              m_extraCubics->size() - 1)); // always the first
        }
      }

    } else {
      const auto idx = (i + targetIndex) % m_cubics.size();
      const auto &cubic = m_cubics[idx];

      const auto endProgress = shape_utils::positiveModulo(
          m_cubics[idx].m_endOtlProgress - cuttingPoint, 1.0f);

      // Filter out "empty" cubics
      if ((endProgress - startOutlineProgress) >
          shape_utils::DISTANCE_EPSILON) {
        retCubics.emplace_back(cubic.m_location, startOutlineProgress,
                               endProgress, cubic.m_size);
        startOutlineProgress = endProgress;
      }
    }
  }
  if (!retCubics.empty()) {
    retCubics.back().m_endOtlProgress = 1.0f;
  }

  std::vector<ProgressableFeature> features;
  features.reserve(m_features.size());
  for (const auto &feature : m_features) {
    features.push_back(ProgressableFeature(
        feature.featureIdx(),
        shape_utils::positiveModulo(feature.progress() - cuttingPoint, 1.0f)));
  }

  return MeasuredPolygon(m_measurer, m_polygon, std::move(retCubics),
                         std::move(features), m_extraCubics);
}

MeasuredPolygon
MeasuredPolygon::measurePolygon(Measurer *measurer,
                                const RoundedPolygon &polygon,
                                std::vector<Cubic> &extraCubicsStorage) {

  std::vector<MeasuredData> measuredData;
  size_t featuresSize = 0;

  float lastMeasurement = 0.0f;

  const auto &features = polygon.features();

  measuredData.reserve(polygon.features().size() * 2);

  for (size_t featureIdx = 0; featureIdx < features.size(); ++featureIdx) {
    const auto &feature = features[featureIdx];
    const auto &cubics = feature.cubics();

    for (size_t cubicIdx = 0; cubicIdx < cubics.size(); ++cubicIdx) {
      const Cubic &cubic = cubics[cubicIdx];
      const float measurement = measurer->measureCubic(cubic);
      Q_ASSERT_X(measurement >= 0.0f,
                 "material::shapes::MeasuredPolygon::measurePolygon",
                 "Measured cubic is expected to be greater or equal to zero");

      bool isProgressableFeature = false;
      if (feature.isCorner() && cubicIdx == cubics.size() / 2) {
        ++featuresSize;
        isProgressableFeature = true;
      }

      measuredData.push_back(
          MeasuredData{.featureIdx = static_cast<uint32_t>(featureIdx),
                       .cubicIdx = static_cast<uint32_t>(cubicIdx),
                       .measurement = lastMeasurement,
                       .size = measurement,
                       .isProgressableFeature = isProgressableFeature});
      lastMeasurement += measurement;
    }
  }

  // qDebug() << "Total Size: " << lastMeasurement;

  std::vector<MeasuredCubic> measuredCubics;
  std::vector<ProgressableFeature> progressableFeatures;
  progressableFeatures.reserve(featuresSize);
  measuredCubics.reserve(measuredData.size());

  float startOutlineProgress = 0.0f;
  for (size_t i = 0; i < measuredData.size(); ++i) {
    const auto &data = measuredData[i];
    auto startProgress = data.measurement / lastMeasurement;
    auto endProgress = (i + 1 < measuredData.size())
                           ? measuredData[i + 1].measurement / lastMeasurement
                           : 1.0f;

    if (data.isProgressableFeature) {
      progressableFeatures.push_back(ProgressableFeature(
          shape_utils::positiveModulo((startProgress + endProgress) / 2, 1.0),
          data.featureIdx));
    }

    // Filter out "empty" cubics
    if ((endProgress - startProgress) > shape_utils::DISTANCE_EPSILON) {

      measuredCubics.emplace_back(CubicLocation(data.featureIdx, data.cubicIdx),
                                  startOutlineProgress, endProgress, data.size);
      // The next measured cubic will start exactly where this one ends.
      startOutlineProgress = endProgress;
    }
  }
  if (!measuredCubics.empty()) {
    // ensure the last end progress is 1.0
    measuredCubics.back().m_endOtlProgress = 1.0f;
  }

  return MeasuredPolygon(measurer, &polygon, std::move(measuredCubics),
                         std::move(progressableFeatures), &extraCubicsStorage);
}

MeasuredPolygon::MeasuredCubic::MeasuredCubic(CubicLocation location,
                                              float start, float end,
                                              float size)
    : m_location(location), m_startOtlProgress(start), m_endOtlProgress(end),
      m_size(size)

{};

std::pair<MeasuredPolygon::MeasuredCubic, MeasuredPolygon::MeasuredCubic>
MeasuredPolygon::MeasuredCubic::cutAtProgress(MeasuredPolygon &parent,
                                              float cutOutlineProgress) const {

  const float boundedCutOutlineProgress =
      std::clamp(cutOutlineProgress, m_startOtlProgress, m_endOtlProgress);
  const float outlineProgressSize = m_endOtlProgress - m_startOtlProgress;
  const float progressFromStart =
      boundedCutOutlineProgress - m_startOtlProgress;
  const float relativeProgress = progressFromStart / outlineProgressSize;
  const float t = parent.m_measurer->findCubicCutPoint(
      getCubic(parent), relativeProgress * m_size);
  Q_ASSERT_X(t >= 0.0f && t <= 1.0f,
             "material::shapes::MeasuredPolygon::cutAtProgress",
             "Cubic cut point is expected to be between 0 and 1");

  // qDebug() << qSetRealNumberPrecision(8)
  //         << "cutAtProgress: progress = " << boundedCutOutlineProgress << " /
  //         "
  //         << "this = [" << m_startOtlProgress << " .. " << m_endOtlProgress
  //         << "] / " << "ps = " << progressFromStart
  //         << " / rp = " << relativeProgress << " / t = " << t;

  const auto &[c1, c2] = getCubic(parent).split(t);
  const auto c1Size = parent.m_measurer->measureCubic(c1);
  const auto c2Size = parent.m_measurer->measureCubic(c2);
  parent.m_extraCubics->push_back(c1);
  parent.m_extraCubics->push_back(c2);

  return std::make_pair(
      MeasuredCubic(CubicLocation(parent.m_extraCubics->size() - 2),
                    m_startOtlProgress, boundedCutOutlineProgress, c1Size),
      MeasuredCubic(CubicLocation(parent.m_extraCubics->size() - 1),
                    boundedCutOutlineProgress, m_endOtlProgress, c2Size));
}

float LengthMeasurer::measureCubic(const Cubic &c) const {
  return closestProgressTo(c, std::numeric_limits<float>::infinity()).second;
}
float LengthMeasurer::findCubicCutPoint(const Cubic &c, float m) const {
  return closestProgressTo(c, m).first;
};

std::pair<float, float>
LengthMeasurer::closestProgressTo(const Cubic &cubic, float threshold) const {
  float total = 0.0f;
  float remainder = threshold;
  Point prev(cubic.anchor0X(), cubic.anchor0Y());

  for (int i = 1; i <= m_segments; ++i) {
    const float progress = static_cast<float>(i) / m_segments;
    const Point point = cubic.pointOnCurve(progress);
    const float segment = (point - prev).distance();

    if (segment >= remainder) {
      return {progress - (1.0f - remainder / segment) / m_segments, threshold};
    }

    remainder -= segment;
    total += segment;
    prev = point;
  }

  return {1.0f, total};
}

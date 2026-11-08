#include "feature_mapping.h"
#include "float_mapping.h"
#include "utils.h"
#include <algorithm>

using namespace material::shapes;

namespace {
using namespace material::shapes;

inline Point featureRepresentativePoint(const Feature &feature) {
  const auto &front = feature.cubics().front();
  const auto &back = feature.cubics().back();
  const auto x = (front.anchor0X() + back.anchor1X()) / 2.0f;
  const auto y = (front.anchor0Y() + back.anchor1Y()) / 2.0f;
  return Point(x, y);
}

float featureDistSquared(const Feature &f1, const Feature &f2) {
  if (f1.isConvexCorner() != f2.isConvexCorner()) {
    // qDebug() << "*** Feature distance ∞ for convex-vs-concave corners";
    return std::numeric_limits<float>::max();
  }
  return (featureRepresentativePoint(f1) - featureRepresentativePoint(f2))
      .distanceSquared();
}

struct PairHasher {
  std::size_t
  operator()(const std::pair<ProgressableFeature, ProgressableFeature> &p)
      const noexcept {
    const auto hashFeature = [](const ProgressableFeature &feature) {
      const auto h1 = std::hash<float>{}(feature.progress());
      const auto h2 = std::hash<uint32_t>{}(feature.featureIdx());

      return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    };

    const auto h1 = hashFeature(p.first);
    const auto h2 = hashFeature(p.second);

    return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
  }
};
;

} // namespace

DoubleMapper feature_mapping::featureMapper(const MeasuredPolygon &p1,
                                            const MeasuredPolygon &p2) {
  auto m = doMapping(p1, p2);
  return DoubleMapper::Create(std::move(m));
}

std::vector<std::pair<float, float>> feature_mapping::doMapping(

    const MeasuredPolygon &p1, const MeasuredPolygon &p2) {

  std::vector<DistanceVertex> distVertexes;
  distVertexes.reserve(std::max(p1.features().size(), p2.features().size()) /
                       2);
  auto featureIsVaildCorner = [](const ProgressableFeature &f,
                                 const MeasuredPolygon &p) {
    return p.hasFeature(f) && p.getFeature(f).isCorner();
  };
  const auto &features1 = p1.features();
  const auto &features2 = p2.features();
  for (size_t i = 0; i < features1.size(); ++i) {
    const auto &f1 = features1[i];
    if (!featureIsVaildCorner(f1, p1)) {
      continue;
    }
    for (size_t j = 0; j < features2.size(); ++j) {
      const auto &f2 = features2[j];
      if (!featureIsVaildCorner(f2, p2)) {
        continue;
      }

      float d = featureDistSquared(p1.getFeature(f1), p2.getFeature(f2));
      //
      if (d != std::numeric_limits<float>::max()) {
        distVertexes.emplace_back(d, f1, f2);
      }
    }
  }

  std::sort(distVertexes.begin(), distVertexes.end(),
            [](const DistanceVertex &a, const DistanceVertex &b) {
              return a.distance < b.distance;
            });

  if (distVertexes.empty()) {
    return {std::make_pair(0.0f, 0.0f), std::make_pair(0.5f, 0.5f)};
  }

  if (distVertexes.size() == 1) {
    const auto &[f1, f2] = distVertexes.front().features;
    return {std::make_pair(f1.progress(), f2.progress()),
            std::make_pair(std::fmod((f1.progress() + 0.5f), 1.0f),
                           std::fmod((f2.progress() + 0.5f), 1.0f))};
  }

  // do mapping
  std::vector<std::pair<float, float>> mapping;
  std::unordered_set<std::pair<ProgressableFeature, ProgressableFeature>,
                     PairHasher>
      used{};

  for (const auto &distVertex : distVertexes) {
    if (used.contains(distVertex.features)) {
      continue;
    }

    const auto &[f1, f2] = distVertex.features;
    const auto it =
        std::lower_bound(mapping.begin(), mapping.end(), f1.progress(),
                         [](const auto &entry, float progress) {
                           return entry.first < progress;
                         });

    const auto index = std::distance(mapping.begin(), it);
    const auto n = mapping.size();

    if (n >= 1) {
      const auto &[before1, before2] = mapping[(index + n - 1) % n];
      const auto &[after1, after2] = mapping[index % n];

      // We don't want features that are way too close to each other, that will
      // make the DoubleMapper unstable
      if (DoubleMapper::progressDistance(f1.progress(), before1) <
              shape_utils::DISTANCE_EPSILON ||
          DoubleMapper::progressDistance(f1.progress(), after1) <
              shape_utils::DISTANCE_EPSILON ||
          DoubleMapper::progressDistance(f2.progress(), before2) <
              shape_utils::DISTANCE_EPSILON ||
          DoubleMapper::progressDistance(f2.progress(), after2) <
              shape_utils::DISTANCE_EPSILON) {
        continue;
      }

      // When we have 2 or more elements, we need to ensure we are not adding
      // extra crossings.
      if (n > 1 &&
          !DoubleMapper::progressInRange(f2.progress(), before2, after2))
        continue;
    }
    mapping.emplace(mapping.begin() + index, f1.progress(), f2.progress());
    used.insert(distVertex.features);
  }

  return mapping;
}

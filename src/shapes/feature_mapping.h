#ifndef MATERIAL_SHAPES_FEATUREMAPPING_H
#define MATERIAL_SHAPES_FEATUREMAPPING_H

#include "float_mapping.h"
#include "polygon_measure.h"
#include "progressable_feature.h"
#include <vector>

namespace material::shapes::feature_mapping {
struct DistanceVertex {
public:
  float distance;
  std::pair<ProgressableFeature, ProgressableFeature> features;
  DistanceVertex(float d, const ProgressableFeature &f1,
                 const ProgressableFeature &f2)
      : distance(d), features(f1, f2) {}
};

DoubleMapper featureMapper(const MeasuredPolygon &p1,
                           const MeasuredPolygon &p2);

std::vector<std::pair<float, float>> doMapping(const MeasuredPolygon &p1,
                                               const MeasuredPolygon &p2);

} // namespace material::shapes::feature_mapping

#endif

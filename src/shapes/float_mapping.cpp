#include "float_mapping.h"
#include "qdebug.h"
#include "utils.h"
#include <qhashfunctions.h>

using namespace material::shapes;

DoubleMapper::DoubleMapper(const std::vector<std::pair<float, float>> &&values)
    : m_values(std::move(values)) {}

namespace {
template <std::size_t X, std::size_t Y>
float linearMap(const std::vector<std::pair<float, float>> &values, float x) {
  Q_ASSERT_X(x >= 0.0f && x <= 1.0f,
             "material::shapes::feature_mapper::linearMap",
             qPrintable(QString("Invalid progress: %1").arg(x, 0, 'g', 8)));

  size_t segmentStartIndex = 0;
  for (; segmentStartIndex < values.size(); ++segmentStartIndex) {
    const float curr = std::get<X>(values[segmentStartIndex]);
    const float next =
        std::get<X>(values[(segmentStartIndex + 1) % values.size()]);

    if (material::shapes::DoubleMapper::progressInRange(x, curr, next)) {
      break;
    }
  }
  const float segmentEndIndex = (segmentStartIndex + 1) % values.size();

  const float segmentSizeX = material::shapes::shape_utils::positiveModulo(
      std::get<X>(values[segmentEndIndex]) -
          std::get<X>(values[segmentStartIndex]),
      1.0f);

  const float segmentSizeY = material::shapes::shape_utils::positiveModulo(
      std::get<Y>(values[segmentEndIndex]) -
          std::get<Y>(values[segmentStartIndex]),
      1.0f);

  const float positionInSegment =
      (segmentSizeX < 0.001f)
          ? 0.5f
          : material::shapes::shape_utils::positiveModulo(
                x - std::get<X>(values[segmentStartIndex]), 1.0f) /
                segmentSizeX;

  return material::shapes::shape_utils::positiveModulo(
      std::get<Y>(values[segmentStartIndex]) + segmentSizeY * positionInSegment,
      1.0f);
}
} // namespace

DoubleMapper DoubleMapper::Create(
    const std::vector<std::pair<float, float>> &&mappings) noexcept {
  Q_ASSERT(!mappings.empty());
  auto [prev1, prev2] = mappings.back();
  size_t wraps = 0;

#define LOCAL_ASSERT(cond, msg, f1, f2)                                        \
  Q_ASSERT_X(cond, "material::shapes::feature_mapper::DoubleMapper::Create",   \
             qPrintable(QString(msg).arg(f1, 0, 'g', 8).arg(f2, 0, 'g', 8)))

  for (const auto [f1, f2] : mappings) {
    LOCAL_ASSERT(f1 >= 0.0f && f1 < 1.0f && f2 >= 0.0f && f2 < 1.0f,
                 "Progress outside of range: %1, %2", f1, f2);
    LOCAL_ASSERT(progressDistance(f1, prev1) > shape_utils::DISTANCE_EPSILON &&
                     progressDistance(f2, prev2) >
                         shape_utils::DISTANCE_EPSILON,
                 "Progress outside of range: %1, %2", f1, f2);
    if (f1 < prev1 && f2 < prev2) {
      ++wraps;
      LOCAL_ASSERT(wraps <= 1, "Progress wraps more than once: %1, %2", f1, f2);
    }

    prev1 = f1;
    prev2 = f2;
  }

#undef LOCAL_ASSERT

  return DoubleMapper(std::move(mappings));
}

float DoubleMapper::map(float x) const { return linearMap<0, 1>(m_values, x); }

float DoubleMapper::mapBack(float x) const {
  return linearMap<1, 0>(m_values, x);
}

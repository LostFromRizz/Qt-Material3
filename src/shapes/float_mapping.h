#ifndef MATERIAL_SHAPES_DOUBLEMAPPER_H
#define MATERIAL_SHAPES_DOUBLEMAPPER_H

#include <cstdlib>
#include <utility>
#include <vector>

namespace material::shapes {
class DoubleMapper {
public:
  static DoubleMapper
  Create(const std::vector<std::pair<float, float>> &&) noexcept;

  static constexpr inline bool progressInRange(float progress,
                                               float progressFrom,
                                               float progressTo) noexcept {
    if (progressTo >= progressFrom) {
      return progress >= progressFrom && progress <= progressTo;
    } else {
      return progress >= progressFrom || progress <= progressTo;
    }
  }

  static constexpr inline float progressDistance(float p1, float p2) {
    const float d = std::abs(p1 - p2);
    return std::min(d, 1.0f - d);
  }

  float map(float x) const;
  float mapBack(float x) const;

private:
  explicit DoubleMapper(const std::vector<std::pair<float, float>> &&values);

  // float linearMap(float x) const;
  const std::vector<std::pair<float, float>> m_values;
};

} // namespace material::shapes

#endif // MATERIAL_SHAPES_DOUBLEMAPPER_H

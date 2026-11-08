#ifndef MATERIAL_SHAPES_PROGRESSABLE_FEATURE_H
#define MATERIAL_SHAPES_PROGRESSABLE_FEATURE_H

#include <cstdint>

namespace material::shapes {

struct ProgressableFeature {
  explicit ProgressableFeature(float progress, uint32_t featureIdx)
      : m_progress(progress), m_featureIdx(featureIdx) {}

  constexpr inline float progress() const noexcept { return m_progress; }
  constexpr inline void setProgress(float progress) noexcept {
    m_progress = progress;
  }
  constexpr inline uint32_t featureIdx() const noexcept { return m_featureIdx; }

  friend constexpr inline bool
  operator==(const ProgressableFeature &lhs,
             const ProgressableFeature &rhs) noexcept {
    return lhs.m_progress == rhs.m_progress &&
           lhs.m_featureIdx == rhs.m_featureIdx;
  }

  friend constexpr inline bool
  operator!=(const ProgressableFeature &lhs,
             const ProgressableFeature &rhs) noexcept {
    return lhs.m_progress != rhs.m_progress &&
           lhs.m_featureIdx != rhs.m_featureIdx;
  }

private:
  float m_progress;
  uint32_t m_featureIdx;
};
} // namespace material::shapes

#endif // MATERIAL_SHAPES_PROGRESSABLEFEATURE_H

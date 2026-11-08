#ifndef MATERIAL_SHAPES_CUBIC_LOCATION_H
#define MATERIAL_SHAPES_CUBIC_LOCATION_H

#include <limits>
#include <qassert.h>
#include <qdebug.h>

namespace material::shapes {

class CubicLocation {
public:
  explicit CubicLocation(uint32_t featureIndex, uint32_t cubicIndex);
  explicit CubicLocation(uint32_t cubicIndex);

  inline bool isExtra() const noexcept;
  inline uint32_t extraCubicIndex() const noexcept;
  inline uint32_t featureCubicIndex() const noexcept;
  inline uint32_t cubicIndex() const noexcept;
  inline uint32_t featureIndex() const noexcept;

  inline QDebug friend operator<<(QDebug debug, const CubicLocation &location) {
    QDebugStateSaver saver(debug);

    return debug.nospace()
           << QString("CubicLocation(featureIndex: %2, cubicIndex: %3)")
                  .arg(location.isExtra()
                           ? QStringLiteral("")
                           : QString::number(location.m_featureIdx))
                  .arg(location.m_cubicIdx);
  }

private:
  static constexpr uint32_t EXTRA = std::numeric_limits<uint32_t>::max();

  uint32_t m_featureIdx;
  uint32_t m_cubicIdx;
};

inline bool CubicLocation::isExtra() const noexcept {
  return m_featureIdx == CubicLocation::EXTRA;
}

inline uint32_t CubicLocation::featureIndex() const noexcept {
  Q_ASSERT_X(m_featureIdx != CubicLocation::EXTRA, "Extra owned cubic",
             "material::shapes::CubicLocation::featureIndex");
  return m_featureIdx;
}

inline uint32_t CubicLocation::cubicIndex() const noexcept {
  return m_cubicIdx;
}

} // namespace material::shapes

#endif // MATERIAL_SHAPES_CUBIC_LOCATION_H

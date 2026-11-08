#ifndef MATERIAL_INTERNAL_SHAPES_FEATURES_H
#define MATERIAL_INTERNAL_SHAPES_FEATURES_H

#include "cubic.h"
#include <internals/collections/slice.h>

namespace material::shapes {
class Feature final {

public:
  explicit Feature();
  explicit Feature(internals::collections::Slice<Cubic> &&cubics);
  explicit Feature(internals::collections::Slice<Cubic> &&cubics, bool convex);

  Feature(const Feature &) = delete;
  Feature &operator=(const Feature &) = delete;

  Feature(Feature &&) noexcept = default;
  Feature &operator=(Feature &&) noexcept = default;

  static inline Feature
  Edge(internals::collections::Slice<Cubic> &&cubics) noexcept {
    return Feature(std::move(cubics));
  }

  static inline Feature Corner(internals::collections::Slice<Cubic> &&cubics,
                               bool convex = true) noexcept {
    return Feature(std::move(cubics), convex);
  }

  inline const internals::collections::Slice<Cubic> &cubics() const noexcept {
    return m_cubics;
  };

  bool isIgnorableFeature() const noexcept {
    return m_type == Feature::Type::EdgeFeature;
  }
  bool isEdge() const noexcept { return m_type == Feature::Type::EdgeFeature; }
  bool isCorner() const noexcept {
    return m_type == Feature::Type::CornerFeature;
  }
  bool isConvexCorner() const noexcept {
    return m_convex && m_type == Feature::Type::CornerFeature;
  }
  bool isConcaveCorner() const noexcept {
    return !m_convex && m_type == Feature::Type::CornerFeature;
  }
  Feature reversed() const noexcept;

  void transform(const Cubic::PointTransformer &) noexcept;

  Feature transformed(const Cubic::PointTransformer &) const noexcept;

  inline Feature clone() const noexcept {
    auto cubicsClone = internals::collections::Slice<Cubic>(m_cubics.size());
    for (std::size_t i = 0; i < m_cubics.size(); ++i) {
      cubicsClone[i] = m_cubics[i];
    }
    return Feature(std::move(cubicsClone), m_type, m_convex);
  }

  inline friend QDebug operator<<(QDebug debug, const Feature &feature) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "Feature";
    if (feature.isCorner()) {
      debug.nospace() << "::Corner";
    } else {
      debug.nospace() << "::Edge";
    }
    debug.nospace() << "{ cubics: " << feature.m_cubics;
    if (feature.isCorner()) {
      debug.nospace() << ", convex: " << feature.m_convex;
    }
    debug.nospace() << " }";
    return debug;
  }

  inline friend bool operator==(const Feature &lhs, const Feature &rhs) {
    return lhs.m_type == rhs.m_type && lhs.m_convex == rhs.m_convex &&
           lhs.m_cubics == rhs.m_cubics;
  }
  inline friend bool operator!=(const Feature &lhs, const Feature &rhs) {
    return !(lhs == rhs);
  }

  QString toString() const;

private:
  enum Type { EdgeFeature, CornerFeature };

  explicit Feature(internals::collections::Slice<Cubic> &&cubics,
                   Type featureType, bool convex);

  internals::collections::Slice<Cubic> m_cubics;
  Type m_type;
  bool m_convex;
};

} // namespace material::shapes

#endif // MATERIAL_INTERNAL_SHAPES_FEATURES_H

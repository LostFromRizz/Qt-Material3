#include "shapes_features.h"

using namespace material::shapes;

Feature::Feature() : m_cubics(0), m_type(EdgeFeature), m_convex(false) {}

Feature::Feature(internals::collections::Slice<Cubic> &&cubics)
    : m_cubics(std::move(cubics)), m_type(EdgeFeature), m_convex(false) {}

Feature::Feature(internals::collections::Slice<Cubic> &&cubics, bool convex)
    : m_cubics(std::move(cubics)), m_type(CornerFeature), m_convex(convex) {}

Feature::Feature(internals::collections::Slice<Cubic> &&cubics,
                 Feature::Type featureType, bool convex)
    : m_cubics(std::move(cubics)), m_type(featureType), m_convex(convex) {}

Feature Feature::reversed() const noexcept {
  auto newCubics = internals::collections::Slice<Cubic>(m_cubics.size());

  std::size_t i = 0;
  for (const auto &item : std::views::reverse(m_cubics)) {
    newCubics[i++] = item.reverse();
  }
  return Feature(std::move(newCubics), m_type, m_convex);
}

void Feature::transform(const Cubic::PointTransformer &f) noexcept {
  for (auto &item : m_cubics) {
    item.transform(f);
  }
}

Feature Feature::transformed(const Cubic::PointTransformer &f) const noexcept {
  auto newCubics = internals::collections::Slice<Cubic>(m_cubics.size());

  std::size_t i = 0;
  for (const auto &item : m_cubics) {
    newCubics[i++] = item.transformed(f);
  }

  return Feature(std::move(newCubics), m_type, m_convex);
}

QString Feature::toString() const {
  QString result = QStringLiteral("Feature::");
  if (isCorner()) {
    result += QStringLiteral("Corner");
  } else {
    result += QStringLiteral("Edge");
  }
  result += "(cubics: [";

  for (size_t i = 0; i < m_cubics.size(); ++i) {
    if (i > 0)
      result += QStringLiteral(", ");

    result += m_cubics[i].toString();
  }
  result += QStringLiteral("], isIgnorableFeature: %1, isEdge: %2, "
                           "isConvexCorner: %3, isConcaveCorner: %4)")
                .arg(isIgnorableFeature())
                .arg(isEdge())
                .arg(isConvexCorner())
                .arg(isConcaveCorner());

  return result;
}

#ifndef MATERIAL_SHAPES_MORPH_H
#define MATERIAL_SHAPES_MORPH_H

#include "cubic_location.h"
#include "rounded_polygon.h"
#include <array>
#include <qtmetamacros.h>
#include <utility>
#include <vector>

namespace material::shapes {

class Morph : public QObject {
  Q_OBJECT
  Q_PROPERTY(material::shapes::RoundedPolygon *start READ start WRITE setStart
                 NOTIFY startChanged FINAL)
  Q_PROPERTY(material::shapes::RoundedPolygon *end READ end WRITE setEnd NOTIFY
                 endChanged FINAL)
  QML_ELEMENT
public:
  struct CubicLocationWrapper {
    const uint32_t polygon; // ignore in case cubic is inside extra
    const CubicLocation location;

    CubicLocationWrapper(CubicLocation location);

    CubicLocationWrapper(uint32_t polygonIndex, CubicLocation location);
  };

  // static Morph Create(const RoundedPolygon &start, const RoundedPolygon
  // &end);

  Morph(QObject *parent = nullptr);
  Morph(const Morph &) = delete;
  Morph &operator=(const Morph &) = delete;
  Morph(Morph &&) = delete;
  Morph &operator=(Morph &&) = delete;

  Cubic::BoundsArray calculateMaxBounds(Cubic::BoundsArray &&bounds) const;
  Cubic::BoundsArray calculateBounds(Cubic::BoundsArray &&bounds,
                                     bool approx = true) const;

  inline friend QDebug operator<<(QDebug debug, const Morph &morph) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "Morph(start: " << *(morph.m_polygons[0])
                    << ", end: " << *(morph.m_polygons[1])
                    << ", extraCubics: " << morph.m_extraCubics
                    << ", matches: ";
    for (std::size_t i = 0; i < morph.m_matches.size(); ++i) {
      if (i != 0)
        debug << ",";
      const auto &match = morph.m_matches[i];
      debug << "(" << morph.getCubic(match.first) << ", "
            << morph.getCubic(match.second) << ")";
    }

    debug << ")";
    return debug;
  }

  std::size_t matchSize() const { return m_matches.size() * 2; }
  std::size_t extraCubicSize() const { return m_extraCubics.size(); }

  RoundedPolygon *start() const;
  void setStart(RoundedPolygon *);

  RoundedPolygon *end() const;
  void setEnd(RoundedPolygon *);

  Q_INVOKABLE void setPolygons(RoundedPolygon *start, RoundedPolygon *end);

  Q_INVOKABLE QList<Cubic> asCubics(float progress);
  Q_INVOKABLE QList<Cubic> inline asCubics(qreal progress) {
    return asCubics(static_cast<float>(progress));
  }

signals:
  void startChanged();
  void endChanged();
  void polygonsChanged();

private:
  // explicit Morph(
  //     std::array<RoundedPolygon *, 2> &&polygons,
  //     std::vector<Cubic> &&ownedCubics,
  //     std::vector<std::pair<CubicLocationWrapper, CubicLocationWrapper>>
  //         &&matches);

  static std::vector<std::pair<CubicLocationWrapper, CubicLocationWrapper>>
  match(const RoundedPolygon &p1, const RoundedPolygon &p2,
        std::vector<Cubic> &ownedCubics);

  const Cubic &getCubic(const CubicLocationWrapper &wrapper) const {
    if (wrapper.location.isExtra()) {
      return m_extraCubics[wrapper.location.cubicIndex()];
    } else {
      return m_polygons[wrapper.polygon]
          ->features()[wrapper.location.featureIndex()]
          .cubics()[wrapper.location.cubicIndex()];
    }
  }

  std::vector<Cubic> m_extraCubics;
  // cubic indexes
  std::vector<std::pair<CubicLocationWrapper, CubicLocationWrapper>> m_matches;
  std::array<RoundedPolygon *, 2> m_polygons;
  QList<Cubic> m_cubics;
  bool m_dirty = true;
};

} // namespace material::shapes
#endif // MATERIAL_SHAPES_MORPH_H

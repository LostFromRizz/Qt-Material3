#ifndef MATERIAL_SHAPES_POLYGON_MEASURE_H
#define MATERIAL_SHAPES_POLYGON_MEASURE_H

#include "cubic_location.h"
#include "progressable_feature.h"
#include "rounded_polygon.h"
#include <optional>

namespace material::shapes {

class Measurer {
public:
  virtual ~Measurer() = default;
  virtual float measureCubic(const Cubic &c) const = 0;
  virtual float findCubicCutPoint(const Cubic &c, float m) const = 0;
};

class MeasuredPolygon {
public:
  friend class MeasuredCubic;

  MeasuredPolygon(const MeasuredPolygon &) = delete;
  MeasuredPolygon &operator=(const MeasuredPolygon &) = delete;

  MeasuredPolygon(MeasuredPolygon &&) = default;
  MeasuredPolygon &operator=(MeasuredPolygon &&) = default;

  class MeasuredCubic {
    friend class MeasuredPolygon;

  public:
    explicit MeasuredCubic(CubicLocation location, float start, float end,
                           float size);

    MeasuredCubic(const MeasuredCubic &) = default;
    MeasuredCubic &operator=(const MeasuredCubic &) = default;
    MeasuredCubic(MeasuredCubic &&) = default;
    MeasuredCubic &operator=(MeasuredCubic &&) = default;

    std::pair<MeasuredCubic, MeasuredCubic>
    cutAtProgress(MeasuredPolygon &parent, float cutOutlineProgress) const;

    inline const Cubic &getCubic(const MeasuredPolygon &parent) const noexcept {
      if (m_location.isExtra()) {
        return (*parent.m_extraCubics)[m_location.cubicIndex()];
      } else {
        return parent.m_polygon->features()[m_location.featureIndex()]
            .cubics()[m_location.cubicIndex()];
      }
    }

    inline bool isExtra() const noexcept { return m_location.isExtra(); }
    inline CubicLocation location() const noexcept { return m_location; }

    inline float startOutlineProgress() const noexcept {
      return m_startOtlProgress;
    }
    inline float endOutlineProgress() const noexcept {
      return m_endOtlProgress;
    }
    inline float size() const noexcept { return m_size; }

    inline QDebug friend operator<<(QDebug debug, const MeasuredCubic &cubic) {
      QDebugStateSaver saver(debug);

      // clang-format off
     debug.nospace() << "MeasuredCubic(" <<
				"location: " <<cubic.m_location<< ", " <<
				"startOutlineProgress: " << cubic.m_startOtlProgress<< ", " <<
				"endOutlineProgress: " << cubic.m_endOtlProgress<< ", " <<
				"size: " << cubic.m_size << ")";
      // clang-format on
      return debug;
    }

  private:
    CubicLocation m_location;
    float m_startOtlProgress, m_endOtlProgress;
    float m_size;
  };

  static MeasuredPolygon measurePolygon(Measurer *measurer,
                                        const RoundedPolygon &polygon,
                                        std::vector<Cubic> &extraCubicStorage);

  const RoundedPolygon &polygon() const noexcept { return *m_polygon; }
  const std::vector<MeasuredCubic> &cubics() const noexcept {
    return m_cubics;
  };
  const std::vector<ProgressableFeature> &features() const noexcept {
    return m_features;
  };
  inline const std::vector<Cubic> &ownedCubics() const noexcept {
    return *m_extraCubics;
  };

  inline bool hasFeature(const ProgressableFeature &f) const {
    const auto &features = m_polygon->features();
    return f.featureIdx() < features.size();
  }

  inline std::optional<std::reference_wrapper<const material::shapes::Feature>>
  getFeatureOpt(const ProgressableFeature &f) const {
    const auto &features = m_polygon->features();
    if (f.featureIdx() < features.size()) {
      return std::cref(features[f.featureIdx()]);
    }
    return std::nullopt;
  }

  inline const material::shapes::Feature &
  getFeature(const ProgressableFeature &f) const {
    return m_polygon->features()[f.featureIdx()];
  }

  inline std::optional<MeasuredCubic> getCubicOpt(std::size_t index) const {
    if (index < m_cubics.size()) {
      return m_cubics[index];
    }
    return std::nullopt;
  }

  inline MeasuredCubic getCubic(size_t index) const { return m_cubics[index]; }

  auto begin() const noexcept { return m_cubics.cbegin(); }
  auto end() const noexcept { return m_cubics.cend(); }
  auto cbegin() const noexcept { return m_cubics.cbegin(); }
  auto cend() const noexcept { return m_cubics.cend(); }
  inline auto size() const noexcept { return m_cubics.size(); }

  std::optional<MeasuredPolygon> cutAndShift(float cuttingPoint);

private:
  MeasuredPolygon(Measurer *measurer, const RoundedPolygon *polygon,
                  const std::vector<MeasuredCubic> &&cubics,
                  const std::vector<ProgressableFeature> &&features,
                  std::vector<Cubic> *extraCubics);

  // references
  Measurer *m_measurer;
  const RoundedPolygon *m_polygon;
  std::vector<MeasuredCubic> m_cubics;
  std::vector<ProgressableFeature> m_features;

  // reference
  std::vector<Cubic> *m_extraCubics;
};

class LengthMeasurer final : public Measurer {
public:
  LengthMeasurer() = default;

  float measureCubic(const Cubic &c) const override;
  float findCubicCutPoint(const Cubic &c, float m) const override;

private:
  std::pair<float, float> closestProgressTo(const Cubic &cubic,
                                            float threshold) const;

  static constexpr int m_segments = 3;
};

} // namespace material::shapes
//

#endif // MATERIAL_SHAPES_MEASUREDPOLYGON_H

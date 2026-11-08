#ifndef MATERIAL_SHAPES_CORNERROUNDING_H
#define MATERIAL_SHAPES_CORNERROUNDING_H

namespace material::shapes {
struct CornerRounding {
public:
  constexpr explicit CornerRounding(float radius = 0.0, float smoothing = 0.0)
      : m_radius(radius), m_smoothing(smoothing) {}

  static const CornerRounding Unbounded;

  constexpr inline float radius() const { return m_radius; }
  constexpr inline float smoothing() const { return m_smoothing; }

private:
  float m_radius;
  float m_smoothing;
};
inline constexpr CornerRounding CornerRounding::Unbounded = CornerRounding();

} // namespace material::shapes

#endif // MATERIAL_SHAPES_CORNERROUNDING_H

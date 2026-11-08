#ifndef MATERIAL_SHAPES_SHAPES_UTILS_H
#define MATERIAL_SHAPES_SHAPES_UTILS_H

// #include "point.h"
#include <cmath>
#include <qassert.h>
#include <qmath.h>

namespace material::shapes::shape_utils {

constexpr inline float toRadians(float f) {
  return f / 360.0f * 2 * std::numbers::pi_v<float>;
}

constexpr inline float distance(float x, float y) {
  return std::sqrt(x * x + y * y);
};

constexpr inline float distanceSquared(float x, float y) {
  return x * x + y * y;
}

constexpr inline float lerp(float start, float stop, float value) {
  return (1.0f - value) * start + value * stop;
}

inline constexpr float positiveModulo(float num, float mod) {
  return std::fmod(std::fmod(num, mod) + mod, mod);
}

constexpr inline float DISTANCE_EPSILON = 1e-4f;
constexpr inline float ANGLE_EPSILON = 1e-6f;
constexpr inline float RELAXED_DISTANCE_EPSILON = 5e-3f;
} // namespace material::shapes::shape_utils

#endif // MATERIAL_INTERNALS_UTILS_H

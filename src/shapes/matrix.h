#ifndef MATERIAL_SHAPES_MATRIX_H
#define MATERIAL_SHAPES_MATRIX_H

#include "point.h"

namespace material::shapes {
struct Matrix {
  float m[4][4];

public:
  constexpr Matrix()
      : m{{1.0f, 0.0f, 0.0f, 0.0f},
          {0.0f, 1.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 1.0f, 0.0f},
          {0.0f, 0.0f, 0.0f, 1.0f}} {}

  constexpr Matrix(const float *data) { std::copy_n(data, 4 * 4, &m[0][0]); }

  constexpr inline Point map(const Point &p) const {
    const float x = p.x();
    const float y = p.y();
    const float z = m[0][3] * y + m[3][3];
    const float inverseZ = 1.0f / z;
    const float pZ = std::isfinite(inverseZ) ? inverseZ : 0.0f;
    return Point(pZ * (m[0][0] * x + m[1][0] * y + m[3][0]),
                 pZ * (m[0][1] * x + m[1][1] * y + m[3][1]));
  }

  inline void rotateZ(float degrees) {
    const float r = degrees * (std::numbers::pi_v<float> / 180.0f);
    const float s = std::sin(r);
    const float c = std::cos(r);

    const float a00 = m[0][0];
    const float a10 = m[1][0];
    const float v00 = c * a00 + s * a10;
    const float v10 = -s * a00 + c * a10;

    const float a01 = m[0][1];
    const float a11 = m[1][1];
    const float v01 = c * a01 + s * a11;
    const float v11 = -s * a01 + c * a11;

    const float a02 = m[0][2];
    const float a12 = m[1][2];
    const float v02 = c * a02 + s * a12;
    const float v12 = -s * a02 + c * a12;

    const float a03 = m[0][3];
    const float a13 = m[1][3];
    const float v03 = c * a03 + s * a13;
    const float v13 = -s * a03 + c * a13;

    m[0][0] = v00;
    m[0][1] = v01;
    m[0][2] = v02;
    m[0][3] = v03;
    m[1][0] = v10;
    m[1][1] = v11;
    m[1][2] = v12;
    m[1][3] = v13;
  }

  constexpr void scale(float x = 1.0f, float y = 1.0f, float z = 1.0f) {
    m[0][0] *= x;
    m[0][1] *= x;
    m[0][2] *= x;
    m[0][3] *= x;
    m[1][0] *= y;
    m[1][1] *= y;
    m[1][2] *= y;
    m[1][3] *= y;
    m[2][0] *= z;
    m[2][1] *= z;
    m[2][2] *= z;
    m[2][3] *= z;
  }
};
} // namespace material::shapes

#endif // MATERIAL_SHAPES_MATRIX_H

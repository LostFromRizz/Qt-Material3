#include "material_shapes.h"
#include <array>
#include <optional>
#include <shapes/utils.h>
#include <span>

using namespace material;
using namespace material::shapes;

namespace {
constexpr static const CornerRounding CornerRound15 = CornerRounding(0.15f);
constexpr static const CornerRounding CornerRound20 = CornerRounding(0.2f);
constexpr static const CornerRounding CornerRound30 = CornerRounding(0.3f);
constexpr static const CornerRounding CornerRound50 = CornerRounding(0.5f);
constexpr static const CornerRounding CornerRound100 = CornerRounding(0.1f);

static const Matrix RotateNeg45 = []() {
  Matrix m;
  m.rotateZ(-45.0f);
  return m;
}();
static const Matrix RotateNeg90 = []() {
  Matrix m;
  m.rotateZ(-90.0f);
  return m;
}();
static const Matrix RotateNeg135 = []() {
  Matrix m;
  m.rotateZ(-135.0f);
  return m;
}();

} // namespace

MaterialShapes::MaterialShapes(QObject *parent) : QObject(parent) {}

QPointNRound::QPointNRound(Point point, CornerRounding rounding)
    : p(point), r(rounding) {}

RoundedPolygon *MaterialShapes::createCircle(int vertices) {
  return RoundedPolygon::Circle(vertices);
}

RoundedPolygon *MaterialShapes::createSquare() {
  return RoundedPolygon::Rectangle(1.0f, 1.0f, CornerRound30);
}

RoundedPolygon *MaterialShapes::createSlanted() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.926f, 0.970f), CornerRounding(0.189f, 0.811f)),
          QPointNRound(Point(-0.021f, 0.967f), CornerRounding(0.187f, 0.057f)),
      },
      2);
}
RoundedPolygon *MaterialShapes::createArch() {
  auto p = RoundedPolygon::Create(
      4, CornerRounding::Unbounded,
      std::array{CornerRound100, CornerRound100, CornerRound20, CornerRound20});

  p->transform(RotateNeg135);
  return p;
}

RoundedPolygon *MaterialShapes::createFan() {
  return customPolygon(
      std::array{
          QPointNRound(Point(1.004f, 1.000f), CornerRounding(0.148f, 0.417f)),
          QPointNRound(Point(0.000f, 1.000f), CornerRounding(0.151f)),
          QPointNRound(Point(0.000f, -0.003f), CornerRounding(0.148f)),
          QPointNRound(Point(0.978f, 0.020f), CornerRounding(0.803f)),
      },
      1);
}
RoundedPolygon *MaterialShapes::createArrow() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.892f), CornerRounding(0.313f)),
          QPointNRound(Point(-0.216f, 1.050f), CornerRounding(0.207f)),
          QPointNRound(Point(0.499f, -0.160f), CornerRounding(0.215f, 1.000f)),
          QPointNRound(Point(1.225f, 1.060f), CornerRounding(0.211f))},
      1);
}
RoundedPolygon *MaterialShapes::createSemiCircle() {
  return RoundedPolygon::Rectangle(
      1.6f, 1.0f, CornerRounding::Unbounded,
      std::array{CornerRound20, CornerRound20, CornerRound100, CornerRound100});
}

RoundedPolygon *MaterialShapes::createOval() {
  Matrix m;
  m.scale(1.0f, 0.64f);
  auto p = RoundedPolygon::Circle();
  p->transform(m);
  p->transform(RotateNeg45);
  return p;
}

RoundedPolygon *MaterialShapes::createPill() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.961f, 0.039f), CornerRounding(0.426f)),
          QPointNRound(Point(1.001f, 0.428f)),
          QPointNRound(Point(1.000f, 0.609f), CornerRounding(1.000f)),
      },
      2, true);
}

RoundedPolygon *MaterialShapes::createTriangle() {
  auto p = RoundedPolygon::Create(3, CornerRound20);
  p->transform(RotateNeg90);
  return p;
}

RoundedPolygon *MaterialShapes::createDiamond() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 1.096f), CornerRounding(0.151f, 0.524f)),
          QPointNRound(Point(0.040f, 0.500f), CornerRounding(0.159f))},
      2);
}

RoundedPolygon *MaterialShapes::createClamShell() {
  return customPolygon(
      std::array{QPointNRound(Point(0.171f, 0.841f), CornerRounding(0.159f)),
                 QPointNRound(Point(-0.020f, 0.500f), CornerRounding(0.140f)),
                 QPointNRound(Point(0.170f, 0.159f), CornerRounding(0.159f))},
      2);
}

RoundedPolygon *MaterialShapes::createPentagon() {
  return customPolygon(
      std::array{QPointNRound(Point(0.500f, -0.009f), CornerRounding(0.172f)),
                 QPointNRound(Point(1.030f, 0.365f), CornerRounding(0.164f)),
                 QPointNRound(Point(0.828f, 0.970f), CornerRounding(0.169f))},
      1, true);
}

RoundedPolygon *MaterialShapes::createGem() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.499f, 1.023f), CornerRounding(0.241f, 0.778f)),
          QPointNRound(Point(-0.005f, 0.792f), CornerRounding(0.208f)),
          QPointNRound(Point(0.073f, 0.258f), CornerRounding(0.228f)),
          QPointNRound(Point(0.433f, -0.000f), CornerRounding(0.491f))},
      1, true);
}

RoundedPolygon *MaterialShapes::createSunny() {
  return RoundedPolygon::Star(8, 0.8f, 0.5f, CornerRound15);
}

RoundedPolygon *MaterialShapes::createVerySunny() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 1.080f), CornerRounding(0.085f)),
          QPointNRound(Point(0.358f, 0.843f), CornerRounding(0.085f)),
      },
      8);
}

RoundedPolygon *MaterialShapes::createCookie4Sided() {
  return customPolygon(
      std::array{
          QPointNRound(Point(1.237f, 1.236f), CornerRounding(0.258f)),
          QPointNRound(Point(0.500f, 0.918f), CornerRounding(0.233f)),
      },
      4);
}

RoundedPolygon *MaterialShapes::createCookie6Sided() {
  // 6-point cookie
  return customPolygon(
      std::array{
          QPointNRound(Point(0.723f, 0.884f), CornerRounding(0.394f)),
          QPointNRound(Point(0.500f, 1.099f), CornerRounding(0.398f)),
      },
      6);
}

RoundedPolygon *MaterialShapes::createCookie7Sided() {
  // 7-point cookie
  auto p = RoundedPolygon::Star(7, 0.75f, 0.5f, CornerRound50);
  p->transform(RotateNeg90);
  return p;
}

RoundedPolygon *MaterialShapes::createCookie9Sided() {
  auto p = RoundedPolygon::Star(9, 0.8f, 0.5f, CornerRound50);
  p->transform(RotateNeg90);
  return p;
}

RoundedPolygon *MaterialShapes::createCookie12Sided() {
  auto p = RoundedPolygon::Star(12, 0.8f,

                                0.5f, CornerRound50);

  p->transform(RotateNeg90);
  return p;
}

RoundedPolygon *MaterialShapes::createGhostish() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.000f), CornerRounding(1.000f)),
          QPointNRound(Point(1.000f, 0.000f), CornerRounding(1.000f)),
          QPointNRound(Point(1.000f, 1.140f), CornerRounding(0.254f, 0.106f)),
          QPointNRound(Point(0.575f, 0.906f), CornerRounding(0.253f)),
      },
      1, true);
}

RoundedPolygon *MaterialShapes::createClover4Leaf() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.074f)),
          QPointNRound(Point(0.725f, -0.099f), CornerRounding(0.476f)),
      },
      4, true);
}

RoundedPolygon *MaterialShapes::createClover8Leaf() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.036f)),
          QPointNRound(Point(0.758f, -0.101f), CornerRounding(0.209f)),
      },
      8);
}

RoundedPolygon *MaterialShapes::createBurst() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, -0.006f), CornerRounding(0.006f)),
          QPointNRound(Point(0.592f, 0.158f), CornerRounding(0.006f)),
      },
      12);
}

RoundedPolygon *MaterialShapes::createSoftBurst() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.193f, 0.277f), CornerRounding(0.053f)),
          QPointNRound(Point(0.176f, 0.055f), CornerRounding(0.053f)),
      },
      10, false, kCenter);
}

RoundedPolygon *MaterialShapes::createBoom() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.457f, 0.296f), CornerRounding(0.007f)),
          QPointNRound(Point(0.500f, -0.051f), CornerRounding(0.007f)),
      },
      15);
}

RoundedPolygon *MaterialShapes::createSoftBoom() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.733f, 0.454f)),
          QPointNRound(Point(0.839f, 0.437f), CornerRounding(0.532f)),
          QPointNRound(Point(0.949f, 0.449f), CornerRounding(0.439f, 1.000f)),
          QPointNRound(Point(0.998f, 0.478f), CornerRounding(0.174f)),
      },
      16, true);
}

RoundedPolygon *MaterialShapes::createFlower() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.370f, 0.187f)),
          QPointNRound(Point(0.416f, 0.049f), CornerRounding(0.381f)),
          QPointNRound(Point(0.479f, 0.001f), CornerRounding(0.095f)),
      },
      8, true);
}

RoundedPolygon *MaterialShapes::createPuffy() {
  Matrix m;
  m.scale(1.000f, 0.742f);

  auto p = customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.053f)),
          QPointNRound(Point(0.545f, -0.040f), CornerRounding(0.405f)),
          QPointNRound(Point(0.670f, -0.035f), CornerRounding(0.426f)),
          QPointNRound(Point(0.717f, 0.066f), CornerRounding(0.574f)),
          QPointNRound(Point(0.722f, 0.128f)),
          QPointNRound(Point(0.777f, 0.002f), CornerRounding(0.360f)),
          QPointNRound(Point(0.914f, 0.149f), CornerRounding(0.660f)),
          QPointNRound(Point(0.926f, 0.289f), CornerRounding(0.660f)),
          QPointNRound(Point(0.881f, 0.346f)),
          QPointNRound(Point(0.940f, 0.344f), CornerRounding(0.126f)),
          QPointNRound(Point(1.003f, 0.437f), CornerRounding(0.255f)),
      },
      2, true);

  p->transform(m);
  return p;
}

RoundedPolygon *MaterialShapes::createPuffyDiamond() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.870f, 0.130f), CornerRounding(0.146f)),
          QPointNRound(Point(0.818f, 0.357f)),
          QPointNRound(Point(1.000f, 0.332f), CornerRounding(0.853f)),
      },
      4, true);
}

RoundedPolygon *MaterialShapes::createPixelCircle() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.000f)),
          QPointNRound(Point(0.704f, 0.000f)),
          QPointNRound(Point(0.704f, 0.065f)),
          QPointNRound(Point(0.843f, 0.065f)),
          QPointNRound(Point(0.843f, 0.148f)),
          QPointNRound(Point(0.926f, 0.148f)),
          QPointNRound(Point(0.926f, 0.296f)),
          QPointNRound(Point(1.000f, 0.296f)),
      },
      2, true);
}

RoundedPolygon *MaterialShapes::createPixelTriangle() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.110f, 0.500f)),
          QPointNRound(Point(0.113f, 0.000f)),
          QPointNRound(Point(0.287f, 0.000f)),
          QPointNRound(Point(0.287f, 0.087f)),
          QPointNRound(Point(0.421f, 0.087f)),
          QPointNRound(Point(0.421f, 0.170f)),
          QPointNRound(Point(0.560f, 0.170f)),
          QPointNRound(Point(0.560f, 0.265f)),
          QPointNRound(Point(0.674f, 0.265f)),
          QPointNRound(Point(0.675f, 0.344f)),
          QPointNRound(Point(0.789f, 0.344f)),
          QPointNRound(Point(0.789f, 0.439f)),
          QPointNRound(Point(0.888f, 0.439f)),
      },
      1, true);
}

RoundedPolygon *MaterialShapes::createBun() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.796f, 0.500f)),
          QPointNRound(Point(0.853f, 0.518f), CornerRounding(1.000f)),
          QPointNRound(Point(0.992f, 0.631f), CornerRounding(1.000f)),
          QPointNRound(Point(0.968f, 1.000f), CornerRounding(1.000f)),
      },
      2, true);
}

RoundedPolygon *MaterialShapes::createHeart() {
  return customPolygon(
      std::array{
          QPointNRound(Point(0.500f, 0.268f), CornerRounding(0.016f)),
          QPointNRound(Point(0.792f, -0.066f), CornerRounding(0.958f)),
          QPointNRound(Point(1.064f, 0.276f), CornerRounding(1.000f)),
          QPointNRound(Point(0.501f, 0.946f), CornerRounding(0.129f)),
      },
      1, true);
}

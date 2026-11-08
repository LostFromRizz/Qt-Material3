#include "elevation.h"

using namespace material::internals;

static constexpr QRgb kKeyUmbraColor = 0x33000000;      // α = 0.20
static constexpr QRgb kKeyPenumbraColor = 0x24000000;   // α = 0.14
static constexpr QRgb kAmbientShadowColor = 0x1F000000; // α = 0.12

static const std::unordered_map<float, QList<ShadowForElevation>>
    shadowsForElvation = {
        {0.0f, QList<ShadowForElevation>(3)},
        {
            1.0f,
            {
                ShadowForElevation(2.0, 1.0, -1.0, kKeyUmbraColor),
                ShadowForElevation(1.0, 1.0, 0.0, kKeyPenumbraColor),
                ShadowForElevation(1.0, 3.0, 0, kAmbientShadowColor),
            },
        },
        {
            2.0f,
            {
                ShadowForElevation(3.0, 1.0, -2.0, kKeyUmbraColor),
                ShadowForElevation(2.0, 2.0, 0.0, kKeyPenumbraColor),
                ShadowForElevation(1.0, 5.0, 0.0, kAmbientShadowColor),
            },
        },
        {
            3.0f,
            {
                ShadowForElevation(3.0, 3.0, -2.0, kKeyUmbraColor),
                ShadowForElevation(3.0, 4.0, 0.0, kKeyPenumbraColor),
                ShadowForElevation(1.0, 8.0, 0.0, kAmbientShadowColor),
            },
        },
        {
            4.0f,
            {
                ShadowForElevation(2.0, 4.0, -1.0, kKeyUmbraColor),
                ShadowForElevation(4.0, 5.0, 0.0, kKeyPenumbraColor),
                ShadowForElevation(1.0, 10.0, 0.0, kAmbientShadowColor),
            },
        },
        {
            6.0f,
            {
                ShadowForElevation(3.0, 5.0, -1.0, kKeyUmbraColor),
                ShadowForElevation(6.0, 10.0, 0.0, kKeyPenumbraColor),
                ShadowForElevation(1.0, 18.0, 0.0, kAmbientShadowColor),
            },
        },
        {
            8.0f,
            {
                ShadowForElevation(5.0, 5.0, -3.0, kKeyUmbraColor),
                ShadowForElevation(8.0, 10.0, 1.0, kKeyPenumbraColor),
                ShadowForElevation(3.0, 14.0, 2.0, kAmbientShadowColor),
            },
        },
        {
            9.0f,
            {
                ShadowForElevation(5.0, 6.0, -3.0, kKeyUmbraColor),
                ShadowForElevation(9.0, 12.0, 1.0, kKeyPenumbraColor),
                ShadowForElevation(3.0, 16.0, 2.0, kAmbientShadowColor),
            },
        },
        {
            12.0f,
            {
                ShadowForElevation(7.0, 8.0, -4.0, kKeyUmbraColor),
                ShadowForElevation(12.0, 17.0, 2.0, kKeyPenumbraColor),
                ShadowForElevation(5.0, 22.0, 4.0, kAmbientShadowColor),
            },
        },
        {
            16.0f,
            {
                ShadowForElevation(8.0, 10.0, -5.0, kKeyUmbraColor),
                ShadowForElevation(16.0, 24.0, 2.0, kKeyPenumbraColor),
                ShadowForElevation(6.0, 30.0, 5.0, kAmbientShadowColor),
            },
        },
        {
            24.0f,
            {
                ShadowForElevation(11.0, 15.0, -7.0, kKeyUmbraColor),
                ShadowForElevation(24.0, 38.0, 3.0, kKeyPenumbraColor),
                ShadowForElevation(9.0, 46.0, 8.0, kAmbientShadowColor),
            },
        }

};

ShadowForElevation::ShadowForElevation(float offset, float blur, float spread,
                                       QRgb color)
    : m_offset(offset), m_blur(blur), m_spread(spread), m_color(color) {}

QList<ShadowForElevation>
material::internals::elevationShadowsFor(qreal elevation) {
  float key = static_cast<float>(std::round(elevation));

  auto it = shadowsForElvation.find(key);
  if (it != shadowsForElvation.end()) {
    return it->second;
  }

  if (elevation > 0.0) {
    return shadowsForElvation.at(0.0f);
  }

  return shadowsForElvation.at(24.0f);
}

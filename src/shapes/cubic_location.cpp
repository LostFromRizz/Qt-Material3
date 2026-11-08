#include "cubic_location.h"

using namespace material::shapes;

CubicLocation::CubicLocation(uint32_t featureIndex, uint32_t cubicIndex)
    : m_featureIdx(featureIndex), m_cubicIdx(cubicIndex) {}

CubicLocation::CubicLocation(uint32_t cubicIndex)
    : m_featureIdx(EXTRA), m_cubicIdx(cubicIndex) {}

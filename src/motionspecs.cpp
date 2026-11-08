#include "motionspecs.h"

using namespace material;

// =========================
// Duration
// =========================

qreal MotionSpecs::durationExtraLong1() const { return 700.0; }
qreal MotionSpecs::durationExtraLong2() const { return 800.0; }
qreal MotionSpecs::durationExtraLong3() const { return 900.0; }
qreal MotionSpecs::durationExtraLong4() const { return 1000.0; }
qreal MotionSpecs::durationLong1() const { return 450.0; }
qreal MotionSpecs::durationLong2() const { return 500.0; }
qreal MotionSpecs::durationLong3() const { return 550.0; }
qreal MotionSpecs::durationLong4() const { return 600.0; }
qreal MotionSpecs::durationMedium1() const { return 250.0; }
qreal MotionSpecs::durationMedium2() const { return 300.0; }
qreal MotionSpecs::durationMedium3() const { return 350.0; }
qreal MotionSpecs::durationMedium4() const { return 400.0; }
qreal MotionSpecs::durationShort1() const { return 50.0; }
qreal MotionSpecs::durationShort2() const { return 100.0; }
qreal MotionSpecs::durationShort3() const { return 150.0; }
qreal MotionSpecs::durationShort4() const { return 200.0; }

// =========================
// Expressive Spatial
// =========================

QList<qreal> MotionSpecs::easingEmphasizedCubicBezier() const {
  return {0.2, 0.0, 0.0, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingEmphasizedAccelerateCubicBezier() const {
  return {0.3, 0.0, 0.8, 0.15, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingEmphasizedDecelerateCubicBezier() const {
  return {0.05, 0.7, 0.1, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingLegacyCubicBezier() const {
  return {0.4, 0.0, 0.2, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingLegacyAccelerateCubicBezier() const {
  return {0.4, 0.0, 1.0, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingLegacyDecelerateCubicBezier() const {
  return {0.0, 0.0, 0.2, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingLinearCubicBezier() const {
  return {0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingStandardCubicBezier() const {
  return {0.2, 0.0, 0.0, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingStandardAccelerateCubicBezier() const {
  return {0.3, 0.0, 1.0, 1.0, 1.0, 1.0};
}
QList<qreal> MotionSpecs::easingStandardDecelerateCubicBezier() const {
  return {0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
}

// =========================
// Expressive Spatial
// =========================

QList<qreal> MotionSpecs::expressiveFastSpatialBezier() const {
  return {0.42, 1.67, 0.21, 0.90, 1.0, 1.0};
}

qreal MotionSpecs::expressiveFastSpatialDuration() const { return 350; }

QList<qreal> MotionSpecs::expressiveDefaultSpatialBezier() const {
  return {0.38, 1.21, 0.22, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::expressiveDefaultSpatialDuration() const { return 500; }

QList<qreal> MotionSpecs::expressiveSlowSpatialBezier() const {
  return {0.39, 1.29, 0.35, 0.98, 1.0, 1.0};
}

qreal MotionSpecs::expressiveSlowSpatialDuration() const { return 650; }

// =========================
// Expressive Effects
// =========================

QList<qreal> MotionSpecs::expressiveFastEffectsBezier() const {
  return {0.31, 0.94, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::expressiveFastEffectsDuration() const { return 150; }

QList<qreal> MotionSpecs::expressiveDefaultEffectsBezier() const {
  return {0.34, 0.80, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::expressiveDefaultEffectsDuration() const { return 200; }

QList<qreal> MotionSpecs::expressiveSlowEffectsBezier() const {
  return {0.34, 0.88, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::expressiveSlowEffectsDuration() const { return 300; }

// =========================
// Standard Spatial
// =========================

QList<qreal> MotionSpecs::standardFastSpatialBezier() const {
  return {0.27, 1.06, 0.18, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardFastSpatialDuration() const { return 350; }

QList<qreal> MotionSpecs::standardDefaultSpatialBezier() const {
  return {0.27, 1.06, 0.18, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardDefaultSpatialDuration() const { return 500; }

QList<qreal> MotionSpecs::standardSlowSpatialBezier() const {
  return {0.27, 1.06, 0.18, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardSlowSpatialDuration() const { return 750; }

// =========================
// Standard Effects
// =========================

QList<qreal> MotionSpecs::standardFastEffectsBezier() const {
  return {0.31, 0.94, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardFastEffectsDuration() const { return 150; }

QList<qreal> MotionSpecs::standardDefaultEffectsBezier() const {
  return {0.34, 0.80, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardDefaultEffectsDuration() const { return 200; }

QList<qreal> MotionSpecs::standardSlowEffectsBezier() const {
  return {0.34, 0.88, 0.34, 1.00, 1.0, 1.0};
}

qreal MotionSpecs::standardSlowEffectsDuration() const { return 300; }

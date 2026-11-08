#ifndef MATERIAL_MOTIONSPECS_H
#define MATERIAL_MOTIONSPECS_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>

namespace material {
class MotionSpecs : public QObject {
  Q_OBJECT
  // =========================
  // Duration
  // =========================

  Q_PROPERTY(qreal durationExtraLong1 READ durationExtraLong1 CONSTANT)
  Q_PROPERTY(qreal durationExtraLong2 READ durationExtraLong2 CONSTANT)
  Q_PROPERTY(qreal durationExtraLong3 READ durationExtraLong3 CONSTANT)
  Q_PROPERTY(qreal durationExtraLong4 READ durationExtraLong4 CONSTANT)
  Q_PROPERTY(qreal durationLong1 READ durationLong1 CONSTANT)
  Q_PROPERTY(qreal durationLong2 READ durationLong2 CONSTANT)
  Q_PROPERTY(qreal durationLong3 READ durationLong3 CONSTANT)
  Q_PROPERTY(qreal durationLong4 READ durationLong4 CONSTANT)
  Q_PROPERTY(qreal durationMedium1 READ durationMedium1 CONSTANT)
  Q_PROPERTY(qreal durationMedium2 READ durationMedium2 CONSTANT)
  Q_PROPERTY(qreal durationMedium3 READ durationMedium3 CONSTANT)
  Q_PROPERTY(qreal durationMedium4 READ durationMedium4 CONSTANT)
  Q_PROPERTY(qreal durationShort1 READ durationShort1 CONSTANT)
  Q_PROPERTY(qreal durationShort2 READ durationShort2 CONSTANT)
  Q_PROPERTY(qreal durationShort3 READ durationShort3 CONSTANT)
  Q_PROPERTY(qreal durationShort4 READ durationShort4 CONSTANT)

  // =========================
  // Expressive Spatial
  // =========================

  Q_PROPERTY(QList<qreal> easingEmphasizedCubicBezier READ
                 easingEmphasizedCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingEmphasizedAccelerateCubicBezier READ
                 easingEmphasizedAccelerateCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingEmphasizedDecelerateCubicBezier READ
                 easingEmphasizedDecelerateCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingLegacyCubicBezier READ easingLegacyCubicBezier
                 CONSTANT)
  Q_PROPERTY(QList<qreal> easingLegacyAccelerateCubicBezier READ
                 easingLegacyAccelerateCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingLegacyDecelerateCubicBezier READ
                 easingLegacyDecelerateCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingLinearCubicBezier READ easingLinearCubicBezier
                 CONSTANT)
  Q_PROPERTY(QList<qreal> easingStandardCubicBezier READ
                 easingStandardCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingStandardAccelerateCubicBezier READ
                 easingStandardAccelerateCubicBezier CONSTANT)
  Q_PROPERTY(QList<qreal> easingStandardDecelerateCubicBezier READ
                 easingStandardDecelerateCubicBezier CONSTANT)

  // =========================
  // Expressive Spatial
  // =========================

  Q_PROPERTY(QList<qreal> expressiveFastSpatialBezier READ
                 expressiveFastSpatialBezier CONSTANT)
  Q_PROPERTY(qreal expressiveFastSpatialDuration READ
                 expressiveFastSpatialDuration CONSTANT)

  Q_PROPERTY(QList<qreal> expressiveDefaultSpatialBezier READ
                 expressiveDefaultSpatialBezier CONSTANT)
  Q_PROPERTY(qreal expressiveDefaultSpatialDuration READ
                 expressiveDefaultSpatialDuration CONSTANT)

  Q_PROPERTY(QList<qreal> expressiveSlowSpatialBezier READ
                 expressiveSlowSpatialBezier CONSTANT)
  Q_PROPERTY(qreal expressiveSlowSpatialDuration READ
                 expressiveSlowSpatialDuration CONSTANT)

  // =========================
  // Expressive Effects
  // =========================

  Q_PROPERTY(QList<qreal> expressiveFastEffectsBezier READ
                 expressiveFastEffectsBezier CONSTANT)
  Q_PROPERTY(qreal expressiveFastEffectsDuration READ
                 expressiveFastEffectsDuration CONSTANT)

  Q_PROPERTY(QList<qreal> expressiveDefaultEffectsBezier READ
                 expressiveDefaultEffectsBezier CONSTANT)
  Q_PROPERTY(qreal expressiveDefaultEffectsDuration READ
                 expressiveDefaultEffectsDuration CONSTANT)

  Q_PROPERTY(QList<qreal> expressiveSlowEffectsBezier READ
                 expressiveSlowEffectsBezier CONSTANT)
  Q_PROPERTY(qreal expressiveSlowEffectsDuration READ
                 expressiveSlowEffectsDuration CONSTANT)

  // =========================
  // Standard Spatial
  // =========================

  Q_PROPERTY(QList<qreal> standardFastSpatialBezier READ
                 standardFastSpatialBezier CONSTANT)
  Q_PROPERTY(qreal standardFastSpatialDuration READ standardFastSpatialDuration
                 CONSTANT)

  Q_PROPERTY(QList<qreal> standardDefaultSpatialBezier READ
                 standardDefaultSpatialBezier CONSTANT)
  Q_PROPERTY(qreal standardDefaultSpatialDuration READ
                 standardDefaultSpatialDuration CONSTANT)

  Q_PROPERTY(QList<qreal> standardSlowSpatialBezier READ
                 standardSlowSpatialBezier CONSTANT)
  Q_PROPERTY(qreal standardSlowSpatialDuration READ standardSlowSpatialDuration
                 CONSTANT)

  // =========================
  // Standard Effects
  // =========================

  Q_PROPERTY(QList<qreal> standardFastEffectsBezier READ
                 standardFastEffectsBezier CONSTANT)
  Q_PROPERTY(qreal standardFastEffectsDuration READ standardFastEffectsDuration
                 CONSTANT)

  Q_PROPERTY(QList<qreal> standardDefaultEffectsBezier READ
                 standardDefaultEffectsBezier CONSTANT)
  Q_PROPERTY(qreal standardDefaultEffectsDuration READ
                 standardDefaultEffectsDuration CONSTANT)

  Q_PROPERTY(QList<qreal> standardSlowEffectsBezier READ
                 standardSlowEffectsBezier CONSTANT)
  Q_PROPERTY(qreal standardSlowEffectsDuration READ standardSlowEffectsDuration
                 CONSTANT)
  QML_ELEMENT
  QML_SINGLETON
public:
  MotionSpecs() = default;

  qreal durationExtraLong1() const;
  qreal durationExtraLong2() const;
  qreal durationExtraLong3() const;
  qreal durationExtraLong4() const;
  qreal durationLong1() const;
  qreal durationLong2() const;
  qreal durationLong3() const;
  qreal durationLong4() const;
  qreal durationMedium1() const;
  qreal durationMedium2() const;
  qreal durationMedium3() const;
  qreal durationMedium4() const;
  qreal durationShort1() const;
  qreal durationShort2() const;
  qreal durationShort3() const;
  qreal durationShort4() const;

  QList<qreal> easingEmphasizedCubicBezier() const;
  QList<qreal> easingEmphasizedAccelerateCubicBezier() const;
  QList<qreal> easingEmphasizedDecelerateCubicBezier() const;
  QList<qreal> easingLegacyCubicBezier() const;
  QList<qreal> easingLegacyAccelerateCubicBezier() const;
  QList<qreal> easingLegacyDecelerateCubicBezier() const;
  QList<qreal> easingLinearCubicBezier() const;
  QList<qreal> easingStandardCubicBezier() const;
  QList<qreal> easingStandardAccelerateCubicBezier() const;
  QList<qreal> easingStandardDecelerateCubicBezier() const;

  QList<qreal> expressiveFastSpatialBezier() const;
  qreal expressiveFastSpatialDuration() const;

  QList<qreal> expressiveDefaultSpatialBezier() const;
  qreal expressiveDefaultSpatialDuration() const;

  QList<qreal> expressiveSlowSpatialBezier() const;
  qreal expressiveSlowSpatialDuration() const;

  QList<qreal> expressiveFastEffectsBezier() const;
  qreal expressiveFastEffectsDuration() const;

  QList<qreal> expressiveDefaultEffectsBezier() const;
  qreal expressiveDefaultEffectsDuration() const;

  QList<qreal> expressiveSlowEffectsBezier() const;
  qreal expressiveSlowEffectsDuration() const;

  QList<qreal> standardFastSpatialBezier() const;
  qreal standardFastSpatialDuration() const;

  QList<qreal> standardDefaultSpatialBezier() const;
  qreal standardDefaultSpatialDuration() const;

  QList<qreal> standardSlowSpatialBezier() const;
  qreal standardSlowSpatialDuration() const;

  QList<qreal> standardFastEffectsBezier() const;
  qreal standardFastEffectsDuration() const;

  QList<qreal> standardDefaultEffectsBezier() const;
  qreal standardDefaultEffectsDuration() const;

  QList<qreal> standardSlowEffectsBezier() const;
  qreal standardSlowEffectsDuration() const;
};

} // namespace material

#endif // MATERIAL_MOTIONSPECS_H

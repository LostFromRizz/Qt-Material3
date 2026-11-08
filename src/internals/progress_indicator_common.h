#ifndef MATERIAL_INTERNALS_PROGRESS_INDICATOR_COMMON_H
#define MATERIAL_INTERNALS_PROGRESS_INDICATOR_COMMON_H

#include "utils.h"
#include <qeasingcurve.h>
#include <qpoint.h>
#include <qvariantanimation.h>

namespace material::internals::progress_indicator {

static constexpr int LinearAnimationProgressDuration = 1750;
static constexpr int FirstLineHeadDuration = 1000;
static constexpr int FirstLineTailDuration = 1000;
static constexpr int SecondLineHeadDuration = 850;
static constexpr int SecondLineTailDuration = 850;

static constexpr int FirstLineHeadDelay = 0;
static constexpr int FirstLineTailDelay = 250;
static constexpr int SecondLineHeadDelay = 650;
static constexpr int SecondLineTailDelay = 900;

static const qreal CircularIndeterminateMinProgress = 0.1;
static const qreal CircularIndeterminateMaxProgress = 0.87;

static const int CircularAnimationProgressDuration = 6000;
static const int CircularAnimationAdditionalRotationDelay = 1500;
static const int CircularAnimationAdditionalRotationDuration = 300;
static const qreal CircularGlobalRotationDegreesTarget = 1080;

static const QEasingCurve EasingEmphasizedAccelerateCubicBezier =
    utils::cubicBezierCurve(QPointF(0.3, 0.0), QPointF(0.8, 0.15),
                            QPointF(1.0, 1.0));

static const utils::AnimSpec IncreasingAmplitudeAnimSpec = utils::AnimSpec{
    .curve = utils::cubicBezierCurve(QPointF(0.2, 0.0), QPointF(1.0, 1.0),
                                     QPointF(1.0, 1.0)),
    .duration = 500};

static const utils::AnimSpec DecreasingAmplitudeAnimSpec = utils::AnimSpec{
    .curve = EasingEmphasizedAccelerateCubicBezier, .duration = 500};

static inline QVariantAnimation *
createCircularGlobalRotationAnimation(QObject *parent) {
  auto *animation = new QVariantAnimation(parent);
  animation->setStartValue(0.0);
  animation->setEndValue(CircularGlobalRotationDegreesTarget);
  animation->setEasingCurve(QEasingCurve::Linear);
  animation->setDuration(CircularAnimationProgressDuration);

  return animation;
}

static inline QVariantAnimation *
createCircularAdditionalRotationAnimation(QObject *parent) {
  auto *animation = new QVariantAnimation(parent);
  animation->setDuration(CircularAnimationProgressDuration);
  animation->setEasingCurve(QEasingCurve::Linear);

  auto duration =
      static_cast<qreal>(CircularAnimationAdditionalRotationDuration);
  auto totalDuration = static_cast<qreal>(CircularAnimationProgressDuration);
  auto delay = static_cast<qreal>(CircularAnimationAdditionalRotationDelay);

  qreal step0 = 0.0;
  qreal step1 = duration / totalDuration;               // 300 ms
  qreal step2 = delay / totalDuration;                  // 1500 ms
  qreal step3 = (duration + delay) / totalDuration;     // 1800 ms
  qreal step4 = (delay * 2) / totalDuration;            // 3000 ms
  qreal step5 = (duration + delay * 2) / totalDuration; // 3300 ms
  qreal step6 = (delay * 3) / totalDuration;            // 4500 ms
  qreal step7 = (duration + delay * 3) / totalDuration; // 4800 ms
  qreal step8 = (delay * 4) / totalDuration;            // 6000 ms
  Q_ASSERT(qFuzzyCompare(step8, 1.0));

  animation->setKeyValues({
      QVariantAnimation::KeyValue{step0, 0.0},
      QVariantAnimation::KeyValue{step1, 90.0},
      QVariantAnimation::KeyValue{step2, 90.0},
      QVariantAnimation::KeyValue{step3, 180.0},
      QVariantAnimation::KeyValue{step4, 180.0},
      QVariantAnimation::KeyValue{step5, 270.0},
      QVariantAnimation::KeyValue{step6, 270.0},
      QVariantAnimation::KeyValue{step7, 360.0},
      QVariantAnimation::KeyValue{step8, 360.0},
  });

  return animation;
}

static inline QVariantAnimation *
createCircularProgressAnimation(QObject *parent) {
  auto *animation = new QVariantAnimation(parent);
  animation->setDuration(CircularAnimationProgressDuration);
  animation->setEasingCurve(QEasingCurve::Linear);

  qreal step0 = 0.0;
  qreal step1 = (static_cast<qreal>(CircularAnimationProgressDuration) / 2) /
                CircularAnimationProgressDuration;
  qreal step2 = step1 * 2;
  Q_ASSERT(qFuzzyCompare(step2, 1.0));

  animation->setKeyValues({
      QVariantAnimation::KeyValue{step0, CircularIndeterminateMinProgress},
      QVariantAnimation::KeyValue{step1, CircularIndeterminateMaxProgress},
      QVariantAnimation::KeyValue{step2, CircularIndeterminateMinProgress},
  });
  return animation;
}

}; // namespace material::internals::progress_indicator

#endif // MATERIAL_INTERNALS_PROGRESS_INDICATOR_COMMON_H

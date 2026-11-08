#include "circular_wavy_progress_indicator.h"

#include "utils.h"

#include "progress_indicator_common.h"
#include <QtCore/qeasingcurve.h>
#include <QtCore/qparallelanimationgroup.h>
#include <QtGui/qpainter.h>
#include <QtGui/qtransform.h>
#include <qabstractanimation.h>
#include <qassert.h>
#include <qmath.h>
#include <qnamespace.h>
#include <qnumeric.h>
#include <qpainterpath.h>
#include <qquickpainteditem.h>
#include <qtpreprocessorsupport.h>
#include <qvariant.h>

using namespace material::internals;
using namespace material::internals::progress_indicator;
using KeyValue = QVariantAnimation::KeyValue;

namespace {

static const QEasingCurve EasingStandardCubicBezier = utils::cubicBezierCurve(
    QPointF(0.2, 0.0), QPointF(0.0, 1.0), QPointF(1.0, 1.0));

static inline QVariantAnimation *createWaveOffsetAnimation(QObject *parent) {
  auto *animation = new QVariantAnimation(parent);
  animation->setStartValue(0.0);
  animation->setEndValue(1.0);
  animation->setEasingCurve(QEasingCurve::Linear);

  return animation;
}

enum AnimationType {
  GlobalRoatationAnimation,
  AdditionalRoatationAnimation,
  ProgressSweepAnimation,
  WaveOffsetAnimation,
};

}; // namespace

QColor CircularWavyProgressIndicatorImpl::color() const { return m_color; }

void CircularWavyProgressIndicatorImpl::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  update();
}

QColor CircularWavyProgressIndicatorImpl::trackColor() const {
  return m_trackColor;
}

void CircularWavyProgressIndicatorImpl::setTrackColor(const QColor &color) {
  if (color == m_trackColor) {
    return;
  }

  m_trackColor = color;
  update();
}

qreal CircularWavyProgressIndicatorImpl::gapSize() const { return m_gapSize; }

void CircularWavyProgressIndicatorImpl::setGapSize(qreal gapSize) {
  if (gapSize == m_gapSize) {
    return;
  }

  m_gapSize = gapSize;
  update();
}

qreal CircularWavyProgressIndicatorImpl::waveLength() const {
  return m_waveLength;
}

void CircularWavyProgressIndicatorImpl::setWaveLength(qreal waveLength) {
  if (waveLength == m_waveLength) {
    return;
  }

  m_waveLength = waveLength;
  updateOffsetAnimationSpec();
  update();
}

qreal CircularWavyProgressIndicatorImpl::amplitude() const {
  return m_amplitude;
}

void CircularWavyProgressIndicatorImpl::setAmplitude(qreal amplitude) {
  if (amplitude == m_amplitude) {
    return;
  }
  updateAmplitudeAnimation(amplitude);
  m_amplitude = amplitude;
  update();
}

qreal CircularWavyProgressIndicatorImpl::waveSpeed() const {
  return m_waveSpeed;
}

void CircularWavyProgressIndicatorImpl::setWaveSpeed(qreal waveSpeed) {
  if (waveSpeed == m_waveSpeed) {
    return;
  }

  m_waveSpeed = waveSpeed;
  updateOffsetAnimationSpec();
  update();
}

qreal CircularWavyProgressIndicatorImpl::strokeWidth() const {
  return m_strokeWidth;
}
void CircularWavyProgressIndicatorImpl::setStrokeWidth(qreal strokeWidth) {
  if (strokeWidth == m_strokeWidth) {
    return;
  }

  m_strokeWidth = strokeWidth;
  update();
}
qreal CircularWavyProgressIndicatorImpl::trackStrokeWidth() const {
  return m_trackStrokeWidth;
}
void CircularWavyProgressIndicatorImpl::setTrackStrokeWidth(
    qreal trackStrokeWidth) {
  if (trackStrokeWidth == m_trackStrokeWidth) {
    return;
  }

  m_trackStrokeWidth = trackStrokeWidth;
  update();
}
bool CircularWavyProgressIndicatorImpl::indeterminate() const {
  return m_indeterminate;
}

void CircularWavyProgressIndicatorImpl::updateOffsetAnimationSpec() {
  auto offsetAnim = waveOffsetAnimation();
  if (m_waveSpeed > 0 && m_waveLength > 0 && m_amplitude > 0) {
    const int duration =
        std::max(utils::roundToInt((m_waveLength / m_waveSpeed) * 1000), 50);

    offsetAnim->setDuration(duration);
    offsetAnim->setEasingCurve(QEasingCurve::Linear);
    offsetAnim->setStartValue(0.0);
    offsetAnim->setEndValue(1.0);
  } else {
    offsetAnim->setStartValue(0.0);
    offsetAnim->setEndValue(0.0);
  }
}

void CircularWavyProgressIndicatorImpl::removeIndeterminateAnimations() {
  m_animations->stop();

  disconnect(progressSweepAnimation(), &QVariantAnimation::valueChanged, this,
             &CircularWavyProgressIndicatorImpl::onAnimationValueChanged);

  delete m_animations->takeAnimation(ProgressSweepAnimation);
  delete m_animations->takeAnimation(AdditionalRoatationAnimation);
  delete m_animations->takeAnimation(GlobalRoatationAnimation);

  connect(waveOffsetAnimation(), &QVariantAnimation::valueChanged, this,
          &CircularWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_indeterminate = false;
  m_animations->start();
}

void CircularWavyProgressIndicatorImpl::createIndeterminateAnimations() {
  m_animations->stop();

  // disconnect from waveOffsetAnimation
  disconnect(waveOffsetAnimation(), &QVariantAnimation::valueChanged, this,
             &CircularWavyProgressIndicatorImpl::onAnimationValueChanged);

  auto *globalRotationAnimation =
      createCircularGlobalRotationAnimation(m_animations);
  auto *additionalRotationAnimation =
      createCircularAdditionalRotationAnimation(m_animations);
  auto *progressSweepAnimation = createCircularProgressAnimation(m_animations);

  m_animations->insertAnimation(GlobalRoatationAnimation,
                                globalRotationAnimation);
  m_animations->insertAnimation(AdditionalRoatationAnimation,
                                additionalRotationAnimation);
  m_animations->insertAnimation(ProgressSweepAnimation, progressSweepAnimation);

  connect(progressSweepAnimation, &QVariantAnimation::valueChanged, this,
          &CircularWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_indeterminate = true;
  m_animations->start();
}

void CircularWavyProgressIndicatorImpl::setIndeterminate(bool indeterminate) {
  if (indeterminate == m_indeterminate) {
    return;
  }

  if (m_indeterminate) {
    removeIndeterminateAnimations();
  } else {
    createIndeterminateAnimations();
  }
}

qreal CircularWavyProgressIndicatorImpl::progress() const { return m_progress; }

void CircularWavyProgressIndicatorImpl::setProgress(qreal progress) {
  if (progress == m_progress) {
    return;
  }
  m_progress = progress;
  if (!m_indeterminate) {
    update();
  }
}

CircularWavyProgressIndicatorImpl::CircularWavyProgressIndicatorImpl(
    QQuickItem *parent)
    : QQuickPaintedItem(parent) {
  m_amplitudeAnim = new QVariantAnimation(this);
  m_amplitudeAnim->setStartValue(m_amplitude);
  m_amplitudeAnim->setEndValue(m_amplitude);

  connect(m_amplitudeAnim, &QVariantAnimation::valueChanged, this,
          [this](const QVariant &) { update(); });

  m_animations = new QParallelAnimationGroup(this);

  auto *waveOffsetAnimation = createWaveOffsetAnimation(m_animations);
  connect(waveOffsetAnimation, &QVariantAnimation::valueChanged, this,
          &CircularWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_animations->insertAnimation(WaveOffsetAnimation, waveOffsetAnimation);
  m_animations->setLoopCount(-1);
}

void CircularWavyProgressIndicatorImpl::componentComplete() {
  QQuickPaintedItem::componentComplete();
  updateOffsetAnimationSpec();
  m_animations->start();
}

QVariantAnimation *
CircularWavyProgressIndicatorImpl::globalRotationAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(GlobalRoatationAnimation));
}
QVariantAnimation *
CircularWavyProgressIndicatorImpl::additionalRotationAnimation() const {

  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(AdditionalRoatationAnimation));
}
QVariantAnimation *
CircularWavyProgressIndicatorImpl::progressSweepAnimation() const {

  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(ProgressSweepAnimation));
}
QVariantAnimation *
CircularWavyProgressIndicatorImpl::waveOffsetAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(WaveOffsetAnimation));
}

void CircularWavyProgressIndicatorImpl::updateAmplitudeAnimation(
    qreal targetValue) {
  if (m_amplitudeAnim->state() == QAbstractAnimation::State::Running) {
    m_amplitudeAnim->stop();
  }
  if (m_amplitudeAnim->currentValue().toReal() < targetValue) {
    m_amplitudeAnim->setEasingCurve(IncreasingAmplitudeAnimSpec.curve);
    m_amplitudeAnim->setDuration(IncreasingAmplitudeAnimSpec.duration);

  } else {
    m_amplitudeAnim->setEasingCurve(DecreasingAmplitudeAnimSpec.curve);
    m_amplitudeAnim->setDuration(DecreasingAmplitudeAnimSpec.duration);
  }

  m_amplitudeAnim->setStartValue(m_amplitudeAnim->currentValue());
  m_amplitudeAnim->setEndValue(targetValue);
  m_amplitudeAnim->start();
}

void CircularWavyProgressIndicatorImpl::drawProgressPath(
    QPainterPath &path, qreal amplitude, qreal radius, qreal startAngle,
    qreal sweepAngle, qreal waveCycles, qreal phase,
    const QPointF &center) const {

  const qreal halfWaveAngle = M_PI / waveCycles;
  const qreal endAngle = startAngle + sweepAngle;

  const qreal taperRange = halfWaveAngle * 0.5;

  auto localAmplitude = [&](qreal angle) {
    if (taperRange <= 0.0)
      return amplitude;

    const qreal distFromStart = angle - startAngle;
    const qreal distFromEnd = endAngle - angle;

    qreal factor = 1.0;

    if (distFromStart < taperRange)
      factor = qMin(factor, distFromStart / taperRange);

    if (distFromEnd < taperRange)
      factor = qMin(factor, distFromEnd / taperRange);

    const qreal smoothFactor = 0.5 - 0.5 * qCos(factor * M_PI);

    return amplitude * smoothFactor;
  };

  auto radiusAt = [&](qreal angle) {
    return radius + localAmplitude(angle) * qSin(angle * waveCycles + phase);
  };

  qreal currentAngle = startAngle;

  const qreal r0 = radiusAt(currentAngle);

  path.moveTo(center.x() + r0 * qCos(currentAngle),
              center.y() + r0 * qSin(currentAngle));

  auto nextHalfWaveBoundary = [](double startAngle, double halfWaveAngle,
                                 double waveOffset, double waveCycles) {
    //   // The zero crossings of sin(θ*N + phase) occur at θ = (kπ -
    //   phase)/N.
    //   // The first one strictly after startAngle:
    auto k = qCeil((startAngle * waveCycles + waveOffset) / M_PI);
    auto boundary = (k * M_PI - waveOffset) / waveCycles;
    // If boundary == startAngle (already on a crossing), step one half-wave
    // further.
    if (qFabs(boundary - startAngle) < 1e-9) {
      return boundary + halfWaveAngle;
    }
    return boundary;
  };

  qreal segEnd =
      nextHalfWaveBoundary(startAngle, halfWaveAngle, phase, waveCycles);

  while (currentAngle < endAngle) {
    const qreal segEndClamped = qMin(segEnd, endAngle);

    const qreal midAngle = (currentAngle + segEndClamped) / 2.0;

    const qreal actualSpan = segEndClamped - currentAngle;

    const qreal segmentCos = qCos(actualSpan / 2.0);

    const qreal rMid =
        (radius / segmentCos) +
        localAmplitude(midAngle) * qSin(midAngle * waveCycles + phase);

    const qreal rEnd = radius + localAmplitude(segEndClamped) *
                                    qSin(segEndClamped * waveCycles + phase);

    const qreal cpx = center.x() + rMid * qCos(midAngle);

    const qreal cpy = center.y() + rMid * qSin(midAngle);

    const qreal epx = center.x() + rEnd * qCos(segEndClamped);

    const qreal epy = center.y() + rEnd * qSin(segEndClamped);

    path.quadTo(cpx, cpy, epx, epy);

    currentAngle = segEndClamped;
    segEnd += halfWaveAngle;
  }
}

void CircularWavyProgressIndicatorImpl::drawTrackPath(
    QPainter &painter, qreal radius, qreal startAngle, qreal sweepAngle,
    qreal progressSweep, qreal gapRadius, const QPointF &center) const {

  QPen pen(m_trackColor, m_trackStrokeWidth);
  pen.setCapStyle(Qt::RoundCap);

  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

  const QRectF rect(center.x() - radius, center.y() - radius, radius * 2.0,
                    radius * 2.0);

  const qreal trackStart = startAngle + progressSweep + gapRadius;

  const int qtStart = qRound(-qRadiansToDegrees(trackStart) * 16.0);

  const int qtSweep = qRound(-qRadiansToDegrees(sweepAngle) * 16.0);

  painter.drawArc(rect, qtStart, qtSweep);
}

void CircularWavyProgressIndicatorImpl::paint(QPainter *painter) {

  const qreal amplitude = m_amplitudeAnim->currentValue().toReal();

  const qreal maxStrokeWidth = std::max(m_strokeWidth, m_trackStrokeWidth);

  const qreal waveLength = m_waveLength;

  const auto center = boundingRect().center();

  const qreal radius = (std::min(width(), height()) - maxStrokeWidth) / 2.0;

  const qreal waveOffset =
      waveOffsetAnimation()->currentValue().toReal() * 2.0 * M_PI;

  const qreal startAngle = -M_PI / 2.0;

  const qreal waveCycles =
      qMax(3.0, std::round(2.0 * M_PI * radius / waveLength));

  auto progressSweep = std::clamp(m_progress, 0.0, 1.0) * 2.0 * M_PI;

  painter->setRenderHint(QPainter::Antialiasing);

  if (m_indeterminate) {
    const qreal globalRotation =
        globalRotationAnimation()->currentValue().toReal();

    const qreal additionalRotation =
        additionalRotationAnimation()->currentValue().toReal();

    const qreal totalDeg = globalRotation + additionalRotation + 90.0;

    progressSweep =
        progressSweepAnimation()->currentValue().toReal() * 2.0 * M_PI;

    painter->translate(center);
    painter->rotate(totalDeg);
    painter->translate(-center);
  }

  const bool hasProgress = (progressSweep > 0.0);

  const auto gapRadius =
      hasProgress * ((m_gapSize + (maxStrokeWidth / 2.0) * 2.0) / radius);

  const auto trackSweep =
      2.0 * M_PI - progressSweep - (hasProgress * 2.0 * gapRadius);

  if (trackSweep > 0.0 && m_trackColor.alpha() != 0) {
    drawTrackPath(*painter, radius, startAngle, trackSweep, progressSweep,
                  gapRadius, center);
  }

  if (progressSweep > 0.0) {
    QPainterPath progressPath;

    drawProgressPath(progressPath, amplitude, radius, startAngle, progressSweep,
                     waveCycles, waveOffset, center);

    QPen pen(m_color, m_strokeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    const QRectF bounds = progressPath.boundingRect();

    const qreal availableRadius =
        (std::min(width(), height()) - m_strokeWidth) / 2.0;

    const qreal pathRadius = std::max({std::abs(bounds.left() - center.x()),
                                       std::abs(bounds.right() - center.x()),
                                       std::abs(bounds.top() - center.y()),
                                       std::abs(bounds.bottom() - center.y())});

    const qreal scale =
        pathRadius > 0.0 ? std::min(1.0, availableRadius / pathRadius) : 1.0;

    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.scale(scale, scale);
    transform.translate(-center.x(), -center.y());

    progressPath = transform.map(progressPath);

    painter->drawPath(progressPath);
  }
}

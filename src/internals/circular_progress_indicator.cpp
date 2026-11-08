#include "circular_progress_indicator.h"
#include "progress_indicator_common.h"
#include <qassert.h>
#include <qpainter.h>
#include <qparallelanimationgroup.h>
#include <qvariantanimation.h>

using namespace material::internals;
using namespace material::internals::progress_indicator;

QColor CircularProgressIndicatorImpl::color() const { return m_color; }
void CircularProgressIndicatorImpl::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  update();
}

QColor CircularProgressIndicatorImpl::trackColor() const {
  return m_trackColor;
}
void CircularProgressIndicatorImpl::setTrackColor(const QColor &color) {
  if (color == m_trackColor) {
    return;
  }

  m_trackColor = color;
  update();
}

qreal CircularProgressIndicatorImpl::gapSize() const { return m_gapSize; }
void CircularProgressIndicatorImpl::setGapSize(qreal gapSize) {
  if (gapSize == m_gapSize) {
    return;
  }

  m_gapSize = gapSize;
  update();
}

qreal CircularProgressIndicatorImpl::strokeWidth() const {
  return m_strokeWidth;
}
void CircularProgressIndicatorImpl::setStrokeWidth(qreal strokeWidth) {
  if (strokeWidth == m_strokeWidth) {
    return;
  }

  m_strokeWidth = strokeWidth;
  update();
}

bool CircularProgressIndicatorImpl::flat() const { return m_flat; }

void CircularProgressIndicatorImpl::setFlat(bool flat) {
  if (flat == m_flat) {
    return;
  }
  m_flat = flat;
  update();
}

qreal CircularProgressIndicatorImpl::progress() const { return m_progress; }

void CircularProgressIndicatorImpl::setProgress(qreal progress) {
  if (progress == m_progress) {
    return;
  }
  m_progress = progress;
  update();
}

CircularProgressIndicatorImpl::CircularProgressIndicatorImpl(QQuickItem *parent)
    : QQuickPaintedItem(parent) {}

QVariantAnimation *
CircularProgressIndicatorImpl::globalRotationAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(GlobalRoatationAnimation));
}
QVariantAnimation *
CircularProgressIndicatorImpl::additionalRotationAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(AdditionalRoatationAnimation));
}
QVariantAnimation *CircularProgressIndicatorImpl::progressAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(ProgressAnimation));
}

void CircularProgressIndicatorImpl::componentComplete() {
  QQuickPaintedItem::componentComplete();
  if (m_animations) {
    Q_ASSERT_X(
        m_indeterminate,
        "material::internals::CircularProgressIndicatorImpl::componentComplete",
        "Indeterminate animations created during determinate state");
    return m_animations->start();
  }
}

bool CircularProgressIndicatorImpl::indeterminate() const {
  return m_indeterminate;
}
void CircularProgressIndicatorImpl::setIndeterminate(bool indeterminate) {
  if (indeterminate == m_indeterminate) {
    return;
  }

  if (m_indeterminate) {
    removeIndeterminateAnimations();
  } else {
    createIndeterminateAnimations();
  }
}

void CircularProgressIndicatorImpl::removeIndeterminateAnimations() {
  Q_ASSERT_X(m_animations,
             "material::internals::CircularProgressIndicatorImpl::"
             "removeIndeterminateAnimations",
             "No animations found");
  m_animations->stop();
  disconnect(progressAnimation(), &QVariantAnimation::valueChanged, this,
             &CircularProgressIndicatorImpl::onAnimationValueChanged);
  m_animations->deleteLater();
  m_animations = nullptr;
  m_indeterminate = false;
  update();
}

void CircularProgressIndicatorImpl::createIndeterminateAnimations() {
  qDebug() << m_indeterminate;
  Q_ASSERT_X(m_animations == nullptr,
             "material::internals::CircularProgressIndicator::"
             "createIndeterminateAnimations",
             "Existing animations found");

  m_animations = new QParallelAnimationGroup(this);

  auto *globalRotationAnimation =
      createCircularGlobalRotationAnimation(m_animations);
  auto *additionalRotationAnimation =
      createCircularAdditionalRotationAnimation(m_animations);
  auto *progressAnimation = createCircularProgressAnimation(m_animations);

  m_animations->insertAnimation(GlobalRoatationAnimation,
                                globalRotationAnimation);
  m_animations->insertAnimation(AdditionalRoatationAnimation,
                                additionalRotationAnimation);
  m_animations->insertAnimation(ProgressAnimation, progressAnimation);
  m_animations->setLoopCount(-1);

  connect(progressAnimation, &QVariantAnimation::valueChanged, this,
          &CircularProgressIndicatorImpl::onAnimationValueChanged);

  m_indeterminate = true;
  m_animations->start();
}

void CircularProgressIndicatorImpl::drawArc(QPainter *painter, qreal startAngle,
                                            qreal sweep) const {
  const auto diameterOffset = static_cast<qreal>(m_strokeWidth) / 2;
  const auto arcDimen = size().width() - 2 * diameterOffset;

  painter->drawArc(QRectF(QPointF(diameterOffset, diameterOffset),
                          QSizeF(arcDimen, arcDimen)),
                   startAngle * 16, sweep * 16);
}

void CircularProgressIndicatorImpl::drawTrack(QPainter *painter,
                                              qreal startAngle,
                                              qreal sweep) const {
  QPen pen(m_trackColor, m_strokeWidth);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  return drawArc(painter, startAngle, sweep);
}
void CircularProgressIndicatorImpl::drawProgressIndicator(QPainter *painter,
                                                          qreal startAngle,
                                                          qreal sweep) const {
  QPen pen(m_color, m_strokeWidth);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  return drawArc(painter, startAngle, sweep);
}

void CircularProgressIndicatorImpl::paint(QPainter *painter) {
  const auto size = this->size();
  const auto height = size.height();
  const auto width = size.width();

  const auto center = boundingRect().center();

  const qreal adjustedGapSize =
      (m_flat || height > width) ? m_gapSize : m_gapSize + m_strokeWidth;
  const auto gapSizeSweep = (adjustedGapSize / (M_PI * width)) * 360.0;

  painter->setRenderHint(QPainter::Antialiasing);
  painter->setBrush(Qt::NoBrush);

  qreal startAngle = 0.0;
  qreal sweep = 0.0;

  if (m_indeterminate) {
    Q_ASSERT_X(m_animations,
               "material::internals::CircularProgressIndicatorImpl::paint",
               "No animations found");
    const auto globalRotation =
        globalRotationAnimation()->currentValue().toReal();
    const auto additionRotation =
        additionalRotationAnimation()->currentValue().toReal();

    painter->translate(center);
    painter->rotate(globalRotation + additionRotation);
    painter->translate(-center);

    sweep = progressAnimation()->currentValue().toReal() * 360.0;

  } else {
    // Start at 12 o'clock
    startAngle = 270.0;
    sweep = std::clamp(m_progress, 0.0, 1.0) * 360.0;
  }

  drawTrack(painter, sweep + qMin(sweep, gapSizeSweep),
            360.0 - sweep - qMin(sweep, gapSizeSweep) * 2);

  drawProgressIndicator(painter, startAngle, sweep);
}

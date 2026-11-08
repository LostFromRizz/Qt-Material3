#include "linear_progress_indicator.h"
#include "progress_indicator_common.h"
#include "utils.h"
#include <QVariantAnimation>
#include <qpainter.h>
#include <qvariantanimation.h>

using namespace material::internals;
using namespace material::internals::progress_indicator;

namespace {
static const QEasingCurve LineEasing = utils::cubicBezierCurve(
    QPointF(0.3, 0.0), QPointF(0.8, 0.15), QPointF(1.0, 1.0));
} // namespace

LinearProgressIndicatorImpl::LinearProgressIndicatorImpl(QQuickItem *parent)
    : QQuickPaintedItem(parent) {}

QVariantAnimation *
LinearProgressIndicatorImpl::createIndeterminateAnimation(QObject *parent) {
  auto anim = new QVariantAnimation(parent);
  anim->setStartValue(0.0);
  anim->setEndValue(1.0);
  anim->setLoopCount(-1);
  anim->setDuration(LinearAnimationProgressDuration);
  return anim;
}

QColor LinearProgressIndicatorImpl::color() const { return m_color; }
void LinearProgressIndicatorImpl::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  update();
}

QColor LinearProgressIndicatorImpl::trackColor() const { return m_trackColor; }
void LinearProgressIndicatorImpl::setTrackColor(const QColor &color) {
  if (color == m_trackColor) {
    return;
  }

  m_trackColor = color;
  update();
}

qreal LinearProgressIndicatorImpl::gapSize() const { return m_gapSize; }
void LinearProgressIndicatorImpl::setGapSize(qreal gapSize) {
  if (gapSize == m_gapSize) {
    return;
  }

  m_gapSize = gapSize;
  update();
}

bool LinearProgressIndicatorImpl::flat() const { return m_flat; }

void LinearProgressIndicatorImpl::setFlat(bool flat) {
  if (flat == m_flat) {
    return;
  }
  m_flat = flat;
  update();
}

qreal LinearProgressIndicatorImpl::visualPosition() const {
  return m_visualPosition;
}

void LinearProgressIndicatorImpl::setVisualPosition(qreal visualPosition) {
  if (visualPosition == m_visualPosition) {
    return;
  }
  m_visualPosition = visualPosition;
  update();
}

bool LinearProgressIndicatorImpl::indeterminate() const {
  return m_indeterminate;
}

void LinearProgressIndicatorImpl::setIndeterminate(bool indeterminate) {
  if (indeterminate == m_indeterminate) {
    return;
  }

  m_indeterminate = indeterminate;
  if (m_indeterminate) {
    m_indeterminateAim = createIndeterminateAnimation(this);
    connect(m_indeterminateAim, &QVariantAnimation::valueChanged, this,
            &LinearProgressIndicatorImpl::onAnimationValueChanged);
    m_indeterminateAim->start();
  } else {
    if (m_indeterminateAim) {
      disconnect(m_indeterminateAim, &QVariantAnimation::valueChanged, this,
                 &LinearProgressIndicatorImpl::onAnimationValueChanged);
      m_indeterminateAim->deleteLater();
      m_indeterminateAim = nullptr;
    }
  }

  update();
}

void LinearProgressIndicatorImpl::onAnimationValueChanged() { update(); }

void LinearProgressIndicatorImpl::drawLinearIndicator(QPainter *painter,
                                                      qreal startFraction,
                                                      qreal endFraction,
                                                      const QColor &color,
                                                      qreal strokeWidth) {
  const QSizeF size = this->size();
  const qreal width = size.width();
  const qreal height = size.height();

  if (endFraction <= startFraction)
    return;

  QPen pen(color, strokeWidth);

  const qreal y = height / 2.0;
  if (m_flat) {
    pen.setCapStyle(Qt::FlatCap);
    painter->setPen(pen);
    painter->drawLine(QPointF(startFraction * width, y),
                      QPointF(endFraction * width, y));

  } else {
    const qreal strokeCap = strokeWidth / 2;
    const qreal adjustedBarStart =
        std::clamp(startFraction * width, strokeCap, width - strokeCap);
    const qreal adjustedBarEnd =
        std::clamp(endFraction * width, strokeCap, width - strokeCap);

    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->drawLine(QPointF(adjustedBarStart, y), QPointF(adjustedBarEnd, y));
  }
}

void LinearProgressIndicatorImpl::paint(QPainter *painter) {
  painter->setRenderHint(QPainter::Antialiasing, !m_flat);

  const QSizeF size = this->size();
  const qreal width = size.width();
  const qreal height = size.height();

  const qreal strokeWidth = height;

  const qreal adjustedGapSize =
      (m_flat || height > width) ? m_gapSize : m_gapSize + strokeWidth;

  const qreal gapSizeFraction = adjustedGapSize / width;
  if (!m_indeterminate) {
    const qreal progress = std::clamp(m_visualPosition, 0.0, 1.0);
    const qreal trackStartFraction = progress + qMin(progress, gapSizeFraction);

    if (trackStartFraction <= 1.0) {
      drawLinearIndicator(painter, trackStartFraction, 1.0, m_trackColor,
                          strokeWidth);
    }

    drawLinearIndicator(painter, 0, progress, m_color, strokeWidth);
  } else {
    Q_ASSERT_X(m_indeterminateAim,
               "material::internals::LinearProgressIndicatorImpl",
               "No animation found for indeterminate state");

    auto animationValue = m_indeterminateAim->currentValue().toReal();

    auto firstLineHead = utils::evaluateIndeterminateSegment(
        animationValue, FirstLineHeadDelay, FirstLineHeadDuration,
        LinearAnimationProgressDuration, LineEasing);
    auto firstLineTail = utils::evaluateIndeterminateSegment(
        animationValue, FirstLineTailDelay, FirstLineTailDuration,
        LinearAnimationProgressDuration, LineEasing);
    auto secondLineHead = utils::evaluateIndeterminateSegment(
        animationValue, SecondLineHeadDelay, SecondLineHeadDuration,
        LinearAnimationProgressDuration, LineEasing);
    auto secondLineTail = utils::evaluateIndeterminateSegment(
        animationValue, SecondLineTailDelay, SecondLineTailDuration,
        LinearAnimationProgressDuration, LineEasing);

    // Track before line 1
    if (firstLineHead < 1.0) {
      const qreal start =
          firstLineHead > 0.0 ? firstLineHead + gapSizeFraction : 0.0;

      drawLinearIndicator(painter, start, 1.0, m_trackColor, strokeWidth);
    }

    // Line 1
    if (firstLineHead - firstLineTail > 0.0) {
      drawLinearIndicator(painter, firstLineTail, firstLineHead, m_color,
                          strokeWidth);
    }

    // Track between line 1 and line 2
    if (firstLineTail > gapSizeFraction) {
      const qreal start =
          secondLineHead > 0.0 ? secondLineHead + gapSizeFraction : 0.0;

      const qreal end =
          firstLineTail < 1.0 ? firstLineTail - gapSizeFraction : 1.0;

      drawLinearIndicator(painter, start, end, m_trackColor, strokeWidth);
    }

    // Line 2
    if (secondLineHead - secondLineTail > 0.0) {
      drawLinearIndicator(painter, secondLineTail, secondLineHead, m_color,
                          strokeWidth);
    }

    // Track after line 2
    if (secondLineTail > gapSizeFraction) {
      const qreal end =
          secondLineTail < 1.0 ? secondLineTail - gapSizeFraction : 1.0;

      drawLinearIndicator(painter, 0.0, end, m_trackColor, strokeWidth);
    }
  }
}

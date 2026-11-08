#include "linear_wavy_progress_indicator.h"
#include "progress_indicator_common.h"
#include "utils.h"
#include <QParallelAnimationGroup>
#include <array>
#include <qabstractanimation.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpen.h>
#include <qquickitem.h>
#include <qvariantanimation.h>

using namespace material::internals;
using namespace material::internals::progress_indicator;

namespace {
static constexpr int IndeterminateLineCount = 2;
static constexpr int DeterminateLineCount = 1;

static inline QVariantAnimation *createWaveOffsetAnimation(QObject *parent) {
  auto valueAnimation = new QVariantAnimation(parent);
  return valueAnimation;
}

static inline QVariantAnimation *createProgressAnimation(QObject *parent) {
  auto anim = new QVariantAnimation(parent);
  anim->setStartValue(0.0);
  anim->setEndValue(1.0);
  anim->setDuration(LinearAnimationProgressDuration);
  return anim;
}

static const QEasingCurve ProgressAnimationCurve =
    QEasingCurve(QEasingCurve::InOutCubic);

} // namespace

QColor LinearWavyProgressIndicatorImpl::color() const { return m_color; }
void LinearWavyProgressIndicatorImpl::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  update();
}

QColor LinearWavyProgressIndicatorImpl::trackColor() const {
  return m_trackColor;
}
void LinearWavyProgressIndicatorImpl::setTrackColor(const QColor &color) {
  if (color == m_trackColor) {
    return;
  }

  m_trackColor = color;
  update();
}

qreal LinearWavyProgressIndicatorImpl::gapSize() const { return m_gapSize; }

void LinearWavyProgressIndicatorImpl::setGapSize(qreal gapSize) {
  if (gapSize == m_gapSize) {
    return;
  }

  m_gapSize = gapSize;
  invalidateCachedPath();
  update();
}

qreal LinearWavyProgressIndicatorImpl::strokeWidth() const {
  return m_strokeWidth;
}
void LinearWavyProgressIndicatorImpl::setStrokeWidth(qreal strokeWidth) {
  if (strokeWidth == m_strokeWidth) {
    return;
  }

  m_strokeWidth = strokeWidth;
  invalidateCachedPath();
  update();
}
qreal LinearWavyProgressIndicatorImpl::trackStrokeWidth() const {
  return m_trackStrokeWidth;
}
void LinearWavyProgressIndicatorImpl::setTrackStrokeWidth(
    qreal trackStrokeWidth) {
  if (trackStrokeWidth == m_trackStrokeWidth) {
    return;
  }

  m_trackStrokeWidth = trackStrokeWidth;
  invalidateCachedPath();
  update();
}

qreal LinearWavyProgressIndicatorImpl::amplitude() const { return m_amplitude; }

void LinearWavyProgressIndicatorImpl::setAmplitude(qreal amplitude) {
  if (amplitude == m_amplitude) {
    return;
  }
  m_amplitude = amplitude;

  invalidateCachedPath();
  updateAmplitudeAnimation(amplitude);
}

qreal LinearWavyProgressIndicatorImpl::waveSpeed() const { return m_waveSpeed; }
void LinearWavyProgressIndicatorImpl::setWaveSpeed(qreal waveSpeed) {
  if (waveSpeed == m_waveSpeed) {
    return;
  }

  m_waveSpeed = waveSpeed;
  updateOffsetAnimationSpec();
  update();
}
qreal LinearWavyProgressIndicatorImpl::waveLength() const {
  return m_waveLength;
}
void LinearWavyProgressIndicatorImpl::setWaveLength(qreal waveLength) {
  if (waveLength == m_waveLength) {
    return;
  }

  m_waveLength = waveLength;
  invalidateCachedPath();
  updateOffsetAnimationSpec();
  update();
}

qreal LinearWavyProgressIndicatorImpl::visualPosition() const {
  return m_progress;
}
void LinearWavyProgressIndicatorImpl::setVisualPosition(qreal visualPositon) {
  if (visualPositon == m_progress) {
    return;
  }

  m_progress = visualPositon;
  if (m_amplitudeAnim->state() == QAbstractAnimation::Stopped) {
    update();
  }
}

bool LinearWavyProgressIndicatorImpl::indeterminate() const {
  return m_indeterminate;
}
void LinearWavyProgressIndicatorImpl::setIndeterminate(bool indeterminate) {
  if (indeterminate == m_indeterminate) {
    return;
  }

  if (m_indeterminate) {
    removeIndeterminateAnimations();
  } else {
    createIndeterminateAnimations();
  }
}

void LinearWavyProgressIndicatorImpl::removeIndeterminateAnimations() {
  m_animations->stop();

  disconnect(progressAnimation(), &QVariantAnimation::valueChanged, this,
             &LinearWavyProgressIndicatorImpl::onAnimationValueChanged);

  delete m_animations->takeAnimation(ProgressAnimation);

  connect(waveOffsetAnimation(), &QVariantAnimation::valueChanged, this,
          &LinearWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_indeterminate = false;
  m_animations->start();
}

void LinearWavyProgressIndicatorImpl::createIndeterminateAnimations() {
  m_animations->stop();

  // disconnect from waveOffsetAnimation
  disconnect(waveOffsetAnimation(), &QVariantAnimation::valueChanged, this,
             &LinearWavyProgressIndicatorImpl::onAnimationValueChanged);

  auto *progressAnimation = createProgressAnimation(m_animations);

  m_animations->insertAnimation(ProgressAnimation, progressAnimation);

  connect(progressAnimation, &QVariantAnimation::valueChanged, this,
          &LinearWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_indeterminate = true;
  m_animations->start();
}

LinearWavyProgressIndicatorImpl::LinearWavyProgressIndicatorImpl(
    QQuickItem *parent)
    : QQuickPaintedItem(parent) {

  m_amplitudeAnim = new QVariantAnimation(this);
  m_amplitudeAnim->setStartValue(m_amplitude);
  m_amplitudeAnim->setEndValue(m_amplitude);

  m_animations = new QParallelAnimationGroup(this);

  auto *waveOffsetAnimation = createWaveOffsetAnimation(m_animations);
  connect(waveOffsetAnimation, &QVariantAnimation::valueChanged, this,
          &LinearWavyProgressIndicatorImpl::onAnimationValueChanged);

  m_animations->insertAnimation(WaveOffsetAnimation, waveOffsetAnimation);
  m_animations->setLoopCount(-1);

  connect(m_amplitudeAnim, &QVariantAnimation::valueChanged, this,
          [this](const QVariant &) {
            invalidateCachedPath();
            update();
          });
  connect(this, &QQuickItem::heightChanged, this,
          [this]() { invalidateCachedPath(); });
  connect(this, &QQuickItem::widthChanged, this,
          [this]() { invalidateCachedPath(); });
}

void LinearWavyProgressIndicatorImpl::componentComplete() {
  QQuickPaintedItem::componentComplete();
  updateOffsetAnimationSpec();
}

QVariantAnimation *
LinearWavyProgressIndicatorImpl::waveOffsetAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(WaveOffsetAnimation));
}
QVariantAnimation *LinearWavyProgressIndicatorImpl::progressAnimation() const {
  return static_cast<QVariantAnimation *>(
      m_animations->animationAt(ProgressAnimation));
}

void LinearWavyProgressIndicatorImpl::updateAmplitudeAnimation(
    qreal targetValue) {
  m_amplitudeAnim->stop();
  if (m_amplitudeAnim->currentValue().toReal() < targetValue) {
    m_amplitudeAnim->setEasingCurve(IncreasingAmplitudeAnimSpec.curve);
    m_amplitudeAnim->setDuration(IncreasingAmplitudeAnimSpec.duration);
  } else {
    m_amplitudeAnim->setEasingCurve(DecreasingAmplitudeAnimSpec.curve);
    m_amplitudeAnim->setDuration(DecreasingAmplitudeAnimSpec.duration);
  }

  m_amplitudeAnim->setStartValue(m_amplitudeAnim->currentValue());
  m_amplitudeAnim->setEndValue(targetValue);
  connect(
      m_amplitudeAnim, &QAbstractAnimation::finished, this,
      [this]() { updateOffsetAnimationSpec(); }, Qt::SingleShotConnection);
  m_amplitudeAnim->start();
}

void LinearWavyProgressIndicatorImpl::updateOffsetAnimationSpec() {
  auto offsetAnim = waveOffsetAnimation();
  if (m_waveSpeed > 0 && m_waveLength > 0 && m_amplitude > 0) {
    bool isStopped = m_animations->state() == QAbstractAnimation::Stopped;
    if (!isStopped) {
      m_animations->pause();
    }
    const int duration =
        std::max(utils::roundToInt((m_waveLength / m_waveSpeed) * 1000), 50);

    offsetAnim->setDuration(duration);
    offsetAnim->setEasingCurve(QEasingCurve::Linear);
    offsetAnim->setStartValue(0.0);
    offsetAnim->setEndValue(1.0);
    if (!isStopped) {
      m_animations->resume();
    } else {
      m_animations->start();
    }
  } else {
    m_animations->stop();
    offsetAnim->setStartValue(0.0);
    offsetAnim->setEndValue(0.0);
    offsetAnim->setDuration(0.0);
  }
}

void LinearWavyProgressIndicatorImpl::updateFullPath(qreal amplitude) {
  const auto size = this->size();
  const auto height = size.height();
  const auto width = size.width();

  QPainterPath path{};

  path.moveTo(0, 0);

  if (amplitude == 0.0) {
    path.lineTo(width, 0);
  } else {
    const qreal halfWavelengthPx = m_waveLength / 2;

    qreal anchorX = halfWavelengthPx;
    const qreal anchorY = 0;

    qreal controlX = halfWavelengthPx / 2;
    qreal controlY = height - m_strokeWidth;

    // // Plot a path that holds a couple of extra waves.
    // This can later be used to create a
    // // progressPathToDraw with a wave offset value to
    // simulate a wave movement.
    // // Note that we add more than one wave-length to
    // support cases where the wavelength is
    // // relatively large and may end up in cases where a
    // single extra wavelength is not
    // // sufficient for the wave's motion drawing.
    const auto widthWithExtraPhase = width + m_waveLength * 2;

    while (anchorX <= widthWithExtraPhase) {
      path.quadTo(controlX, controlY, anchorX, anchorY);
      anchorX += halfWavelengthPx;
      controlX += halfWavelengthPx;
      controlY *= -1.0;
    }
  }

  path.translate(0, height / 2);

  m_cachedPath.emplace(path);
}

void LinearWavyProgressIndicatorImpl::drawIndicator(
    const QPainterPath fullPath, std::span<QPainterPath> &progressPaths,
    QPainterPath &trackPath, const std::span<const qreal> progressFractions,
    qreal waveShift, const QSizeF &size) {

  const qreal height = size.height();
  const auto width = size.width();
  const qreal halfHeight = height / 2;
  const qreal scale =
      fullPath.length() / (fullPath.boundingRect().width() + 0.00000001);

  qreal strokeCapWidth = std::max(m_strokeWidth / 2, m_trackStrokeWidth / 2);

  bool activeIndicatorVisible = false;
  qreal adjustedGap = m_gapSize + strokeCapWidth * 2;

  auto nextEndTrackOffset = width - strokeCapWidth;
  trackPath.moveTo(nextEndTrackOffset, halfHeight);

  for (std::size_t i = 0; i < progressPaths.size(); ++i) {
    auto startProgressFraction = progressFractions[i * 2];
    auto endProgressFraction = progressFractions[i * 2 + 1];

    auto barTail = startProgressFraction * width;
    auto barHead = endProgressFraction * width;

    if (i == 0) {
      // Potentially shorten the gap and insets when the progress bar just
      // enters the track. When rounded caps are applied, we need enough space
      // to draw the initial path (i.e. circle), so by only adjusting the gap
      // size when the barHead >= currentStrokeCapWidth we ensure that the
      // track is not being shortened in this initial progress phase.
      adjustedGap = (barHead < strokeCapWidth)
                        ? 0.0
                        : qMin(barHead - strokeCapWidth, m_gapSize);
      activeIndicatorVisible = barHead >= strokeCapWidth;
    }

    // stroke's caps.
    qreal adjustedBarHead =
        std::clamp(barHead, strokeCapWidth, width - strokeCapWidth);
    qreal adjustedBarTail =
        std::clamp(barTail, strokeCapWidth, width - strokeCapWidth);

    // Update the progressPathToDraw
    if (std::abs(endProgressFraction - startProgressFraction) > 0) {
      const qreal startDist = (adjustedBarTail + waveShift) * scale;
      const qreal endDist = (adjustedBarHead + waveShift) * scale;

      const qreal pathLength = fullPath.length();

      progressPaths[i] =
          fullPath.trimmed(startDist / pathLength, endDist / pathLength);
    }

    // While we draw the progress parts from left to right, we also draw the
    // track parts from right to left and update the nextEndTrackOffset on
    // every pass. Before that, we calculate the spacing between the active
    // indicator and the track to adjust it if needed when the progress is
    // small.
    const auto adaptiveTrackSpacing =
        activeIndicatorVisible ? adjustedGap + strokeCapWidth * 2 : adjustedGap;
    if (nextEndTrackOffset > adjustedBarHead + adaptiveTrackSpacing) {
      trackPath.lineTo(
          qMax(strokeCapWidth, adjustedBarHead + adaptiveTrackSpacing),
          halfHeight);
    }

    if (barHead > barTail) {
      // Update the nextEndTrackOffset and move the path to prepare for the
      // next draw.
      nextEndTrackOffset =
          qMax(strokeCapWidth, adjustedBarTail - adaptiveTrackSpacing);
      trackPath.moveTo(nextEndTrackOffset, halfHeight);
    }
  }

  // Final track drawing, if needed. This will fill any track gaps to the left
  // of the progress.
  if (nextEndTrackOffset > strokeCapWidth) {
    trackPath.lineTo(strokeCapWidth, halfHeight);
  }
}

void LinearWavyProgressIndicatorImpl::paint(QPainter *painter) {
  const qreal amplitude = m_amplitudeAnim->currentValue().toReal();

  if (!m_cachedPath.has_value()) {
    updateFullPath(amplitude);
  }

  const QSizeF size = this->size();
  const qreal halfHeight = size.height() / 2;

  const QPainterPath &fullPath = m_cachedPath.value();

  const qreal waveOffset = waveOffsetAnimation()->currentValue().toReal();
  const qreal waveShift = amplitude > 0 ? waveOffset * m_waveLength : 0.0;

  QPainterPath trackPath;

  auto progressPathsStorage =
      std::array<QPainterPath,
                 static_cast<std::size_t>(IndeterminateLineCount)>();
  std::size_t progressPathsCount = 0;

  if (m_indeterminate) {
    const auto progress = progressAnimation()->currentValue().toReal();

    const auto progressFractions = std::array{
        utils::evaluateIndeterminateSegment(
            progress, FirstLineTailDelay, FirstLineTailDuration,
            LinearAnimationProgressDuration,
            EasingEmphasizedAccelerateCubicBezier),
        utils::evaluateIndeterminateSegment(
            progress, FirstLineHeadDelay, FirstLineHeadDuration,
            LinearAnimationProgressDuration,
            EasingEmphasizedAccelerateCubicBezier),
        utils::evaluateIndeterminateSegment(
            progress, SecondLineTailDelay, SecondLineTailDuration,
            LinearAnimationProgressDuration,
            EasingEmphasizedAccelerateCubicBezier),
        utils::evaluateIndeterminateSegment(
            progress, SecondLineHeadDelay, SecondLineHeadDuration,
            LinearAnimationProgressDuration,
            EasingEmphasizedAccelerateCubicBezier),
    };

    progressPathsCount = IndeterminateLineCount;
    auto progressPaths = std::span<QPainterPath>{progressPathsStorage.data(),
                                                 progressPathsCount};

    drawIndicator(fullPath, progressPaths, trackPath, progressFractions,
                  waveShift, size);
  } else {
    const auto progressFractions = std::array{0.0, m_progress};

    progressPathsCount = DeterminateLineCount;
    auto progressPaths = std::span<QPainterPath>{progressPathsStorage.data(),
                                                 progressPathsCount};

    drawIndicator(fullPath, progressPaths, trackPath, progressFractions,
                  waveShift, size);
  }

  QPen pen(m_trackColor, m_trackStrokeWidth);

  pen.setJoinStyle(Qt::RoundJoin);
  pen.setCapStyle(Qt::RoundCap);

  painter->setRenderHint(QPainter::Antialiasing);

  painter->setPen(pen);

  painter->drawPath(trackPath);

  painter->save();

  pen.setColor(m_color);
  pen.setWidth(m_strokeWidth);
  painter->setPen(pen);

  QTransform transform;
  transform.translate(waveShift > 0 ? -waveShift : 0, halfHeight);
  transform.scale(1.0, amplitude);
  transform.translate(0, -halfHeight);

  for (std::size_t i = 0; i < progressPathsCount; ++i) {
    painter->drawPath(transform.map(progressPathsStorage[i]));
  }

  painter->restore();
}

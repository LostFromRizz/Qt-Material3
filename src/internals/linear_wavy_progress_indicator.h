#ifndef MATERIAL_INTERNALS_LINEAR_WAVY_PROGRESS_INDICATOR_H
#define MATERIAL_INTERNALS_LINEAR_WAVY_PROGRESS_INDICATOR_H

#include <QtGui/qcolor.h>
#include <QtGui/qpainterpath.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>
#include <qpainter.h>
#include <qtpreprocessorsupport.h>

class QVariantAnimation;
class QParallelAnimationGroup;

namespace material::internals {

class LinearWavyProgressIndicatorImpl : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
  Q_PROPERTY(qreal gapSize READ gapSize WRITE setGapSize)
  Q_PROPERTY(qreal amplitude READ amplitude WRITE setAmplitude)
  Q_PROPERTY(qreal waveLength READ waveLength WRITE setWaveLength)
  Q_PROPERTY(qreal waveSpeed READ waveSpeed WRITE setWaveSpeed)
  Q_PROPERTY(qreal strokeWidth READ strokeWidth WRITE setStrokeWidth)
  Q_PROPERTY(
      qreal trackStrokeWidth READ trackStrokeWidth WRITE setTrackStrokeWidth)
  Q_PROPERTY(qreal visualPosition READ visualPosition WRITE setVisualPosition)
  Q_PROPERTY(bool indeterminate READ indeterminate WRITE setIndeterminate)

  QML_ELEMENT

public:
  explicit LinearWavyProgressIndicatorImpl(QQuickItem *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &);
  QColor trackColor() const;
  void setTrackColor(const QColor &);
  qreal gapSize() const;
  void setGapSize(qreal);
  qreal strokeWidth() const;
  void setStrokeWidth(qreal);
  qreal trackStrokeWidth() const;
  void setTrackStrokeWidth(qreal);
  qreal amplitude() const;
  void setAmplitude(qreal);
  qreal waveLength() const;
  void setWaveLength(qreal);
  qreal waveSpeed() const;
  void setWaveSpeed(qreal);
  bool indeterminate() const;
  void setIndeterminate(bool);
  qreal visualPosition() const;
  void setVisualPosition(qreal);

  void paint(QPainter *painter) override;

private slots:
  inline void onAnimationValueChanged(const QVariant &v) {
    Q_UNUSED(v)
    update();
  }

private:
  enum Animations { WaveOffsetAnimation, ProgressAnimation };

  void inline invalidateCachedPath() { m_cachedPath.reset(); }

  void componentComplete() override;
  void updateFullPath(qreal amplitude);
  void updateAmplitudeAnimation(qreal targetValue);
  void updateOffsetAnimationSpec();

  void createIndeterminateAnimations();
  void removeIndeterminateAnimations();

  QVariantAnimation *waveOffsetAnimation() const;
  QVariantAnimation *progressAnimation() const;

  void drawIndicator(const QPainterPath fullPath,
                     std::span<QPainterPath> &progressPaths,
                     QPainterPath &trackPath,
                     const std::span<const qreal> progressFractions,
                     qreal waveShift, const QSizeF &size);

  void drawTrackPath(QPainter *painter);

  QColor m_color, m_trackColor;
  qreal m_gapSize;
  qreal m_waveLength;
  qreal m_amplitude;
  qreal m_waveSpeed;
  qreal m_progress = 0.0;
  int m_strokeWidth;
  int m_trackStrokeWidth;
  bool m_indeterminate = false;
  std::optional<QPainterPath> m_cachedPath;
  QVariantAnimation *m_amplitudeAnim;
  QParallelAnimationGroup *m_animations;
};

} // namespace material::internals

#endif // MATERIAL_INTERNALS_LINEAR_WAVY_PROGRESS_INDICATOR_H

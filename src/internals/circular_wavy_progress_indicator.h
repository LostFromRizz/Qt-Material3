#ifndef MATERIAL_INTERNALS_CIRCULAR_WAVY_PROGRESS_BAR_IMPL_H
#define MATERIAL_INTERNALS_CIRCULAR_WAVY_PROGRESS_BAR_IMPL_H

#include <QtGui/qcolor.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>
#include <qvariant.h>

class QVariantAnimation;
class QParallelAnimationGroup;

namespace material::internals {

class CircularWavyProgressIndicatorImpl : public QQuickPaintedItem {
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
  Q_PROPERTY(bool indeterminate READ indeterminate WRITE setIndeterminate)
  Q_PROPERTY(qreal progress READ progress WRITE setProgress)

  QML_ELEMENT

public:
  explicit CircularWavyProgressIndicatorImpl(QQuickItem *parent = nullptr);

  void paint(QPainter *painter) override;
  void componentComplete() override;

  QColor color() const;
  void setColor(const QColor &);
  QColor trackColor() const;
  void setTrackColor(const QColor &);
  qreal gapSize() const;
  void setGapSize(qreal);
  qreal waveLength() const;
  void setWaveLength(qreal);
  qreal amplitude() const;
  void setAmplitude(qreal);
  qreal waveSpeed() const;
  void setWaveSpeed(qreal);
  qreal strokeWidth() const;
  void setStrokeWidth(qreal);
  qreal trackStrokeWidth() const;
  void setTrackStrokeWidth(qreal);
  qreal progress() const;
  void setProgress(qreal);
  bool indeterminate() const;
  void setIndeterminate(bool);

private slots:
  void inline onAnimationValueChanged(const QVariant &v) {
    Q_UNUSED(v);
    update();
  }

  void removeIndeterminateAnimations();
  void createIndeterminateAnimations();

private:
  enum AnimationType {
    WaveOffsetAnimation,
    GlobalRoatationAnimation,
    AdditionalRoatationAnimation,
    ProgressSweepAnimation,
  };

  void updateAmplitudeAnimation(qreal targetValue);
  void updateOffsetAnimationSpec();

  void drawProgressPath(QPainterPath &path, qreal amplitude, qreal radius,
                        qreal startAngle, qreal sweepAngle, qreal waveOffset,
                        qreal waveCycles, const QPointF &center) const;
  void drawTrackPath(QPainter &painter, qreal radius, qreal startAngle,
                     qreal sweepAngle, qreal progressSweep, qreal gapSize,
                     const QPointF &center) const;

  QVariantAnimation *globalRotationAnimation() const;
  QVariantAnimation *waveOffsetAnimation() const;
  QVariantAnimation *additionalRotationAnimation() const;
  QVariantAnimation *progressSweepAnimation() const;

  QColor m_color, m_trackColor;
  qreal m_gapSize;
  qreal m_waveLength;
  qreal m_amplitude;
  qreal m_waveSpeed;
  int m_strokeWidth;
  int m_trackStrokeWidth;
  qreal m_progress;
  bool m_indeterminate = false;

  QVariantAnimation *m_amplitudeAnim;
  QParallelAnimationGroup *m_animations;
};
}; // namespace material::internals

#endif // MATERIAL_INTERNALS_CIRCULAR_WAVY_PROGRESS_BAR_IMPL_H

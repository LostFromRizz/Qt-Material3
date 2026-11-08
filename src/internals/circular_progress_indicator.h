#ifndef MATERIAL_INTERNALS_CIRCULAR_PROGRESS_BAR_IMPL_H
#define MATERIAL_INTERNALS_CIRCULAR_PROGRESS_BAR_IMPL_H

#include <QtGui/qcolor.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>
#include <qvariant.h>

class QVariantAnimation;
class QParallelAnimationGroup;

namespace material::internals {

class CircularProgressIndicatorImpl : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
  Q_PROPERTY(qreal gapSize READ gapSize WRITE setGapSize)
  Q_PROPERTY(qreal strokeWidth READ strokeWidth WRITE setStrokeWidth)
  Q_PROPERTY(qreal progress READ progress WRITE setProgress)
  Q_PROPERTY(bool indeterminate READ indeterminate WRITE setIndeterminate)
  Q_PROPERTY(bool flat READ flat WRITE setFlat)
  QML_ELEMENT

public:
  explicit CircularProgressIndicatorImpl(QQuickItem *parent = nullptr);

  void paint(QPainter *painter) override;
  void componentComplete() override;

  QColor color() const;
  void setColor(const QColor &);
  QColor trackColor() const;
  void setTrackColor(const QColor &);
  qreal gapSize() const;
  void setGapSize(qreal);
  qreal strokeWidth() const;
  void setStrokeWidth(qreal);
  qreal progress() const;
  void setProgress(qreal);
  bool indeterminate() const;
  void setIndeterminate(bool);
  bool flat() const;
  void setFlat(bool);

private slots:
  void inline onAnimationValueChanged(const QVariant &v) {
    Q_UNUSED(v);
    update();
  }

  void removeIndeterminateAnimations();
  void createIndeterminateAnimations();

private:
  enum AnimationType {
    GlobalRoatationAnimation,
    AdditionalRoatationAnimation,
    ProgressAnimation,
  };

  void drawArc(QPainter *painter, qreal startAngle, qreal sweep) const;
  void drawTrack(QPainter *painter, qreal startAngle, qreal sweep) const;
  void drawProgressIndicator(QPainter *painter, qreal startAngle,
                             qreal sweep) const;

  QVariantAnimation *globalRotationAnimation() const;
  QVariantAnimation *additionalRotationAnimation() const;
  QVariantAnimation *progressAnimation() const;

  QColor m_color, m_trackColor;
  qreal m_gapSize = 0.0;
  int m_strokeWidth = 0.0;
  int m_trackStrokeWidth = 0.0;
  qreal m_progress = 0.0;
  bool m_flat = false;
  bool m_indeterminate = false;

  QParallelAnimationGroup *m_animations = nullptr;
};
}; // namespace material::internals

#endif // MATERIAL_INTERNALS_CIRCULAR_WAVY_PROGRESS_BAR_IMPL_H

#ifndef MATERIAL_INTERNALS_LINEAR_PROGRESS_INDICATOR_H
#define MATERIAL_INTERNALS_LINEAR_PROGRESS_INDICATOR_H

#include <QtGui/qcolor.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>

class QVariantAnimation;

namespace material::internals {
class LinearProgressIndicatorImpl : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(QColor trackColor READ trackColor WRITE setTrackColor)
  Q_PROPERTY(qreal gapSize READ gapSize WRITE setGapSize)
  Q_PROPERTY(bool flat READ flat WRITE setFlat)
  Q_PROPERTY(qreal visualPosition READ visualPosition WRITE setVisualPosition)
  Q_PROPERTY(bool indeterminate READ indeterminate WRITE setIndeterminate)
  QML_ELEMENT

public:
  LinearProgressIndicatorImpl(QQuickItem *parent = nullptr);

  void paint(QPainter *painter) override;

  QColor color() const;
  void setColor(const QColor &);
  QColor trackColor() const;
  void setTrackColor(const QColor &);
  qreal gapSize() const;
  void setGapSize(qreal);
  bool flat() const;
  void setFlat(bool);
  qreal visualPosition() const;
  void setVisualPosition(qreal);
  bool indeterminate() const;
  void setIndeterminate(bool);

private slots:
  void onAnimationValueChanged();

private:
  void drawLinearIndicator(QPainter *painter, qreal startFraction,
                           qreal endFraction, const QColor &color,
                           qreal strokeWidth);

  static QVariantAnimation *createIndeterminateAnimation(QObject *parent);

  QColor m_color, m_trackColor;
  qreal m_gapSize;
  qreal m_visualPosition;

  bool m_flat = false;
  bool m_indeterminate = false;

  QVariantAnimation *m_indeterminateAim = nullptr;
};
} // namespace material::internals

#endif // MATERIAL_INTERNALS_LINEAR_PROGRESS_INDICATOR_H

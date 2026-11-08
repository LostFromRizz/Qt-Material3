#ifndef MATERIAL_INTERNALS_RIPPLE_H
#define MATERIAL_INTERNALS_RIPPLE_H

#include <QPainterPath>
#include <QtGui/qcolor.h>
#include <QtQml/qqml.h>
#include <qquickitem.h>

namespace material::internals {
class Ripple : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(qreal radius READ radius WRITE setRadius)
  QML_ELEMENT

public:
  explicit Ripple(QQuickItem *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &);
  qreal radius() const;
  void setRadius(qreal radius);

private:
  QColor m_color;
  qreal m_topRadius, m_leftRadius, m_bottomRadius, m_rightRadius;
};
} // namespace material::internals
#endif // MATERIAL_INTERNALS_RIPPLE_H

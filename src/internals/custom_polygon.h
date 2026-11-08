#ifndef MATERIAL_INTERNALS_CUSTOM_POLYGON_H
#define MATERIAL_INTERNALS_CUSTOM_POLYGON_H

#include "cubic.h"
#include "rounded_polygon.h"
#include <QtGui/qcolor.h>
#include <QtGui/qpainterpath.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>

namespace material::internals {
class PolygonPainter : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QList<material::internals::Cubic> cubics READ polygon WRITE
                 setPolygon NOTIFY polygonChanged FINAL)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)

  QML_ELEMENT

public:
  explicit PolygonPainter(QQuickItem *parent = nullptr);

  QList<shapes::Cubic> cubics() const;
  void setCubics(const QList<shapes::Cubic> &&);

  QColor color() const;
  void setColor(const QColor &);

  void paint(QPainter *painter) override;

signals:
  void cubicsChanged();
  void colorChanged();

private:
  QList<shapes::Cubic> m_cubics;
  float m_scaleFactor = 1.0f;
  QColor m_color;
};

} // namespace material::internals

#endif // MATERIAL_INTERNALS_CUSTOM_POLYGON_H

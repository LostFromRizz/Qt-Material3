#ifndef MATERIAL_INTERNALS_POLYGON_PAINTER_H
#define MATERIAL_INTERNALS_POLYGON_PAINTER_H

#include "rounded_polygon.h"
#include <QtGui/qcolor.h>
#include <QtGui/qpainterpath.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickpainteditem.h>
#include <shapes/cubic.h>

namespace material {
class PolygonPainter : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(material::shapes::RoundedPolygon *polygon READ polygon WRITE
                 setPolygon NOTIFY polygonChanged FINAL)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)

  QML_ELEMENT

public:
  explicit PolygonPainter(QQuickItem *parent = nullptr);

  shapes::RoundedPolygon *polygon() const;
  void setPolygon(shapes::RoundedPolygon *);

  QColor color() const;
  void setColor(const QColor &);

  void paint(QPainter *painter) override;

signals:
  void polygonChanged();
  void colorChanged();

private:
  QColor m_color;
  shapes::RoundedPolygon *m_polygon = nullptr;
  float m_scaleFactor = 1.0f;
};

} // namespace material

#endif // MATERIAL_INTERNALS_POLYGON_PAINTER_H

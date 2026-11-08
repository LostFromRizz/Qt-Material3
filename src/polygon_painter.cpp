#include "polygon_painter.h"
#include "painting.h"
#include <qpainter.h>

using namespace material;
using namespace material::internals;
using namespace material::shapes;

namespace {
inline float height(const Cubic::BoundsArray &bounds) {
  return bounds[3] - bounds[1];
}
inline float width(const Cubic::BoundsArray &bounds) {
  return bounds[2] - bounds[0];
}

float calculateScaleFactor(const RoundedPolygon &polygon) {
  // Axis-aligned max bounding box for this object, where the rectangles
  // left, top, right, and bottom values will be stored in entries 0, 1, 2,
  // and 3, in that order.
  auto bounds = Cubic::BoundsArray();
  auto maxBounds = Cubic::BoundsArray();

  polygon.calculateBounds(bounds);
  polygon.calculateMaxBounds(maxBounds);
  auto scaleX = width(bounds) / width(maxBounds);
  auto scaleY = height(bounds) / height(maxBounds);
  return std::min(1.0f, std::max(scaleX, scaleY));
}
} // namespace

PolygonPainter::PolygonPainter(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_color(Qt::black) {}

QColor PolygonPainter::color() const { return m_color; }
void PolygonPainter::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  emit colorChanged();
  update();
}

RoundedPolygon *PolygonPainter::polygon() const { return m_polygon; }
void PolygonPainter::setPolygon(RoundedPolygon *polygon) {
  if (polygon == m_polygon) {
    return;
  }

  m_polygon = polygon;
  m_scaleFactor =
      m_polygon != nullptr ? calculateScaleFactor(*m_polygon) : 1.0f;
  emit polygonChanged();
  update();
}

void PolygonPainter::paint(QPainter *painter) {
  if (!m_polygon) {
    return;
  }

  painter->setRenderHint(QPainter::Antialiasing, true);

  const auto size = this->size();

  // Scale to the desired size.
  QPainterPath path;
  path = shapes::roundedPolygonPath(path, *m_polygon, 0);

  QTransform scaleMatrix;
  scaleMatrix.reset();
  scaleMatrix.scale(size.width() * m_scaleFactor,
                    size.height() * m_scaleFactor);
  path = scaleMatrix.map(path);

  // Translate the path to align its center with the available size center.
  const QPointF sizeCenter(size.width() / 2.0, size.height() / 2.0);
  const QPointF pathCenter = path.boundingRect().center();

  path.translate(sizeCenter - pathCenter);

  painter->fillPath(path, m_color);
}

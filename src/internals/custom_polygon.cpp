#include "custom_polygon.h"
#include "painting.h"
#include <qpainter.h>
#include <qquickitem.h>
#include <qquickpainteditem.h>

using namespace material::internals;
using namespace material::shapes;

namespace {
inline float height(const shapes::Cubic::BoundsArray &bounds) {
  return bounds[3] - bounds[1];
}
inline float width(const shapes::Cubic::BoundsArray &bounds) {
  return bounds[2] - bounds[0];
}

float calculateScaleFactor(const QRoundedPolygon &polygon) {
  // Axis-aligned max bounding box for this object, where the rectangles
  // left, top, right, and bottom values will be stored in entries 0, 1, 2,
  // and 3, in that order.
  auto bounds = shapes::Cubic::BoundsArray();
  auto maxBounds = shapes::Cubic::BoundsArray();

  const auto *inner = polygon.polygon();
  if (!inner) {
    return 1.0f;
  }
  inner->calculateBounds(bounds);
  inner->calculateMaxBounds(maxBounds);
  auto scaleX = width(bounds) / width(maxBounds);
  auto scaleY = height(bounds) / height(maxBounds);
  return std::min(1.0f, std::max(scaleX, scaleY));
}
} // namespace

CustomPolygon::CustomPolygon(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_color(Qt::black) {}

QRoundedPolygon CustomPolygon::polygon() const { return m_polygon; }
void CustomPolygon::setPolygon(const shapes::QRoundedPolygon &polygon) {
  if (polygon == m_polygon) {
    return;
  }

  m_polygon = polygon;
  m_scaleFactor = calculateScaleFactor(m_polygon);
  emit polygonChanged();
  update();
}

QColor CustomPolygon::color() const { return m_color; }
void CustomPolygon::setColor(const QColor &color) {
  if (color == m_color) {
    return;
  }

  m_color = color;
  emit colorChanged();
  update();
}

void CustomPolygon::paint(QPainter *painter) {
  const auto *polygon = m_polygon.polygon();
  if (!polygon) {
    return;
  }

  painter->setRenderHint(QPainter::Antialiasing, true);

  const auto size = this->size();

  // Scale to the desired size.
  QPainterPath path;
  path = shapes::roundedPolygonPath(path, *polygon, 0);

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

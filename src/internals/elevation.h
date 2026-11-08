#ifndef MATERIAL_INTERNALS_ELEVATION_H
#define MATERIAL_INTERNALS_ELEVATION_H

#include <QtGui/qcolor.h>
#include <QtGui/qrgb.h>
#include <QtQmlIntegration/QtQmlIntegration>

namespace material::internals {
struct ShadowForElevation {
  Q_GADGET
  Q_PROPERTY(qreal offset READ offset CONSTANT)
  Q_PROPERTY(qreal blur READ blur CONSTANT)
  Q_PROPERTY(qreal spread READ spread CONSTANT)
  Q_PROPERTY(QColor color READ color CONSTANT)
  QML_ANONYMOUS
public:
  explicit ShadowForElevation(float offset = 0.0, float blur = 0.0,
                              float spread = 0.0, QRgb color = 0x00000000);

  ShadowForElevation(const ShadowForElevation &other) = default;

  inline qreal offset() const;
  inline qreal blur() const;
  inline qreal spread() const;
  inline QColor color() const;

private:
  float m_offset;
  float m_blur;
  float m_spread;
  QRgb m_color;
};

qreal ShadowForElevation::offset() const { return qreal(m_offset); }
qreal ShadowForElevation::blur() const { return qreal(m_blur); }
qreal ShadowForElevation::spread() const { return qreal(m_spread); }
QColor ShadowForElevation::color() const { return QColor::fromRgba(m_color); }

QList<ShadowForElevation> elevationShadowsFor(qreal elevation);

} // namespace material::internals

#endif // MATERIAL_INTERNALS_ELEVATION_H

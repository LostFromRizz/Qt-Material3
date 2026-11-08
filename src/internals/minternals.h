#ifndef MATERIAL_INTERNALS_H
#define MATERIAL_INTERNALS_H

#include "elevation.h"
#include "icon_data.h"
#include <QtQmlIntegration/QtQmlIntegration>

namespace material::internals {

class MInternals : public QObject {
  Q_OBJECT
  Q_PROPERTY(qreal hoveredAlpha READ hoveredAlpha CONSTANT FINAL)
  Q_PROPERTY(qreal pressedAlpha READ pressedAlpha CONSTANT FINAL)
  QML_ELEMENT
  QML_SINGLETON
public:
  explicit MInternals(QObject *parent = nullptr);

  inline qreal hoveredAlpha() const { return 0.08; }
  inline qreal pressedAlpha() const { return 0.10; }

  Q_INVOKABLE QList<ShadowForElevation> shadowsFor(qreal elevation);
  Q_INVOKABLE qreal lerp(qreal start, qreal end, qreal amount);
  Q_INVOKABLE qreal clamp(qreal value, qreal min, qreal max);

  Q_INVOKABLE bool iconColorResolved(const IconData &icon);
};

} // namespace material::internals

#endif // MATERIAL_INTERNALS_H

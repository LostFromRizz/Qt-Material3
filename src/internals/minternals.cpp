#include "minternals.h"
#include "elevation.h"
#include "icon_data_private.h"

using namespace material::internals;

MInternals::MInternals(QObject *parent) : QObject(parent) {}

QList<ShadowForElevation> MInternals::shadowsFor(qreal elevation) {
  return elevationShadowsFor(elevation);
}

qreal MInternals::lerp(qreal start, qreal end, qreal amount) {
  return start + (end - start) * amount;
}
qreal MInternals::clamp(qreal value, qreal min, qreal max) {
  return qMax(min, qMin(max, value));
}

bool MInternals::iconColorResolved(const IconData &icon) {
  return IconDataPrivate::isResolved(icon, IconDataPrivate::ColorResolved);
}

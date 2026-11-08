#include "icon_data.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <qnamespace.h>

using namespace material::internals;

bool IconDataPrivate::isResolved(const IconData &icon, int resolveMask) {
  return icon.d->resolveMask & resolveMask;
}

IconData::IconData() : d(new IconDataPrivate) {}

IconData::IconData(const IconData &other) : d(other.d) {}

IconData::~IconData() {}

IconData &IconData::operator=(const IconData &other) {
  d = other.d;
  return *this;
}

bool IconData::operator==(const IconData &other) const {
  return d == other.d ||
         (d->name == other.d->name && d->source == other.d->source &&
          d->resolvedSource == other.d->resolvedSource &&
          d->width == other.d->width && d->height == other.d->height &&
          d->color == other.d->color && d->cache == other.d->cache);
}

bool IconData::operator!=(const IconData &other) const {
  return !(*this == other);
}

bool IconData::isEmpty() const {
  return d->name.isEmpty() && d->source.isEmpty();
}

QString IconData::name() const { return d->name; }

void IconData::setName(const QString &name) {
  if ((d->resolveMask & IconDataPrivate::NameResolved) && d->name == name)
    return;

  d.detach();
  d->name = name;
  d->resolveMask |= IconDataPrivate::NameResolved;
}

void IconData::resetName() {
  d.detach();
  d->name = QString();
  d->resolveMask &= ~IconDataPrivate::NameResolved;
}

QUrl IconData::source() const { return d->source; }

void IconData::setSource(const QUrl &source) {
  if ((d->resolveMask & IconDataPrivate::SourceResolved) && d->source == source)
    return;

  d.detach();
  d->source = source;
  d->resolvedSource.clear();
  d->resolveMask |= IconDataPrivate::SourceResolved;
}

void IconData::resetSource() {
  d.detach();
  d->source.clear();
  d->resolvedSource.clear();
  d->resolveMask &= ~IconDataPrivate::SourceResolved;
}

QUrl IconData::resolvedSource() const {
  return d->resolvedSource.isEmpty() ? d->source : d->resolvedSource;
}

// must be called by the property owner (e.g. Button) prior to emitting changed
// signal.
void IconData::ensureRelativeSourceResolved(const QObject *owner) {
  if (d->source.isEmpty())
    return;
  if (!d->resolvedSource.isEmpty())
    return; // already resolved relative to (possibly) different owner
  const auto *context = QQmlEngine::contextForObject(owner);
  if (!context)
    return;
  d.detach();
  d->resolvedSource = context->resolvedUrl(d->source);
}

int IconData::width() const { return d->width; }

void IconData::setWidth(int width) {
  if ((d->resolveMask & IconDataPrivate::WidthResolved) && d->width == width)
    return;

  d.detach();
  d->width = width;
  d->resolveMask |= IconDataPrivate::WidthResolved;
}

void IconData::resetWidth() {
  d.detach();
  d->width = 0;
  d->resolveMask &= ~IconDataPrivate::WidthResolved;
}

int IconData::height() const { return d->height; }

void IconData::setHeight(int height) {
  if ((d->resolveMask & IconDataPrivate::HeightResolved) && d->height == height)
    return;

  d.detach();
  d->height = height;
  d->resolveMask |= IconDataPrivate::HeightResolved;
}

void IconData::resetHeight() {
  d.detach();
  d->height = 0;
  d->resolveMask &= ~IconDataPrivate::HeightResolved;
}

QColor IconData::color() const { return d->color; }

void IconData::setColor(const QColor &color) {
  if ((d->resolveMask & IconDataPrivate::ColorResolved) && d->color == color)
    return;

  d.detach();
  d->color = color;
  resolveColor();
}

void IconData::resetColor() {
  d.detach();
  d->color = Qt::transparent;
  d->resolveMask &= ~IconDataPrivate::ColorResolved;
}

void IconData::resolveColor() {
  d->resolveMask |= IconDataPrivate::ColorResolved;
}

bool IconData::cache() const { return d->cache; }

void IconData::setCache(bool cache) {
  if ((d->resolveMask & IconDataPrivate::CacheResolved) && d->cache == cache)
    return;

  d.detach();
  d->cache = cache;
  d->resolveMask |= IconDataPrivate::CacheResolved;
}

void IconData::resetCache() {
  d.detach();
  d->cache = true;
  d->resolveMask &= ~IconDataPrivate::CacheResolved;
}

IconData IconData::resolve(const IconData &other) const {
  IconData resolved = *this;
  resolved.d.detach();

  if (!(d->resolveMask & IconDataPrivate::NameResolved))
    resolved.d->name = other.d->name;

  if (!(d->resolveMask & IconDataPrivate::SourceResolved)) {
    resolved.d->source = other.d->source;
    resolved.d->resolvedSource = other.d->resolvedSource;
  }

  if (!(d->resolveMask & IconDataPrivate::WidthResolved))
    resolved.d->width = other.d->width;

  if (!(d->resolveMask & IconDataPrivate::HeightResolved))
    resolved.d->height = other.d->height;

  if (!(d->resolveMask & IconDataPrivate::ColorResolved))
    resolved.d->color = other.d->color;

  if (!(d->resolveMask & IconDataPrivate::CacheResolved))
    resolved.d->cache = other.d->cache;

  return resolved;
}

#ifndef MATERIAL_INTERNALS_ICON_DATA_PRIVATE_H
#define MATERIAL_INTERNALS_ICON_DATA_PRIVATE_H

#include <QColor>
#include <QUrl>
#include <QtQmlIntegration/QtQmlIntegration>
#include <qnamespace.h>

namespace material::internals {
class IconData;
class IconDataPrivate : public QSharedData {
public:
  static bool isResolved(const IconData &iconData, int resolveMask);

  // This is based on QFont's resolve_mask.
  enum ResolveProperties {
    NameResolved = 0x0001,
    SourceResolved = 0x0002,
    WidthResolved = 0x0004,
    HeightResolved = 0x0008,
    ColorResolved = 0x0010,
    CacheResolved = 0x0020,
    AllPropertiesResolved = 0x1ffff
  };
  int resolveMask;

  QString name;
  QUrl source;
  QUrl resolvedSource;
  int width = 0;
  int height = 0;
  QColor color = Qt::transparent;
  bool cache = true;
};
} // namespace material::internals

#endif // MATERIAL_INTERNALS_ICON_DATA_PRIVATE_H

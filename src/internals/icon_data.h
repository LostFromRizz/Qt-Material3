#ifndef MATERIAL_INTERNALS_ICON_DATA_H
#define MATERIAL_INTERNALS_ICON_DATA_H

#include "icon_data_private.h"
#include <QColor>
#include <QUrl>
#include <QtQmlIntegration/QtQmlIntegration>

namespace material::internals {
class IconData {
  Q_GADGET
  Q_PROPERTY(QString name READ name WRITE setName RESET resetName FINAL)
  Q_PROPERTY(QUrl source READ source WRITE setSource RESET resetSource FINAL)
  Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth FINAL)
  Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight FINAL)
  Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor FINAL)
  Q_PROPERTY(bool cache READ cache WRITE setCache RESET resetCache FINAL)
  QML_VALUE_TYPE(icon)

public:
  IconData();
  IconData(const IconData &other);
  ~IconData();

  IconData &operator=(const IconData &other);
  bool operator==(const IconData &other) const;
  bool operator!=(const IconData &other) const;

  bool isEmpty() const;

  QString name() const;
  void setName(const QString &name);
  void resetName();

  QUrl source() const;
  void setSource(const QUrl &source);
  void resetSource();
  QUrl resolvedSource() const;
  void ensureRelativeSourceResolved(const QObject *owner);

  int width() const;
  void setWidth(int width);
  void resetWidth();

  int height() const;
  void setHeight(int height);
  void resetHeight();

  QColor color() const;
  void setColor(const QColor &color);
  void resetColor();
  void resolveColor();

  bool cache() const;
  void setCache(bool cache);
  void resetCache();

  IconData resolve(const IconData &other) const;

private:
  friend class IconDataPrivate;
  QExplicitlySharedDataPointer<IconDataPrivate> d;
};
} // namespace material::internals

#endif // MATERIAL_INTERNALS_ICON_DATA_H

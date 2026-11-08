#ifndef MATERIAL_INTERNALS_ICON_DATA_H
#define MATERIAL_INTERNALS_ICON_DATA_H

#include <QColor>
#include <QString>
#include <QUrl>
#include <QtQml/QtQml>

namespace material::internals {
class IconData {
  Q_GADGET
  Q_PROPERTY(QString name READ name WRITE setName RESET resetName FINAL)
  Q_PROPERTY(QUrl source READ source WRITE setSource RESET resetSource FINAL)
  Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth FINAL)
  Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight FINAL)
  Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor FINAL)
  Q_PROPERTY(bool cache READ cache WRITE setCache RESET resetCache FINAL)
  QML_ANONYMOUS

public:
  IconData();
  IconData(const QString &name, int width, int height, const QColor &color);
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
  class IconDataPrivate : public QSharedData {
  public:
    static bool isResolved(const IconData &iconData, int resolveMask);

    IconDataPrivate() {};
    explicit IconDataPrivate(const QString &name, int width, int height,
                             const QColor &color);

    // This is based on QFont's resolve_mask.
    enum ResolveProperties {
      NameResolved = 0x0001,
      SourceResolved = 0x0002,
      WidthResolved = 0x0004,
      HeightResolved = 0x0008,
      CacheResolved = 0x0020,
      AllPropertiesResolved = 0x1ffff
    };

    enum Alignment { Start, End, Middle };

    int resolveMask = 0;

    QString name;
    QUrl source;
    QUrl resolvedSource;
    int width = 0;
    int height = 0;
    bool cache = true;
    Alignment alignment = End;
  };

  friend class IconDataPrivate;
  QExplicitlySharedDataPointer<IconDataPrivate> d;
};
} // namespace material::internals

#endif // ICON_DATA_H

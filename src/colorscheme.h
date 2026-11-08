#ifndef MATERIAL_COLORSCHEME_H
#define MATERIAL_COLORSCHEME_H

#include <QObject>
#include <QtGui/QColor>
#include <QtGui/QRgb>
#include <QtQmlIntegration/QtQmlIntegration>
#include <qjsvalue.h>

namespace material {

struct ColorSchemePrivate {
#define COLORS                                                                 \
  QRgb primary;                                                                \
  QRgb onPrimary;                                                              \
  QRgb primaryContainer;                                                       \
  QRgb onPrimaryContainer;                                                     \
  QRgb secondary;                                                              \
  QRgb onSecondary;                                                            \
  QRgb secondaryContainer;                                                     \
  QRgb onSecondaryContainer;                                                   \
  QRgb tertiary;                                                               \
  QRgb onTertiary;                                                             \
  QRgb tertiaryContainer;                                                      \
  QRgb onTertiaryContainer;                                                    \
  QRgb error;                                                                  \
  QRgb onError;                                                                \
  QRgb errorContainer;                                                         \
  QRgb onErrorContainer;                                                       \
  QRgb surface;                                                                \
  QRgb onSurface;                                                              \
  QRgb surfaceVariant;                                                         \
  QRgb onSurfaceVariant;                                                       \
  QRgb surfaceContainerHighest;                                                \
  QRgb surfaceContainerHigh;                                                   \
  QRgb surfaceContainer;                                                       \
  QRgb surfaceContainerLow;                                                    \
  QRgb surfaceContainerLowest;                                                 \
  QRgb inverseSurface;                                                         \
  QRgb inverseOnSurface;                                                       \
  QRgb surfaceTint;                                                            \
  QRgb surfaceBright;                                                          \
  QRgb surfaceDim;                                                             \
  QRgb shadow;                                                                 \
  QRgb scrim;                                                                  \
  QRgb outline;                                                                \
  QRgb outlineVariant;

  COLORS

public:
  ColorSchemePrivate() = default;
  ColorSchemePrivate(const ColorSchemePrivate &other) = default;
  ~ColorSchemePrivate() = default;

  bool operator==(const ColorSchemePrivate &other) const;
  bool operator!=(const ColorSchemePrivate &other) const;

  static inline std::shared_ptr<ColorSchemePrivate> baseLine(bool dark) {
    return dark ? baseLineDark() : baseLineLight();
  }

  static std::shared_ptr<ColorSchemePrivate> fromJSValue(const QJSValue &);

private:
  struct Colors {
    COLORS
  };
#undef COLORS

  explicit ColorSchemePrivate(Colors data);

  static std::shared_ptr<ColorSchemePrivate> baseLineDark();
  static std::shared_ptr<ColorSchemePrivate> baseLineLight();
};

class ColorScheme {
  Q_GADGET
  // Primary
  Q_PROPERTY(QColor primary READ primary WRITE setPrimary FINAL)
  Q_PROPERTY(QColor onPrimary READ onPrimary WRITE setOnPrimary FINAL)
  Q_PROPERTY(QColor primaryContainer READ primaryContainer WRITE
                 setPrimaryContainer FINAL)
  Q_PROPERTY(QColor onPrimaryContainer READ onPrimaryContainer WRITE
                 setOnPrimaryContainer FINAL)

  // Secondary
  Q_PROPERTY(QColor secondary READ secondary WRITE setSecondary FINAL)
  Q_PROPERTY(QColor onSecondary READ onSecondary WRITE setOnSecondary FINAL)
  Q_PROPERTY(QColor secondaryContainer READ secondaryContainer WRITE
                 setSecondaryContainer FINAL)
  Q_PROPERTY(QColor onSecondaryContainer READ onSecondaryContainer WRITE
                 setOnSecondaryContainer FINAL)

  // Tertiary
  Q_PROPERTY(QColor tertiary READ tertiary WRITE setTertiary FINAL)
  Q_PROPERTY(QColor onTertiary READ onTertiary WRITE setOnTertiary FINAL)
  Q_PROPERTY(QColor tertiaryContainer READ tertiaryContainer WRITE
                 setTertiaryContainer FINAL)
  Q_PROPERTY(QColor onTertiaryContainer READ onTertiaryContainer WRITE
                 setOnTertiaryContainer FINAL)

  // Error
  Q_PROPERTY(QColor error READ error WRITE setError FINAL)
  Q_PROPERTY(QColor onError READ onError WRITE setOnError FINAL)
  Q_PROPERTY(
      QColor errorContainer READ errorContainer WRITE setErrorContainer FINAL)
  Q_PROPERTY(QColor onErrorContainer READ onErrorContainer WRITE
                 setOnErrorContainer FINAL)

  // Surface
  Q_PROPERTY(QColor surface READ surface WRITE setSurface FINAL)
  Q_PROPERTY(QColor onSurface READ onSurface WRITE setOnSurface FINAL)
  Q_PROPERTY(
      QColor surfaceVariant READ surfaceVariant WRITE setSurfaceVariant FINAL)
  Q_PROPERTY(QColor onSurfaceVariant READ onSurfaceVariant WRITE
                 setOnSurfaceVariant FINAL)
  Q_PROPERTY(QColor surfaceContainerHighest READ surfaceContainerHighest WRITE
                 setSurfaceContainerHighest FINAL)
  Q_PROPERTY(QColor surfaceContainerHigh READ surfaceContainerHigh WRITE
                 setSurfaceContainerHigh FINAL)
  Q_PROPERTY(QColor surfaceContainer READ surfaceContainer WRITE
                 setSurfaceContainer FINAL)
  Q_PROPERTY(QColor surfaceContainerLow READ surfaceContainerLow WRITE
                 setSurfaceContainerLow FINAL)
  Q_PROPERTY(QColor surfaceContainerLowest READ surfaceContainerLowest WRITE
                 setSurfaceContainerLowest FINAL)
  Q_PROPERTY(
      QColor inverseSurface READ inverseSurface WRITE setInverseSurface FINAL)
  Q_PROPERTY(QColor inverseOnSurface READ inverseOnSurface WRITE
                 setInverseOnSurface FINAL)
  Q_PROPERTY(QColor surfaceTint READ surfaceTint WRITE setSurfaceTint FINAL)
  Q_PROPERTY(
      QColor surfaceBright READ surfaceBright WRITE setSurfaceBright FINAL)
  Q_PROPERTY(QColor surfaceDim READ surfaceDim WRITE setSurfaceDim FINAL)
  Q_PROPERTY(QColor scrim READ scrim WRITE setScrim FINAL)
  Q_PROPERTY(QColor shadow READ shadow WRITE setShadow FINAL)

  // Outline
  Q_PROPERTY(QColor outline READ outline WRITE setOutline FINAL)
  Q_PROPERTY(
      QColor outlineVariant READ outlineVariant WRITE setOutlineVariant FINAL)

  QML_VALUE_TYPE(colorscheme)
  QML_STRUCTURED_VALUE
public:
  explicit ColorScheme(bool dark = false);
  Q_INVOKABLE ColorScheme(const QJSValue &);

  bool operator==(const ColorScheme &other) const;
  bool operator!=(const ColorScheme &other) const;

  inline void swap(const ColorScheme &other) noexcept { *this->d = *other.d; }

  ColorScheme(const ColorScheme &other) = default;
  ColorScheme &operator=(const ColorScheme &other) = default;

  ColorScheme(ColorScheme &&other) = default;
  ColorScheme &operator=(ColorScheme &&other) = default;

  ~ColorScheme() = default;

  inline QColor primary() const noexcept;
  inline void setPrimary(const QColor &) noexcept;
  inline QColor onPrimary() const noexcept;
  inline void setOnPrimary(const QColor &) noexcept;
  inline QColor primaryContainer() const noexcept;
  inline void setPrimaryContainer(const QColor &) noexcept;
  inline QColor onPrimaryContainer() const noexcept;
  inline void setOnPrimaryContainer(const QColor &) noexcept;

  inline QColor secondary() const noexcept;
  inline void setSecondary(const QColor &) noexcept;
  inline QColor onSecondary() const noexcept;
  inline void setOnSecondary(const QColor &) noexcept;
  inline QColor secondaryContainer() const noexcept;
  inline void setSecondaryContainer(const QColor &) noexcept;
  inline QColor onSecondaryContainer() const noexcept;
  inline void setOnSecondaryContainer(const QColor &) noexcept;

  inline QColor tertiary() const noexcept;
  inline void setTertiary(const QColor &) noexcept;
  inline QColor onTertiary() const noexcept;
  inline void setOnTertiary(const QColor &) noexcept;
  inline QColor tertiaryContainer() const noexcept;
  inline void setTertiaryContainer(const QColor &) noexcept;
  inline QColor onTertiaryContainer() const noexcept;
  inline void setOnTertiaryContainer(const QColor &) noexcept;

  inline QColor error() const noexcept;
  inline void setError(const QColor &) noexcept;
  inline QColor onError() const noexcept;
  inline void setOnError(const QColor &) noexcept;
  inline QColor errorContainer() const noexcept;
  inline void setErrorContainer(const QColor &) noexcept;
  inline QColor onErrorContainer() const noexcept;
  inline void setOnErrorContainer(const QColor &) noexcept;

  inline QColor surface() const noexcept;
  inline void setSurface(const QColor &) noexcept;
  inline QColor onSurface() const noexcept;
  inline void setOnSurface(const QColor &) noexcept;
  inline QColor surfaceVariant() const noexcept;
  inline void setSurfaceVariant(const QColor &) noexcept;
  inline QColor onSurfaceVariant() const noexcept;
  inline void setOnSurfaceVariant(const QColor &) noexcept;
  inline QColor surfaceContainerHighest() const noexcept;
  inline void setSurfaceContainerHighest(const QColor &) noexcept;
  inline QColor surfaceContainerHigh() const noexcept;
  inline void setSurfaceContainerHigh(const QColor &) noexcept;
  inline QColor surfaceContainer() const noexcept;
  inline void setSurfaceContainer(const QColor &) noexcept;
  inline QColor surfaceContainerLow() const noexcept;
  inline void setSurfaceContainerLow(const QColor &) noexcept;
  inline QColor surfaceContainerLowest() const noexcept;
  inline void setSurfaceContainerLowest(const QColor &) noexcept;
  inline QColor inverseSurface() const noexcept;
  inline void setInverseSurface(const QColor &) noexcept;
  inline QColor inverseOnSurface() const noexcept;
  inline void setInverseOnSurface(const QColor &) noexcept;
  inline QColor surfaceTint() const noexcept;
  inline void setSurfaceTint(const QColor &) noexcept;
  inline QColor surfaceBright() const noexcept;
  inline void setSurfaceBright(const QColor &) noexcept;
  inline QColor surfaceDim() const noexcept;
  inline void setSurfaceDim(const QColor &) noexcept;
  inline QColor scrim() const noexcept;
  inline void setScrim(const QColor &) noexcept;
  inline QColor shadow() const noexcept;
  inline void setShadow(const QColor &) noexcept;

  inline QColor outline() const noexcept;
  inline void setOutline(const QColor &) noexcept;
  inline QColor outlineVariant() const noexcept;
  inline void setOutlineVariant(const QColor &) noexcept;

  // Q_INVOKABLE QString toString();

private:
  ColorScheme(std::shared_ptr<ColorSchemePrivate>);
  std::shared_ptr<ColorSchemePrivate> d;
};

#define GETTER_SETTER(color_name, getter, setter)                              \
  QColor ColorScheme::getter() const noexcept {                                \
    return QColor::fromRgba(d->color_name);                                    \
  }                                                                            \
  void ColorScheme::setter(const QColor &color) noexcept {                     \
    const QRgb rgba = color.rgba();                                            \
    if (rgba == d->color_name) {                                               \
      return;                                                                  \
    }                                                                          \
    d->color_name = rgba;                                                      \
  }

GETTER_SETTER(primary, primary, setPrimary)
GETTER_SETTER(onPrimary, onPrimary, setOnPrimary)
GETTER_SETTER(primaryContainer, primaryContainer, setPrimaryContainer)
GETTER_SETTER(onPrimaryContainer, onPrimaryContainer, setOnPrimaryContainer)
GETTER_SETTER(secondary, secondary, setSecondary)
GETTER_SETTER(onSecondary, onSecondary, setOnSecondary)
GETTER_SETTER(secondaryContainer, secondaryContainer, setSecondaryContainer)
GETTER_SETTER(onSecondaryContainer, onSecondaryContainer,
              setOnSecondaryContainer)
GETTER_SETTER(tertiary, tertiary, setTertiary)
GETTER_SETTER(onTertiary, onTertiary, setOnTertiary)
GETTER_SETTER(tertiaryContainer, tertiaryContainer, setTertiaryContainer)
GETTER_SETTER(onTertiaryContainer, onTertiaryContainer, setOnTertiaryContainer)
GETTER_SETTER(error, error, setError)
GETTER_SETTER(onError, onError, setOnError)
GETTER_SETTER(errorContainer, errorContainer, setErrorContainer)
GETTER_SETTER(onErrorContainer, onErrorContainer, setOnErrorContainer)
GETTER_SETTER(surface, surface, setSurface)
GETTER_SETTER(onSurface, onSurface, setOnSurface)
GETTER_SETTER(surfaceVariant, surfaceVariant, setSurfaceVariant)
GETTER_SETTER(onSurfaceVariant, onSurfaceVariant, setOnSurfaceVariant)
GETTER_SETTER(surfaceContainerHighest, surfaceContainerHighest,
              setSurfaceContainerHighest)
GETTER_SETTER(surfaceContainerHigh, surfaceContainerHigh,
              setSurfaceContainerHigh)
GETTER_SETTER(surfaceContainer, surfaceContainer, setSurfaceContainer)
GETTER_SETTER(surfaceContainerLow, surfaceContainerLow, setSurfaceContainerLow)
GETTER_SETTER(surfaceContainerLowest, surfaceContainerLowest,
              setSurfaceContainerLowest)
GETTER_SETTER(inverseSurface, inverseSurface, setInverseSurface)
GETTER_SETTER(inverseOnSurface, inverseOnSurface, setInverseOnSurface)
GETTER_SETTER(surfaceTint, surfaceTint, setSurfaceTint)
GETTER_SETTER(surfaceBright, surfaceBright, setSurfaceBright)
GETTER_SETTER(surfaceDim, surfaceDim, setSurfaceDim)
GETTER_SETTER(shadow, shadow, setShadow)
GETTER_SETTER(scrim, scrim, setScrim)
GETTER_SETTER(outline, outline, setOutline)
GETTER_SETTER(outlineVariant, outlineVariant, setOutlineVariant)

#undef GETTER_SETTER

} // namespace material

// Q_DECLARE_TYPEINFO(material::ColorScheme, Q_MOVABLE_TYPE);

#endif // MATERIAL_COLORSCHEME_H

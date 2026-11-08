#ifndef MATERIAL_THEME_H
#define MATERIAL_THEME_H

#include "colorscheme.h"
#include "typography.h"
#include <QtQml/qqml.h>
#include <QtQuickControls2/qquickattachedpropertypropagator.h>
#include <memory>
#include <qtmetamacros.h>

namespace material {
class Theme : public QQuickAttachedPropertyPropagator {
  Q_OBJECT
  Q_PROPERTY(
      material::ColorScheme colorScheme READ colorScheme WRITE setColorScheme
          RESET resetColorScheme NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(material::Typography typography READ typography WRITE setTypography
                 RESET resetTypography NOTIFY typographyChanged FINAL)
  Q_PROPERTY(material::Typography emphasizedTypography READ emphasizedTypography
                 WRITE setEmphasizedTypography RESET resetEmphasizedTypography
                     NOTIFY emphasizedTypographyChanged FINAL)
  Q_PROPERTY(
      QColor backgroundColor READ backgroundColor WRITE setBackgroundColor RESET
          resetBackgroundColor NOTIFY backgroundColorChanged FINAL)
  Q_PROPERTY(QColor contentColor READ contentColor WRITE setContentColor RESET
                 resetContentColor NOTIFY contentColorChanged FINAL)
  // Q_PROPERTY(QFont font READ font WRITE setFont RESET resetFont NOTIFY
  //                fontChanged FINAL)
  Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize RESET resetIconSize
                 NOTIFY iconSizeChanged FINAL)

  Q_PROPERTY(
      material::Theme::ThemeMode themeMode READ themeMode WRITE setThemeMode
          RESET resetThemeMode NOTIFY themeModeChanged FINAL)
  QML_NAMED_ELEMENT(Theme)
  QML_ATTACHED(Theme)
  QML_UNCREATABLE("")
public:
  explicit Theme(QObject *parent = nullptr);

  enum ThemeMode {
    Light,
    Dark,
    System,
  };
  Q_ENUM(ThemeMode)

  static Theme *qmlAttachedProperties(QObject *object);

  QColor backgroundColor() const;
  void setBackgroundColor(const QColor &);
  void inheritBackgroundColor(QRgb);
  void propagateBackgroundColor();
  void resetBackgroundColor();

  QColor contentColor() const;
  void setContentColor(const QColor &);
  void inheritContentColor(QRgb);
  void propagateContentColor();
  void resetContentColor();

  material::ColorScheme colorScheme() const;
  void setColorScheme(const material::ColorScheme &);
  void inheritColorScheme(const material::ColorScheme &);
  void propagateColorScheme();
  void resetColorScheme();

  material::Typography typography() const;
  void setTypography(const material::Typography &);
  void inheritTypography(const material::Typography &);
  void propagateTypography();
  void resetTypography();

  material::Typography emphasizedTypography() const;
  void setEmphasizedTypography(const material::Typography &);
  void inheritEmphasizedTypography(const material::Typography &);
  void propagateEmphasizedTypography();
  void resetEmphasizedTypography();

  // QFont font() const;
  // void setFont(const QFont &);
  // void inheritFont(const QFont &);
  // void propagateFont();
  // void resetFont();

  QSize iconSize() const;
  void setIconSize(const QSize &);
  void inheritIconSize(const QSize &);
  void propagateIconSize();
  void resetIconSize();

  material::Theme::ThemeMode themeMode() const;
  void setThemeMode(material::Theme::ThemeMode);
  void inheritThemeMode(material::Theme::ThemeMode);
  void propagateThemeMode();
  void resetThemeMode();

signals:
  void colorSchemeChanged();
  void typographyChanged();
  void backgroundColorChanged();
  void contentColorChanged();
  void themeModeChanged();
  void emphasizedTypographyChanged();
  void iconSizeChanged();
  // void fontChanged();

protected:
  void
  attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                       QQuickAttachedPropertyPropagator *oldParent) override;

private:
  struct ThemeData {
    material::ColorScheme colorScheme;
    material::Typography typography;
    material::Typography emphasizedTypography;
  };

  enum Flags {
    SystemDarkTheme = 1 << 0,
    ThemeModeOverride = 1 << 1,
    ColorSchemeOverride = 1 << 2,
    TypographyOverride = 1 << 3,
    EmphasizedTypographyOverride = 1 << 4,
    BackgroundColorOverride = 1 << 5,
    ContentColorOverride = 1 << 6,
    IconSizeOverride = 1 << 7,
    // FontOverride = 1 << 8,
  };

  void updateBackgroundAndContentColor();
  void inheritThemeData(const material::Theme::ThemeData &);

  std::shared_ptr<material::Theme::ThemeData> themeDataCopy() const;
  inline void setFlag(int flag) { m_flags |= flag; }
  inline void removeFlag(int flag) { m_flags &= ~flag; }
  inline bool hasFlag(int flag) const { return m_flags & flag; }

  inline bool isSystemDarkTheme() const {
    return hasFlag(material::Theme::Flags::SystemDarkTheme);
  }
  inline bool explicitThemeMode() const {
    return hasFlag(material::Theme::Flags::ThemeModeOverride);
  }
  inline bool explicitColorScheme() const {
    return hasFlag(material::Theme::Flags::ColorSchemeOverride);
  }
  inline bool explicitTypography() const {
    return hasFlag(material::Theme::Flags::TypographyOverride);
  }
  inline bool explicitBackgroundColor() const {
    return hasFlag(material::Theme::Flags::BackgroundColorOverride);
  }
  inline bool explicitContentColor() const {
    return hasFlag(material::Theme::Flags::ContentColorOverride);
  }
  inline bool explicitIconSize() const {
    return hasFlag(material::Theme::Flags::IconSizeOverride);
  }

  // inline bool explicitFont() const {
  //   return hasFlag(material::Theme::Flags::FontOverride);
  // }

  ThemeData m_themeData;
  ThemeMode m_themeMode = ThemeMode::System;
  QRgb m_backgroundColor;
  QRgb m_contentColor;
  // QFont m_font;
  QSize m_iconSize = QSize(20, 20);
  int m_flags = 0;
};

} // namespace material

#endif // MATERIAL_THEME_H

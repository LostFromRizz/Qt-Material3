#include "theme.h"
#include "colorscheme.h"
#include <QtGui/qguiapplication.h>
#include <QtGui/qpalette.h>
#include <QtGui/qstylehints.h>
#include <QtQuick/qquickitem.h>
#include <qobject.h>

using namespace material;

bool _isSystemDarkTheme() {
  if (const QStyleHints *style = QGuiApplication::styleHints()) {
    if (style->colorScheme() != Qt::ColorScheme::Unknown)
      return style->colorScheme() == Qt::ColorScheme::Dark;
  }

  const QPalette palette = QGuiApplication::palette();

  return palette.windowText().color().lightnessF() >
         palette.window().color().lightnessF();
}

Theme::Theme(QObject *parent) : QQuickAttachedPropertyPropagator(parent) {
  bool isSystemDarkTheme = _isSystemDarkTheme();
  m_themeData = Theme::ThemeData{
      .colorScheme = ColorScheme(isSystemDarkTheme),
      .typography = Typography(false),
      .emphasizedTypography = Typography(true),
  };

  m_backgroundColor = m_themeData.colorScheme.surface().rgba();
  m_contentColor = m_themeData.colorScheme.onSurface().rgba();
  m_iconSize = QSize(20, 20);
  if (isSystemDarkTheme) {
    setFlag(SystemDarkTheme);
  }

  QQuickAttachedPropertyPropagator::initialize();
}

Theme *Theme::qmlAttachedProperties(QObject *object) {
  return new Theme(object);
}

Theme::ThemeMode Theme::themeMode() const { return m_themeMode; }
void Theme::setThemeMode(Theme::ThemeMode themeMode) {
  setFlag(ThemeModeOverride);

  bool systemDarkTheme = _isSystemDarkTheme();

  m_themeMode = themeMode;

  if (((themeMode == Light && !systemDarkTheme) ||
       (themeMode == Dark && systemDarkTheme)) &&
      this->isSystemDarkTheme() == systemDarkTheme) {
    return;
  }

  if (systemDarkTheme) {
    setFlag(SystemDarkTheme);
  } else {
    removeFlag(SystemDarkTheme);
  }

  propagateThemeMode();
  themeModeChanged();

  if (!explicitColorScheme()) {
    ColorScheme newColorScheme = ColorScheme(
        themeMode == System ? systemDarkTheme : m_themeMode == Dark);

    m_themeData.colorScheme.swap(newColorScheme);
    propagateColorScheme();
    colorSchemeChanged();
  }

  updateBackgroundAndContentColor();
}

void Theme::updateBackgroundAndContentColor() {
  if (!explicitBackgroundColor()) {
    m_backgroundColor = m_themeData.colorScheme.surface().rgba();
    propagateBackgroundColor();
    backgroundColorChanged();
  }
  if (!explicitContentColor()) {
    m_contentColor = m_themeData.colorScheme.onSurface().rgba();
    propagateContentColor();
    contentColorChanged();
  }
}
void Theme::inheritThemeMode(Theme::ThemeMode themeMode) {

  bool systemDarkTheme = isSystemDarkTheme();
  if (explicitThemeMode() || isSystemDarkTheme() == systemDarkTheme) {
    return;
  }

  m_themeMode = themeMode;
  propagateThemeMode();
  themeModeChanged();
}

void Theme::propagateThemeMode() {
  const auto children = attachedChildren();

  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritThemeMode(m_themeMode);
    }
  }
}

void Theme::resetThemeMode() {
  if (!explicitThemeMode())
    return;
  removeFlag(ThemeModeOverride);
  Theme *theme = qobject_cast<Theme *>(attachedParent());
  inheritThemeMode(theme ? theme->themeMode() : System);
}

// std::shared_ptr<Theme::ThemeData> Theme::themeDataCopy() const {
//   return std::make_shared<Theme::ThemeData>(Theme::ThemeData{
//       .colorScheme = m_themeData.colorScheme,
//       .typography = m_themeData->typography,
//       .emphasizedTypography = m_themeData->emphasizedTypography,
//   });
// }

ColorScheme Theme::colorScheme() const { return m_themeData.colorScheme; }

void Theme::setColorScheme(const ColorScheme &colorScheme) {
  setFlag(ColorSchemeOverride);

  if (colorScheme == m_themeData.colorScheme) {
    return;
  }

  m_themeData.colorScheme = colorScheme;

  propagateColorScheme();
  updateBackgroundAndContentColor();
  colorSchemeChanged();
}

void Theme::inheritColorScheme(const ColorScheme &colorScheme) {
  if (explicitColorScheme())
    return;

  m_themeData.colorScheme.swap(colorScheme);
  propagateColorScheme();
  updateBackgroundAndContentColor();
  colorSchemeChanged();
}

void Theme::propagateColorScheme() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritColorScheme(m_themeData.colorScheme);
    }
  }
}

void Theme::resetColorScheme() {
  if (!explicitColorScheme())
    return;

  removeFlag(ColorSchemeOverride);

  Theme *theme = qobject_cast<Theme *>(attachedParent());
  ColorScheme colorScheme;
  if (theme) {
    colorScheme = theme->colorScheme();
  } else {
    colorScheme = ColorScheme(m_themeMode == System ? isSystemDarkTheme()
                                                    : m_themeMode == Dark);
  }

  inheritColorScheme(colorScheme);
}

Typography Theme::typography() const { return m_themeData.typography; }

void Theme::setTypography(const Typography &typography) {
  setFlag(TypographyOverride);

  if (typography == m_themeData.typography)
    return;

  m_themeData.typography = typography;
  propagateTypography();
  typographyChanged();
}

void Theme::inheritTypography(const Typography &typography) {
  if (explicitTypography())
    return;

  m_themeData.typography.swap(typography);
  propagateTypography();
  typographyChanged();
}

void Theme::propagateTypography() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritTypography(m_themeData.typography);
    }
  }
}

void Theme::resetTypography() {
  if (!explicitTypography())
    return;

  removeFlag(TypographyOverride);

  Theme *theme = qobject_cast<Theme *>(attachedParent());
  Typography typography;
  if (theme) {
    typography = theme->typography();
  } else {
    typography = Typography(false);
  }

  inheritTypography(typography);
}

Typography Theme::emphasizedTypography() const {
  return m_themeData.emphasizedTypography;
}

void Theme::setEmphasizedTypography(const Typography &typography) {
  setFlag(EmphasizedTypographyOverride);

  if (typography == m_themeData.emphasizedTypography)
    return;

  m_themeData.emphasizedTypography = typography;
  propagateEmphasizedTypography();
  emphasizedTypographyChanged();
}

void Theme::inheritEmphasizedTypography(const Typography &typography) {
  if (explicitTypography())
    return;

  m_themeData.emphasizedTypography.swap(typography);
  propagateEmphasizedTypography();
  emphasizedTypographyChanged();
}

void Theme::propagateEmphasizedTypography() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritEmphasizedTypography(m_themeData.emphasizedTypography);
    }
  }
}

void Theme::resetEmphasizedTypography() {
  if (!explicitTypography())
    return;

  removeFlag(EmphasizedTypographyOverride);

  Theme *theme = qobject_cast<Theme *>(attachedParent());
  Typography typography;
  if (theme) {
    typography = m_themeData.emphasizedTypography;
  } else {
    typography = Typography(true);
  }

  inheritEmphasizedTypography(typography);
}

QColor Theme::backgroundColor() const {
  return QColor::fromRgba(m_backgroundColor);
}

void Theme::setBackgroundColor(const QColor &color) {
  setFlag(BackgroundColorOverride);

  if (color == m_backgroundColor)
    return;

  m_backgroundColor = color.rgba();
  propagateBackgroundColor();
  backgroundColorChanged();
}

void Theme::inheritBackgroundColor(QRgb color) {
  if (hasFlag(BackgroundColorOverride))
    return;

  m_backgroundColor = color;
  propagateBackgroundColor();
  backgroundColorChanged();
}

void Theme::propagateBackgroundColor() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritBackgroundColor(m_backgroundColor);
    }
  }
}

void Theme::resetBackgroundColor() {
  if (!hasFlag(BackgroundColorOverride))
    return;

  removeFlag(BackgroundColorOverride);
  Theme *theme = qobject_cast<Theme *>(attachedParent());
  inheritBackgroundColor(
      (theme ? theme->backgroundColor() : m_themeData.colorScheme.surface())
          .rgba());
}

QColor Theme::contentColor() const { return QColor::fromRgba(m_contentColor); }

void Theme::setContentColor(const QColor &color) {
  setFlag(ContentColorOverride);

  if (color == m_contentColor)
    return;

  m_contentColor = color.rgba();
  propagateContentColor();
  contentColorChanged();
}

void Theme::inheritContentColor(QRgb color) {
  if (hasFlag(ContentColorOverride))
    return;
  m_contentColor = color;
  propagateContentColor();
  contentColorChanged();
}

void Theme::propagateContentColor() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritContentColor(m_contentColor);
    }
  }
}

void Theme::resetContentColor() {
  if (!hasFlag(ContentColorOverride))
    return;
  removeFlag(ContentColorOverride);
  Theme *theme = qobject_cast<Theme *>(attachedParent());
  inheritContentColor(
      (theme ? theme->contentColor() : m_themeData.colorScheme.onSurface())
          .rgba());
}

QSize Theme::iconSize() const { return m_iconSize; }
void Theme::setIconSize(const QSize &iconSize) {
  setFlag(IconSizeOverride);

  if (iconSize == m_iconSize)
    return;

  m_iconSize = iconSize;
  propagateIconSize();
  iconSizeChanged();
}

void Theme::inheritIconSize(const QSize &iconSize) {
  if (explicitIconSize())
    return;
  m_iconSize = iconSize;
  propagateIconSize();
  iconSizeChanged();
}

void Theme::propagateIconSize() {
  const auto children = attachedChildren();
  for (QQuickAttachedPropertyPropagator *child : children) {
    Theme *theme = qobject_cast<Theme *>(child);
    if (theme) {
      theme->inheritIconSize(m_iconSize);
    }
  }
}
void Theme::resetIconSize() {
  if (!explicitIconSize())
    return;
  removeFlag(IconSizeOverride);
  Theme *theme = qobject_cast<Theme *>(attachedParent());
  if (theme) {
    inheritIconSize(theme->m_iconSize);
  }

  inheritIconSize(QSize(20, 20));
}

// QFont Theme::font() const { return m_font; }
// void Theme::setFont(const QFont &font) {
//   setFlag(FontOverride);
//
//   if (font == m_font)
//     return;
//
//   m_font = font;
//   propagateFont();
//   fontChanged();
// }
//
// void Theme::inheritFont(const QFont &font) {
//   if (hasFlag(FontOverride))
//     return;
//   m_font = font;
//   propagateFont();
//   fontChanged();
// }
//
// void Theme::propagateFont() {
//   const auto children = attachedChildren();
//   for (QQuickAttachedPropertyPropagator *child : children) {
//     Theme *theme = qobject_cast<Theme *>(child);
//     if (theme) {
//       theme->inheritFont(m_font);
//     }
//   }
// }
// void Theme::resetFont() {
//   if (!hasFlag(FontOverride))
//     return;
//   removeFlag(FontOverride);
//   Theme *theme = qobject_cast<Theme *>(attachedParent());
//   inheritFont(theme->m_font);
// }

void Theme::attachedParentChange(QQuickAttachedPropertyPropagator *newParent,
                                 QQuickAttachedPropertyPropagator *oldParent) {
  Q_UNUSED(oldParent);
  Theme *theme = qobject_cast<Theme *>(newParent);

  if (theme) {
    inheritThemeData(theme->m_themeData);
    inheritBackgroundColor(theme->m_backgroundColor);
    inheritContentColor(theme->m_contentColor);
  }
}

void Theme::inheritThemeData(const ThemeData &themeData) {
  inheritColorScheme(themeData.colorScheme);
  inheritTypography(themeData.typography);
  inheritEmphasizedTypography(themeData.emphasizedTypography);
}

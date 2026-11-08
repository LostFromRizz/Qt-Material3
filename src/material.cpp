#include "material.h"
#include "colorscheme.h"
#include "typography.h"
#include <QtGui/qfontdatabase.h>
#include <initializer_list>
#include <internals/elevation.h>
#include <qlatin1stringview.h>
#include <qnamespace.h>
#include <utility>

static const float DISABLED_ALPHA = 0.1;
static const float DISABLE_CONTENT_ALPHA = 0.38;

using namespace material;

template <typename T, typename R>
R selectBySize(T value, std::initializer_list<std::pair<T, R>> thresholds,
               R defaultValue) noexcept {
  for (const auto &[limit, result] : thresholds) {
    if (value <= limit) {
      return result;
    }
  }
  return defaultValue;
}

template <typename T>
T Material::valueForButtonHeight(qreal height, T extraSmallValue, T smallValue,
                                 T mediumValue, T largeValue,
                                 T extraLargeValue) const {
  const qreal xs = buttonHeightExtraSmall();
  const qreal s = buttonHeightSmall();
  const qreal m = buttonHeightMedium();
  const qreal l = buttonHeightLarge();
  const qreal xl = buttonHeightExtraLarge();

  if (height <= (xs + s) / 2)
    return extraSmallValue;
  if (height <= (s + m) / 2)
    return smallValue;
  if (height <= (m + l) / 2)
    return mediumValue;
  if (height <= (l + xl) / 2)
    return largeValue;
  return extraLargeValue;
}

// template <typename T, typename R>
// R valueForButtonHeight(T buttonHeight) noexcept {
//   const T xSmallHeight =
//   const T smallHeight = ButtonDefaults::MinHeight;
//   const T mediumHeight = ButtonDefaults::MediumContainerHeight;
//   const T largeHeight = ButtonDefaults::LargeContainerHeight;
//   const T xLargeHeight = ButtonDefaults::ExtraLargeContainerHeight;
//
//   return selectBySize<T, R>(
//       buttonHeight,
//       {
//           {(xSmallHeight + smallHeight) / 2,
//            trailingButtonShapesInternal(ExtraSmallInnerCornerSize,
//                                         ExtraSmallInnerCornerSizePressed)},
//           {(smallHeight + mediumHeight) / 2,
//            trailingButtonShapesInternal(SmallInnerCornerSize,
//                                         SmallInnerCornerSizePressed)},
//           {(mediumHeight + largeHeight) / 2,
//            trailingButtonShapesInternal(MediumInnerCornerSize,
//                                         MediumInnerCornerSizePressed)},
//           {(largeHeight + xLargeHeight) / 2,
//            trailingButtonShapesInternal(LargeInnerCornerSize,
//                                         LargeInnerCornerSizePressed)},
//       },
//       trailingButtonShapesInternal(ExtraLargeInnerCornerSize,
//                                    ExtraLargeInnerCornerSizePressed));
// }

Material::Material(QObject *parent) : QObject(parent) {
  auto m_fontFamily = QLatin1String("Roboto");
  if (!QFontDatabase::hasFamily(m_fontFamily)) {
    m_fontFamily = QLatin1String("Noto"); // fallback
    if (!QFontDatabase::hasFamily(m_fontFamily))
      m_fontFamily = QLatin1String("");
  }
}

ColorScheme Material::colorScheme(bool dark) { return ColorScheme(dark); }

ColorScheme Material::colorScheme(const QJSValue &value) {
  return ColorScheme(value);
}

qreal Material::buttonHeightExtraSmall() const noexcept { return 32.0; }
qreal Material::buttonHeightSmall() const noexcept { return 40.0; }
qreal Material::buttonHeightMedium() const noexcept { return 56.0; }
qreal Material::buttonHeightLarge() const noexcept { return 96.0; }
qreal Material::buttonHeightExtraLarge() const noexcept { return 136.0; }

qreal Material::buttonInnerRadiusExtraSmall() const noexcept { return 4.0; }
qreal Material::buttonInnerRadiusSmall() const noexcept { return 4.0; }
qreal Material::buttonInnerRadiusMedium() const noexcept { return 4.0; }
qreal Material::buttonInnerRadiusLarge() const noexcept { return 8.0; }
qreal Material::buttonInnerRadiusExtraLarge() const noexcept { return 12.0; }

qreal Material::buttonGroupSpacingExtraSmall() const noexcept { return 18.0; }
qreal Material::buttonGroupSpacingSmall() const noexcept { return 12.0; }
qreal Material::buttonGroupSpacingMedium() const noexcept { return 8.0; }
qreal Material::buttonGroupSpacingLarge() const noexcept { return 8.0; }
qreal Material::buttonGroupSpacingExtraLarge() const noexcept { return 8.0; }

qreal Material::iconButtonHeightExtraSmall() const noexcept { return 32.0; }
qreal Material::iconButtonHeightSmall() const noexcept { return 40.0; }
qreal Material::iconButtonHeightMedium() const noexcept { return 56.0; }
qreal Material::iconButtonHeightLarge() const noexcept { return 96.0; }
qreal Material::iconButtonHeightExtraLarge() const noexcept { return 136.0; }

qreal Material::fabHeightSmall() const noexcept { return 56.0; }
qreal Material::fabHeightMedium() const noexcept { return 80.0; }
qreal Material::fabHeightLarge() const noexcept { return 96.0; }

qreal Material::sliderHeightExtraSmall() const noexcept { return 16.0; }
qreal Material::sliderHeightSmall() const noexcept { return 24.0; }
qreal Material::sliderHeightMedium() const noexcept { return 40.0; }
qreal Material::sliderHeightLarge() const noexcept { return 56.0; }
qreal Material::sliderHeightExtraLarge() const noexcept { return 96.0; }

qreal Material::appBarHeightSmall() const noexcept { return 64.0; }
qreal Material::appBarHeightMedium() const noexcept { return 112.0; }
qreal Material::appBarHeightLarge() const noexcept { return 128.0; }

int Material::appBarIconSize() const noexcept { return 24; }

qreal Material::textFieldMinimumHeight() const noexcept { return 56.0; }
qreal Material::textFieldMinimumWidth() const noexcept { return 280.0; }

int Material::textFieldIconSize() const noexcept { return 24; }

int Material::listIconSize() const noexcept { return 20; }
qreal Material::listAvatarSize() const noexcept { return 40.0; }
qreal Material::listImageSize() const noexcept { return 56.0; }
qreal Material::listVideoSize() const noexcept { return 100.0; }

qreal Material::plainTooltipWidth() const noexcept { return 200.0; }
qreal Material::richTooltipWidth() const noexcept { return 320.0; }

qreal Material::buttonVerticalPadding(qreal height) const noexcept {
  return selectBySize(height,
                      {{buttonHeightExtraSmall(), 6.0},
                       {buttonHeightSmall(), 8.0},
                       {buttonHeightMedium(), 16.0},
                       {buttonHeightLarge(), 32.0}},
                      48.0);
}

qreal Material::buttonHorizontalPadding(qreal height) const noexcept {
  return selectBySize(height,
                      {{buttonHeightExtraSmall(), 12.0},
                       {buttonHeightSmall(), 16.0},
                       {buttonHeightMedium(), 24.0},
                       {buttonHeightLarge(), 48.0}},
                      64.0);
}
int Material::buttonIconSize(qreal height) const noexcept {
  return selectBySize(height,
                      {{buttonHeightSmall(), 20},
                       {buttonHeightMedium(), 24},
                       {buttonHeightLarge(), 32}},
                      40);
}
qreal Material::buttonSpacing(qreal height) const noexcept {
  return selectBySize(
      height, {{buttonHeightMedium(), 8.0}, {buttonHeightLarge(), 12.0}}, 16.0);
}

qreal Material::splitButtonInnerRadius(qreal height) const noexcept {
  return valueForButtonHeight(
      height, buttonInnerRadiusExtraSmall(), buttonInnerRadiusMedium(),
      buttonInnerRadiusSmall(), buttonInnerRadiusLarge(),
      buttonInnerRadiusExtraLarge()

  );
}

qreal Material::buttonSelectedRadius(qreal height) const noexcept {
  return selectBySize(height,
                      {
                          {buttonHeightSmall(), 12.0},
                          {buttonHeightMedium(), 16.0},
                      },
                      28.0);
}

qreal Material::buttonInnerRadius(qreal height) const noexcept {
  return selectBySize(height,
                      {

                          {buttonHeightExtraSmall(), 4.0},
                          {buttonHeightMedium(), 8.0},
                          {buttonHeightLarge(), 16.0},
                      },
                      20.0);
}

QFont Material::buttonFont(const Typography &typography,
                           qreal height) noexcept {
  return selectBySize(height,
                      {
                          {buttonHeightSmall(), typography.labelLarge()},
                          {buttonHeightMedium(), typography.titleMedium()},
                          {buttonHeightLarge(), typography.headlineSmall()},
                      },
                      typography.headlineLarge());
}

int Material::iconButtonIconSize(qreal height) noexcept {
  return selectBySize(height,
                      {{buttonHeightExtraSmall(), 20},
                       {buttonHeightMedium(), 24},
                       {buttonHeightLarge(), 32}},
                      40);
}
qreal Material::iconButtonNarrowPadding(qreal height) noexcept {
  return selectBySize(height,
                      {{buttonHeightSmall(), 4.0},
                       {buttonHeightMedium(), 12.0},
                       {buttonHeightLarge(), 16.0}},
                      32.0);
}
qreal Material::iconButtonUniformPadding(qreal height) noexcept {
  return selectBySize(height,
                      {{buttonHeightExtraSmall(), 6.0},
                       {buttonHeightSmall(), 8.0},
                       {buttonHeightMedium(), 16.0},
                       {buttonHeightLarge(), 32.0}},
                      48.0);
}
qreal Material::iconButtonWidePadding(qreal height) noexcept {
  return selectBySize(height,
                      {{buttonHeightExtraSmall(), 10.0},
                       {buttonHeightSmall(), 14.0},
                       {buttonHeightMedium(), 24.0},
                       {buttonHeightLarge(), 48.0}},
                      72.0);
}

qreal Material::iconButtonSelectedRadius(qreal height) noexcept {
  return selectBySize(
      height, {{buttonHeightSmall(), 12.0}, {buttonHeightMedium(), 16.0}},
      28.0);
}

int Material::fabIconSize(qreal height) noexcept {
  return selectBySize(height, {{fabHeightMedium(), 24}, {fabHeightLarge(), 28}},
                      36);
}

qreal Material::fabRadius(qreal height) noexcept {
  return selectBySize(
      height, {{fabHeightMedium(), 16.0}, {fabHeightLarge(), 20.0}}, 28.0);
}

qreal Material::fabSpacing(qreal height) noexcept {
  return selectBySize(
      height, {{fabHeightMedium(), 8.0}, {fabHeightLarge(), 12.0}}, 16.0);
}

qreal Material::fabHorizontalPadding(qreal height) noexcept {
  return selectBySize(
      height, {{fabHeightSmall(), 16.0}, {fabHeightMedium(), 26.0}}, 28.0);
}

QFont Material::fabFont(const Typography &typography, qreal height) noexcept {
  return selectBySize(height,
                      {{fabHeightMedium(), typography.titleMedium()},
                       {fabHeightLarge(), typography.titleLarge()}},
                      typography.headlineSmall());
}

int Material::sliderIconSize(qreal height) noexcept {
  return selectBySize(
      height, {{sliderHeightSmall(), 0}, {sliderHeightLarge(), 24}}, 32);
}

qreal Material::sliderIconMargin(qreal height) noexcept {
  return selectBySize(
      height, {{sliderHeightSmall(), 0.0}, {sliderHeightLarge(), 6.0}}, 8.0);
}

qreal Material::sliderCornerRadius(qreal height) noexcept {
  return selectBySize(height,
                      {
                          {sliderHeightSmall(), 8.0},
                          {sliderHeightMedium(), 12.0},
                          {sliderHeightLarge(), 16.0},
                      },
                      28.0);
}

QSize Material::sliderHandleSize(qreal height) noexcept {
  return QSize(4, selectBySize(height,
                               {
                                   {sliderHeightSmall(), 44.0},
                                   {sliderHeightMedium(), 52.0},
                                   {sliderHeightLarge(), 68.0},
                               },
                               108.0));
}

QFont Material::appBarFont(const Typography &typography,
                           qreal height) noexcept {
  return selectBySize(height,
                      {
                          {appBarHeightMedium(), typography.titleLarge()},
                          {sliderHeightLarge(), typography.headlineSmall()},
                      },
                      typography.headlineMedium());
}

QFont Material::appBarSubtitleFont(const Typography &typography,
                                   qreal height) noexcept {
  return selectBySize(height,
                      {
                          {appBarHeightMedium(), typography.labelMedium()},
                          {sliderHeightLarge(), typography.labelLarge()},
                      },
                      typography.titleMedium());
}

QFont Material::textFieldLabelFont(const Typography &typography,
                                   bool hasFocus) noexcept {
  if (hasFocus) {
    return typography.bodySmall();
  }
  return typography.bodyLarge();
}

inline QColor withAlphaF(const QColor &color, float alpha) {
  return QColor::fromRgbF(color.redF(), color.greenF(), color.blueF(), alpha);
}

QColor Material::disabledBackgroundColor(const QColor &color) {
  return withAlphaF(color, DISABLED_ALPHA);
}
QColor Material::disabledContentColor(const QColor &color) {
  return withAlphaF(color, DISABLE_CONTENT_ALPHA);
}

QColor Material::contentColorFor(const QColor &backgroundColor,
                                 const ColorScheme &colorScheme) noexcept {

  if (backgroundColor == colorScheme.primary()) {
    return colorScheme.onPrimary();
  } else if (backgroundColor == colorScheme.secondary()) {
    return colorScheme.onSecondary();
  } else if (backgroundColor == colorScheme.tertiary()) {
    return colorScheme.onTertiary();
  } else if (backgroundColor == colorScheme.error()) {
    return colorScheme.onError();
  } else if (backgroundColor == colorScheme.primaryContainer()) {
    return colorScheme.onPrimaryContainer();
  } else if (backgroundColor == colorScheme.secondaryContainer()) {
    return colorScheme.onSecondaryContainer();
  } else if (backgroundColor == colorScheme.tertiaryContainer()) {
    return colorScheme.onTertiaryContainer();
  } else if (backgroundColor == colorScheme.errorContainer()) {
    return colorScheme.onErrorContainer();
  } else if (backgroundColor == colorScheme.inverseSurface()) {
    return colorScheme.inverseOnSurface();
  } else if (backgroundColor == colorScheme.surface()) {
    return colorScheme.onSurface();
  } else if (backgroundColor == colorScheme.surfaceVariant()) {
    return colorScheme.onSurfaceVariant();
  } else if (backgroundColor == colorScheme.surfaceBright() ||
             backgroundColor == colorScheme.surfaceContainer() ||
             backgroundColor == colorScheme.surfaceContainerHigh() ||
             backgroundColor == colorScheme.surfaceContainerHighest() ||
             backgroundColor == colorScheme.surfaceContainerLow() ||
             backgroundColor == colorScheme.surfaceContainerLowest() ||
             backgroundColor == colorScheme.surfaceDim()) {
    return colorScheme.onSurface();
  } else {
    return QColor{};
  }
}

QSizeF Material::shadowElevationSize(qreal elevation) {
  QSizeF maxSize(0.0, 0.0);

  if (elevation < 1.0) {
    return maxSize;
  }

  QList<internals::ShadowForElevation> shadows =
      internals::elevationShadowsFor(elevation);

  for (const auto &shadowElevation : shadows) {
    maxSize.setWidth(std::max(maxSize.width(), shadowElevation.blur() +
                                                   shadowElevation.spread()));

    maxSize.setHeight(std::max(maxSize.height(), shadowElevation.blur() +
                                                     shadowElevation.spread() +
                                                     shadowElevation.offset()));
  }

  return maxSize;
}

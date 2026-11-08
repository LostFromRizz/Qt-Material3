#ifndef MATERIAL_MATERIAL_H
#define MATERIAL_MATERIAL_H

#include "colorscheme.h"
#include "typography.h"
#include <QtCore/qobject.h>
#include <QtGui/qfont.h>
#include <QtQml/qqml.h>
#include <QtQml/qqmlparserstatus.h>
#include <qjsvalue.h>
#include <qtmetamacros.h>

namespace material {
class ColorScheme;
class Material : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString fontFamily MEMBER m_fontFamily CONSTANT FINAL)

  // BUTTONS
  Q_PROPERTY(
      qreal buttonHeightExtraSmall READ buttonHeightExtraSmall CONSTANT FINAL)
  Q_PROPERTY(qreal buttonHeightSmall READ buttonHeightSmall CONSTANT FINAL)
  Q_PROPERTY(qreal buttonHeightMedium READ buttonHeightMedium CONSTANT FINAL)
  Q_PROPERTY(qreal buttonHeightLarge READ buttonHeightLarge CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonHeightExtraLarge READ buttonHeightExtraLarge CONSTANT FINAL)

  Q_PROPERTY(qreal buttonInnerRadiusExtraSmall READ buttonInnerRadiusExtraSmall
                 CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonInnerRadiusSmall READ buttonInnerRadiusSmall CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonInnerRadiusMedium READ buttonInnerRadiusMedium CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonInnerRadiusLarge READ buttonInnerRadiusLarge CONSTANT FINAL)
  Q_PROPERTY(qreal buttonInnerRadiusExtraLarge READ buttonInnerRadiusExtraLarge
                 CONSTANT FINAL)

  Q_PROPERTY(qreal buttonGroupSpacingExtraSmall READ
                 buttonGroupSpacingExtraSmall CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonGroupSpacingSmall READ buttonGroupSpacingSmall CONSTANT FINAL)
  Q_PROPERTY(qreal buttonGroupSpacingMedium READ buttonGroupSpacingMedium
                 CONSTANT FINAL)
  Q_PROPERTY(
      qreal buttonGroupSpacingLarge READ buttonGroupSpacingLarge CONSTANT FINAL)
  Q_PROPERTY(qreal buttonGroupSpacingExtraLarge READ
                 buttonGroupSpacingExtraLarge CONSTANT FINAL)

  Q_PROPERTY(qreal iconButtonHeightExtraSmall READ iconButtonHeightExtraSmall
                 CONSTANT FINAL)
  Q_PROPERTY(
      qreal iconButtonHeightSmall READ iconButtonHeightSmall CONSTANT FINAL)
  Q_PROPERTY(
      qreal iconButtonHeightMedium READ iconButtonHeightMedium CONSTANT FINAL)
  Q_PROPERTY(
      qreal iconButtonHeightLarge READ iconButtonHeightLarge CONSTANT FINAL)
  Q_PROPERTY(qreal iconButtonHeightExtraLarge READ iconButtonHeightExtraLarge
                 CONSTANT FINAL)
  Q_PROPERTY(int listIconSize READ listIconSize CONSTANT FINAL)
  Q_PROPERTY(qreal listAvatarSize READ listAvatarSize CONSTANT FINAL)
  Q_PROPERTY(qreal listImageSize READ listImageSize CONSTANT FINAL)
  Q_PROPERTY(qreal listVideoSize READ listVideoSize CONSTANT FINAL)

  Q_PROPERTY(
      qreal sliderHeightExtraSmall READ sliderHeightExtraSmall CONSTANT FINAL)
  Q_PROPERTY(qreal sliderHeightSmall READ sliderHeightSmall CONSTANT FINAL)
  Q_PROPERTY(qreal sliderHeightMedium READ sliderHeightMedium CONSTANT FINAL)
  Q_PROPERTY(qreal sliderHeightLarge READ sliderHeightLarge CONSTANT FINAL)
  Q_PROPERTY(
      qreal sliderHeightExtraLarge READ sliderHeightExtraLarge CONSTANT FINAL)
  Q_PROPERTY(qreal appBarHeightSmall READ appBarHeightSmall CONSTANT FINAL)
  Q_PROPERTY(qreal appBarHeightMedium READ appBarHeightMedium CONSTANT FINAL)
  Q_PROPERTY(qreal appBarHeightLarge READ appBarHeightLarge CONSTANT FINAL)
  Q_PROPERTY(int appBarIconSize READ appBarIconSize CONSTANT FINAL)

  Q_PROPERTY(
      qreal textFieldMinimumHeight READ textFieldMinimumHeight CONSTANT FINAL)
  Q_PROPERTY(
      qreal textFieldMinimumWidth READ textFieldMinimumWidth CONSTANT FINAL)
  Q_PROPERTY(int textFieldIconSize READ textFieldIconSize CONSTANT FINAL)

  Q_PROPERTY(qreal fabHeightSmall READ fabHeightSmall CONSTANT FINAL)
  Q_PROPERTY(qreal fabHeightMedium READ fabHeightMedium CONSTANT FINAL)
  Q_PROPERTY(qreal fabHeightLarge READ fabHeightLarge CONSTANT FINAL)
  Q_PROPERTY(qreal plainTooltipWidth READ plainTooltipWidth CONSTANT FINAL)
  Q_PROPERTY(qreal richTooltipWidth READ richTooltipWidth CONSTANT FINAL)
  QML_ELEMENT
  QML_SINGLETON

public:
  explicit Material(QObject *parent = nullptr);

  Q_INVOKABLE material::ColorScheme colorScheme(bool dark = false);
  Q_INVOKABLE material::ColorScheme colorScheme(const QJSValue &);

  qreal buttonHeightExtraSmall() const noexcept;
  qreal buttonHeightSmall() const noexcept;
  qreal buttonHeightMedium() const noexcept;
  qreal buttonHeightLarge() const noexcept;
  qreal buttonHeightExtraLarge() const noexcept;

  qreal buttonInnerRadiusExtraSmall() const noexcept;
  qreal buttonInnerRadiusMedium() const noexcept;
  qreal buttonInnerRadiusSmall() const noexcept;
  qreal buttonInnerRadiusLarge() const noexcept;
  qreal buttonInnerRadiusExtraLarge() const noexcept;

  qreal buttonGroupSpacingExtraSmall() const noexcept;
  qreal buttonGroupSpacingSmall() const noexcept;
  qreal buttonGroupSpacingMedium() const noexcept;
  qreal buttonGroupSpacingLarge() const noexcept;
  qreal buttonGroupSpacingExtraLarge() const noexcept;

  qreal iconButtonHeightExtraSmall() const noexcept;
  qreal iconButtonHeightSmall() const noexcept;
  qreal iconButtonHeightMedium() const noexcept;
  qreal iconButtonHeightLarge() const noexcept;
  qreal iconButtonHeightExtraLarge() const noexcept;

  qreal sliderHeightExtraSmall() const noexcept;
  qreal sliderHeightSmall() const noexcept;
  qreal sliderHeightMedium() const noexcept;
  qreal sliderHeightLarge() const noexcept;
  qreal sliderHeightExtraLarge() const noexcept;

  qreal appBarHeightSmall() const noexcept;
  qreal appBarHeightMedium() const noexcept;
  qreal appBarHeightLarge() const noexcept;
  int appBarIconSize() const noexcept;

  qreal textFieldMinimumHeight() const noexcept;
  qreal textFieldMinimumWidth() const noexcept;
  int textFieldIconSize() const noexcept;

  qreal fabHeightSmall() const noexcept;
  qreal fabHeightMedium() const noexcept;
  qreal fabHeightLarge() const noexcept;

  int listIconSize() const noexcept;
  qreal listAvatarSize() const noexcept;
  qreal listImageSize() const noexcept;
  qreal listVideoSize() const noexcept;

  qreal plainTooltipWidth() const noexcept;
  qreal richTooltipWidth() const noexcept;

  Q_INVOKABLE qreal buttonVerticalPadding(qreal) const noexcept;
  Q_INVOKABLE qreal buttonHorizontalPadding(qreal) const noexcept;
  Q_INVOKABLE int buttonIconSize(qreal) const noexcept;
  Q_INVOKABLE qreal buttonSpacing(qreal) const noexcept;
  Q_INVOKABLE qreal buttonSelectedRadius(qreal) const noexcept;
  Q_INVOKABLE qreal buttonInnerRadius(qreal) const noexcept;
  Q_INVOKABLE qreal splitButtonInnerRadius(qreal height) const noexcept;
  Q_INVOKABLE QFont buttonFont(const Typography &, qreal) noexcept;
  Q_INVOKABLE int iconButtonIconSize(qreal) noexcept;
  Q_INVOKABLE qreal iconButtonNarrowPadding(qreal) noexcept;
  Q_INVOKABLE qreal iconButtonUniformPadding(qreal) noexcept;
  Q_INVOKABLE qreal iconButtonWidePadding(qreal) noexcept;
  Q_INVOKABLE qreal iconButtonSelectedRadius(qreal) noexcept;

  Q_INVOKABLE int fabIconSize(qreal height) noexcept;
  Q_INVOKABLE qreal fabRadius(qreal) noexcept;
  Q_INVOKABLE qreal fabSpacing(qreal) noexcept;
  Q_INVOKABLE qreal fabHorizontalPadding(qreal) noexcept;
  Q_INVOKABLE QFont fabFont(const Typography &, qreal) noexcept;

  Q_INVOKABLE int sliderIconSize(qreal) noexcept;
  Q_INVOKABLE qreal sliderIconMargin(qreal) noexcept;
  Q_INVOKABLE qreal sliderCornerRadius(qreal) noexcept;
  Q_INVOKABLE QSize sliderHandleSize(qreal) noexcept;

  Q_INVOKABLE QFont appBarFont(const Typography &, qreal) noexcept;
  Q_INVOKABLE QFont appBarSubtitleFont(const Typography &, qreal) noexcept;

  Q_INVOKABLE QFont textFieldLabelFont(const Typography &,
                                       bool hasFocus) noexcept;

  Q_INVOKABLE QColor disabledBackgroundColor(const QColor &);
  Q_INVOKABLE QColor disabledContentColor(const QColor &);
  Q_INVOKABLE QColor contentColorFor(const QColor &backgroundColor,
                                     const ColorScheme &colorScheme) noexcept;
  Q_INVOKABLE QSizeF shadowElevationSize(qreal elevation);

private:
  template <typename T>
  T valueForButtonHeight(qreal height, T extraSmallValue, T smallValue,
                         T mediumValue, T largeValue, T extraLargeValue) const;

  QString m_fontFamily = QLatin1String("");
};
} // namespace material

#endif // MATERIAL_MATERIAL_H

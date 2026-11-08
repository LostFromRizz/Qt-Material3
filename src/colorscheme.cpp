#include "colorscheme.h"
#include <qrgb.h>

using namespace material;

ColorSchemePrivate::ColorSchemePrivate(Colors data)
    : primary(data.primary), onPrimary(data.onPrimary),
      primaryContainer(data.primaryContainer),
      onPrimaryContainer(data.onPrimaryContainer), secondary(data.secondary),
      onSecondary(data.onSecondary),
      secondaryContainer(data.secondaryContainer),
      onSecondaryContainer(data.onSecondaryContainer), tertiary(data.tertiary),
      onTertiary(data.onTertiary), tertiaryContainer(data.tertiaryContainer),
      onTertiaryContainer(data.onTertiaryContainer), error(data.error),
      onError(data.onError), errorContainer(data.errorContainer),
      onErrorContainer(data.onErrorContainer), surface(data.surface),
      onSurface(data.onSurface), surfaceVariant(data.surfaceVariant),
      onSurfaceVariant(data.onSurfaceVariant),
      surfaceContainerHighest(data.surfaceContainerHighest),
      surfaceContainerHigh(data.surfaceContainerHigh),
      surfaceContainer(data.surfaceContainer),
      surfaceContainerLow(data.surfaceContainerLow),
      surfaceContainerLowest(data.surfaceContainerLowest),
      inverseSurface(data.inverseSurface),
      inverseOnSurface(data.inverseOnSurface), surfaceTint(data.surfaceTint),
      surfaceBright(data.surfaceBright), surfaceDim(data.surfaceDim),
      shadow(data.shadow), scrim(data.scrim), outline(data.outline),
      outlineVariant(data.outlineVariant) {}

std::shared_ptr<ColorSchemePrivate> ColorSchemePrivate::baseLineDark() {
  return std::make_shared<ColorSchemePrivate>(ColorSchemePrivate(Colors{
      // Primary
      .primary = 0xFFD0BCFF,
      .onPrimary = 0xFF381E72,
      .primaryContainer = 0xFF4F378B,
      .onPrimaryContainer = 0xFFEADDFF,

      // Secondary
      .secondary = 0xFFCCC2DC,
      .onSecondary = 0xFF332D41,
      .secondaryContainer = 0xFF4A4458,
      .onSecondaryContainer = 0xFFE8DEF8,

      // Tertiary
      .tertiary = 0xFFEFB8C8,
      .onTertiary = 0xFF492532,
      .tertiaryContainer = 0xFF633B48,
      .onTertiaryContainer = 0xFFFFD8E4,

      // Error
      .error = 0xFFF2B8B5,
      .onError = 0xFF601410,
      .errorContainer = 0xFF8C1D18,
      .onErrorContainer = 0xFFF9DEDC,

      // Surface
      .surface = 0xFF141218,
      .onSurface = 0xFFE6E0E9,
      .surfaceVariant = 0xFF49454F,
      .onSurfaceVariant = 0xFFCAC4D0,
      .surfaceContainerHighest = 0xFF36343B,
      .surfaceContainerHigh = 0xFF2B2930,
      .surfaceContainer = 0xFF211F26,
      .surfaceContainerLow = 0xFF1D1B20,
      .surfaceContainerLowest = 0xFF0F0D13,
      .inverseSurface = 0xFFE6E0E9,
      .inverseOnSurface = 0xFF322F35,
      .surfaceTint = 0xFFD0BCFF,
      .surfaceBright = 0xFF3B383E,
      .surfaceDim = 0xFF141218,
      .shadow = 0xFF00000,
      .scrim = 0xFF00000,

      // Outline
      .outline = 0xFF938F99,
      .outlineVariant = 0xFF49454F,

  }));
}

std::shared_ptr<ColorSchemePrivate> ColorSchemePrivate::baseLineLight() {
  return std::make_shared<ColorSchemePrivate>(ColorSchemePrivate(Colors{
      .primary = 0xFF6750A4,
      .onPrimary = 0xFFFFFFFF,
      .primaryContainer = 0xFFEADDFF,
      .onPrimaryContainer = 0xFF4F378B,

      // Secondary
      .secondary = 0xFF625B71,
      .onSecondary = 0xFFFFFFFF,
      .secondaryContainer = 0xFFEADDFF,
      .onSecondaryContainer = 0xFF4A4458,

      // Tertiary
      .tertiary = 0xFF7D5260,
      .onTertiary = 0xFFFFFFFF,
      .tertiaryContainer = 0xFFFFD8E4,
      .onTertiaryContainer = 0xFF633B48,

      // Error
      .error = 0xFFB3261E,
      .onError = 0xFFFFFFFF,
      .errorContainer = 0xFFF9DEDC,
      .onErrorContainer = 0xFF8C1D18,

      // Surface
      .surface = 0xFFFEF7FF,
      .onSurface = 0xFF1D1B20,
      .surfaceVariant = 0xFFE7E0EC,
      .onSurfaceVariant = 0xFF49454F,
      .surfaceContainerHighest = 0xFFE6E0E9,
      .surfaceContainerHigh = 0xFFECE6F0,
      .surfaceContainer = 0xFFF3EDF7,
      .surfaceContainerLow = 0xFFF7F2FA,
      .surfaceContainerLowest = 0xFFFFFFFF,
      .inverseSurface = 0xFF322F35,
      .inverseOnSurface = 0xFFF5EFF7,
      .surfaceTint = 0xFF6750A4,
      .surfaceBright = 0xFFFEF7FF,
      .surfaceDim = 0xFFDED8E1,
      .shadow = 0xFF00000,
      .scrim = 0xFF000000,

      // Outline
      .outline = 0xFF79747E,
      .outlineVariant = 0xFFCAC4D0,

  }));
}

std::shared_ptr<ColorSchemePrivate>
ColorSchemePrivate::fromJSValue(const QJSValue &value) {
  auto getColor = [&value](const QString &name) {
    const auto &property = value.property(name);
    if (property.isString()) {
      const auto &color = QColor(property.toString());
      if (color.isValid()) {
        return color.rgba();
      }
    }
    return 0xFF000000;
  };

  return std::make_shared<ColorSchemePrivate>(ColorSchemePrivate(Colors{
      .primary = getColor("primary"),
      .onPrimary = getColor("onPrimary"),
      .primaryContainer = getColor("primaryContainer"),
      .onPrimaryContainer = getColor("onPrimaryContainer"),

      // Secondary
      .secondary = getColor("secondary"),
      .onSecondary = getColor("onSecondary"),
      .secondaryContainer = getColor("secondaryContainer"),
      .onSecondaryContainer = getColor("onSecondaryContainer"),

      // Tertiary
      .tertiary = getColor("tertiary"),
      .onTertiary = getColor("onTertiary"),
      .tertiaryContainer = getColor("tertiaryContainer"),
      .onTertiaryContainer = getColor("onTertiaryContainer"),

      // Error
      .error = getColor("error"),
      .onError = getColor("onError"),
      .errorContainer = getColor("errorContainer"),
      .onErrorContainer = getColor("onErrorContainer"),

      // Surface
      .surface = getColor("surface"),
      .onSurface = getColor("onSurface"),
      .surfaceVariant = getColor("surfaceVariant"),
      .onSurfaceVariant = getColor("onSurfaceVariant"),
      .surfaceContainerHighest = getColor("surfaceContainerHighest"),
      .surfaceContainerHigh = getColor("surfaceContainerHigh"),
      .surfaceContainer = getColor("surfaceContainer"),
      .surfaceContainerLow = getColor("surfaceContainerLow"),
      .surfaceContainerLowest = getColor("surfaceContainerLowest"),
      .inverseSurface = getColor("inverseSurface"),
      .inverseOnSurface = getColor("inverseOnSurface"),
      .surfaceTint = getColor("surfaceTint"),
      .surfaceBright = getColor("surfaceBright"),
      .surfaceDim = getColor("surfaceDim"),
      .shadow = getColor("shadow"),
      .scrim = getColor("scrim"),

      // Outline
      .outline = getColor("outline"),
      .outlineVariant = getColor("outlineVariant"),

  }));
}

// value.property("").isString()

bool ColorSchemePrivate::operator==(const ColorSchemePrivate &other) const {
  return primary == other.primary && onPrimary == other.onPrimary &&
         primaryContainer == other.primaryContainer &&
         onPrimaryContainer == other.onPrimaryContainer &&
         secondary == other.secondary && onSecondary == other.onSecondary &&
         secondaryContainer == other.secondaryContainer &&
         onSecondaryContainer == other.onSecondaryContainer &&
         tertiary == other.tertiary && onTertiary == other.onTertiary &&
         tertiaryContainer == other.tertiaryContainer &&
         onTertiaryContainer == other.onTertiaryContainer &&
         error == other.error && onError == other.onError &&
         errorContainer == other.errorContainer &&
         onErrorContainer == other.onErrorContainer &&
         surface == other.surface && onSurface == other.onSurface &&
         surfaceVariant == other.surfaceVariant &&
         onSurfaceVariant == other.onSurfaceVariant &&
         surfaceContainerHighest == other.surfaceContainerHighest &&
         surfaceContainerHigh == other.surfaceContainerHigh &&
         surfaceContainer == other.surfaceContainer &&
         surfaceContainerLow == other.surfaceContainerLow &&
         surfaceContainerLowest == other.surfaceContainerLowest &&
         inverseSurface == other.inverseSurface &&
         inverseOnSurface == other.inverseOnSurface &&
         surfaceTint == other.surfaceTint &&
         surfaceBright == other.surfaceBright &&
         surfaceDim == other.surfaceDim && shadow == other.shadow &&
         scrim == other.scrim && outline == other.outline &&
         outlineVariant == other.outlineVariant;
}

bool ColorSchemePrivate::operator!=(const ColorSchemePrivate &other) const {
  return !(*this == other);
}

// static const std::map<QString, QRgb ColorSchemePrivate::*> fieldMap = {
//     {QStringLiteral("primary"), &ColorSchemePrivate::primary},
//     {QStringLiteral("onPrimary"), &ColorSchemePrivate::onPrimary},
//     {QStringLiteral("primaryContainer"),
//     &ColorSchemePrivate::primaryContainer},
//     {QStringLiteral("onPrimaryContainer"),
//      &ColorSchemePrivate::onPrimaryContainer},
//     {QStringLiteral("secondary"), &ColorSchemePrivate::secondary},
//     {QStringLiteral("onSecondary"), &ColorSchemePrivate::onSecondary},
//     {QStringLiteral("secondaryContainer"),
//      &ColorSchemePrivate::secondaryContainer},
//     {QStringLiteral("onSecondaryContainer"),
//      &ColorSchemePrivate::onSecondaryContainer},
//     {QStringLiteral("tertiary"), &ColorSchemePrivate::tertiary},
//     {QStringLiteral("onTertiary"), &ColorSchemePrivate::onTertiary},
//     {QStringLiteral("tertiaryContainer"),
//      &ColorSchemePrivate::tertiaryContainer},
//     {QStringLiteral("onTertiaryContainer"),
//      &ColorSchemePrivate::onTertiaryContainer},
//     {QStringLiteral("error"), &ColorSchemePrivate::error},
//     {QStringLiteral("onError"), &ColorSchemePrivate::onError},
//     {QStringLiteral("errorContainer"), &ColorSchemePrivate::errorContainer},
//     {QStringLiteral("onErrorContainer"),
//     &ColorSchemePrivate::onErrorContainer}, {QStringLiteral("surface"),
//     &ColorSchemePrivate::surface}, {QStringLiteral("onSurface"),
//     &ColorSchemePrivate::onSurface}, {QStringLiteral("surfaceVariant"),
//     &ColorSchemePrivate::surfaceVariant},
//     {QStringLiteral("onSurfaceVariant"),
//     &ColorSchemePrivate::onSurfaceVariant},
//     {QStringLiteral("surfaceContainerHighest"),
//      &ColorSchemePrivate::surfaceContainerHighest},
//     {QStringLiteral("surfaceContainerHigh"),
//      &ColorSchemePrivate::surfaceContainerHigh},
//     {QStringLiteral("surfaceContainer"),
//     &ColorSchemePrivate::surfaceContainer},
//     {QStringLiteral("surfaceContainerLow"),
//      &ColorSchemePrivate::surfaceContainerLow},
//     {QStringLiteral("surfaceContainerLowest"),
//      &ColorSchemePrivate::surfaceContainerLowest},
//     {QStringLiteral("inverseSurface"), &ColorSchemePrivate::inverseSurface},
//     {QStringLiteral("inverseOnSurface"),
//     &ColorSchemePrivate::inverseOnSurface}, {QStringLiteral("surfaceTint"),
//     &ColorSchemePrivate::surfaceTint}, {QStringLiteral("surfaceBright"),
//     &ColorSchemePrivate::surfaceBright}, {QStringLiteral("surfaceDim"),
//     &ColorSchemePrivate::surfaceDim}, {QStringLiteral("shadow"),
//     &ColorSchemePrivate::shadow}, {QStringLiteral("scrim"),
//     &ColorSchemePrivate::scrim}, {QStringLiteral("outline"),
//     &ColorSchemePrivate::outline}, {QStringLiteral("outlineVariant"),
//     &ColorSchemePrivate::outlineVariant},
// };
//
ColorScheme::ColorScheme(bool dark) : d(ColorSchemePrivate::baseLine(dark)) {}

ColorScheme::ColorScheme(std::shared_ptr<ColorSchemePrivate> ptr) : d(ptr) {}

ColorScheme::ColorScheme(const QJSValue &value)
    : d(ColorSchemePrivate::fromJSValue(value)) {}

// ColorScheme ColorScheme::fromJs(const QJSValue &value) {
//   if (!value.isObject())
//     return ColorScheme(false);
//
//   auto ptr = new ColorSchemePrivate();
//
//   for (QJSValueIterator it(value); it.hasNext();) {
//     it.next();
//
//     auto mapIt = fieldMap.find(it.name());
//     if (mapIt == fieldMap.end())
//       continue;
//
//     QRgb rgba = 0x00000000;
//     auto value = it.value();
//
//     if (value.isString()) {
//       QColor color(value.toString());
//       if (color.isValid()) {
//         rgba = color.rgba();
//       }
//     } else if (value.isNumber()) {
//       // todo
//     }
//
//     ptr->*(mapIt->second) = rgba;
//   }
//   return ColorScheme(QExplicitlySharedDataPointer(ptr));
// }

bool ColorScheme::operator==(const ColorScheme &other) const {
  return other.d == this->d;
}

bool ColorScheme::operator!=(const ColorScheme &other) const {
  return !(*this == other);
}

// QString ColorScheme::toString() {
//   auto hex = [](QRgb c) {
//     return QString("#%1").arg(c & 0xFFFFFF, 6, 16, QChar('0')).toUpper();
//   };
//
//   return QString("ColorScheme {\n"
//                  "  primary:                 %1\n"
//                  "  onPrimary:               %2\n"
//                  "  primaryContainer:        %3\n"
//                  "  onPrimaryContainer:      %4\n"
//                  "  secondary:               %5\n"
//                  "  onSecondary:             %6\n"
//                  "  secondaryContainer:      %7\n"
//                  "  onSecondaryContainer:    %8\n"
//                  "  tertiary:                %9\n"
//                  "  onTertiary:              %10\n"
//                  "  tertiaryContainer:       %11\n"
//                  "  onTertiaryContainer:     %12\n"
//                  "  error:                   %13\n"
//                  "  onError:                 %14\n"
//                  "  errorContainer:          %15\n"
//                  "  onErrorContainer:        %16\n"
//                  "  surface:                 %17\n"
//                  "  onSurface:               %18\n"
//                  "  surfaceVariant:          %19\n"
//                  "  onSurfaceVariant:        %20\n"
//                  "  surfaceContainerHighest: %21\n"
//                  "  surfaceContainerHigh:    %22\n"
//                  "  surfaceContainer:        %23\n"
//                  "  surfaceContainerLow:     %24\n"
//                  "  surfaceContainerLowest:  %25\n"
//                  "  inverseSurface:          %26\n"
//                  "  inverseOnSurface:        %27\n"
//                  "  surfaceTint:             %28\n"
//                  "  surfaceBright:           %29\n"
//                  "  surfaceDim:              %30\n"
//                  "  shadow:                  %31\n"
//                  "  scrim:                   %32\n"
//                  "  outline:                 %33\n"
//                  "  outlineVariant:          %34\n"
//                  "}")
//       .arg(hex(d->primary), hex(d->onPrimary), hex(d->primaryContainer),
//            hex(d->onPrimaryContainer), hex(d->secondary),
//            hex(d->onSecondary), hex(d->secondaryContainer),
//            hex(d->onSecondaryContainer), hex(d->tertiary),
//            hex(d->onTertiary))
//       .arg(hex(d->tertiaryContainer), hex(d->onTertiaryContainer),
//            hex(d->error), hex(d->onError), hex(d->errorContainer),
//            hex(d->onErrorContainer), hex(d->surface), hex(d->onSurface),
//            hex(d->surfaceVariant), hex(d->onSurfaceVariant))
//       .arg(hex(d->surfaceContainerHighest), hex(d->surfaceContainerHigh),
//            hex(d->surfaceContainer), hex(d->surfaceContainerLow),
//            hex(d->surfaceContainerLowest), hex(d->inverseSurface),
//            hex(d->inverseOnSurface), hex(d->surfaceTint),
//            hex(d->surfaceBright), hex(d->surfaceDim))
//       .arg(hex(d->shadow), hex(d->scrim), hex(d->outline),
//            hex(d->outlineVariant));
// }

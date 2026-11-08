#include "typography.h"
#include <memory>

using namespace material;

struct TypeScale {
  QFont large, medium, small;
};

class FontBuilder {
public:
  FontBuilder() : m_font(QFont()) {}

  FontBuilder &weight(QFont::Weight weight) {
    m_font.setWeight(weight);
    return *this;
  }
  FontBuilder &pixelSize(int pixelSize) {
    m_font.setPixelSize(pixelSize);
    m_font.setVariableAxis("opsz", static_cast<float>(pixelSize));
    return *this;
  }

  FontBuilder &letterSpacing(qreal spacing) {
    m_font.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    return *this;
  }
  FontBuilder &wdth(float wdth) {
    m_font.setVariableAxis("wdth", wdth);
    return *this;
  }

  QFont build() {
    m_font.setFamilies(QStringList{"Roboto", "Notot"});
    return m_font;
  }

private:
  QFont m_font;
};

static const TypeScale display = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Normal)
                 .pixelSize(57)
                 .letterSpacing(-0.25)
                 .build(),

    .medium = FontBuilder().weight(QFont::Weight::Normal).pixelSize(45).build(),
    .small = FontBuilder().weight(QFont::Weight::Normal).pixelSize(36).build(),

};

static const TypeScale headline = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Normal)
                 .pixelSize(32)
                 .letterSpacing(0)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Normal)
                  .pixelSize(28)
                  .letterSpacing(0)
                  .build(),
    .small = FontBuilder().weight(QFont::Weight::Normal).pixelSize(24).build(),

};

static const TypeScale title = {
    .large = FontBuilder().weight(QFont::Weight::Normal).pixelSize(22).build(),

    .medium = FontBuilder().weight(QFont::Weight::Medium).pixelSize(16).build(),

    .small = FontBuilder().weight(QFont::Weight::Medium).pixelSize(14).build(),
};

static const TypeScale label = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .letterSpacing(0.1)
                 .pixelSize(14)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Medium)
                  .pixelSize(12)
                  .letterSpacing(0.5)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(11)
                 .letterSpacing(0.5)
                 .build(),
};

static const TypeScale body = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Normal)
                 .pixelSize(16)
                 .letterSpacing(0.5)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Normal)
                  .pixelSize(14)
                  .letterSpacing(0.25)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(12)
                 .letterSpacing(0.4)
                 .build(),
};

static const TypeScale displayEmphasized = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(57)
                 .wdth(100.0)
                 .build(),

    .medium = FontBuilder()
                  .weight(QFont::Weight::Medium)
                  .pixelSize(45)
                  .wdth(100.0)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(36)
                 .wdth(100.0)
                 .build(),

};

static const TypeScale headlineEmphasized = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(32)
                 .letterSpacing(0)
                 .wdth(100.0)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Medium)
                  .pixelSize(28)
                  .letterSpacing(0)
                  .wdth(100.0)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(24)
                 .wdth(100.0)
                 .build(),

};

static const TypeScale titleEmphasized = {
    .large = FontBuilder().weight(QFont::Weight::Medium).pixelSize(22).build(),

    .medium = FontBuilder().weight(QFont::Weight::Bold).pixelSize(16).build(),

    .small = FontBuilder().weight(QFont::Weight::Bold).pixelSize(14).build(),
};

static const TypeScale labelEmphasized = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Bold)
                 .letterSpacing(0)
                 .pixelSize(14)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Bold)
                  .pixelSize(12)
                  .letterSpacing(0)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Bold)
                 .pixelSize(11)
                 .letterSpacing(0.5)
                 .build(),
};

static const TypeScale bodyEmphasized = {
    .large = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(16)
                 .letterSpacing(0)
                 .build(),
    .medium = FontBuilder()
                  .weight(QFont::Weight::Medium)
                  .pixelSize(14)
                  .letterSpacing(0)
                  .build(),
    .small = FontBuilder()
                 .weight(QFont::Weight::Medium)
                 .pixelSize(12)
                 .letterSpacing(0)
                 .build(),
};

TypographyPrivate::TypographyPrivate(bool emphasized) {
  if (emphasized) {
    displayLarge = displayEmphasized.large;
    displayMedium = displayEmphasized.medium;
    displaySmall = displayEmphasized.small;

    headlineLarge = headlineEmphasized.large;
    headlineMedium = headlineEmphasized.medium;
    headlineSmall = headlineEmphasized.small;

    titleLarge = titleEmphasized.large;
    titleMedium = titleEmphasized.medium;
    titleSmall = titleEmphasized.small;

    labelLarge = labelEmphasized.large;
    labelMedium = labelEmphasized.medium;
    labelSmall = labelEmphasized.small;

    bodyLarge = bodyEmphasized.large;
    bodyMedium = bodyEmphasized.medium;
    bodySmall = bodyEmphasized.small;

  } else {
    displayLarge = display.large;
    displayMedium = display.medium;
    displaySmall = display.small;

    headlineLarge = headline.large;
    headlineMedium = headline.medium;
    headlineSmall = headline.small;

    titleLarge = title.large;
    titleMedium = title.medium;
    titleSmall = title.small;

    labelLarge = label.large;
    labelMedium = label.medium;
    labelSmall = label.small;

    bodyLarge = body.large;
    bodyMedium = body.medium;
    bodySmall = body.small;
  }
}

bool TypographyPrivate::operator==(const TypographyPrivate &other) const {
  return displayLarge == other.displayLarge &&
         displayMedium == other.displayMedium &&
         displaySmall == other.displaySmall &&
         headlineLarge == other.headlineLarge &&
         headlineMedium == other.headlineMedium &&
         headlineSmall == other.headlineSmall &&
         titleLarge == other.titleLarge && titleMedium == other.titleMedium &&
         titleSmall == other.titleSmall && labelLarge == other.labelLarge &&
         labelMedium == other.labelMedium && labelSmall == other.labelSmall &&
         bodyLarge == other.bodyLarge && bodyMedium == other.bodyMedium &&
         bodySmall == other.bodySmall;
}

bool TypographyPrivate::operator!=(const TypographyPrivate &other) const {
  return !(*this == other);
}

Typography::Typography(bool emphasized)
    : d(std::make_shared<TypographyPrivate>(TypographyPrivate(emphasized))) {}

bool Typography::operator==(const Typography &other) const {
  return this->d == other.d;
}

bool Typography::operator!=(const Typography &other) const {
  return this->d != other.d;
}

#define GETTER_SETTER_IMPL(getter, setter)                                     \
  QFont Typography::getter() const { return d->getter; }                       \
  void Typography::setter(QFont font) {                                        \
    if (d->getter == font) {                                                   \
      return;                                                                  \
    }                                                                          \
    d->getter = font;                                                          \
  }

GETTER_SETTER_IMPL(displayLarge, setDisplayLarge)
GETTER_SETTER_IMPL(displayMedium, setDisplayMedium)
GETTER_SETTER_IMPL(displaySmall, setDisplaySmall)

GETTER_SETTER_IMPL(headlineLarge, setHeadlineLarge)
GETTER_SETTER_IMPL(headlineMedium, setHeadlineMedium)
GETTER_SETTER_IMPL(headlineSmall, setHeadlineSmall)

GETTER_SETTER_IMPL(titleLarge, setTitleLarge)
GETTER_SETTER_IMPL(titleMedium, setTitleMedium)
GETTER_SETTER_IMPL(titleSmall, setTitleSmall)

GETTER_SETTER_IMPL(labelLarge, setLabelLarge)
GETTER_SETTER_IMPL(labelMedium, setLabelMedium)
GETTER_SETTER_IMPL(labelSmall, setLabelSmall)

GETTER_SETTER_IMPL(bodyLarge, setBodyLarge)
GETTER_SETTER_IMPL(bodyMedium, setBodyMedium)
GETTER_SETTER_IMPL(bodySmall, setBodySmall)

#undef GETTER_SETTER_IMPL

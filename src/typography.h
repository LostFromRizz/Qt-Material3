#ifndef MATERIAL_TYPOGRAPHY_H
#define MATERIAL_TYPOGRAPHY_H

#include <QtGui/qfont.h>
#include <QtQml/qqml.h>
#include <memory>
#include <qqmlintegration.h>

namespace material {
struct TypographyPrivate;
struct TypographyPrivate {
  QFont displayLarge;
  QFont displayMedium;
  QFont displaySmall;

  QFont headlineLarge;
  QFont headlineMedium;
  QFont headlineSmall;

  QFont titleLarge;
  QFont titleMedium;
  QFont titleSmall;

  QFont labelLarge;
  QFont labelMedium;
  QFont labelSmall;

  QFont bodyLarge;
  QFont bodyMedium;
  QFont bodySmall;

public:
  TypographyPrivate(const TypographyPrivate &other) = default;
  ~TypographyPrivate() = default;
  bool operator==(const TypographyPrivate &other) const;
  bool operator!=(const TypographyPrivate &other) const;

  explicit TypographyPrivate(bool emphasized);
};

class Typography {
  Q_GADGET
  Q_PROPERTY(QFont displayLarge READ displayLarge WRITE setDisplayLarge FINAL)
  Q_PROPERTY(
      QFont displayMedium READ displayMedium WRITE setDisplayMedium FINAL)
  Q_PROPERTY(QFont displaySmall READ displaySmall WRITE setDisplaySmall FINAL)
  Q_PROPERTY(
      QFont headlineLarge READ headlineLarge WRITE setHeadlineLarge FINAL)
  Q_PROPERTY(
      QFont headlineMedium READ headlineMedium WRITE setHeadlineMedium FINAL)
  Q_PROPERTY(
      QFont headlineSmall READ headlineSmall WRITE setHeadlineSmall FINAL)
  Q_PROPERTY(QFont titleLarge READ titleLarge WRITE setTitleLarge FINAL)
  Q_PROPERTY(QFont titleMedium READ titleMedium WRITE setTitleMedium FINAL)
  Q_PROPERTY(QFont titleSmall READ titleSmall WRITE setTitleSmall FINAL)
  Q_PROPERTY(QFont labelLarge READ labelLarge WRITE setLabelLarge FINAL)
  Q_PROPERTY(QFont labelMedium READ labelMedium WRITE setLabelMedium FINAL)
  Q_PROPERTY(QFont labelSmall READ labelSmall WRITE setLabelSmall FINAL)
  Q_PROPERTY(QFont bodyLarge READ bodyLarge WRITE setBodyLarge FINAL)
  Q_PROPERTY(QFont bodyMedium READ bodyMedium WRITE setBodyMedium FINAL)
  Q_PROPERTY(QFont bodySmall READ bodySmall WRITE setBodySmall FINAL)
  QML_VALUE_TYPE(typography)
  QML_STRUCTURED_VALUE
public:
  explicit Typography(bool emphasized = false);

  inline void swap(const Typography &other) noexcept { *this->d = *other.d; }

  bool operator==(const Typography &other) const;
  bool operator!=(const Typography &other) const;

  Typography(const Typography &other) = default;
  Typography &operator=(const Typography &other) = default;

  Typography(Typography &&other) = default;
  Typography &operator=(Typography &&other) = default;

  ~Typography() = default;

  void setDisplayLarge(QFont);
  QFont displayLarge() const;
  void setDisplayMedium(QFont);
  QFont displayMedium() const;
  void setDisplaySmall(QFont);
  QFont displaySmall() const;

  void setHeadlineLarge(QFont);
  QFont headlineLarge() const;
  void setHeadlineMedium(QFont);
  QFont headlineMedium() const;
  void setHeadlineSmall(QFont);
  QFont headlineSmall() const;

  void setTitleLarge(QFont);
  QFont titleLarge() const;
  void setTitleMedium(QFont);
  QFont titleMedium() const;
  void setTitleSmall(QFont);
  QFont titleSmall() const;

  void setLabelLarge(QFont);
  QFont labelLarge() const;
  void setLabelMedium(QFont);
  QFont labelMedium() const;
  void setLabelSmall(QFont);
  QFont labelSmall() const;

  void setBodyLarge(QFont);
  QFont bodyLarge() const;
  void setBodyMedium(QFont);
  QFont bodyMedium() const;
  void setBodySmall(QFont);
  QFont bodySmall() const;

private:
  std::shared_ptr<TypographyPrivate> d;
};

} // namespace material

#endif // MATERIAL_TYPOGRAPHY_H

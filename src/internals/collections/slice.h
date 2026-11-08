#ifndef MATERIAL_INTERNALS_SLICE_H
#define MATERIAL_INTERNALS_SLICE_H

#include <QDebug>
#include <memory>
#include <span>

// Todo: use raw pointer
namespace material::internals::collections {
template <typename T> class Slice {
private:
  template <bool Const> class Iterator {
    using Pointer = std::conditional_t<Const, const T *, T *>;
    using Reference = std::conditional_t<Const, const T &, T &>;

  public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;

    using pointer = Pointer;
    using reference = Reference;

    // C++20 ranges
    using iterator_concept = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;

    constexpr Iterator() noexcept = default;

    constexpr explicit Iterator(Pointer ptr) noexcept : m_ptr(ptr) {}

    constexpr Reference operator*() const noexcept { return *m_ptr; }

    constexpr Pointer operator->() const noexcept { return m_ptr; }

    constexpr Iterator &operator++() noexcept {
      ++m_ptr;
      return *this;
    }

    constexpr Iterator operator++(int) noexcept {
      auto result = *this;
      ++m_ptr;
      return result;
    }

    constexpr Iterator &operator--() noexcept {
      --m_ptr;
      return *this;
    }

    constexpr Iterator operator--(int) noexcept {
      auto result = *this;
      --m_ptr;
      return result;
    }

    constexpr Iterator &operator+=(difference_type n) noexcept {
      m_ptr += n;
      return *this;
    }

    constexpr Iterator &operator-=(difference_type n) noexcept {
      m_ptr -= n;
      return *this;
    }

    constexpr Reference operator[](difference_type n) const noexcept {
      return m_ptr[n];
    }

    friend constexpr Iterator operator+(Iterator it,
                                        difference_type n) noexcept {
      it += n;
      return it;
    }

    friend constexpr Iterator operator+(difference_type n,
                                        Iterator it) noexcept {
      it += n;
      return it;
    }

    friend constexpr Iterator operator-(Iterator it,
                                        difference_type n) noexcept {
      it -= n;
      return it;
    }

    friend constexpr difference_type operator-(const Iterator &a,
                                               const Iterator &b) noexcept {
      return a.m_ptr - b.m_ptr;
    }

    friend constexpr bool operator==(const Iterator &a,
                                     const Iterator &b) noexcept {
      return a.m_ptr == b.m_ptr;
    }

    friend constexpr bool operator<(const Iterator &a,
                                    const Iterator &b) noexcept {
      return a.m_ptr < b.m_ptr;
    }

    friend constexpr bool operator>(const Iterator &a,
                                    const Iterator &b) noexcept {
      return b < a;
    }

    friend constexpr bool operator<=(const Iterator &a,
                                     const Iterator &b) noexcept {
      return !(b < a);
    }

    friend constexpr bool operator>=(const Iterator &a,
                                     const Iterator &b) noexcept {
      return !(a < b);
    }

  private:
    Pointer m_ptr;
  };

public:
  constexpr Slice(std::unique_ptr<T[]> &&ptr, std::size_t size)
      : m_ptr(std::move(ptr)), m_size(size) {}

  constexpr Slice(std::size_t size)
      : m_ptr(std::make_unique<T[]>(size)), m_size(size) {}

  Slice(std::initializer_list<T> values)
      : m_ptr(std::make_unique<T[]>(values.size())), m_size(values.size()) {
    std::copy(values.begin(), values.end(), m_ptr.get());
  }

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  constexpr iterator begin() { return iterator(m_ptr.get()); }

  constexpr iterator end() { return iterator(m_ptr.get() + m_size); }

  constexpr T &front() noexcept { return m_ptr[0]; }

  constexpr const T &front() const noexcept { return m_ptr[0]; }

  constexpr T &back() noexcept { return m_ptr[m_size - 1]; }

  constexpr const T &back() const noexcept { return m_ptr[m_size - 1]; }

  constexpr bool empty() const noexcept { return m_size == 0; }

  constexpr std::size_t size() const noexcept { return m_size; }

  constexpr T &operator[](std::size_t index) { return m_ptr[index]; }

  constexpr const T &operator[](std::size_t index) const {
    return m_ptr[index];
  }

  constexpr const_iterator begin() const { return const_iterator(m_ptr.get()); }

  constexpr const_iterator end() const {
    return const_iterator(m_ptr.get() + m_size);
  }

  constexpr const_iterator cbegin() const {
    return const_iterator(m_ptr.get());
  }

  constexpr const_iterator cend() const {
    return const_iterator(m_ptr.get() + m_size);
  }

  // template <typename... Args>
  // constexpr T &emplace(std::size_t index, Args &&...args) {
  //   return *std::construct_at(m_ptr.get() + index,
  //   std::forward<Args>(args)...);
  // }

  inline friend QDebug operator<<(QDebug debug, const Slice<T> &slice) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "material::internals::collection::Slice(";
    for (std::size_t i = 0; i < slice.m_size; ++i) {
      if (i > 0) {
        debug << ", ";
      }

      debug << slice[i];
    }
    debug << ")";

    return debug;
  }

  operator std::span<T>() { return std::span<T>(m_ptr.get(), m_size); }

  operator std::span<const T>() const {
    return std::span<const T>(m_ptr.get(), m_size);
  }

  inline friend bool operator==(const Slice<T> &lhs, const Slice<T> &rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs));
  }
  inline friend bool operator!=(const Slice<T> &lhs, const Slice<T> &rhs) {
    return !(lhs == rhs);
  }

private:
  std::unique_ptr<T[]> m_ptr;
  std::size_t m_size;
};
} // namespace material::internals::collections

#endif // MATERIAL_INTERNALS_SLICE_H

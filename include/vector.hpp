#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "json.hpp"

template <typename T>
class Vector {
 public:
  using iterator = T*;
  using size_type = size_t;
  using element_type = T;

 private:
  T* m_arr{nullptr};
  size_type m_capacity{0};
  size_type m_size{0};

 public:
  Vector() = default;

  Vector(Vector const& other)
      : m_arr{new T[other.m_size]},
        m_capacity{other.m_size},
        m_size{other.m_size} {
    std::copy(other.begin(), other.end(), m_arr);
  }

  Vector(Vector&& other) noexcept
      : m_arr{std::exchange(other.m_arr, nullptr)},
        m_capacity{std::exchange(other.m_capacity, 0)},
        m_size{std::exchange(other.m_size, 0)} {}

  Vector(std::initializer_list<T> const& il) {
    this->reserve(il.size());
    for (auto const& e : il) {
      this->push_back(e);
    }
  }

  ~Vector() { delete[] m_arr; }

  void swap(Vector& other) {
    using std::swap;
    swap(m_arr, other.m_arr);
    swap(m_capacity, other.m_capacity);
    swap(m_size, other.m_size);
  }

  void swap(Vector&& other) {
    using std::swap;
    swap(m_arr, other.m_arr);
    swap(m_capacity, other.m_capacity);
    swap(m_size, other.m_size);
  }

  auto operator=(Vector const& other) -> Vector& {
    this->swap(Vector{other});
    return *this;
  }

  auto operator=(Vector&& other) noexcept -> Vector& {
    this->swap(other);
    return *this;
  }

  auto operator==(Vector const& other) const -> bool {
    if (m_size != other.m_size) {
      return false;
    }

    for (size_type i = 0; i < m_size; ++i) {
      if (m_arr[i] != other[i]) {
        return false;
      }
    }

    return true;
  }

  auto operator!=(Vector const& other) const -> bool {
    return !(*this == other);
  }

  auto begin() const -> iterator { return m_arr; }

  auto end() const -> iterator { return m_arr + m_size; }

  auto front() -> element_type& { return *this->begin(); }
  auto front() const -> element_type const& { return *this->begin(); }
  auto back() -> element_type& { return m_arr[m_size - 1]; }
  auto back() const -> element_type const& { return m_arr[m_size - 1]; }

  auto operator[](size_type index) -> element_type& { return m_arr[index]; }

  auto operator[](size_type index) const -> element_type const& {
    return m_arr[index];
  }

  auto at(size_type index) -> element_type& {
    if (m_size <= index) {
      throw std::runtime_error("Index out of range");
    }

    return (*this)[index];
  }

  void reserve(size_type capacity) {
    if (m_capacity >= capacity) {
      return;
    }

    T* new_arr = new T[capacity];
    for (size_type i = 0; i < m_size; ++i) {
      new_arr[i] = std::move(m_arr[i]);
    }

    delete[] m_arr;
    m_arr = new_arr;
    m_capacity = capacity;
  }

  void push_back(T e) { this->emplace_back(std::move(e)); }

  template <typename... Args>
  auto emplace_back(Args&&... args) -> T& {
    this->ensure_extra();

    // FIXME: Not actually emplacing
    m_arr[m_size] = T{args...};
    m_size++;
    return m_arr[m_size - 1];
  }

  void pop_back() { m_size--; }

  void clear() {
    delete[] m_arr;
    m_arr = nullptr;
    m_capacity = 0;
    m_size = 0;
  }

  [[nodiscard]] auto size() const -> size_type { return m_size; }

  [[nodiscard]] auto empty() const -> bool { return m_size == 0; }

 private:
  void enlarge() { this->reserve(std::max(size_type{4}, m_capacity * 2)); }

  void ensure_extra() {
    if (m_size >= m_capacity) {
      this->enlarge();
    }
  }

 public:
  friend auto to_json(nlohmann::json& j, Vector const& vec) -> void {
    j.clear();

    for (auto const& e : vec) {
      j.push_back(e);
    }
  }

  friend auto from_json(const nlohmann::json& j, Vector& vec) -> void {
    vec.clear();
    for (auto const& e : j) {
      vec.push_back(e);
    }
  };
};

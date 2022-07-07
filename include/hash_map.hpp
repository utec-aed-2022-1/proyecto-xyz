#pragma once

#include <cassert>
#include <functional>
#include <initializer_list>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "circular.hpp"
#include "vector.hpp"

template <typename Key, typename Value>
class HashMap {
 private:
  using kv_pair = std::pair<const Key, Value>;

 public:
  using size_type = size_t;
  using iterator = typename CircularList<kv_pair>::iterator;

 private:
  using bucket_t = Vector<typename CircularList<kv_pair>::iterator>;

  std::hash<Key> m_hash{};
  Vector<bucket_t> m_array{};
  CircularList<kv_pair> m_pairs{};
  size_t m_front_partition_size{0};
  size_t m_next_two_power{1};

 public:
  HashMap() = default;

  HashMap(std::initializer_list<kv_pair> il) : HashMap{} {
    for (auto const& [key, value] : il) {
      (*this)[key] = value;
    }
  }

  HashMap(HashMap const& other) : HashMap{} {
    for (auto const& [k, v] : other) {
      (*this)[k] = v;
    }
  }

  HashMap(HashMap&& other) = delete;

  ~HashMap() = default;

  void swap(HashMap& other) {
    using std::swap;
    swap(m_hash, other.m_hash);
    m_array.swap(other.m_array);
    m_pairs.swap(other.m_pairs);
    swap(m_front_partition_size, other.m_front_partition_size);
    swap(m_next_two_power, other.m_next_two_power);
  }

  void swap(HashMap&& other) {
    using std::swap;
    swap(m_hash, other.m_hash);
    m_array.swap(other.m_array);
    m_pairs.swap(other.m_pairs);
    swap(m_front_partition_size, other.m_front_partition_size);
    swap(m_next_two_power, other.m_next_two_power);
  }

  friend void swap(HashMap& h1, HashMap& h2) { h1.swap(h2); }

  auto operator=(HashMap const& other) -> HashMap& {
    this->swap(HashMap(other));
    return *this;
  }

  auto operator=(HashMap&& other) noexcept -> HashMap& {
    this->swap(other);
    return *this;
  }

  auto operator==(HashMap const& other) const -> bool {
    return m_array == other.m_array;
  }

  [[nodiscard]] auto size() const -> size_type { return m_pairs.size(); }

  auto find(Key const& key) -> iterator {
    if (this->empty()) {
      return this->end();
    }

    return this->find_bucket(key, this->hash(key));
  }

  auto operator[](Key const& key) -> Value& {
    auto it = find(key);
    if (it != this->end()) {
      return it->second;
    } else {
      m_array.emplace_back();

      this->split_to_last_bucket();

      auto h = this->hash(key);
      assert(h < m_array.size());

      m_pairs.push_front({key, Value{}});
      auto& bucket = m_array[h];
      bucket.push_back(m_pairs.begin());
      this->sort_bucket(bucket);

      if (m_array.size() == m_next_two_power) {
        m_front_partition_size = m_next_two_power;
        m_next_two_power *= 2;
      }

      return m_pairs.front().second;
    }
  }

  [[nodiscard]] auto empty() const -> bool { return m_pairs.empty(); }

  void clear() {
    m_array.clear();
    m_pairs.clear();
  }

  auto count(Key const& key) -> size_t {
    if (this->find(key) == this->end()) {
      return 0;
    }
    return 1;
  }

  auto begin() const -> iterator { return m_pairs.begin(); }

  auto end() const -> iterator { return m_pairs.end(); }

  [[nodiscard]] auto str_bucket(bucket_t const& bucket) const -> std::string {
    std::ostringstream oss;
    if (bucket.size() == 0) {
      return "{ }";
    }
    auto itt = bucket.begin();
    oss << "{ " << (*itt)->first << ": " << (*itt)->second;
    ++itt;

    while (itt != bucket.end()) {
      oss << ", " << (*itt)->first << ": " << (*itt)->second;
      ++itt;
    }
    oss << " }";
    return oss.str();
  }

  [[nodiscard]] auto str_buckets() const -> std::string {
    std::ostringstream oss;

    for (size_t i = 0; i < m_array.size(); ++i) {
      oss << "[" << i << "] " << this->str_bucket(m_array[i]) << "\n";
    }

    return oss.str();
  }

  // FIXME: The iterator ought to traverse in the proper order, this should not
  // be needed.
  auto get_array() const -> Vector<bucket_t> const& { return m_array; }

  friend auto operator<<(std::ostream& os, HashMap const& hm) -> std::ostream& {
    os << "{";
    for (auto const& [key, value] : hm) {
      os << " [" << key << ", " << value << "]";
    }
    os << " }";

    return os;
  }

 private:
  auto hash(Key const& key) -> size_t {
    size_t h = m_hash(key);
    if (h % m_next_two_power < m_array.size()) {
      return h % m_next_two_power;
    } else {
      return h % m_front_partition_size;
    }
  }

  auto find_bucket(Key const& key, size_t n_bucket) -> iterator {
    assert(n_bucket < m_array.size());

    for (auto const& it : m_array[n_bucket]) {
      if (it->first == key) {
        return it;
      }
    }
    return this->end();
  }

  void sort_bucket(bucket_t& bucket) {
    std::sort(bucket.begin(), bucket.end(),
              [](auto const& kv1, auto const& kv2) {
                return kv1->first < kv2->first;
              });
  }

  void split_to_last_bucket() {
    if (m_array.size() < 2) {
      return;
    }

    size_t last_n = m_array.size() - 1;
    size_t from_n = last_n - m_front_partition_size;
    bucket_t& from = m_array[from_n];
    bucket_t& last = m_array[last_n];

    // This can be solved without sorting, as the `from` bucket is already
    // sorted.
    for (size_t i = 0; i < from.size();) {
      if (this->hash(from[i]->first) != from_n) {
        assert(this->hash(from[i]->first) == last_n);

        if (i + 1 != from.size()) {
          using std::swap;
          swap(from[i], from.back());
        }

        last.push_back(from.back());
        from.pop_back();
      } else {
        i++;
      }
    }

    this->sort_bucket(from);
    this->sort_bucket(last);
  }

  friend auto to_json(nlohmann::json& j, HashMap const& hm) -> void {
    for (auto const& [k, v] : hm) {
      j[k] = v;
    }
  }

  friend auto from_json(const nlohmann::json& j, HashMap& hm) -> void {
    for (auto const& [key, value] : j.items()) {
      hm[key] = value;
    }
  }
};

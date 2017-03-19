#pragma once
#include <boost/utility/string_view.hpp>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename CharT> struct constexpr_char_traits : public std::char_traits<CharT>
{
  using typename std::char_traits<CharT>::char_type;
  using std::char_traits<CharT>::eq;
  // These 2 methods are not constexpr in C++14, however
  // they *can* be implemented with constexpr
  static constexpr std::size_t length(const CharT *s)
  {
    std::size_t len = 0;
    for(; !eq(*s, char_type(0)); ++s)
      ++len;
    return len;
  }

  static constexpr int compare(const CharT *s1, const CharT *s2, int cnt)
  {
    while(cnt--)
    {
      if(*s1 < *s2)
        return -1;
      else if(*s1 > *s2)
        return 1;
      ++s1;
      ++s2;
    }
    return 0;
  }
};

template <typename CharT> using constexpr_basic_string_view = boost::basic_string_view<CharT, constexpr_char_traits<CharT>>;

using constexpr_string_view = constexpr_basic_string_view<char>;


template <typename T> struct EqualOp
{
  static constexpr bool run_impl(const T &a, const T &b, bool) { return a == b; }

  // prefer this one
  template <typename CharT> static constexpr bool run_impl(const constexpr_basic_string_view<CharT> &a, const constexpr_basic_string_view<CharT> &b, int) { return a.compare(b) == 0; }

  static constexpr bool run(const T &a, const T &b)
  {
    // prefer basic_string_view version
    return run_impl(a, b, 0);
  }
};

template <typename T> struct HashOp
{
  struct integral_tag
  {
  };
  struct default_tag
  {
  };

  // TODO: 32-bit system compatibility
  static constexpr std::size_t hash_impl(integral_tag, const T &v)
  {
    if(sizeof(v) < 4)
      return v;
    constexpr std::size_t basis = 14695981039346656037ULL, prime = 1099511628211ULL;
    std::size_t hash_val = basis;
    for(std::size_t i = 0; i < sizeof(int); ++i)
    {
      hash_val ^= (std::size_t) v & (0xffULL << i);
      hash_val *= prime;  // unsigned overflow is well-defined
    }
    return hash_val;
  }

  // BKDRHash.
  template <typename CharT> static constexpr size_t hash_impl(default_tag, const constexpr_basic_string_view<CharT> &str_view)
  {
    size_t hash_val = 0;
    constexpr size_t seed = 31;  // odd, prime, 2^n-1
    for(std::size_t i = 0; i < str_view.size(); ++i)
      hash_val = hash_val * seed + str_view[i];
    return hash_val;
  }

  static constexpr size_t hash(const T &v) { return hash_impl(std::conditional_t<std::is_integral<T>::value, integral_tag, default_tag>(), v); }
};


template <typename KeyT, typename MT, unsigned SIZE, typename Equal = EqualOp<KeyT>, typename Hash = HashOp<KeyT>> class StaticMap
{
public:
  using KeyType = KeyT;
  using MappedType = MT;
  static constexpr std::size_t Size = SIZE;
  static constexpr std::size_t TableSize = 1.618 * Size;  // :) by instinct!

  using PairT = std::pair<KeyType, MappedType>;

private:
  struct Item
  {
    KeyT key;
    MT value;
    bool has_item;
    constexpr Item()
        : key()
        , value()
        , has_item(false)
    {
    }
    constexpr Item(const KeyT &key, const MT &value, bool has_item)
        : key(key)
        , value(value)
        , has_item(has_item)
    {
    }
  };

  using TableT = Item[TableSize];

  KeyT key_buf[TableSize];
  MappedType map_buf[TableSize];
  bool has_buf[TableSize];

  constexpr void try_insert(const PairT &p, size_t pos)
  {
    if(has_buf[pos])
      try_insert(p, (pos + 1) % TableSize);
    else
    {
      key_buf[pos] = p.first;
      map_buf[pos] = p.second;
      has_buf[pos] = true;
    }

    // return buf[pos].has_item ? : buf[pos] = Item { p.first, p.second, true };
  }

  template <typename... Us> constexpr void init(const PairT &p, Us &&... args)
  {
    std::size_t pos = static_hash(p.first) % TableSize;
    try_insert(p, pos);
    init(std::forward<Us>(args)...);
  }
  constexpr void init() {}

  static constexpr const MT &at_oor() { throw std::out_of_range("OOR"); }

  constexpr const MT &at_linear(size_t pos, KeyT key, size_t start_pos) const { return pos == start_pos ? at_oor() : (equal(key_buf[pos], key) ? map_buf[pos] : at_linear((pos + 1) % TableSize, key, start_pos)); }


  static constexpr std::size_t static_hash(const KeyT &key) { return Hash::hash(key); }

  static constexpr bool equal(const KeyT &key1, const KeyT &key2) { return Equal::run(key1, key2); }

  inline constexpr const MT &at_impl(KeyT key) const { return equal(key_buf[static_hash(key) % TableSize], key) ? map_buf[static_hash(key) % TableSize] : at_linear((static_hash(key) + 1) % TableSize, key, static_hash(key) % TableSize); }

public:
  template <typename... Us>
  constexpr StaticMap(Us &&... args)
      : key_buf{}
      , map_buf{}
      , has_buf{}
  {
    init(std::forward<Us>(args)...);
  }

  constexpr const MappedType &operator[](KeyT key) const { return at_impl(key); }
};

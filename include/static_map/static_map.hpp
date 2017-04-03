#pragma once
#include <climits>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace static_map
{

    template <typename T>
    struct constexpr_hash;

    template <>
    struct constexpr_hash<int>
    {
        constexpr std::size_t operator()(int v) const
        {
            constexpr std::size_t basis = 14695981039346656037ULL, prime = 1099511628211ULL;
            std::size_t hash_val = basis;
            for(std::size_t i = 0; i < sizeof(int); ++i)
            {
                hash_val ^= (std::size_t) v & (0xffULL << i);
                hash_val *= prime;  // unsigned overflow is well-defined
            }
            return hash_val;
        }
    };

    template <typename KeyT, typename MT, unsigned SIZE, typename Equal = std::equal_to<KeyT>,
              typename Hash = constexpr_hash<KeyT>>
    class StaticMap
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

        template <typename... Us>
        constexpr void init(const PairT &p, Us &&... args)
        {
            std::size_t pos = static_hash(p.first) % TableSize;
            try_insert(p, pos);
            init(std::forward<Us>(args)...);
        }

        constexpr void init() {}

        static constexpr std::size_t at_oor() { throw std::out_of_range("OOR"); return 0; }

        constexpr std::size_t at_linear(size_t pos, KeyT key, size_t start_pos) const
        {
            return pos == start_pos
                   ? at_oor()
                   : (equal(key_buf[pos], key) ? pos : at_linear((pos + 1) % TableSize, key, start_pos));
        }

        static constexpr std::size_t static_hash(const KeyT &key) { return Hash()(key); }

        static constexpr bool equal(const KeyT &key1, const KeyT &key2) { return key1 == key2; }

        inline constexpr std::size_t at_impl(KeyT key) const
        {
            return equal(key_buf[static_hash(key) % TableSize], key)
                   ? static_hash(key) % TableSize
                   : at_linear((static_hash(key) + 1) % TableSize, key, static_hash(key) % TableSize);
        }

      public:
        template <typename... Us>
        constexpr StaticMap(Us &&... args)
            : key_buf{}
            , map_buf{}
            , has_buf{}
        {
            init(std::forward<Us>(args)...);
        }

        constexpr const MappedType &operator[](KeyT key) const { return map_buf[at_impl(key)]; }
        constexpr MappedType &operator[](KeyT key) { return map_buf[at_impl(key)]; }
    };
}

//
// Created by lz on 3/19/17.
//

#ifndef STATIC_MAP_CONSTEXPR_STRING_VIEW_HPP
#define STATIC_MAP_CONSTEXPR_STRING_VIEW_HPP

#include <boost/utility/string_view.hpp>
#include <cstddef>
#include <string>
#include <type_traits>

namespace static_map
{
    template <typename CharT>
    struct constexpr_char_traits : public std::char_traits<CharT>
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

    template <typename CharT>
    class constexpr_basic_string_view : public boost::basic_string_view<CharT, constexpr_char_traits<CharT>>
    {
        using BaseT = boost::basic_string_view<CharT, constexpr_char_traits<CharT>>;

      public:
        template <typename... Us>
        constexpr constexpr_basic_string_view(Us &&... args)
            : BaseT(std::forward<Us>(args)...)
        {
        }

        friend constexpr bool operator==(const constexpr_basic_string_view &a, const constexpr_basic_string_view &b)
        {
            return a.compare(b) == 0;
        }
    };

    using constexpr_string_view = constexpr_basic_string_view<char>;

    template <typename T>
    struct constexpr_hash;

    template <typename CharT>
    struct constexpr_hash<constexpr_basic_string_view<CharT>>
    {
        constexpr std::size_t operator()(const constexpr_basic_string_view<CharT> &str_view) const
        {
            size_t hash_val = 0;
            constexpr size_t seed = 31;  // odd, prime, 2^n-1
            for(std::size_t i = 0; i < str_view.size(); ++i)
                hash_val = hash_val * seed + str_view[i];
            return hash_val;
        }
    };
}
#endif  // STATIC_MAP_CONSTEXPR_STRING_VIEW_HPP

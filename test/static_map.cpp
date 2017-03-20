#include "static_map/static_map.hpp"
#include "static_map/constexpr_string_view.hpp"

using std::make_pair;

constexpr const char *pear_str = "pear";
constexpr static_map::StaticMap<int, const char *, 7> cmap(make_pair(2, "apple"), make_pair(10, "banana"),
                                                           make_pair(5, pear_str), make_pair(6, "orange"),
                                                           make_pair(1, "watermelon"), make_pair(0, "peaches"),
                                                           make_pair(12, "strawberry"));
// 1.618 * 7 = 11, so 12 and 1 would face hash collision

__attribute__((noinline)) void test_int_key_constexpr()
{
    static_assert(cmap[5] == pear_str);
}

__attribute__((noinline)) void test_int_key_nonconstexpr()
{
    const char *t = cmap[6];
    if(strcmp(t, "orange"))
        abort();

    if(strcmp(cmap[12], "strawberry"))
        abort();
}

__attribute__((noinline)) void test_int_key_assignment()
{
    static_map::StaticMap<int, const char *, 7> cmap_mut(
    make_pair(2, "apple"), make_pair(10, "banana"), make_pair(5, pear_str), make_pair(6, "orange"),
    make_pair(1, "watermelon"), make_pair(0, "peaches"), make_pair(12, "strawberry"));
    cmap_mut[12] = pear_str;
    if(cmap_mut[12] != pear_str)
        abort();
}

constexpr static_map::StaticMap<static_map::constexpr_string_view, int, 6>
cmap_2(make_pair("apple", 2), make_pair("banana", 10), make_pair("pear", 5), make_pair("orange", 6),
       make_pair("watermelon", 1), make_pair("peaches", 0));
__attribute__((noinline)) void test_string_view_key_constexpr()
{

    constexpr int six = cmap_2["orange"];
    static_assert(6 == six, "cmap_2 orange should be 6");
}

__attribute__((noinline)) void test_string_view_key_nonconstexpr()
{
    // const char *tt = cmap[13];
    if(cmap_2["orange"] != 6)
        abort();
}

int main()
{
    test_int_key_constexpr();
    test_int_key_nonconstexpr();
    test_int_key_assignment();
    test_string_view_key_constexpr();
    test_string_view_key_nonconstexpr();
}

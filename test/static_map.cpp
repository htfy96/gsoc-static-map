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
    static_assert(cmap[5] == pear_str, "cmap[5] should be pear");
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

__attribute__((noinline)) void test_construct_large()
{
    constexpr static_map::StaticMap<int, int, 200>
        cmap_large(
                make_pair(1, 50),
                make_pair(2, 51),
                make_pair(3, 52),
                make_pair(4, 53),
                make_pair(5, 54),
                make_pair(6, 55),
                make_pair(7, 56),
                make_pair(8, 57),
                make_pair(9, 58),
                make_pair(10, 59),
                make_pair(11, 60),
                make_pair(12, 61),
                make_pair(13, 62),
                make_pair(14, 63),
                make_pair(15, 64),
                make_pair(16, 65),
                make_pair(17, 66),
                make_pair(18, 67),
                make_pair(19, 68),
                make_pair(20, 69),
                make_pair(21, 70),
                make_pair(22, 71),
                make_pair(23, 72),
                make_pair(24, 73),
                make_pair(25, 74),
                make_pair(26, 75),
                make_pair(27, 76),
                make_pair(28, 77),
                make_pair(29, 78),
                make_pair(30, 79),
                make_pair(31, 80),
                make_pair(32, 81),
                make_pair(33, 82),
                make_pair(34, 83),
                make_pair(35, 84),
                make_pair(36, 85),
                make_pair(37, 86),
                make_pair(38, 87),
                make_pair(39, 88),
                make_pair(40, 89),
                make_pair(41, 90),
                make_pair(42, 91),
                make_pair(43, 92),
                make_pair(44, 93),
                make_pair(45, 94),
                make_pair(46, 95),
                make_pair(47, 96),
                make_pair(48, 97),
                make_pair(49, 98),
                make_pair(50, 99),
                make_pair(51, 100),
                make_pair(52, 101),
                make_pair(53, 102),
                make_pair(54, 103),
                make_pair(55, 104),
                make_pair(56, 105),
                make_pair(57, 106),
                make_pair(58, 107),
                make_pair(59, 108),
                make_pair(60, 109),
                make_pair(61, 110),
                make_pair(62, 111),
                make_pair(63, 112),
                make_pair(64, 113),
                make_pair(65, 114),
                make_pair(66, 115),
                make_pair(67, 116),
                make_pair(68, 117),
                make_pair(69, 118),
                make_pair(70, 119),
                make_pair(71, 120),
                make_pair(72, 121),
                make_pair(73, 122),
                make_pair(74, 123),
                make_pair(75, 124),
                make_pair(76, 125),
                make_pair(77, 126),
                make_pair(78, 127),
                make_pair(79, 128),
                make_pair(80, 129),
                make_pair(81, 130),
                make_pair(82, 131),
                make_pair(83, 132),
                make_pair(84, 133),
                make_pair(85, 134),
                make_pair(86, 135),
                make_pair(87, 136),
                make_pair(88, 137),
                make_pair(89, 138),
                make_pair(90, 139),
                make_pair(91, 140),
                make_pair(92, 141),
                make_pair(93, 142),
                make_pair(94, 143),
                make_pair(95, 144),
                make_pair(96, 145),
                make_pair(97, 146),
                make_pair(98, 147),
                make_pair(99, 148),
                make_pair(100, 149),
                make_pair(101, 150),
                make_pair(102, 151),
                make_pair(103, 152),
                make_pair(104, 153),
                make_pair(105, 154),
                make_pair(106, 155),
                make_pair(107, 156),
                make_pair(108, 157),
                make_pair(109, 158),
                make_pair(110, 159),
                make_pair(111, 160),
                make_pair(112, 161),
                make_pair(113, 162),
                make_pair(114, 163),
                make_pair(115, 164),
                make_pair(116, 165),
                make_pair(117, 166),
                make_pair(118, 167),
                make_pair(119, 168),
                make_pair(120, 169),
                make_pair(121, 170),
                make_pair(122, 171),
                make_pair(123, 172),
                make_pair(124, 173),
                make_pair(125, 174),
                make_pair(126, 175),
                make_pair(127, 176),
                make_pair(128, 177),
                make_pair(129, 178),
                make_pair(130, 179),
                make_pair(131, 180),
                make_pair(132, 181),
                make_pair(133, 182),
                make_pair(134, 183),
                make_pair(135, 184),
                make_pair(136, 185),
                make_pair(137, 186),
                make_pair(138, 187),
                make_pair(139, 188),
                make_pair(140, 189),
                make_pair(141, 190),
                make_pair(142, 191),
                make_pair(143, 192),
                make_pair(144, 193),
                make_pair(145, 194),
                make_pair(146, 195),
                make_pair(147, 196),
                make_pair(148, 197),
                make_pair(149, 198),
                make_pair(150, 199),
                make_pair(151, 200),
                make_pair(152, 201),
                make_pair(153, 202),
                make_pair(154, 203),
                make_pair(155, 204),
                make_pair(156, 205),
                make_pair(157, 206),
                make_pair(158, 207),
                make_pair(159, 208),
                make_pair(160, 209),
                make_pair(161, 210),
                make_pair(162, 211),
                make_pair(163, 212),
                make_pair(164, 213),
                make_pair(165, 214),
                make_pair(166, 215),
                make_pair(167, 216),
                make_pair(168, 217),
                make_pair(169, 218),
                make_pair(170, 219),
                make_pair(171, 220),
                make_pair(172, 221),
                make_pair(173, 222),
                make_pair(174, 223),
                make_pair(175, 224),
                make_pair(176, 225),
                make_pair(177, 226),
                make_pair(178, 227),
                make_pair(179, 228),
                make_pair(180, 229),
                make_pair(181, 230),
                make_pair(182, 231),
                make_pair(183, 232),
                make_pair(184, 233),
                make_pair(185, 234),
                make_pair(186, 235),
                make_pair(187, 236),
                make_pair(188, 237),
                make_pair(189, 238),
                make_pair(190, 239),
                make_pair(191, 240),
                make_pair(192, 241),
                make_pair(193, 242),
                make_pair(194, 243),
                make_pair(195, 244),
                make_pair(196, 245),
                make_pair(197, 246),
                make_pair(198, 247),
                make_pair(199, 248),
                make_pair(200, 249)
        );

    static_assert(cmap_large[100] == 149, "");
    static_assert(cmap_large[150] == 199, "");
    static_assert(cmap_large[50] == 99, "");
}

int main()
{
    test_int_key_constexpr();
    test_int_key_nonconstexpr();
    test_int_key_assignment();
    test_string_view_key_constexpr();
    test_string_view_key_nonconstexpr();
    test_construct_large();
}

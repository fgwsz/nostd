#pragma once
#include<type_traits>
//|     |A    ||B    |C    |D    |E    ||F    |G    |H    |I     ||J    |K    |L    |M    |
//|1    |f\t  ||T    |Tc   |Tv   |Tcv  ||T&   |Tc&  |Tv&  |Tcv&  ||T&&  |Tc&& |Tv&& |Tcv&&|
//------------||-----------------------||------------------------||------------------------
//|2    |T    ||O-   |O    |O    |O    ||X    |O    |X    |X     ||O    |O    |O    |O    |
//|3    |Tc   ||O    |O-   |O    |O    ||X    |O    |X    |X     ||X    |O    |X    |O    |
//|4    |Tv   ||O    |O    |O-   |O    ||X    |X    |X    |X     ||X    |X    |O    |O    |
//|5    |Tcv  ||O    |O    |O    |O-   ||X    |X    |X    |X     ||X    |X    |X    |O    |
//------------||-----------------------||------------------------||------------------------
//|6    |T&   ||O    |O    |O    |O    ||O-   |O    |O    |O     ||X    |X    |X    |X    |
//|7    |Tc&  ||O    |O    |O    |O    ||X    |O-   |X    |O     ||X    |X    |X    |X    |
//|8    |Tv&  ||O    |O    |O    |O    ||X    |X    |O-   |O     ||X    |X    |X    |X    |
//|9    |Tcv& ||O    |O    |O    |O    ||X    |X    |X    |O-    ||X    |X    |X    |X    |
//------------||-----------------------||------------------------||------------------------
//|10   |T&&  ||O    |O    |O    |O    ||X    |O    |X    |X     ||O-   |O    |O    |O    |
//|11   |Tc&& ||O    |O    |O    |O    ||X    |O    |X    |X     ||X    |O-   |X    |O    |
//|12   |Tv&& ||O    |O    |O    |O    ||X    |X    |X    |X     ||X    |X    |O-   |O    |
//|13   |Tcv&&||O    |O    |O    |O    ||X    |X    |X    |X     ||X    |X    |X    |O-   |
using _Type=int;
static constexpr auto value_2B=::std::is_convertible_v<_Type,_Type>;
static constexpr auto value_2C=::std::is_convertible_v<_Type,_Type const>;
static constexpr auto value_2D=::std::is_convertible_v<_Type,_Type volatile>;
static constexpr auto value_2E=::std::is_convertible_v<_Type,_Type const volatile>;
static constexpr auto value_2F=::std::is_convertible_v<_Type,_Type &>;
static constexpr auto value_2G=::std::is_convertible_v<_Type,_Type const&>;
static constexpr auto value_2H=::std::is_convertible_v<_Type,_Type volatile&>;
static constexpr auto value_2I=::std::is_convertible_v<_Type,_Type const volatile&>;
static constexpr auto value_2J=::std::is_convertible_v<_Type,_Type &&>;
static constexpr auto value_2K=::std::is_convertible_v<_Type,_Type const&&>;
static constexpr auto value_2L=::std::is_convertible_v<_Type,_Type volatile&&>;
static constexpr auto value_2M=::std::is_convertible_v<_Type,_Type const volatile&&>;

static constexpr auto value_3B=::std::is_convertible_v<_Type const,_Type>;
static constexpr auto value_3C=::std::is_convertible_v<_Type const,_Type const>;
static constexpr auto value_3D=::std::is_convertible_v<_Type const,_Type volatile>;
static constexpr auto value_3E=::std::is_convertible_v<_Type const,_Type const volatile>;
static constexpr auto value_3F=::std::is_convertible_v<_Type const,_Type &>;
static constexpr auto value_3G=::std::is_convertible_v<_Type const,_Type const&>;
static constexpr auto value_3H=::std::is_convertible_v<_Type const,_Type volatile&>;
static constexpr auto value_3I=::std::is_convertible_v<_Type const,_Type const volatile&>;
static constexpr auto value_3J=::std::is_convertible_v<_Type const,_Type &&>;
static constexpr auto value_3K=::std::is_convertible_v<_Type const,_Type const&&>;
static constexpr auto value_3L=::std::is_convertible_v<_Type const,_Type volatile&&>;
static constexpr auto value_3M=::std::is_convertible_v<_Type const,_Type const volatile&&>;

static constexpr auto value_4B=::std::is_convertible_v<_Type volatile,_Type>;
static constexpr auto value_4C=::std::is_convertible_v<_Type volatile,_Type const>;
static constexpr auto value_4D=::std::is_convertible_v<_Type volatile,_Type volatile>;
static constexpr auto value_4E=::std::is_convertible_v<_Type volatile,_Type const volatile>;
static constexpr auto value_4F=::std::is_convertible_v<_Type volatile,_Type &>;
static constexpr auto value_4G=::std::is_convertible_v<_Type volatile,_Type const&>;
static constexpr auto value_4H=::std::is_convertible_v<_Type volatile,_Type volatile&>;
static constexpr auto value_4I=::std::is_convertible_v<_Type volatile,_Type const volatile&>;
static constexpr auto value_4J=::std::is_convertible_v<_Type volatile,_Type &&>;
static constexpr auto value_4K=::std::is_convertible_v<_Type volatile,_Type const&&>;
static constexpr auto value_4L=::std::is_convertible_v<_Type volatile,_Type volatile&&>;
static constexpr auto value_4M=::std::is_convertible_v<_Type volatile,_Type const volatile&&>;

static constexpr auto value_5B=::std::is_convertible_v<_Type const volatile,_Type>;
static constexpr auto value_5C=::std::is_convertible_v<_Type const volatile,_Type const>;
static constexpr auto value_5D=::std::is_convertible_v<_Type const volatile,_Type volatile>;
static constexpr auto value_5E=::std::is_convertible_v<_Type const volatile,_Type const volatile>;
static constexpr auto value_5F=::std::is_convertible_v<_Type const volatile,_Type &>;
static constexpr auto value_5G=::std::is_convertible_v<_Type const volatile,_Type const&>;
static constexpr auto value_5H=::std::is_convertible_v<_Type const volatile,_Type volatile&>;
static constexpr auto value_5I=::std::is_convertible_v<_Type const volatile,_Type const volatile&>;
static constexpr auto value_5J=::std::is_convertible_v<_Type const volatile,_Type &&>;
static constexpr auto value_5K=::std::is_convertible_v<_Type const volatile,_Type const&&>;
static constexpr auto value_5L=::std::is_convertible_v<_Type const volatile,_Type volatile&&>;
static constexpr auto value_5M=::std::is_convertible_v<_Type const volatile,_Type const volatile&&>;

static constexpr auto value_6B=::std::is_convertible_v<_Type&,_Type>;
static constexpr auto value_6C=::std::is_convertible_v<_Type&,_Type const>;
static constexpr auto value_6D=::std::is_convertible_v<_Type&,_Type volatile>;
static constexpr auto value_6E=::std::is_convertible_v<_Type&,_Type const volatile>;
static constexpr auto value_6F=::std::is_convertible_v<_Type&,_Type &>;
static constexpr auto value_6G=::std::is_convertible_v<_Type&,_Type const&>;
static constexpr auto value_6H=::std::is_convertible_v<_Type&,_Type volatile&>;
static constexpr auto value_6I=::std::is_convertible_v<_Type&,_Type const volatile&>;
static constexpr auto value_6J=::std::is_convertible_v<_Type&,_Type &&>;
static constexpr auto value_6K=::std::is_convertible_v<_Type&,_Type const&&>;
static constexpr auto value_6L=::std::is_convertible_v<_Type&,_Type volatile&&>;
static constexpr auto value_6M=::std::is_convertible_v<_Type&,_Type const volatile&&>;

static constexpr auto value_7B=::std::is_convertible_v<_Type const&,_Type>;
static constexpr auto value_7C=::std::is_convertible_v<_Type const&,_Type const>;
static constexpr auto value_7D=::std::is_convertible_v<_Type const&,_Type volatile>;
static constexpr auto value_7E=::std::is_convertible_v<_Type const&,_Type const volatile>;
static constexpr auto value_7F=::std::is_convertible_v<_Type const&,_Type &>;
static constexpr auto value_7G=::std::is_convertible_v<_Type const&,_Type const&>;
static constexpr auto value_7H=::std::is_convertible_v<_Type const&,_Type volatile&>;
static constexpr auto value_7I=::std::is_convertible_v<_Type const&,_Type const volatile&>;
static constexpr auto value_7J=::std::is_convertible_v<_Type const&,_Type &&>;
static constexpr auto value_7K=::std::is_convertible_v<_Type const&,_Type const&&>;
static constexpr auto value_7L=::std::is_convertible_v<_Type const&,_Type volatile&&>;
static constexpr auto value_7M=::std::is_convertible_v<_Type const&,_Type const volatile&&>;

static constexpr auto value_8B=::std::is_convertible_v<_Type volatile&,_Type>;
static constexpr auto value_8C=::std::is_convertible_v<_Type volatile&,_Type const>;
static constexpr auto value_8D=::std::is_convertible_v<_Type volatile&,_Type volatile>;
static constexpr auto value_8E=::std::is_convertible_v<_Type volatile&,_Type const volatile>;
static constexpr auto value_8F=::std::is_convertible_v<_Type volatile&,_Type &>;
static constexpr auto value_8G=::std::is_convertible_v<_Type volatile&,_Type const&>;
static constexpr auto value_8H=::std::is_convertible_v<_Type volatile&,_Type volatile&>;
static constexpr auto value_8I=::std::is_convertible_v<_Type volatile&,_Type const volatile&>;
static constexpr auto value_8J=::std::is_convertible_v<_Type volatile&,_Type &&>;
static constexpr auto value_8K=::std::is_convertible_v<_Type volatile&,_Type const&&>;
static constexpr auto value_8L=::std::is_convertible_v<_Type volatile&,_Type volatile&&>;
static constexpr auto value_8M=::std::is_convertible_v<_Type volatile&,_Type const volatile&&>;

static constexpr auto value_9B=::std::is_convertible_v<_Type const volatile&,_Type>;
static constexpr auto value_9C=::std::is_convertible_v<_Type const volatile&,_Type const>;
static constexpr auto value_9D=::std::is_convertible_v<_Type const volatile&,_Type volatile>;
static constexpr auto value_9E=::std::is_convertible_v<_Type const volatile&,_Type const volatile>;
static constexpr auto value_9F=::std::is_convertible_v<_Type const volatile&,_Type &>;
static constexpr auto value_9G=::std::is_convertible_v<_Type const volatile&,_Type const&>;
static constexpr auto value_9H=::std::is_convertible_v<_Type const volatile&,_Type volatile&>;
static constexpr auto value_9I=::std::is_convertible_v<_Type const volatile&,_Type const volatile&>;
static constexpr auto value_9J=::std::is_convertible_v<_Type const volatile&,_Type &&>;
static constexpr auto value_9K=::std::is_convertible_v<_Type const volatile&,_Type const&&>;
static constexpr auto value_9L=::std::is_convertible_v<_Type const volatile&,_Type volatile&&>;
static constexpr auto value_9M=::std::is_convertible_v<_Type const volatile&,_Type const volatile&&>;

static constexpr auto value_10B=::std::is_convertible_v<_Type&&,_Type>;
static constexpr auto value_10C=::std::is_convertible_v<_Type&&,_Type const>;
static constexpr auto value_10D=::std::is_convertible_v<_Type&&,_Type volatile>;
static constexpr auto value_10E=::std::is_convertible_v<_Type&&,_Type const volatile>;
static constexpr auto value_10F=::std::is_convertible_v<_Type&&,_Type &>;
static constexpr auto value_10G=::std::is_convertible_v<_Type&&,_Type const&>;
static constexpr auto value_10H=::std::is_convertible_v<_Type&&,_Type volatile&>;
static constexpr auto value_10I=::std::is_convertible_v<_Type&&,_Type const volatile&>;
static constexpr auto value_10J=::std::is_convertible_v<_Type&&,_Type &&>;
static constexpr auto value_10K=::std::is_convertible_v<_Type&&,_Type const&&>;
static constexpr auto value_10L=::std::is_convertible_v<_Type&&,_Type volatile&&>;
static constexpr auto value_10M=::std::is_convertible_v<_Type&&,_Type const volatile&&>;

static constexpr auto value_11B=::std::is_convertible_v<_Type const&&,_Type>;
static constexpr auto value_11C=::std::is_convertible_v<_Type const&&,_Type const>;
static constexpr auto value_11D=::std::is_convertible_v<_Type const&&,_Type volatile>;
static constexpr auto value_11E=::std::is_convertible_v<_Type const&&,_Type const volatile>;
static constexpr auto value_11F=::std::is_convertible_v<_Type const&&,_Type &>;
static constexpr auto value_11G=::std::is_convertible_v<_Type const&&,_Type const&>;
static constexpr auto value_11H=::std::is_convertible_v<_Type const&&,_Type volatile&>;
static constexpr auto value_11I=::std::is_convertible_v<_Type const&&,_Type const volatile&>;
static constexpr auto value_11J=::std::is_convertible_v<_Type const&&,_Type &&>;
static constexpr auto value_11K=::std::is_convertible_v<_Type const&&,_Type const&&>;
static constexpr auto value_11L=::std::is_convertible_v<_Type const&&,_Type volatile&&>;
static constexpr auto value_11M=::std::is_convertible_v<_Type const&&,_Type const volatile&&>;

static constexpr auto value_12B=::std::is_convertible_v<_Type volatile&&,_Type>;
static constexpr auto value_12C=::std::is_convertible_v<_Type volatile&&,_Type const>;
static constexpr auto value_12D=::std::is_convertible_v<_Type volatile&&,_Type volatile>;
static constexpr auto value_12E=::std::is_convertible_v<_Type volatile&&,_Type const volatile>;
static constexpr auto value_12F=::std::is_convertible_v<_Type volatile&&,_Type &>;
static constexpr auto value_12G=::std::is_convertible_v<_Type volatile&&,_Type const&>;
static constexpr auto value_12H=::std::is_convertible_v<_Type volatile&&,_Type volatile&>;
static constexpr auto value_12I=::std::is_convertible_v<_Type volatile&&,_Type const volatile&>;
static constexpr auto value_12J=::std::is_convertible_v<_Type volatile&&,_Type &&>;
static constexpr auto value_12K=::std::is_convertible_v<_Type volatile&&,_Type const&&>;
static constexpr auto value_12L=::std::is_convertible_v<_Type volatile&&,_Type volatile&&>;
static constexpr auto value_12M=::std::is_convertible_v<_Type volatile&&,_Type const volatile&&>;

static constexpr auto value_13B=::std::is_convertible_v<_Type const volatile&&,_Type>;
static constexpr auto value_13C=::std::is_convertible_v<_Type const volatile&&,_Type const>;
static constexpr auto value_13D=::std::is_convertible_v<_Type const volatile&&,_Type volatile>;
static constexpr auto value_13E=::std::is_convertible_v<_Type const volatile&&,_Type const volatile>;
static constexpr auto value_13F=::std::is_convertible_v<_Type const volatile&&,_Type &>;
static constexpr auto value_13G=::std::is_convertible_v<_Type const volatile&&,_Type const&>;
static constexpr auto value_13H=::std::is_convertible_v<_Type const volatile&&,_Type volatile&>;
static constexpr auto value_13I=::std::is_convertible_v<_Type const volatile&&,_Type const volatile&>;
static constexpr auto value_13J=::std::is_convertible_v<_Type const volatile&&,_Type &&>;
static constexpr auto value_13K=::std::is_convertible_v<_Type const volatile&&,_Type const&&>;
static constexpr auto value_13L=::std::is_convertible_v<_Type const volatile&&,_Type volatile&&>;
static constexpr auto value_13M=::std::is_convertible_v<_Type const volatile&&,_Type const volatile&&>;
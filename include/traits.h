#pragma once

#include "stdafx.h"

// Convert array into a tuple
template<typename Array,
        std::size_t... I>
constexpr auto __to_tuple(const Array& a, std::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}

 template < typename T,
         std::size_t N,
         typename Indices = std::make_index_sequence<N>
         >
constexpr auto to_tuple(const std::array<T, N>& a)
{
    return __to_tuple(a, Indices{});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

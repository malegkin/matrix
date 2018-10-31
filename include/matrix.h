#pragma once

#include "stdafx.h"

/*
template < typename T, T t, typename... Ts>
struct Matrix{
    using
};
*/
template <typename T, T t, typename Key>
struct _Matrix {
    using key_type      = Key;
    using value_type    = T;

    _Matrix()
    : _default_value(t)
    {}

    std::size_t size(){
        return _values.size();
    }



private:
    value_type  _default_value;
    std::unordered_map<key_type, value_type> _values;

};
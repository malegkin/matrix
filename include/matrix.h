#pragma once

#include "stdafx.h"

#include "traits.h"

/*
template < typename T, T t, typename... Ts>
struct Matrix{
    using
};
*/




template < typename value_type,
                value_type default_value,
                size_t dimension = 2,
                size_t offset_max_value = 100,
                typename = std::enable_if_t< (dimension > 0) >>

struct Matrix {

    using index_offset_type = uint64_t ;

    struct Index {
        Index()
        :_next_uninitialized_offset(dimension)
        { }

        Index(index_offset_type i ) {
            _offsets[0] = i;
            _next_uninitialized_offset = 1;
        }

        Index(const Index& index)
        : _next_uninitialized_offset( index._next_uninitialized_offset )
        , _iterable_offset( index._iterable_offset )
        , _offsets( index._offsets )
        {}

        Index next() const {

            Index out(*this);
            out++;
            return std::move(out);
        }

        Index& operator++()
        {
            if ( isEnd() )
                throw new std::out_of_range("index.operator++ ");

            //// increment lower (with max index in _offset) coordinate
            (*std::prev(std::end(_offsets)))++;

            for (auto it = std::rbegin(_offsets); it != std::prev(std::rend(_offsets)); ++it)  {
                if (*it == offset_max_value)    {
                    *it = 0;
                    (*std::next(it))++;
                }
            }

            return *this;
        }

        Index& operator++(int)
        {
            Index out(*this);
            operator++();
            return out;
        }


        bool operator==(const Index& rhs) const  {
            // check end of index
            if ( isEnd() && rhs.isEnd() )
                return true;

            return _offsets == rhs._offsets;
        }

        bool operator!=(const Index& rhs) const {
            return !( *this == rhs );
        }

        Index begin() const {
            return std::move(Index());
        }


        Index end() const {
            Index out(offset_max_value);

            return std::move(out);
        }

        bool isValid() {
            return dimension == _next_uninitialized_offset ;
        }

        bool isEnd() const {
            return _offsets[0] == default_value;
        }

        auto toTuple() const {
            return to_tuple(_offsets);
        }
        /*
        Index& operator[](index_offset_type i){
            auto a = _values.find(i);
            return (a == _values.end()) ? default_value : a;
        }
        */

        std::string toString()
        {
            return std::accumulate(
                    std::next(std::begin(_offsets)),
                    std::end(_offsets),
                    std::to_string((*(std::begin(_offsets)))),
                    [](std::string out, auto a) {
                        return out + "." + std::to_string(a);
                    });
        }

    private:
        size_t _next_uninitialized_offset{};
        size_t _iterable_offset{};
        std::array<index_offset_type, dimension> _offsets{};
    };

    using values_container_type = std::map<Index, value_type>;

    struct matrix_iterator: public std::iterator< std::bidirectional_iterator_tag, value_type >
    {
        matrix_iterator() = default;
        matrix_iterator( const  values_container_type && ) = delete;

        matrix_iterator( const  values_container_type & values)
        : _values( values )
        { }

        matrix_iterator( const matrix_iterator & mi)
        : _values( mi._values )
        { }
/*
//prefix
        matrix_iterator& operator++() { _ptr = _ptr->_next; return *this; }
        matrix_iterator& operator--() { _ptr = _ptr->_prev; return *this; }

//postfix
        matrix_iterator operator++(int) { _iterator_t out = *this; _ptr = _ptr->_next; return out; }
        matrix_iterator operator--(int) { _iterator_t out = *this; _ptr = _ptr->_prev; return out; }

        T&   operator*()   { return _ptr->_value ;   }
        T*   operator->()  { return &(_ptr->_value); }

        bool operator==(const _iterator_t& rhs){ return _ptr == rhs._ptr; }
        bool operator!=(const _iterator_t& rhs){ return !operator==(rhs); }

    */
    private:
        const values_container_type & _values;
        Index _index;
    };



    Matrix() {}

    std::size_t size(){
        return _values.size();
    }


    value_type operator()(Index i){
        auto a = _values.find(i);
        return (a == _values.end()) ? default_value : a;
    }


private:
    values_container_type _values;

};
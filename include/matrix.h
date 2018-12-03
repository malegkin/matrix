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
            value_type default_value = 0,
            size_t dimension = 2,
            size_t offset_max_value = 10,
            typename offset_type = size_t,
            typename = std::enable_if< (dimension > 0) >>

struct Matrix {


                template < class ComparisonFunctor >
    struct matrix_iterator :
            public std::iterator <
                    std::bidirectional_iterator_tag,
                    value_type >
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









    class IIndex {
    public:
        IIndex() = default;
        IIndex(offset_type offset){
            _offsets[0] = offset;
        }

        virtual bool isEnd() const = 0;

        bool operator==(const IIndex& rhs) const {
            if ( isEnd() && rhs.isEnd() )
                return true;

            return this->_offsets == rhs._offsets;
        }

        bool operator!=(const IIndex& rhs) const {
            return !( *this == rhs );
        }

        std::string toString() const {
            return std::accumulate(
                    std::next(std::begin(_offsets)),
                    std::end(_offsets),
                    std::to_string((*(std::begin(_offsets)))),
                    [](std::string out, auto a) {
                        return out + "." + std::to_string(a);
                    });
        }

        auto toTuple() const {
            return to_tuple( _offsets );
        }

        auto toArray() const {
            return _offsets;
        }


    protected:
        std::array< offset_type, dimension > _offsets{};

    };


    class Index : public IIndex {

    public:
        Index next() const {
            Index out(*this);
            out++;
            return std::move(out);
        }

        Index operator++()
        {
            if ( isEnd() )
                throw new std::out_of_range("index.operator++ ");

            //// increment lower (with max index in _offset) coordinate
            (*std::prev(std::end( this->_offsets )))++;

            for (auto it = std::rbegin( this->_offsets ); it != std::prev(std::rend( this->_offsets )); ++it)  {
                if (*it == offset_max_value)    {
                    *it = 0;
                    (*std::next(it))++;
                }
            }

            return *this;
        }

        Index operator++(int)
        {
            Index out(*this);
            operator++();
            return std::move(out);
        }


        Index begin() const {
            return std::move(Index());
        }


        Index end() const {
            Index out(offset_max_value);

            return std::move(out);
        }


        bool isEnd() const {
            return this->_offsets[0] == offset_max_value;
        }


    };


/*
    struct IndexMD : Index {



    };

*/




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
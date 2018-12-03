#include "stdafx.h"
#include "matrix.h"

#define BOOST_TEST_MODULE test_matrix
#include <boost/test/unit_test.hpp>

#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( test_matrix )

    BOOST_AUTO_TEST_CASE( test_matrix__index_increment_postfix ) {

        Matrix<uint32_t, 0, 3>::Index index;

        for (size_t i = 0; i < 10; i++){
            for (size_t j = 0; j < 10; j++){
                for (size_t k = 0; k < 10; k++) {
                    BOOST_REQUIRE( index.toTuple() == std::make_tuple(i, j, k) );
                    index++;
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE( test_matrix__index_increment_prefix ) {

        Matrix<uint32_t, 0, 3>::Index index;

        for (size_t i = 0; i < 10; i++){
            for (size_t j = 0; j < 10; j++){
                for (size_t k = 0; k < 10; k++) {
                    BOOST_REQUIRE( index.toTuple() == std::make_tuple(i, j, k) );
                    ++index;
                }
            }
        }
    }





    BOOST_AUTO_TEST_CASE( test_matrix__check_base_examples_from_task ) {
        Matrix<int, -1> matrix; // бесконечная матрица int заполнена значениями -1
        BOOST_REQUIRE(matrix.size() == 0); // все ячейки свободны
        //auto a = matrix[0][0];
        //assert(a == -1);

        BOOST_REQUIRE( true );
    }


BOOST_AUTO_TEST_SUITE_END()

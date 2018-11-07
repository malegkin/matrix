
#include "stdafx.h"
#include "traits.h"

#define BOOST_TEST_MODULE test_matrix
#include <boost/test/unit_test.hpp>

#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( test_traits )

    BOOST_AUTO_TEST_CASE( test_traits__array_to_tuple ) {

        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 0>()) == std::tuple<>() );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 1>({0})) == std::make_tuple(0) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 2>({0, 1})) == std::make_tuple(0, 1) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 3>({0, 1, 2 })) == std::make_tuple(0, 1, 2) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 4>({0, 1, 2, 3 })) == std::make_tuple(0, 1, 2, 3) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 5>({0, 1, 2, 3, 4 })) == std::make_tuple(0, 1, 2, 3, 4) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 6>({0, 1, 2, 3, 4, 5 })) == std::make_tuple(0, 1, 2, 3, 4, 5) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 7>({0, 1, 2, 3, 4, 5, 6})) == std::make_tuple(0, 1, 2, 3, 4, 5, 6) );
        BOOST_REQUIRE( to_tuple(std::array<uint32_t, 8>({0, 1, 2, 3, 4, 5, 6, 7})) == std::make_tuple(0, 1, 2, 3, 4, 5, 6, 7));



        std::array<uint32_t, 1025> arr;
        uint32_t i = 0;
        std::generate_n( begin(arr), 1025, [&](){return i++;});

        auto t = to_tuple(arr);

        BOOST_REQUIRE(8 ==  std::get<8>(t));
        BOOST_REQUIRE(16 ==  std::get<16>(t));
        BOOST_REQUIRE(32 ==  std::get<32>(t));
        BOOST_REQUIRE(64 ==  std::get<64>(t));
        BOOST_REQUIRE(128 ==  std::get<128>(t));
        BOOST_REQUIRE(256 ==  std::get<256>(t));
        BOOST_REQUIRE(512 ==  std::get<512>(t));
        BOOST_REQUIRE(756 ==  std::get<756>(t));
        BOOST_REQUIRE(1024 ==  std::get<1024>(t));
   }

BOOST_AUTO_TEST_SUITE_END()

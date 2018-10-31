function(add_new_test test_name)
    add_executable( ${test_name}    "${CMAKE_SOURCE_DIR}/test/${test_name}.cpp")
    add_test(       ${test_name}    ${test_name} )

    set_tests_properties (  ${test_name}    PROPERTIES TIMEOUT 30   )
    target_link_libraries(  ${test_name}    ${Boost_LIBRARIES}      )
endfunction()

add_new_test(test_matrix)


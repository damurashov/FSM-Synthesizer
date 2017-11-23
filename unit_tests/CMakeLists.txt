# test_int_set
project( test_int_set )
add_executable( test_int_set test_int_set.cpp )
target_link_libraries( test_int_set int_set gtest gtest_main )

# test_position
project( test_position )
add_executable( test_position test_position.cpp )
target_link_libraries( test_position position int_set gtest gtest_main )

# test_positions_map
project( test_positions_map )
add_executable( test_positions_map test_positions_map.cpp )
target_link_libraries( test_positions_map positions_map gtest gtest_main )

# test_machine_matrix
project( test_machine_matrix )
add_executable( test_machine_matrix test_machine_matrix.cpp )
target_link_libraries( test_machine_matrix machine_matrix gtest gtest_main )

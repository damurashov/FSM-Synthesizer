cmake_minimum_required( VERSION 2.6 )
set( CMAKE_CXX_STANDARD 11 )
option( _TEST "Testing mode" OFF )

# ------------------ MAIN ------------------

add_definitions( -D_VARIADIC_MAX=10 )
add_definitions( -D_DEBUG )
add_definitions( -D_MT )
add_definitions( -D_DLL )

# int_set
add_subdirectory( int_set )
include_directories( ${int_set_SOURCE_DIR} )

# position
add_subdirectory( position )
include_directories( ${position_SOURCE_DIR} )

# positions_map
add_subdirectory( positions_map )
include_directories( ${positions_map_SOURCE_DIR} )

# machine matrix
add_subdirectory( machine_matrix )
include_directories( ${machine_matrix_SOURCE_DIR} )

# main
add_subdirectory( main )

# ------------------ TEST ------------------
if(_TEST)
    # gtest
    add_subdirectory( gtest )
    include_directories( ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include )
    # unit_tests
    add_subdirectory( unit_tests )
endif()

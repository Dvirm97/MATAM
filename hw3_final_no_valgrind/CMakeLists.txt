cmake_minimum_required(VERSION 3.9.6)
project(hw3 C)

set(CMAKE_C_STANDARD 99)
add_executable(hw3 main.c mtmflix.c user.h user.c series.h series.c mtm_ex3.h
<<<<<<< HEAD
        mtmflix.h list.h map.h set.h test_utilities.h test_utilities_2.h)
=======
        mtmflix.h list.h map.h set.h)
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
target_link_libraries(hw3 ${CMAKE_SOURCE_DIR}/libmtm.a ${CMAKE_SOURCE_DIR}/libmtm_ex3.a)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")
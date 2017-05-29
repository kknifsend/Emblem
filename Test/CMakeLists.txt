cmake_minimum_required (VERSION 3.3.2)

set(${ProjectName}_Development ON CACHE BOOL ON)
set(${ProjectName}_UnitTests OFF CACHE BOOL OFF)

if(${ProjectName}_Development)
    add_executable(Development Main.cpp)
    include_directories(${Emblem_Include_Directory})
    #target_link_libraries(Development ${ProjectName})
endif(${ProjectName}_Development)

if(${ProjectName}_UnitTests)
    set(GTEST_ROOT "" CACHE PATH "")

    find_package(GTest REQUIRED)

    add_executable(UnitTests UnitTest.cpp)
    include_directories(${Emblem_Include_Directory} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(UnitTests PRIVATE ${GTEST_BOTH_LIBRARIES})
endif(${ProjectName}_UnitTests)
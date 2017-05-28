cmake_minimum_required (VERSION 3.3.2)

set(${ProjectName}_Development ON CACHE BOOL ON)
set(${ProjectName}_UnitTests ON CACHE BOOL ON)

if(${ProjectName}_Development)
    add_executable(Development Main.cpp)
    include_directories(${Emblem_Include_Directory})
    #target_link_libraries(Development ${ProjectName})
endif(${ProjectName}_Development)

if(${ProjectName}_UnitTests)
    add_executable(UnitTests UnitTest.cpp)
    include_directories(${Emblem_Include_Directory})
    #target_link_libraries(Development ${ProjectName})
endif(${ProjectName}_UnitTests)
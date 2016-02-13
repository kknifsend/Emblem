cmake_minimum_required (VERSION 3.3.2)
set(CMAKE_SYSTEM_VERSION 8.1)

#Project settings
set(ProjectVersion "1.0.1")
set(ProjectName "Emblem")
project (${ProjectName})
set(Development ON CACHE BOOL ON)


add_subdirectory(${ProjectName})
add_subdirectory(test)
add_subdirectory(doc)
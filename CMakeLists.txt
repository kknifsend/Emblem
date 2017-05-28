cmake_minimum_required (VERSION 3.3.2)
#set(CMAKE_SYSTEM_VERSION 8.1)

#Project settings
set(ProjectVersion "1.0.5")
set(ProjectName "Emblem")
#project (${ProjectName} ${ProjectVersion})
project (${ProjectName})

add_subdirectory(Include)
add_subdirectory(Test)
add_subdirectory(Doc)
cmake_minimum_required (VERSION 3.3.2)

# Create main target
set(PUBLIC_HEADERS
	${ProjectName}/Expression.h
    ${ProjectName}/Symbol.h
)

set(INTERNAL_HEADERS
    ${ProjectName}/Internal/TermNode.h
    ${ProjectName}/Internal/UnaryOperators.h
    ${ProjectName}/Internal/BinaryOperators.h
    ${ProjectName}/Internal/BinaryTree.h
    ${ProjectName}/Internal/Derivative.h
)

add_library(${ProjectName}
    ${PUBLIC_HEADERS} 
    ${INTERNAL_HEADERS})
target_include_directories(${ProjectName} PUBLIC ./.)
source_group("Header Files\\Internal" FILES ${INTERNAL_HEADERS})
set_target_properties(${ProjectName} PROPERTIES LINKER_LANGUAGE CXX)

set(Emblem_Include_Directory ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
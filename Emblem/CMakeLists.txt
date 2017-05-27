cmake_minimum_required (VERSION 3.3.2)

set(PUBLIC_HEADERS
	Expression.h
    Symbol.h
)

set(INTERNAL_HEADERS
    Internal/TermNode.h
    Internal/UnaryOperators.h
    Internal/BinaryOperators.h
    Internal/BinaryTree.h
)

add_library(${ProjectName} 
	${PUBLIC_HEADERS} 
	${INTERNAL_HEADERS}
)
include_directories(../.)
set_target_properties(${ProjectName} PROPERTIES LINKER_LANGUAGE CXX)

set(HEADER_STR "Header Files")
source_group("${HEADER_STR}\\Internal" FILES ${INTERNAL_HEADERS})


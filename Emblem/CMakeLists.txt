cmake_minimum_required (VERSION 3.3.2)

set(PUBLIC_HEADERS
	Expression.h
)

set(INTERNAL_HEADERS
	Internal/ExpressionTree.h
	Internal/ExpressionData.h
	Internal/Types.h
)

set(MATH_HEADERS
	Internal/Math/ExpressionBase.h
	Internal/Math/ArithmeticExpressions.h
)

set(COLLECTION_HEADERS
	Internal/Collection/BinaryTree.h
	Internal/Collection/IfcPack.h
	Internal/Collection/Queue.h
	Internal/Collection/Stack.h
	Internal/Collection/TupleVector.h
)

set(ITERATOR_HEADERS
	Internal/Collection/Iterator/IteratorBinaryTree.h
	Internal/Collection/Iterator/IteratorInOrder.h
	Internal/Collection/Iterator/IteratorPostOrder.h
	Internal/Collection/Iterator/IteratorPreOrder.h
)

add_library(${ProjectName} 
	${PUBLIC_HEADERS} 
	${INTERNAL_HEADERS}
	${MATH_HEADERS}
	${COLLECTION_HEADERS}
	${ITERATOR_HEADERS}
)
include_directories(../.)
set_target_properties(${ProjectName} PROPERTIES LINKER_LANGUAGE CXX)

set(HEADER_STR "Header Files")
source_group("${HEADER_STR}\\Internal" FILES ${INTERNAL_HEADERS})

source_group("${HEADER_STR}\\Internal\\Math" FILES ${MATH_HEADERS})
source_group("${HEADER_STR}\\Internal\\Collection" FILES ${COLLECTION_HEADERS})
source_group("${HEADER_STR}\\Internal\\Collection\\Iterator" FILES ${ITERATOR_HEADERS})

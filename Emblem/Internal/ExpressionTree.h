/**
* \file ExpressionTree.h

* Copyright (c) 2016, Kevin Knifsend, https://nullbreak.wordpress.com/

* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.

* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

#include "Emblem/Internal/Collection/BinaryTree.h"
#include "Emblem/Internal/Collection/Stack.h"
#include "Emblem\Internal\ExpressionData.h"
#include "Emblem/Internal/Math/ExpressionBase.h"

#include "Emblem/Internal/Types.h"


namespace Emblem
{

///////////////////////////////////////////////////////////////////////

/**
* \class ExpressionTree
* \brief Tree structure used to manage expressions.
* \tparam T Type of evaluation in expression.
* \tparam SYMBOL_KEY Type of symbol in expression.
*/
template <class T, class SYMBOL_KEY, class ALLOC = std::allocator<T>>
class ExpressionTree
{
	struct Types
	{
		typedef T ValueType;
		typedef ALLOC ValueAllocator;
		typedef SYMBOL_KEY SymbolType;
		typedef Math::ExpressionBase<T> ExpressionType;
		typedef ValueMap<SYMBOL_KEY, T> ValueMap;
		typedef typename Math::ExpressionBase<T>::Parameters Parameters;
	};
	typedef ExpressionData<Types> ExpressionData;
	typedef typename ExpressionData::Type Type;
	typedef typename ExpressionData::TypedIndex TypedIndex;
	typedef Collection::BinaryTree<TypedIndex> BinaryTree;
public:
	typedef T ValueType;
	typedef SYMBOL_KEY SymbolType;
	typedef typename Math::ExpressionBase<T> ExpressionType;

	/** \brief Mapping of variables to their values. */
	typedef typename Types::ValueMap ValueMap;
	typedef typename Types::Parameters Parameters;

	/** \copydoc Expression::evaluate() */
	T evaluate(const ValueMap& rValueMap) const;

	/** \copydoc Expression::substitute() */
	template <class U>
	void substitute(const SYMBOL_KEY& rSymbol, const U& rU);

	/** \brief Deletes expression tree. */
	void clear();

	/** \brief Adds expression to right of tree at head. */
	template <class EXPR, class U>
	void addExpressionLeft(const U&);

	/** \brief Adds expression to left of tree at head. */
	template <class EXPR, class U>
	void addExpressionRight(const U&);

	template <class EXPR, class LEFT, class RIGHT>
	static ExpressionTree Init(const LEFT&, const RIGHT&);

	template <class EXPR, class LEFT>
	static ExpressionTree Init(const LEFT&);

	template <class U>
	static ExpressionTree Init(const U&);

private:
	template <class U>
	void addLeft(const U& rU)
	{
		using Emblem::Collection::InsertDirection; 
		const ExpressionData::TypedIndex index = mExpressionData.insert(rU);
		mBinaryTree.insert<InsertDirection::LEFT>(
			mBinaryTree.head(), index);
	}

	template <>
	void addLeft<ExpressionTree>(const ExpressionTree& rTree)
	{
		using Emblem::Collection::InsertDirection;
		const auto newIndex = mBinaryTree.insert<InsertDirection::LEFT>(
			mBinaryTree.head(), rTree.mBinaryTree);

		const size_t offsets[3] =
		{
			mExpressionData.size<Math::ExpressionBase<T>>(),
			mExpressionData.size<T>(),
			mExpressionData.size<SYMBOL_KEY>()
		};

		mExpressionData.concatenate<Math::ExpressionBase<T>>(rTree.mExpressionData);
		mExpressionData.concatenate<T>(rTree.mExpressionData);
		mExpressionData.concatenate<SYMBOL_KEY>(rTree.mExpressionData);

		auto begin = mBinaryTree.beginIn(newIndex);
		auto end = mBinaryTree.end();
		while (begin != end)
		{
			auto& rTypedIndex = *begin;
			rTypedIndex.mIndex += (uint32_t)offsets[rTypedIndex.mType];
			++begin;
		}
	}

	template <class U>
	void addRight(const U& rU)
	{
		using Emblem::Collection::InsertDirection;
		const TypedIndex index = mExpressionData.insert(rU);
		mBinaryTree.insert<InsertDirection::RIGHT>(
			mBinaryTree.head(), index);
	}

	template <>
	void addRight<ExpressionTree>(const ExpressionTree& rTree)
	{
		using Emblem::Collection::InsertDirection;
		const auto newIndex = mBinaryTree.insert<InsertDirection::RIGHT>(
						mBinaryTree.head(), rTree.mBinaryTree);

		const size_t offsets[3] =
		{
			mExpressionData.size<Math::ExpressionBase<T>>(),
			mExpressionData.size<T>(),
			mExpressionData.size<SYMBOL_KEY>()
		};

		mExpressionData.concatenate<Math::ExpressionBase<T>>(rTree.mExpressionData);
		mExpressionData.concatenate<T>(rTree.mExpressionData);
		mExpressionData.concatenate<SYMBOL_KEY>(rTree.mExpressionData);

		auto begin = mBinaryTree.beginIn(newIndex);
		auto end = mBinaryTree.end();
		while (begin != end)
		{
			auto& rTypedIndex = *begin;
			rTypedIndex.mIndex += (uint32_t)offsets[rTypedIndex.mType];
			++begin;
		}
	}

	template <class T> static Type GetType() { return Type::EXPRESSION; }
	template <> static Type GetType<SYMBOL_KEY>() { return Type::SYMBOL; }
	template <> static Type GetType<T>() { return Type::CONSTANT; }


	template <class T, class SYMBOL_KEY, class ALLOC>
	friend std::ostream& operator<<(std::ostream&, const ExpressionTree<T, SYMBOL_KEY, ALLOC>&);

	static void OutputLeaf(const ExpressionTree<T, SYMBOL_KEY, ALLOC>& rTree,
		typename ExpressionTree<T, SYMBOL_KEY, ALLOC>::BinaryTree::IndexType index,
		std::ostringstream& rOut);

	Collection::BinaryTree<TypedIndex> mBinaryTree;
	ExpressionData mExpressionData;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////// Construction ////////////////////////////
///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class EXPR, class LEFT, class RIGHT>
typename ExpressionTree<T, SYMBOL_KEY, ALLOC> ExpressionTree<T, SYMBOL_KEY, ALLOC>::Init(const LEFT& rLeft, const RIGHT& rRight)
{
	ExpressionTree expr;
	auto& rBinaryTree = expr.mBinaryTree;

	const TypedIndex expressionIndex = expr.mExpressionData.insert((Math::ExpressionBase<T>)EXPR());
	rBinaryTree.insertToHead(expressionIndex);
	expr.addLeft(rLeft);
	expr.addRight(rRight);

	return expr;
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class EXPR, class LEFT>
typename ExpressionTree<T, SYMBOL_KEY, ALLOC> ExpressionTree<T, SYMBOL_KEY, ALLOC>::Init(const LEFT& rLeft)
{
	ExpressionTree expr;
	auto& rBinaryTree = expr.mBinaryTree;

	const TypedIndex expressionIndex = expr.mExpressionData.insert((Math::ExpressionBase<T>)EXPR());
	rBinaryTree.insertToHead(expressionIndex);
	expr.addLeft(rLeft);
	
	return expr;
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class U>
typename ExpressionTree<T, SYMBOL_KEY, ALLOC> ExpressionTree<T, SYMBOL_KEY, ALLOC>::Init(const U& rA)
{
	ExpressionTree expr;
	auto& rBinaryTree = expr.mBinaryTree;
	expr.addLeft(rA);
	return expr;
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class EXPR, class U>
void ExpressionTree<T, SYMBOL_KEY, ALLOC>::addExpressionLeft(const U& rA)
{
	const TypedIndex expressionIndex = mExpressionData.insert((Math::ExpressionBase<T>)EXPR());
	mBinaryTree.insertToHead(expressionIndex);
	addLeft(rA);
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class EXPR, class U>
void ExpressionTree<T, SYMBOL_KEY, ALLOC>::addExpressionRight(const U& rA)
{
	const TypedIndex expressionIndex = mExpressionData.insert((Math::ExpressionBase<T>)EXPR());
	mBinaryTree.insertToHead(expressionIndex);
	addRight(rA);
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
T ExpressionTree<T, SYMBOL_KEY, ALLOC>::evaluate(const ValueMap& rValueMap) const
{
	if (mBinaryTree.head() == BinaryTree::INVALID_INDEX)
	{
		return (T)0;
	}

	Math::ExpressionBase<T>::Parameters parameters;
	auto curIter = mBinaryTree.beginPost();
	auto endIter = mBinaryTree.end();
	while (curIter != endIter)
	{
		if (mBinaryTree.isLeaf(curIter))
		{
			if (!mExpressionData.append(*curIter, rValueMap, parameters))
			{
				// rValueMap was not populated by all the symbols expected by the tree.
				assert(0);
			}
		}
		else
		{
			T result;
			if (!mExpressionData.evaluate(*curIter, parameters, result))
			{
				assert(0);
			}

			parameters.push(result);
		}
		++curIter;
	}

	return parameters.top();
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
template <class U>
void ExpressionTree<T, SYMBOL_KEY, ALLOC>::substitute(const SYMBOL_KEY& rSymbol, const U& rU)
{
	auto curIter = postOrderBegin();
	auto endIter = end();

	while (curIter != endIter)
	{
		if (curIter->isOfType(Node::EXPRESSION))
		{
			auto pChildLeft = curIter->left();
			auto pChildRight = curIter->right();

			if (pChildLeft != nullptr)
			{
				if (pChildLeft->isOfType(Node::SYMBOL))
				{
					SymbolNode* pLeftSymbol = (SymbolNode*)pChildLeft;
					if (pLeftSymbol->mSymbol == rSymbol)
					{
						delete pLeftSymbol;
						curIter->left() = Node::CreateNode(rU);
					}
				}
			}

			if (pChildRight != nullptr)
			{
				if (pChildRight->isOfType(Node::SYMBOL))
				{
					SymbolNode* pRightSymbol = (SymbolNode*)pChildRight;
					if (pRightSymbol->mSymbol == rSymbol)
					{
						delete pRightSymbol;
						curIter->right() = Node::CreateNode(rU);
					}
				}
			}
		}
		++curIter;
	}
}


///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
void ExpressionTree<T, SYMBOL_KEY, ALLOC>::clear()
{
	mBinaryTree.clear();
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
void ExpressionTree<T, SYMBOL_KEY, ALLOC>::OutputLeaf(
	const ExpressionTree<T, SYMBOL_KEY, ALLOC>& rTree,
	typename ExpressionTree<T, SYMBOL_KEY, ALLOC>::BinaryTree::IndexType index,
	std::ostringstream& rOut)
{
	const auto typedIndex = rTree.mBinaryTree.get(index);
	if (typedIndex.mType == ExpressionTree::ExpressionData::Type::CONSTANT)
	{
		const T& rConstant = rTree.mExpressionData.at<T>(typedIndex.mIndex);
		rOut << rConstant;
	}
	else
	{
		const SYMBOL_KEY& rSymbol = rTree.mExpressionData.at<SYMBOL_KEY>(typedIndex.mIndex);
		::operator<<(rOut, rSymbol);
	}
}

///////////////////////////////////////////////////////////////////////

template <class T, class SYMBOL_KEY, class ALLOC>
std::ostream& operator<<(std::ostream& rOut,
	const ExpressionTree<T, SYMBOL_KEY, ALLOC>& rTree)
{
	typedef ExpressionTree<T, SYMBOL_KEY, ALLOC> ExpressionTree;
	if (rTree.mBinaryTree.head() == ExpressionTree::BinaryTree::INVALID_INDEX)
	{
		return rOut;
	}

	auto itInOrder = rTree.mBinaryTree.beginIn();
	auto end = rTree.mBinaryTree.end();

	size_t parensCount = 0;

	std::ostringstream sout("");
	while (itInOrder != end)
	{
		if (rTree.mBinaryTree.isLeaf(itInOrder))
		{
			if (parensCount == 0)
			{
				sout << '(';
				parensCount++;
				ExpressionTree::OutputLeaf(rTree, itInOrder, sout);
			}
			else
			{
				ExpressionTree::OutputLeaf(rTree, itInOrder, sout);
				sout << ')';
				parensCount--;
			}	
		}
		else
		{
			const ExpressionTree::ExpressionType& rExpression = rTree.mExpressionData.at<ExpressionTree::ExpressionType>(itInOrder->mIndex);
			
			if (rExpression.isUnary())
			{
				std::string temp = sout.str();
				sout.str("");
				sout << rExpression.toString() << '(' << temp << ')';
			}
			else
			{
				sout << rExpression.toString();
			}
		}
		++itInOrder;
	}

	rOut << sout.str();

	return rOut;
}

///////////////////////////////////////////////////////////////////////

}

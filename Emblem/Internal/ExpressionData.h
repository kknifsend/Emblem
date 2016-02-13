/**
* \file ExpressionData.h

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

#include "Emblem\Internal\Collection\TupleVector.h"
#include "Emblem\Internal\Types.h"
#include "Emblem\Internal\Math\ExpressionBase.h"


namespace Emblem
{

///////////////////////////////////////////////////////////////////////
/**
* \class ExpressionData
* \brief Data stored by expression.
*/
template <class TYPES>
class ExpressionData 
	: public Collection::TupleVector<
		Collection::SmartType<typename TYPES::ValueType, typename TYPES::ValueAllocator>,
		Collection::SmartType<typename TYPES::ExpressionType>,
		Collection::SmartType<typename TYPES::SymbolType>
	>
{
public:
	enum Type { EXPRESSION = 0, CONSTANT, SYMBOL };
	struct TypedIndex
	{
		Type mType;
		uint32_t mIndex;
	};

	template <class U>
	TypedIndex insert(const U& rU);

	bool evaluate(const TypedIndex& rTypedIndex, 
		typename TYPES::Parameters& rParams, 
		typename TYPES::ValueType& rResult) const;

	bool append(const TypedIndex& rTypedIndex,
		typename const TYPES::ValueMap& rValueMap,
		typename TYPES::Parameters& rValues) const;


private:
	template <class U> static Type GetType() { return Type::EXPRESSION; }
	template <> static Type GetType<typename TYPES::SymbolType>() { return Type::SYMBOL; }
	template <> static Type GetType<typename TYPES::ValueType>() { return Type::CONSTANT; }
};

///////////////////////////////////////////////////////////////////////

template <class TYPES>
template <class U>
typename ExpressionData<TYPES>::TypedIndex
	ExpressionData<TYPES>::insert(const U& rU)
{
	const uint32_t index = (uint32_t)size<U>();
	const TypedIndex ti = { ExpressionData::GetType<U>(), index };
	push_back<U>(rU);
	return ti;
}

///////////////////////////////////////////////////////////////////////

template <class TYPES>
bool ExpressionData<TYPES>::append(const TypedIndex& rTypedIndex,
	typename const TYPES::ValueMap& rValueMap,
	typename TYPES::Parameters& rValues) const
{
	switch (rTypedIndex.mType)
	{
	case Type::SYMBOL:
	{
		const auto& rSymbol = at<TYPES::SymbolType>(rTypedIndex.mIndex);
		const auto findPos = rValueMap.find(rSymbol);
		if (findPos == rValueMap.end())
		{
			return false;
		}

		rValues.push(findPos->second);
		return true;
	}
	case Type::CONSTANT:
	{
		rValues.push(at<TYPES::ValueType>(rTypedIndex.mIndex));
		return true;
	}
	default:;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////

template <class TYPES>
bool ExpressionData<TYPES>::evaluate(
	const TypedIndex& rTypedIndex,
	typename TYPES::Parameters& rParams,
	typename TYPES::ValueType& rResult) const
{
	switch (rTypedIndex.mType)
	{
	case Type::EXPRESSION:
	{
		const auto& rExpression = at<TYPES::ExpressionType>(rTypedIndex.mIndex);
		const size_t numOfParams = rParams.size();
		const size_t expectedNumOfParams = rExpression.isUnary() ? 1 : 2;

		if (numOfParams < expectedNumOfParams)
		{
			return false;
		}

		rResult = rExpression(rParams);

		return true;
	}
	default:;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////

}

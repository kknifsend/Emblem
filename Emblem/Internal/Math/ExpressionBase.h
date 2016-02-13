/**
* \file ExpressionBase.h

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

#include <string>

#include "Emblem/Internal/Collection/Stack.h"
#include "Emblem/Internal/Types.h"

namespace Emblem
{
namespace Math
{

///////////////////////////////////////////////////////////////////////

/**
* \class ExpressionBase
* \brief Defines an expression which takes input, and returns output
* \tparam T Input/Output type of expression.
*/
template<class T>
class ExpressionBase
{
public:
	/** \typedef Parameters defining the supplied input. */
	typedef Parameters<T> Parameters;


	/** \typedef Used for evaluation of function.	*/
	typedef T(*Function)(Parameters& rParameters);


	/** \typedef Used for string representation of expression. */
	typedef std::string&(*FunctionToString)();

	ExpressionBase(const Function& rFunc, const FunctionToString& rToString, bool isUnary)
		: mFunction(rFunc), mToString(rToString), mIsUnary(isUnary) { }

	/** \brief Indicates whether wrapped function is unary or binary. */
	bool isUnary() const
	{
		return mIsUnary;
	}

	/** \brief Indicates whether wrapped function is unary or binary. */
	T operator()(Parameters& rParams) const
	{
		return mFunction(rParams);
	}

	/** \brief Create string representation of expression. */
	std::string& toString() const
	{
		return mToString();
	}

private:
	bool mIsUnary;
	Function mFunction;
	FunctionToString mToString;
};

///////////////////////////////////////////////////////////////////////

}
}
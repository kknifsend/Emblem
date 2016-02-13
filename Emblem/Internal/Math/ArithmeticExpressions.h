/**
* \file ArithmeticExpressions.h

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

#include "Emblem/Internal/Math/ExpressionBase.h"

namespace Emblem
{
namespace Math
{

///////////////////////////////////////////////////////////////////////

template <class T,
	typename ExpressionBase<T>::Function EXPRESSION,
	typename ExpressionBase<T>::FunctionToString TO_STRING,
	bool IS_UNARY>
class TemplateExpression : public ExpressionBase<T>
{
public:
	TemplateExpression()
		: ExpressionBase(EXPRESSION, TO_STRING, IS_UNARY)
	{ }
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Sin
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return sin(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Sin";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Csc
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return 1.0 / sin(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Csc";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Cos
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return cos(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Cos";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Sec
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return 1.0 / cos(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Sec";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Tan
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return tan(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Tan";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Cot
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return 1.0 / tan(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Cot";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Exp
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return exp(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Exp";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Log
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return log10(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Log";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Ln
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();
		return log(param1);
	}

	static std::string& ToString()
	{
		static std::string str = "Ln";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Pow
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param2 = rParams.top();
		rParams.pop();
		const T param1 = rParams.top();
		rParams.pop();

		return pow(param1, param2);
	}

	static std::string& ToString()
	{
		static std::string str = "^";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Add
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param2 = rParams.top();
		rParams.pop();
		const T param1 = rParams.top();
		rParams.pop();

		return param1 + param2;
	}

	static std::string& ToString()
	{
		static std::string str = "+";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Sub
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param2 = rParams.top();
		rParams.pop();
		const T param1 = rParams.top();
		rParams.pop();

		return param1 - param2;
	}

	static std::string& ToString()
	{
		static std::string str = "-";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Mul
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param2 = rParams.top();
		rParams.pop();
		const T param1 = rParams.top();
		rParams.pop();

		return param1 * param2;
	}

	static std::string& ToString()
	{
		static std::string str = "*";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Div
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param2 = rParams.top();
		rParams.pop();
		const T param1 = rParams.top();
		rParams.pop();

		return param1 / param2;
	}

	static std::string& ToString()
	{
		static std::string str = "/";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T>
struct Identity
{
	static T Eval(typename ExpressionBase<T>::Parameters& rParams)
	{
		const T param1 = rParams.top();
		rParams.pop();

		return param1;
	}

	static std::string& ToString()
	{
		static std::string str = "";
		return str;
	}
};

///////////////////////////////////////////////////////////////////////

template <class T> using ExpressionAdd = TemplateExpression<T, Add<T>::Eval, Add<T>::ToString, false>;
template <class T> using ExpressionSub = TemplateExpression<T, Sub<T>::Eval, Sub<T>::ToString, false>;
template <class T> using ExpressionMul = TemplateExpression<T, Mul<T>::Eval, Mul<T>::ToString, false>;
template <class T> using ExpressionDiv = TemplateExpression<T, Div<T>::Eval, Div<T>::ToString, false>;

template <class T> using ExpressionSin = TemplateExpression<T, Sin<T>::Eval, Sin<T>::ToString, true>;
template <class T> using ExpressionCos = TemplateExpression<T, Cos<T>::Eval, Cos<T>::ToString, true>;
template <class T> using ExpressionTan = TemplateExpression<T, Tan<T>::Eval, Tan<T>::ToString, true>;

template <class T> using ExpressionCsc = TemplateExpression<T, Csc<T>::Eval, Csc<T>::ToString, true>;
template <class T> using ExpressionSec = TemplateExpression<T, Sec<T>::Eval, Sec<T>::ToString, true>;
template <class T> using ExpressionCot = TemplateExpression<T, Cot<T>::Eval, Cot<T>::ToString, true>;

template <class T> using ExpressionLog = TemplateExpression<T, Log<T>::Eval, Log<T>::ToString, true>;
template <class T> using ExpressionLn = TemplateExpression<T, Ln<T>::Eval, Ln<T>::ToString, true>;
template <class T> using ExpressionExp = TemplateExpression<T, Exp<T>::Eval, Exp<T>::ToString, true>;
template <class T> using ExpressionPow = TemplateExpression<T, Pow<T>::Eval, Pow<T>::ToString, false>;

template <class T> using ExpressionIdentity = TemplateExpression<T, Identity<T>::Eval, Identity<T>::ToString, true>;

///////////////////////////////////////////////////////////////////////

}
}

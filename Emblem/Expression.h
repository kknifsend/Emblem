/**
* \file Expression.h

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
#include <iostream>

#include "Emblem/Internal/ExpressionTree.h"
#include "Emblem/Internal/Math/ArithmeticExpressions.h"


///////////////////////////////////////////////////////////////////////

/**
* \namespace Emblem
*/
namespace Emblem
{
	template <class T, class ALLOC> class Expression;
	template <class T> class Symbol;
}

template <class T, class ALLOC>
std::ostream& operator<<(std::ostream&, const Emblem::Expression<T, ALLOC>&);

template <class T>
std::ostream& operator<<(std::ostream& rOut, const Emblem::Symbol<T>&);

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> sin(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> cos(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> tan(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> exp(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> log(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> log10(const Emblem::Expression<T, ALLOC>& rTree);
template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> pow(const Emblem::Expression<T, ALLOC>& rTree);

///////////////////////////////////////////////////////////////////////

namespace Emblem
{

/** 
* \class Expression
* \brief Defines mathmatical expressions as a combination of variables, and constants.
* \tparam T Type of evaluation in expression.
*/
template <class T, class ALLOC = std::allocator<T>>
class Expression
{   
    typedef ExpressionTree<T, Symbol<T>, ALLOC> ExpressionTree;
public:
	/** \brief Mapping of variables to their values. */
    typedef typename ExpressionTree::ValueMap ValueMap;

	Expression() {}
    Expression(const Symbol<T>& rSymbol);
    Expression(const T& rConstant);

	/**
	* \brief Function used to evaluate an expression given mapping of values.
	*
	* If expression is empty, returns 0. 
	*
	* If the value map is not populated by all the symbols expected by the expression,
	* an assertion is triggered.
	* \return Returns the result of the expression evaluation.
	*/
    T evaluate(const ValueMap& rValues) const;

	/**
	* \brief Substitutes the supplied expression for the given symbol
	* 
	* Replaces all instances of the given symbol with the supplied expression, constant, or symbol.
	*/
	void substitute(const Symbol<T>& rSymbol, const Expression& rExpr)
	{
		mTree.substitute(rSymbol, rExpr.mTree);
	}

	/** @copydoc substitute()*/
	void substitute(const Symbol<T>& rSymbol, const T& rConstant)
	{
		mTree.substitute(rSymbol, rConstant);
	}

	/** @copydoc substitute()*/
	void substitute(const Symbol<T>& rSymbol, const Symbol<T>& rSubs)
	{
		mTree.substitute(rSymbol, rSubs);
	}


	/**
	*/
	Expression derivative(const Symbol<T>&) const;


    // Operators
    Expression operator+(const Symbol<T>& rB) const
    {
        return appendRight<Math::ExpressionAdd<T> >(rB);
    }

    Expression operator-(const Symbol<T>& rB) const
    {
        return appendRight<Math::ExpressionSub<T> >(rB);
    }

    Expression operator*(const Symbol<T>& rB) const
    {
        return appendRight<Math::ExpressionMul<T> >(rB);
    }
    
    Expression operator/(const Symbol<T>& rB) const
    {
        return appendRight<Math::ExpressionDiv<T> >(rB);
    }

    Expression operator+(const Expression& rB) const
    {
        return appendRight<Math::ExpressionAdd<T> >(rB.mTree);
    }

    Expression operator-(const Expression& rB) const
    {
        return appendRight<Math::ExpressionSub<T> >(rB.mTree);
    }

    Expression operator*(const Expression& rB) const
    {
        return appendRight<Math::ExpressionMul<T> >(rB.mTree);
    }

    Expression operator/(const Expression& rB) const
    {
        return appendRight<Math::ExpressionDiv<T> >(rB.mTree);
    }

    // Assignment math operators
    template <class U>
    Expression& operator+=(const U& rB)
    {
        return appendRightInPlace<Math::ExpressionAdd<T> >(rB);
    }

    template <class U>
    Expression& operator-=(const U& rB)
    {
        return appendRightInPlace<Math::ExpressionSub<T> >(rB);
    }

    template <class U>
    Expression& operator*=(const U& rB)
    {
        return appendRightInPlace<Math::ExpressionMul<T> >(rB);
    }

    template <class U>
    Expression& operator/=(const U& rB)
    {
        return appendRightInPlace<Math::ExpressionDiv<T> >(rB);
    }

    template <>
    Expression& operator+=<Expression>(const Expression& rB)
    {
        return appendRightInPlace<Math::ExpressionAdd<T> >(rB.mTree);
    }

    template <>
    Expression& operator-=<Expression>(const Expression& rB)
    {
        return appendRightInPlace<Math::ExpressionSub<T> >(rB.mTree);
    }

    template <>
    Expression& operator*=<Expression>(const Expression& rB)
    {
        return appendRightInPlace<Math::ExpressionMul<T> >(rB.mTree);
    }

    template <>
    Expression& operator/=<Expression>(const Expression& rB)
    {
        return appendRightInPlace<Math::ExpressionDiv<T> >(rB.mTree);
    }

    Expression operator-() const
    {
        return Expression::CreateRoot<Math::ExpressionMul<T> >(*this, -1);
    }

private:
	// Tree construction functions
	template <class EXPR, class LEFT, class RIGHT>
	static Expression CreateRoot(const LEFT& rLeft, const RIGHT& rRight)
	{
		Expression expr;
		expr.mTree = ExpressionTree::Init<EXPR>(rLeft, rRight);
		return expr;
	}

	template <class EXPR, class U>
	static Expression CreateRoot(const U& rU)
	{
		Expression expr;
		expr.mTree = ExpressionTree::Init<EXPR>(rU);
		return expr;
	}

	template <class EXPR, class U>
	Expression appendRight(const U& rParam) const
	{
		Expression expression = *this;
		expression.mTree.addExpressionRight<EXPR>(rParam);
		return expression;
	}

	template <class EXPR, class U>
	Expression& appendRightInPlace(const U& rParam)
	{
		mTree.addExpressionRight<EXPR>(rParam);
		return *this;
	}

	template <class EXPR, class U>
	Expression appendLeft(const U& rParam1) const
	{
		Expression expression = *this;
		expression.mTree.addExpressionLeft<EXPR>(rParam1);
		return expression;
	}

	// Friendship declarations
	friend class Symbol<T>;

	//! @cond
    template <class T, class ALLOC>
    friend std::ostream& (::operator<<)(std::ostream&, const Emblem::Expression<T, ALLOC>&);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::sin)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::cos)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::tan)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::exp)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::log)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::log10)(const Emblem::Expression<T, ALLOC>& rTree);
    template <class T, class ALLOC>
    friend Emblem::Expression<T, ALLOC> (::pow)(const Emblem::Expression<T, ALLOC>& rTree);
	//! @endcond

	ExpressionTree mTree;
};

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Expression<T, ALLOC>::Expression(const Symbol<T>& rSymbol)
{
	mTree = ExpressionTree::Init(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Expression<T, ALLOC>::Expression(const T& rConstant)
{
	mTree = ExpressionTree::Init(rConstant);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
T Expression<T, ALLOC>::evaluate(const ValueMap& rValues) const
{
    return mTree.evaluate(rValues);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Expression<T, ALLOC> Expression<T, ALLOC>::derivative(const Symbol<T>& rVar) const
{
	Expression<T> deriv;

	return deriv;
}

///////////////////////////////////////////////////////////////////////

/** 
* \class Symbol
* \brief Defines a variable in of an expression.
* \tparam T Type of associated expression. 
*/
template <class T>
class Symbol
{
public:
    Symbol(const char* const pStr)
        : mString(pStr) {}

    bool operator<(const Symbol& rB) const
    {
        return mString < rB.mString;
    }

    bool operator==(const Symbol& rB) const
    {
        return mString == rB.mString;
    }

    template <class U>
	typename Expression<T> operator+(const U& rU) const
    {
        return Expression<T>::CreateRoot<Math::ExpressionAdd<T> >(*this, rU);
    }

    template <class U>
	typename Expression<T> operator-(const U& rU) const
    {
        return Expression<T>::CreateRoot<Math::ExpressionSub<T> >(*this, rU);
    }
    
    template <class U>
	typename Expression<T> operator*(const U& rU) const
    {
        return Expression<T>::CreateRoot<Math::ExpressionMul<T> >(*this, rU);
    }

    template <class U>
	typename Expression<T> operator/(const U& rU) const
    {
        return Expression<T>::CreateRoot<Math::ExpressionDiv<T> >(*this, rU);
    }

    typename Expression<T> operator-() const
    {
        return Expression<T>::CreateRoot<Math::ExpressionMul<T> >(*this, -1);
    }

private:
	template <class T>
	friend std::ostream& (::operator<<)(std::ostream& rOut, const Symbol<T>&);

	std::string mString;
};
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> sin(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionSin<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> cos(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionCos<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> tan(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionTan<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> exp(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionExp<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> log(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionLn<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> log10(const Emblem::Symbol<T>& rSymbol)
{
	return Expression<T>::CreateRoot<Emblem::Math::ExpressionLog<T> >(rSymbol);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> pow(const Emblem::Symbol<T>& rSymbol)
{
	return Emblem::Expression<T>::CreateRoot(Emblem::Math::ExpressionPow<T> > (rSymbol));
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> sin(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionSin<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> csc(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionCsc<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> cos(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionCos<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> tan(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionTan<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> exp(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionExp<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> log(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionLn<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> log10(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionLog<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> pow(const Emblem::Expression<T, ALLOC>& rTree)
{
	return Emblem::Expression<T, ALLOC>::CreateRoot<Emblem::Math::ExpressionPow<T> >(rTree.mTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator+(const T& rB, const Emblem::Expression<T, ALLOC>& rExpr)
{
	return rExpr.appendLeft<Emblem::Math::ExpressionAdd<T> >(rB);
}

/////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator-(const T& rB, const Emblem::Expression<T, ALLOC>& rExpr)
{
	return rExpr.appendLeft<Emblem::Math::ExpressionSub<T> >(rB);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator*(const T& rB, const Emblem::Expression<T, ALLOC>& rExpr)
{
	return rExpr.appendLeft<Emblem::Math::ExpressionMul<T> >(rB);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator/(const T& rB, const Emblem::Expression<T, ALLOC>& rExpr)
{
	return rExpr.appendLeft<Emblem::Math::ExpressionDiv<T> >(rB);
}

/////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator+(const Emblem::Expression<T, ALLOC>& rExpr, const T& rB)
{
	return rExpr.appendRight<Emblem::Math::ExpressionAdd<T> >(rB);
}

/////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator-(const Emblem::Expression<T, ALLOC>& rExpr, const T& rB)
{
	return rExpr.appendRight<Emblem::Math::ExpressionSub<T> >(rB);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator*(const Emblem::Expression<T, ALLOC>& rExpr, const T& rB)
{
	return rExpr.appendRight<Emblem::Math::ExpressionMul<T> >(rB);
}

///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
Emblem::Expression<T, ALLOC> operator/(const Emblem::Expression<T, ALLOC>& rExpr, const T& rB)
{
	return rExpr.appendRight<Emblem::Math::ExpressionDiv<T> >(rB);
}


///////////////////////////////////////////////////////////////////////

template <class T, class ALLOC>
std::ostream& operator<<(std::ostream& rOut, const Emblem::Expression<T, ALLOC>& rExpression)
{
	rOut << rExpression.mTree;
	return rOut;
}

///////////////////////////////////////////////////////////////////////

template <class T>
std::ostream& operator<<(std::ostream& rOut, const Emblem::Symbol<T>& rSymbol)
{
	rOut << rSymbol.mString;
	return rOut;
}


///////////////////////////////////////////////////////////////////////

/** \mainpage Emblem
*
* \section Introduction
* Emblem is a library aimed at implementing symbolic computation of 
* a mathematical expression within a templated C++ framework. 
* Expressions are implemented via a binary expression tree.
* Expressions strictly define a single function, but can be grouped
* using a 3rd party matrix class, or array to provide vector 
* function functionality.
*/
/**
* \file Symbol.h

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

#include "Expression.h"

#include <string>
#include <iostream>
#include <cstdint>
#include <functional>

///////////////////////////////////////////////////////////////////////
namespace Emblem
{
template <class T, class Alloc> class Symbol;
}

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Symbol<T, Alloc>& rA);

template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(const Emblem::Symbol<T, Alloc>& rA);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(const Emblem::Symbol<T, Alloc>& rA);

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB);

template <class T, class Alloc>
std::ostream& operator<<(std::ostream& rOut, const Emblem::Symbol<T, Alloc>&);

/** \namespace Emblem */
namespace Emblem
{
/**
* \class Symbol
* \brief Defines a variable in of an expression.
* \tparam T Type of associated expression.
*/
template <class T, class Alloc = std::allocator<T>>
class Symbol
{
    typedef Internal::BinaryOperator<T> BinaryOperator;
    typedef Internal::UnaryOperator<T> UnaryOperator;
    typedef Expression<T, Alloc> Expression;
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

    const std::string& toString() const
    {
        return mString;
    }

    operator const std::string& () const
    {
        return mString;
    }


    Expression operator+(const Expression& rB) const
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
                                    rB.mExpressionTree.clone());
    }

    Expression operator-(const Expression& rB) const
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
                                    rB.mExpressionTree.clone());
    }

    Expression operator*(const Expression& rB) const
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
                                    rB.mExpressionTree.clone());
    }

    Expression operator/(const Expression& rB) const
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
                                    rB.mExpressionTree.clone());
    }

    Expression operator+(Expression&& rB)
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
                                    rB.mExpressionTree);
    }

    Expression operator-(Expression&& rB)
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
                                    rB.mExpressionTree);
    }

    Expression operator*(Expression&& rB)
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
                                    rB.mExpressionTree);
    }

    Expression operator/(Expression&& rB)
    {
        Expression exprA(*this);
        return Expression::BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
                                    rB.mExpressionTree);
    }

    Expression operator-() const
    {
        Expression exprA(*this);
        return Expression::UnaryOp(exprA.mExpressionTree, UnaryOperator::Negate);
    }

private:
    friend std::ostream& (::operator<<)(std::ostream& rOut, const Symbol<T, Alloc>&);

    friend Emblem::Expression<T, Alloc> (::sin)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc> (::cos)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc> (::tan)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc>(::abs)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc>(::exp)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc>(::log)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc>(::log10)(const Emblem::Symbol<T, Alloc>& rA);
    friend Emblem::Expression<T, Alloc>(::sqrt)(const Emblem::Symbol<T, Alloc>& rA);

    friend Emblem::Expression<T, Alloc> (::operator+)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator-)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator*)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator/)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);


    std::string mString;
};
} // namespace Emblem

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Cos);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Tan);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Abs);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Exp);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Ln);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Log10);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(const Emblem::Symbol<T, Alloc>& rA)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return Expression<T, Alloc>::UnaryOp(
               exprA.mExpressionTree, UnaryOperator<T>::Sqrt);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    Expression<T, Alloc> exprB(rB);
    return Expression<T, Alloc>::BinaryOp(exprA.mExpressionTree, BinaryOperator<T>::Addition,
                                          exprB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    Expression<T, Alloc> exprB(rB);
    return Expression<T, Alloc>::BinaryOp(exprA.mExpressionTree, BinaryOperator<T>::Subtraction,
                                          exprB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    Expression<T, Alloc> exprB(rB);
    return Expression<T, Alloc>::BinaryOp(exprA.mExpressionTree, BinaryOperator<T>::Multiplication,
                                          exprB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, const Emblem::Symbol<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    Expression<T, Alloc> exprB(rB);
    return Expression<T, Alloc>::BinaryOp(exprA.mExpressionTree, BinaryOperator<T>::Division,
                                          exprB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
std::ostream& operator<<(
    std::ostream& rOut, const Emblem::Symbol<T, Alloc>& rSymbol)
{
    rOut << rSymbol.mString;
    return rOut;
}

///////////////////////////////////////////////////////////////////////
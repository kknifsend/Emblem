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

///////////////////////////////////////////////////////////////////////

/** \namespace Emblem */
namespace Emblem
{
/**
* \class Symbol
* \brief Defines a variable in of an expression.
* \tparam T Type of associated expression.
*/
template <class T>
class Symbol
{
    typedef BinaryOperator<T> BinaryOperator;
    typedef UnaryOperator<T> UnaryOperator;
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

    Expression<T> operator+(const Symbol& rB) const
    {
        Expression<T> exprA(*this);
        Expression<T> exprB(rB);
        return Expression<T>::BinaryOp(
            exprA.mExpressionTree, BinaryOperator::Addition,
            exprB.mExpressionTree);
    }

    Expression<T> operator-(const Symbol& rB) const
    {
        Expression<T> exprA(*this);
        Expression<T> exprB(rB);
        return Expression<T>::BinaryOp(
            exprA.mExpressionTree, BinaryOperator::Subtraction,
            exprB.mExpressionTree);
    }

    Expression<T> operator*(const Symbol& rB) const
    {
        Expression<T> exprA(*this);
        Expression<T> exprB(rB);
        return Expression<T>::BinaryOp(
            exprA.mExpressionTree, BinaryOperator::Multiplication,
            exprB.mExpressionTree);
    }

    Expression<T> operator/(const Symbol& rB) const
    {
        Expression<T> exprA(*this);
        Expression<T> exprB(rB);
        return Expression<T>::BinaryOp(
            exprA.mExpressionTree, BinaryOperator::Division,
            exprB.mExpressionTree);
    }

private:
    template <class T>
    friend std::ostream& (::operator<<)(std::ostream& rOut, const Symbol<T>&);

    std::string mString;
};
} // namespace Emblem

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> sin(const Symbol<T>& rA)
{
    Emblem::Expression<T> exprA(rA);
    return Emblem::Expression<T, Alloc>::UnaryOp(
        exprA.mExpressionTree, UnaryOperatorNode<T, Alloc>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T>
std::ostream& operator<<(std::ostream& rOut, const Emblem::Symbol<T>& rSymbol)
{
    rOut << rSymbol.mString;
    return rOut;
}

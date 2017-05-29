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
#include <cmath>

namespace Emblem
{
namespace Internal
{

///////////////////////////////////////////////////////////////////////

template <class T>
class UnaryOperator
{
    typedef T(*Operator)(const T&);
public:
    UnaryOperator(
        Operator op,
        const std::string& rOpenString,
        const std::string& rCloseString)
        : mOperator(op), mOpenString(rOpenString),
          mCloseString(rCloseString)
    {
    }

    T operator()(const T& rValue) const
    {
        return mOperator(rValue);
    }

    const std::string& GetOpenString() const
    {
        return mOpenString;
    }

    const std::string& GetCloseString() const
    {
        return mCloseString;
    }

    static UnaryOperator Sin;
    static UnaryOperator Cos;
    static UnaryOperator Tan;
    static UnaryOperator Identity;
    static UnaryOperator Abs;
    static UnaryOperator Negate;
    static UnaryOperator Exp;
    static UnaryOperator Ln;
    static UnaryOperator Log10;
    static UnaryOperator Sqrt;

private:
    const Operator mOperator;
    std::string mOpenString;
    std::string mCloseString;
};

///////////////////////////////////////////////////////////////////////

/** Unary Operators */
template <class T>
T FuncSin(const T& rA) { return sin(rA); }

template <class T>
T FuncCos(const T& rA) { return cos(rA); }

template <class T>
T FuncTan(const T& rA) { return tan(rA); }

template <class T>
T FuncIdentity(const T& rA) { return rA; }

template <class T>
T FuncAbs(const T& rA) { return std::abs(rA); }

template <class T>
T FuncNegate(const T& rA) { return -rA; }

template <class T>
T FuncExp(const T& rA) { return exp(rA); }

template <class T>
T FuncLn(const T& rA) { return log(rA); }

template <class T>
T FuncLog10(const T& rA) { return log10(rA); }

template <class T>
T FuncSqrt(const T& rA) { return sqrt(rA); }

///////////////////////////////////////////////////////////////////////

template <class T>
UnaryOperator<T> UnaryOperator<T>::Sin(FuncSin<T>, "sin(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Cos(FuncCos<T>, "cos(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Tan(FuncTan<T>, "tan(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Identity(FuncIdentity<T>, "", "");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Abs(FuncAbs<T>, "|", "|");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Negate(FuncNegate<T>, "-", "");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Exp(FuncExp<T>, "e^(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Ln(FuncLn<T>, "ln(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Log10(FuncLog10<T>, "log10(", ")");

template <class T>
UnaryOperator<T> UnaryOperator<T>::Sqrt(FuncSqrt<T>, "(", ")^(1/2)");

} // namespace Internal
} // namespace Emblem
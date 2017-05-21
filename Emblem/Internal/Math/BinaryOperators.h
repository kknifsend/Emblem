/**
* \file BinaryOperators.h

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

template <class T>
class BinaryOperator
{
public:
    typedef T(Operator)(const T&, const T&);
    BinaryOperator(
        const Operator& rOperator,
        const std::string& rString)
        : mOperator(rOperator), mString(rString)
    {
    }

    T operator()(const T& rValue0, const T& rValue1) const
    {
        return mOperator(rValue0, rValue1);
    }

private:
    Operator mOperator;
    std::string mString;
};

template <class T>
T Add(const T& rA, const T& rB)
{
    return (rA + rB);
}

template <class T>
T Sub(const T& rA, const T& rB)
{
    return (rA - rB);
}
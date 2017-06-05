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

#include "BinaryOperators.h"
#include "UnaryOperators.h"

#include <allocators>
#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>

namespace Emblem
{
template <class T, class Alloc> class Symbol;
namespace Internal
{

/////////////////////////////////////////////////

template <class T, class Allocator>
class TermNode : public Internal::Node<TermNode<T, Allocator>>
{
public:
    typedef std::unordered_map<
    std::string, T, std::hash<std::string>,
        std::equal_to<std::string>, Allocator> ValueMap;

    TermNode()
        : Internal::Node<TermNode<T, Allocator>>()
    {

    }

    virtual T evaluate(const ValueMap& rValueMap) const = 0;
    virtual void Output(bool withParens, std::ostream& rOut) const = 0;

    virtual bool isOperand() const { return false; }
    virtual bool isOperator() const { return false; }
    virtual bool isSymbol() const { return false; }
};

/////////////////////////////////////////////////

template <class T, class Allocator>
class BinaryOperatorNode : public TermNode<T, Allocator>
{
public:
    BinaryOperatorNode(const BinaryOperator<T>& rBinaryOperator)
        : TermNode(), mBinaryOperator(rBinaryOperator) {}

    T evaluate(const ValueMap& rValueMap) const override
    {
        assert(mpLeftNode != nullptr);
        assert(mpRightNode != nullptr);

        const T leftVal = ((TermNode*)mpLeftNode)->evaluate(rValueMap);
        const T rightVal = ((TermNode*)mpRightNode)->evaluate(rValueMap);

        return mBinaryOperator(leftVal, rightVal);
    }

    void Output(bool withParens, std::ostream& rOut) const override
    {
        if (withParens)
        {
            rOut << '(';
        }

        // Output left node
        const BinaryOperatorNode* pLeftOperation =
            dynamic_cast<BinaryOperatorNode*>(mpLeftNode);
        const bool isLeftOpEqual =
            (pLeftOperation != nullptr) &&
            (mBinaryOperator == pLeftOperation->mBinaryOperator);
        mpLeftNode->Output(!isLeftOpEqual, rOut);

        // Output operator
        rOut << mBinaryOperator.GetOperatorString();

        // Output right node
        const BinaryOperatorNode* pRightOperation =
            dynamic_cast<BinaryOperatorNode*>(mpLeftNode);
        const bool isRightOpEqual =
            (pRightOperation != nullptr) &&
            (mBinaryOperator == pRightOperation->mBinaryOperator);
        mpRightNode->Output(!isRightOpEqual, rOut);

        if (withParens)
        {
            rOut << ')';
        }
    }

    virtual TermNode* clone() const override
    {
        return new BinaryOperatorNode(*this);
    }

    const BinaryOperator<T>& GetOperator() const
    {
        return mBinaryOperator;
    }

    virtual bool isOperator() const { return true; }
private:
    BinaryOperator<T> mBinaryOperator;
};

/////////////////////////////////////////////////

template <class T, class Allocator>
class UnaryOperatorNode : public TermNode<T, Allocator>
{
public:
    UnaryOperatorNode(const UnaryOperator<T>& rUnaryOperator)
        : TermNode(), mUnaryOperator(rUnaryOperator) {}

    T evaluate(const ValueMap& rValueMap) const override
    {
        if (mpLeftNode != nullptr)
        {
            const T val = ((TermNode*)mpLeftNode)->evaluate(rValueMap);
            return mUnaryOperator(val);
        }

        const T val = ((TermNode*)mpRightNode)->evaluate(rValueMap);
        return mUnaryOperator(val);
    }

    void Output(bool withParens, std::ostream& rOut) const override
    {
        rOut << mUnaryOperator.GetOpenString();
        mpLeftNode->Output(false, rOut);
        rOut << mUnaryOperator.GetCloseString();
    }

    virtual TermNode* clone() const override
    {
        return new UnaryOperatorNode(*this);
    }

    const UnaryOperator<T>& GetOperator() const
    {
        return mUnaryOperator;
    }

    virtual bool isOperator() const { return true; }
private:
    UnaryOperator<T> mUnaryOperator;
};

/////////////////////////////////////////////////

template <class T, class Allocator>
class SymbolNode : public TermNode<T, Allocator>
{
    const Symbol<T, Allocator> mSymbol;
public:
    SymbolNode(const Symbol<T, Allocator>& rSymbol)
        : TermNode(), mSymbol(rSymbol)
    {}

    T evaluate(const ValueMap& rValueMap) const override
    {
        return rValueMap.at(mSymbol.toString());
    }

    void Output(bool withParens, std::ostream& rOut) const override
    {
        rOut << mSymbol;
    }

    virtual TermNode* clone() const override
    {
        return new SymbolNode(*this);
    }

    const Symbol<T, Allocator>& GetSymbol() const
    {
        return mSymbol;
    }

    virtual bool isOperand() const { return true; }
    virtual bool isSymbol() const { return true; }
};

/////////////////////////////////////////////////

template <class T, class Allocator>
class ConstantNode : public TermNode<T, Allocator>
{
public:
    ConstantNode(const T& rData)
        : mpData(mAllocator.allocate(1))
    {
        *mpData = rData;
    }

    ConstantNode(const ConstantNode& rOther)
        : mpData(mAllocator.allocate(1))
    {
        *mpData = *rOther.mpData;
    }

    T evaluate(const ValueMap& rValueMap) const override
    {
        return *mpData;
    }

    void Output(bool withParens, std::ostream& rOut) const override
    {
        rOut << *mpData;
    }

    virtual TermNode* clone() const override
    {
        return new ConstantNode(*this);
    }

    ~ConstantNode()
    {
        mAllocator.deallocate(mpData, 1);
        mpData = nullptr;
    }

    virtual bool isOperand() const { return true; }
private:
    ConstantNode& operator=(const ConstantNode&);

    Allocator mAllocator;
    T* mpData;
};

} // namespace Internal
} // namespace Emblem
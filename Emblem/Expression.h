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

#include "Internal\Collection\BinaryTree.h"
#include "Internal\TermNode.h"

///////////////////////////////////////////////////////////////////////

/**
* \namespace Emblem
*/
namespace Emblem
{
template <class T, class Alloc> class Expression;
template <class T> class Symbol;
}

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Expression<T, Alloc>&);

///////////////////////////////////////////////////////////////////////

namespace Emblem
{

/**
* \class Expression
* \brief Defines mathmatical expressions as a combination of variables, and constants.
* \tparam T Type of evaluation in expression.
*/
template <class T, class Alloc = std::allocator<T>>
class Expression
{
    typedef TermNode<T, Alloc> TermNode;
    typedef SymbolNode<T, Alloc> SymbolNode;
    typedef ConstantNode<T, Alloc> ConstantNode;
    typedef BinaryOperatorNode<T, Alloc> BinaryOperatorNode;
    typedef UnaryOperatorNode<T, Alloc> UnaryOperatorNode;

    typedef Symbol<T> Symbol;
    typedef BinaryOperator<T> BinaryOperator;
    typedef UnaryOperator<T> UnaryOperator;
    typedef Collection::BinaryTree<TermNode> ExpressionTree;
public:
    /** \brief Mapping of variables to their values. */
    typedef typename TermNode::ValueMap ValueMap;


    Expression() {}
    Expression(const Symbol& rSymbol)
    {
        mExpressionTree.insertToHead(new SymbolNode(rSymbol));
    }

    Expression(const T& rConstant)
    {
        mExpressionTree.insertToHead(new ConstantNode(rConstant));
    }

    /**
    * \brief Function used to evaluate an expression given mapping of values.
    *
    * If expression is empty, returns 0.
    *
    * If the value map is not populated by all the symbols expected by the expression,
    * an assertion is triggered.
    * \return Returns the result of the expression evaluation.
    */
    T evaluate(const ValueMap& rValues) const
    {
        const TermNode* pNode = mExpressionTree.head();
        assert(pNode != nullptr);
        return pNode->evaluate(rValues);
    }

    /**
    * \brief Substitutes the supplied expression for the given symbol
    *
    * Replaces all instances of the given symbol with the supplied expression, constant, or symbol.
    */
    void substitute(const Symbol& rSymbol, const Expression& rExpr) {}

    /** */
    Expression derivative(const Symbol&) const {}

    // Operators
    Expression operator+(const Expression& rB) const
    {
        return BinaryOp(
                   mExpressionTree.clone(), BinaryOperator::Addition,
                   rB.mExpressionTree.clone());
    }

    Expression operator+(Expression&& rB) const
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Addition,
                        rB.mExpressionTree);
    }

    Expression operator-(const Expression& rB) const
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Subtraction,
                        rB.mExpressionTree.clone());
    }

    Expression operator-(Expression&& rB) const
    {
        return BinaryOp(mExpressionTree.clone(),BinaryOperator::Subtraction,
                        rB.mExpressionTree);
    }

    Expression operator*(const Expression& rB) const
    {
        return BinaryOp(mExpressionTree.clone(),BinaryOperator::Multiplication,
                        rB.mExpressionTree.clone());
    }

    Expression operator*(Expression&& rB) const
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Multiplication,
                        rB.mExpressionTree);
    }

    Expression operator/(const Expression& rB) const
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Division,
                        rB.mExpressionTree.clone());
    }

    Expression operator/(Expression&& rB) const
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Division,
                        rB.mExpressionTree);
    }

    // Assignment math operators
    Expression& operator+=(const Expression& rB)
    {
        mExpressionTree = BinaryOp(mExpressionTree, BinaryOperator::Addition,
                                   rB.mExpressionTree.clone());
        return *this;
    }

    Expression& operator-=(const Expression& rB)
    {
        mExpressionTree = BinaryOp(mExpressionTree, BinaryOperator::Subtraction,
                                   rB.mExpressionTree.clone());
        return *this;
    }

    Expression& operator*=(const Expression& rB)
    {
        mExpressionTree = BinaryOp(mExpressionTree, BinaryOperator::Multiplication,
                                   rB.mExpressionTree.clone());
        return *this;
    }

    Expression& operator/=(const Expression& rB)
    {
        mExpressionTree = BinaryOp(mExpressionTree, BinaryOperator::Division,
                                   rB.mExpressionTree.clone());
        return *this;
    }

private:
    static Expression BinaryOp(
        ExpressionTree& rA, const BinaryOperator& rOperator,
        ExpressionTree& rB)
    {
        BinaryOperatorNode* pOperationNode(new BinaryOperatorNode(rOperator));
        pOperationNode->mpLeftNode = rA.release();
        pOperationNode->mpRightNode = rB.release();

        Expression result;
        result.mExpressionTree.insertChildLeft(nullptr, pOperationNode);
        return result;
    }

    static Expression UnaryOp(
        ExpressionTree& rA, const UnaryOperator& rOperator)
    {
        UnaryOperatorNode* pOperationNode(new UnaryOperatorNode(rOperator));
        pOperationNode->mpLeftNode = rA.release();

        Expression result;
        result.mExpressionTree.insertChildLeft(nullptr, pOperationNode);
        return result;
    }

    friend class Symbol;

    //! @cond
    friend Expression sin(const Expression& rTree);
    friend Expression cos(const Expression& rTree);
    friend Expression tan(const Expression& rTree);
    //! @endcond

    ExpressionTree mExpressionTree;
};
} // namespace Emblem

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Expression<T, Alloc>& rTree)
{
    return Emblem::Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperatorNode<T, Alloc>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Expression<T, Alloc>& rTree)
{
    return Emblem::Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperatorNode<T, Alloc>::Cos);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Expression<T, Alloc>& rTree)
{
    return Emblem::Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperatorNode<T, Alloc>::Tan);
}


///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> sin(const Emblem::Symbol<T>& rA)
{
    Emblem::Expression<T> exprA(rA);
    return Emblem::Expression<T>::UnaryOp(
        exprA.mExpressionTree, UnaryOperatorNode<T>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> cos(const Emblem::Symbol<T>& rA)
{
    Emblem::Expression<T> exprA(rA);
    return Emblem::Expression<T>::UnaryOp(
        exprA.mExpressionTree, UnaryOperatorNode<T>::Cos);
}

///////////////////////////////////////////////////////////////////////

template <class T>
Emblem::Expression<T> tan(const Emblem::Symbol<T>& rA)
{
    Emblem::Expression<T> exprA(rA);
    return Emblem::Expression<T>::UnaryOp(
        exprA.mExpressionTree, UnaryOperatorNode<T>::Tan);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const Emblem::Symbol<T>& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
                    rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const Emblem::Symbol<T>& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const Emblem::Symbol<T>& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const Emblem::Symbol<T>& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
        rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    Emblem::Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
        rB.mExpressionTree.clone());
}


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
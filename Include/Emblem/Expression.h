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

#include "Internal\BinaryTree.h"
#include "Internal\TermNode.h"

///////////////////////////////////////////////////////////////////////

/**
* \namespace Emblem
*/
namespace Emblem
{
template <class T, class Alloc> class Expression;
template <class T, class Alloc> class Symbol;
}

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(const Emblem::Expression<T, Alloc>&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(const Emblem::Expression<T, Alloc>&);

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(Emblem::Expression<T, Alloc>&&);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(Emblem::Expression<T, Alloc>&&);


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
    const T& rA, const Emblem::Expression<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, const Emblem::Expression<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, const Emblem::Expression<T, Alloc>& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, const Emblem::Expression<T, Alloc>& rB);

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, Emblem::Expression<T, Alloc>&& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, Emblem::Expression<T, Alloc>&& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, Emblem::Expression<T, Alloc>&& rB);
template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, Emblem::Expression<T, Alloc>&& rB);

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
    typedef Internal::TermNode<T, Alloc> TermNode;
    typedef Internal::SymbolNode<T, Alloc> SymbolNode;
    typedef Internal::ConstantNode<T, Alloc> ConstantNode;
    typedef Internal::BinaryOperatorNode<T, Alloc> BinaryOperatorNode;
    typedef Internal::UnaryOperatorNode<T, Alloc> UnaryOperatorNode;

    typedef Internal::BinaryOperator<T> BinaryOperator;
    typedef Internal::UnaryOperator<T> UnaryOperator;
    typedef Internal::BinaryTree<TermNode> ExpressionTree;
public:
    /** \brief Mapping of variables to their values. */
    typedef typename TermNode::ValueMap ValueMap;
    typedef Symbol<T, Alloc> Symbol;

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
        if (pNode == nullptr)
        {
            assert(0);
            return T();
        }
        return pNode->evaluate(rValues);
    }

    /**
    * \brief Substitutes the supplied expression for the given symbol
    *
    * Replaces all instances of the given symbol with the supplied expression, constant, or symbol.
    */
    void substitute(const Symbol& rSymbol, const Expression& rExpr)
    {
        Expression::Substitute(mExpressionTree, rSymbol, rExpr.mExpressionTree.clone());
    }

    void substitute(const Symbol& rSymbol, Expression&& rExpr)
    {
        Expression::Substitute(mExpressionTree, rSymbol, rExpr.mExpressionTree);
    }

    void simplify();

    /** */
    Expression derivative(const Symbol&) const;

    // Operators
    ///////////////////////////////////////////////////
    ///////////////// Addition ////////////////////////
    ///////////////////////////////////////////////////
    Expression operator+(const Expression& rB) const&
    {
        return BinaryOp(
                   mExpressionTree.clone(), BinaryOperator::Addition,
                   rB.mExpressionTree.clone());
    }

    Expression operator+(Expression&& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Addition,
                        rB.mExpressionTree);
    }

    Expression operator+(const Expression& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Addition,
                        rB.mExpressionTree.clone());
    }

    Expression operator+(Expression&& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Addition,
                        rB.mExpressionTree);
    }

    ///////////////////////////////////////////////////
    ///////////////// Subtraction /////////////////////
    ///////////////////////////////////////////////////
    Expression operator-(const Expression& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Subtraction,
                        rB.mExpressionTree.clone());
    }

    Expression operator-(Expression&& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(),BinaryOperator::Subtraction,
                        rB.mExpressionTree);
    }

    Expression operator-(const Expression& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Subtraction,
                        rB.mExpressionTree.clone());
    }

    Expression operator-(Expression&& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Subtraction,
                        rB.mExpressionTree);
    }

    ///////////////////////////////////////////////////
    ///////////////// Multiplication //////////////////
    ///////////////////////////////////////////////////
    Expression operator*(const Expression& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(),BinaryOperator::Multiplication,
                        rB.mExpressionTree.clone());
    }

    Expression operator*(Expression&& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Multiplication,
                        rB.mExpressionTree);
    }

    Expression operator*(const Expression& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Multiplication,
                        rB.mExpressionTree.clone());
    }

    Expression operator*(Expression&& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Multiplication,
                        rB.mExpressionTree);
    }

    ///////////////////////////////////////////////////
    ///////////////// Division ////////////////////////
    ///////////////////////////////////////////////////
    Expression operator/(const Expression& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Division,
                        rB.mExpressionTree.clone());
    }

    Expression operator/(Expression&& rB) const&
    {
        return BinaryOp(mExpressionTree.clone(), BinaryOperator::Division,
                        rB.mExpressionTree);
    }

    Expression operator/(const Expression& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Division,
                        rB.mExpressionTree.clone());
    }

    Expression operator/(Expression&& rB)&&
    {
        return BinaryOp(mExpressionTree, BinaryOperator::Division,
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

    // Unary negation
    Expression operator-() const&
    {
        return Expression::UnaryOp(mExpressionTree.clone(), UnaryOperator::Negate);
    }

    Expression operator-()&&
    {
        return Expression::UnaryOp(mExpressionTree, UnaryOperator::Negate);
    }

    void Output(std::ostream& rOut) const;

private:
    static Expression BinaryOp(
        ExpressionTree& rA, const BinaryOperator& rOperator,
        ExpressionTree& rB)
    {
        BinaryOperatorNode* pOperationNode(new BinaryOperatorNode(rOperator));
        pOperationNode->mpLeftNode = rA.release();
        pOperationNode->mpRightNode = rB.release();

        pOperationNode->mpLeftNode->mpParentNode = pOperationNode;
        pOperationNode->mpRightNode->mpParentNode = pOperationNode;

        Expression result;
        result.mExpressionTree.insertToHead(pOperationNode);
        return result;
    }

    static Expression UnaryOp(
        ExpressionTree& rA, const UnaryOperator& rOperator)
    {
        UnaryOperatorNode* pOperationNode(new UnaryOperatorNode(rOperator));
        pOperationNode->mpLeftNode = rA.release();
        pOperationNode->mpLeftNode->mpParentNode = pOperationNode;

        Expression result;
        result.mExpressionTree.insertToHead(pOperationNode);
        return result;
    }

    static void Substitute(
        ExpressionTree& rExpr, const Symbol& rSymbol,
        ExpressionTree& rSubExpr);

    friend class Symbol;

    friend Emblem::Expression<T, Alloc> (::sin)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::cos)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::tan)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::abs)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::exp)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::log)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::log10)(const Emblem::Expression<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::sqrt)(const Emblem::Expression<T, Alloc>&);

    friend Emblem::Expression<T, Alloc> (::sin)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::cos)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::tan)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::abs)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::exp)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::log)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::log10)(Emblem::Expression<T, Alloc>&&);
    friend Emblem::Expression<T, Alloc> (::sqrt)(Emblem::Expression<T, Alloc>&&);

    friend Emblem::Expression<T, Alloc> (::sin)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::cos)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::tan)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::abs)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::exp)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::log)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::log10)(const Emblem::Symbol<T, Alloc>&);
    friend Emblem::Expression<T, Alloc> (::sqrt)(const Emblem::Symbol<T, Alloc>&);

    friend Emblem::Expression<T, Alloc> (::operator+)(const T& rA,
            const Emblem::Expression<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator-)(const T& rA,
            const Emblem::Expression<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator*)(const T& rA,
            const Emblem::Expression<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator/)(const T& rA,
            const Emblem::Expression<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc> (::operator+)(const T& rA, Emblem::Expression<T, Alloc>&& rB);
    friend Emblem::Expression<T, Alloc> (::operator-)(const T& rA, Emblem::Expression<T, Alloc>&& rB);
    friend Emblem::Expression<T, Alloc> (::operator*)(const T& rA, Emblem::Expression<T, Alloc>&& rB);
    friend Emblem::Expression<T, Alloc> (::operator/)(const T& rA, Emblem::Expression<T, Alloc>&& rB);
    friend Emblem::Expression<T, Alloc>(::operator+)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc>(::operator-)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc>(::operator*)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    friend Emblem::Expression<T, Alloc>(::operator/)(const T& rA, const Emblem::Symbol<T, Alloc>& rB);
    ExpressionTree mExpressionTree;
};

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
void Expression<T, Alloc>::simplify()
{

}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
void Expression<T, Alloc>::Substitute(
    ExpressionTree& rExpr, const Symbol& rSymbol,
    ExpressionTree& rSubExpr)
{
    if ((rExpr.head() == nullptr) || (rSubExpr.head() == nullptr))
    {
        return;
    }

    const SymbolNode* pHeadSymbol =
        dynamic_cast<const SymbolNode*>(rExpr.head());
    if ((pHeadSymbol != nullptr) && (pHeadSymbol->GetSymbol() == rSymbol))
    {
        rExpr.insertToHead(rSubExpr.release());
        return;
    }

    std::stack<const TermNode*> nodeStack;
    nodeStack.push(rExpr.head());
    while (!nodeStack.empty())
    {
        const TermNode* pCurNode = nodeStack.top();
        nodeStack.pop();
        if ((pCurNode == nullptr) || pCurNode->isLeaf())
        {
            continue;
        }

        if (pCurNode->mpLeftNode->isSymbol())
        {
            const SymbolNode* pLeftSymbol =
                dynamic_cast<const SymbolNode*>(pCurNode->mpLeftNode);
            assert(pLeftSymbol != nullptr);
            if (pLeftSymbol->GetSymbol() == rSymbol)
            {
                ExpressionTree exprSub = rSubExpr.clone();
                rExpr.replace(pCurNode->mpLeftNode, exprSub.release());
            }
        }
        else
        {
            nodeStack.push(pCurNode->mpLeftNode);
        }

        if (pCurNode->mpRightNode->isSymbol())
        {
            const SymbolNode* pRightSymbol =
                dynamic_cast<const SymbolNode*>(pCurNode->mpRightNode);
            assert(pRightSymbol != nullptr);
            if (pRightSymbol->GetSymbol() == rSymbol)
            {
                ExpressionTree exprSub = rSubExpr.clone();
                rExpr.replace(pCurNode->mpRightNode, exprSub.release());
            }
        }
        else
        {
            nodeStack.push(pCurNode->mpRightNode);
        }
    }
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Expression<T, Alloc> Expression<T, Alloc>::derivative(const Symbol&) const
{

}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
void Expression<T, Alloc>::Output(std::ostream& rOut) const
{
    const TermNode* pHead = mExpressionTree.head();
    if (pHead == nullptr)
    {
        return;
    }

    pHead->Output(false, rOut);
}

} // namespace Emblem

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sin(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Sin);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Cos);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> cos(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Cos);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Tan);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> tan(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Tan);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Abs);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> abs(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Abs);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Exp);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> exp(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Exp);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Ln);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Ln);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Log10);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> log10(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Log10);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(const Emblem::Expression<T, Alloc>& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree.clone(), UnaryOperator<T>::Sqrt);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> sqrt(Emblem::Expression<T, Alloc>&& rTree)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    return Expression<T, Alloc>::UnaryOp(
               rTree.mExpressionTree, UnaryOperator<T>::Sqrt);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
                    rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator+(
    const T& rA, Emblem::Expression<T, Alloc>&& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Addition,
                    rB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
                    rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator-(
    const T& rA, Emblem::Expression<T, Alloc>&& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Subtraction,
                    rB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
                    rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator*(
    const T& rA, Emblem::Expression<T, Alloc>&& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Multiplication,
                    rB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, const Emblem::Expression<T, Alloc>& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
                    rB.mExpressionTree.clone());
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
Emblem::Expression<T, Alloc> operator/(
    const T& rA, Emblem::Expression<T, Alloc>&& rB)
{
    using namespace Emblem;
    using namespace Emblem::Internal;
    Expression<T, Alloc> exprA(rA);
    return BinaryOp(exprA.mExpressionTree, BinaryOperator::Division,
                    rB.mExpressionTree);
}

///////////////////////////////////////////////////////////////////////

template <class T, class Alloc>
std::ostream& operator<<(
    std::ostream& rOut, const Emblem::Expression<T, Alloc>& rExpr)
{
    rExpr.Output(rOut);
    return rOut;
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
#include "Emblem/Symbol.h"
/**
* \file Derivative.h

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

#include "BinaryTree.h"
#include "BinaryOperators.h"
#include "UnaryOperators.h"
#include "TermNode.h"

#include "../Symbol.h"

namespace Emblem
{
namespace Internal
{

template <class T, class Alloc>
using ExpressionTree = BinaryTree<TermNode<T, Alloc>>;

template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(
    const BinaryOperatorNode<T, Alloc>* pBinaryOp, const Symbol<T, Alloc>& rSymbol);
template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(
    const UnaryOperatorNode<T, Alloc>* pUnaryOp, const Symbol<T, Alloc>& rSymbol);

template <class T, class Alloc>
TermNode<T, Alloc>* Derivative(const TermNode<T, Alloc>* pNode, const Symbol<T, Alloc>& rSymbol)
{
    typedef ConstantNode<T, Alloc> ConstantNode;
    typedef SymbolNode<T, Alloc> SymbolNode;
    typedef BinaryOperatorNode<T, Alloc> BinaryOperatorNode;
    typedef UnaryOperatorNode<T, Alloc> UnaryOperatorNode;

    if (pNode->isOperator())
    {
        const BinaryOperatorNode* pBinaryOp =
            dynamic_cast<const BinaryOperatorNode*>(pNode);
        if (pBinaryOp != nullptr)
        {
            return OperatorDerivative(pBinaryOp, rSymbol);
        }
        else
        {
            const UnaryOperatorNode* pUnaryOp =
                dynamic_cast<const UnaryOperatorNode*>(pNode);
            assert(pUnaryOp != nullptr);
            return OperatorDerivative(pUnaryOp, rSymbol);
        }
    }
    else
    {
        if (pNode->isSymbol())
        {
            // Symbol
            const SymbolNode* pSymbolNode =
                dynamic_cast<const SymbolNode*>(pNode);
            if (pSymbolNode->GetSymbol() == rSymbol)
            {
                return new ConstantNode((T)1.0);
            }
            else
            {
                return new ConstantNode((T)0.0);
            }
        }
        else
        {
            // Constant
            return new ConstantNode((T)0.0);
        }
    }
}

template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(
    const BinaryOperatorNode<T, Alloc>* pBinaryOp, const Symbol<T, Alloc>& rSymbol)
{
    typedef TermNode<T, Alloc> TermNode;
    typedef BinaryOperator<T> BinaryOperator;
    typedef BinaryOperatorNode<T, Alloc> BinaryOperatorNode;
    typedef ConstantNode<T, Alloc> ConstantNode;

    TermNode* pDerivative = nullptr;
    const auto& rOperator = pBinaryOp->GetOperator();
    if ((rOperator == BinaryOperator::Addition) ||
            (rOperator == BinaryOperator::Subtraction))
    {
        pDerivative = pBinaryOp->clone();
        pDerivative->setLeft(Derivative(pBinaryOp->mpLeftNode, rSymbol));
        pDerivative->setRight(Derivative(pBinaryOp->mpRightNode, rSymbol));
    }
    else if (rOperator == BinaryOperator::Multiplication)
    {
        pDerivative = new BinaryOperatorNode(BinaryOperator::Addition);

        TermNode* pLeftTerm = new BinaryOperatorNode(BinaryOperator::Multiplication);
        TermNode* pRightTerm = new BinaryOperatorNode(BinaryOperator::Multiplication);
        pDerivative->setLeft(pLeftTerm);
        pDerivative->setRight(pRightTerm);

        pLeftTerm->setLeft(Derivative(pBinaryOp->mpLeftNode, rSymbol));
        pLeftTerm->setRight(pBinaryOp->mpRightNode->clone());

        pRightTerm->setLeft(pBinaryOp->mpLeftNode->clone());
        pRightTerm->setRight(Derivative(pBinaryOp->mpRightNode, rSymbol));
    }
    else if (rOperator == BinaryOperator::Division)
    {
        pDerivative = new BinaryOperatorNode(BinaryOperator::Division);

        TermNode* pTopTerm = new BinaryOperatorNode(BinaryOperator::Subtraction);
        TermNode* pBottomTerm = new BinaryOperatorNode(BinaryOperator::Pow);
        pDerivative->setLeft(pTopTerm);
        pDerivative->setRight(pBottomTerm);

        TermNode* pLeftTerm = new BinaryOperatorNode(BinaryOperator::Multiplication);
        TermNode* pRightTerm = new BinaryOperatorNode(BinaryOperator::Multiplication);
        pTopTerm->setLeft(pLeftTerm);
        pTopTerm->setRight(pRightTerm);

        pLeftTerm->setLeft(Derivative(pBinaryOp->mpLeftNode, rSymbol));
        pLeftTerm->setRight(pBinaryOp->mpRightNode->clone());

        pRightTerm->setLeft(pBinaryOp->mpLeftNode->clone());
        pRightTerm->setRight(Derivative(pBinaryOp->mpRightNode, rSymbol));

        pBottomTerm->setLeft(pBinaryOp->mpRightNode->clone());
        pBottomTerm->setRight(new ConstantNode(2.0));
    }

    return pDerivative;
}

template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(
    const UnaryOperatorNode<T, Alloc>* pUnaryOp, const Symbol<T, Alloc>& rSymbol)
{
    return nullptr;
}


} // namespace Internal
} // namespace Emblem
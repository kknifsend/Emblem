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
TermNode<T, Alloc>* OperatorDerivative(const BinaryOperatorNode<T, Alloc>* pBinaryOp);
template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(const UnaryOperatorNode<T, Alloc>* pUnaryOp);

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
            DerivativeBinaryOp(pBinaryOp->GetOperator());
        }
        else
        {
            const UnaryOperatorNode* pUnaryOp =
                dynamic_cast<const UnaryOperatorNode*>(pNode);
            assert(pUnaryOp != nullptr);
            OperatorDerivative(pUnaryOp->GetOperator());
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
TermNode<T, Alloc>* OperatorDerivative(const BinaryOperatorNode<T, Alloc>* pBinaryOp)
{

}

template <class T, class Alloc>
TermNode<T, Alloc>* OperatorDerivative(const UnaryOperatorNode<T, Alloc>* pUnaryOp)
{

}


} // namespace Internal
} // namespace Emblem
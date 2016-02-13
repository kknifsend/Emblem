/**
* \file IteratorPreOrder.h

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

#include <stack>
#include <deque>

#include "IteratorBinaryTree.h"

namespace Emblem
{
namespace Collection
{
namespace Iterator
{

///////////////////////////////////////////////////////////////////////

/**
* \class IteratorPreOrder
* \brief Pre-order binary tree traversal.
*/
template <class TREE>
class IteratorPreOrder : public IteratorBinaryTree<TREE>
{
public:
	IteratorPreOrder(TREE& rTree);
	IteratorPreOrder(TREE& rTree, typename TREE::IndexType start);
};

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorPreOrder<TREE>::IteratorPreOrder(TREE& rTree, typename TREE::IndexType start)
{
	typedef typename TREE::IndexType IndexType;
	if (start != TREE::INVALID_INDEX)
	{
		std::stack<IndexType> nodes;
		nodes.push(start);
		while (!nodes.empty())
		{
			const IndexType current = nodes.top();
			nodes.pop();
			mNodeIndices.push_back(current);

			if (rTree.right(current) != TREE::INVALID_INDEX)
			{
				nodes.push(rTree.right(current));
			}

			if (rTree.left(current) != TREE::INVALID_INDEX)
			{
				nodes.push(rTree.left(current));
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorPreOrder<TREE>::IteratorPreOrder(TREE& rTree)
	: IteratorPreOrder(rTree, rTree.head())
{
}

///////////////////////////////////////////////////////////////////////

}
}
}

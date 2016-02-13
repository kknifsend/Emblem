/**
* \file IteratorInOrder.h

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

/**
* \class IteratorInOrder
* \brief In-order binary tree traversal.
*/
template <class TREE>
class IteratorInOrder : public IteratorBinaryTree<TREE>
{
public:
	IteratorInOrder(TREE& rTree);
	IteratorInOrder(TREE& rTree, typename TREE::IndexType start);
};

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorInOrder<TREE>::IteratorInOrder(TREE& rTree, typename TREE::IndexType start)
	: IteratorBinaryTree<TREE>(rTree)
{
	typedef typename TREE::IndexType IndexType;
	if (start != TREE::INVALID_INDEX)
	{
		std::stack<IndexType> nodes;
		IndexType current = start;

		while ((current != TREE::INVALID_INDEX) || !nodes.empty())
		{
			while (current != TREE::INVALID_INDEX)
			{
				nodes.push(current);
				current = rTree.left(current);
			}

			IndexType popped = nodes.top();
			nodes.pop();

			mNodeIndices.push_back(popped);

			current = rTree.right(popped);
		}
	}
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorInOrder<TREE>::IteratorInOrder(TREE& rTree)
	: IteratorInOrder(rTree, rTree.head())
{
}

///////////////////////////////////////////////////////////////////////

}
}
}
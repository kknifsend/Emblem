/**
* \file IteratorPostOrder.h

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
* \class IteratorPostOrder
* \brief Post-order binary tree traversal.
*/
template <class TREE>
class IteratorPostOrder : public IteratorBinaryTree<TREE>
{
public:
	IteratorPostOrder(TREE& rTree);

	IteratorPostOrder(TREE& rTree, typename TREE::IndexType start);
};

///////////////////////////////////////////////////////////////////////


template <class TREE>
IteratorPostOrder<TREE>::IteratorPostOrder(TREE& rTree, typename TREE::IndexType start)
	: IteratorBinaryTree<TREE>(rTree)
{
	typedef typename TREE::IndexType IndexType;
	if (start != TREE::INVALID_INDEX)
	{
		std::deque<IndexType> reverseNodes;
		IndexType current = start;

		//mNodeIndices.push_back(TREE::INVALID_INDEX);
		reverseNodes.push_back(current);
		while (!reverseNodes.empty())
		{
			current = reverseNodes.back();
			reverseNodes.pop_back();
			mNodeIndices.push_front(current);

			if (rTree.left(current) != TREE::INVALID_INDEX)
			{
				reverseNodes.push_back(rTree.left(current));
			}

			if (rTree.right(current) != TREE::INVALID_INDEX)
			{
				reverseNodes.push_back(rTree.right(current));
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorPostOrder<TREE>::IteratorPostOrder(TREE& rTree)
	: IteratorPostOrder(rTree, rTree.head())
{
}

///////////////////////////////////////////////////////////////////////

}
}
}

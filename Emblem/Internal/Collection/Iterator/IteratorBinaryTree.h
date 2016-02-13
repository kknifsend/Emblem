/**
* \file IteratorBinaryTree.h

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

#include <iterator>
#include <deque>
#include <type_traits>

namespace Emblem
{
namespace Collection
{
namespace Iterator
{

///////////////////////////////////////////////////////////////////////

/**
* \class IteratorBinaryTree
* \brief Base class iterator for binary tree. Construction is non-constant.
*/
template <class TREE>
class IteratorBinaryTree : public std::iterator<std::input_iterator_tag, TREE>
{
	typedef typename TREE::IndexType IndexType;
	typedef typename std::conditional<std::is_const<TREE>::value,
		typename const TREE::ValueType, typename TREE::ValueType>::type ValueType;

public:
	IteratorBinaryTree(TREE& rTree) : mpTree(&rTree), mCurrentIndex(0) {}
	IteratorBinaryTree(const IteratorBinaryTree&);
	IteratorBinaryTree(IteratorBinaryTree&&);

	IteratorBinaryTree& operator=(const IteratorBinaryTree&);
	IteratorBinaryTree& operator=(IteratorBinaryTree&&);

	bool operator==(const IteratorBinaryTree& rIt) const;
	bool operator!=(const IteratorBinaryTree& rIt) const;

	ValueType& operator*();
	ValueType* operator->();

	IteratorBinaryTree& operator++(); //Prefix
	IteratorBinaryTree& operator--();

	IteratorBinaryTree operator++(int); //Postfix
	IteratorBinaryTree operator--(int);

	void reset();

	operator ValueType*();

	operator IndexType() const;

private:
	ValueType* GetCurrentNode() const;
	
	IndexType GetCurrentIndex() const;

protected:
	TREE* mpTree;
	std::deque<IndexType> mNodeIndices;
	uint32_t mCurrentIndex;
};

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>::IteratorBinaryTree(const IteratorBinaryTree& rB)
	: mpTree(rB.mpTree), mCurrentIndex(rB.mCurrentIndex)
{
	mNodeIndices = rB.mNodeIndices;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>::IteratorBinaryTree(IteratorBinaryTree&& rB)
	: mpTree(rB.mpTree), mCurrentIndex(rB.mCurrentIndex)
{
	mNodeIndices.swap(rB.mNodeIndices);
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>& IteratorBinaryTree<TREE>::operator=(const IteratorBinaryTree& rB)
{
	if (this != &rB)
	{
		mpTree = rB.mpTree;
		mCurrentIndex = rB.mCurrentIndex;
		mNodeIndices = rB.mNodeIndices;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>& IteratorBinaryTree<TREE>::operator=(IteratorBinaryTree&& rB)
{
	mpTree = rB.mpTree;
	mCurrentIndex = mCurrentIndex;
	mNodeIndices.swap(rB.mNodeIndices);
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
typename IteratorBinaryTree<TREE>::ValueType& IteratorBinaryTree<TREE>::operator*()
{
	return *(GetCurrentNode());
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
typename IteratorBinaryTree<TREE>::ValueType* IteratorBinaryTree<TREE>::operator->()
{
	return GetCurrentNode();
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>& IteratorBinaryTree<TREE>::operator++()
{
	++mCurrentIndex;
	return *this;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>& IteratorBinaryTree<TREE>::operator--()
{
	if (mCurrentIndex >= 0)
	{
		--mCurrentIndex;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE> IteratorBinaryTree<TREE>::operator++(int) //Postfix
{
	const auto copy = *this;
	++mCurrentIndex;
	return copy;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE> IteratorBinaryTree<TREE>::operator--(int) //Postfix
{
	const auto copy = *this;
	if (mCurrentIndex >= 0)
	{
		--mCurrentIndex;
	}
	return copy;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
bool IteratorBinaryTree<TREE>::operator==(typename const IteratorBinaryTree<TREE>& rIt) const
{
	ValueType* pCurNode = GetCurrentNode();
	ValueType* pNodeB = rIt.GetCurrentNode();

	return (pCurNode == pNodeB);
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
bool IteratorBinaryTree<TREE>::operator!=(const IteratorBinaryTree<TREE>& rIt) const
{
	return !(*this == rIt);
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
void IteratorBinaryTree<TREE>::reset()
{
	mCurrentIndex = 0;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
IteratorBinaryTree<TREE>::operator ValueType*()
{
	return GetCurrentNode();
}

template <class TREE>
IteratorBinaryTree<TREE>::operator IndexType() const
{
	return GetCurrentIndex();
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
typename TREE::IndexType IteratorBinaryTree<TREE>::GetCurrentIndex() const
{
	if (mNodeIndices.empty() == false)
	{
		if ((mCurrentIndex < mNodeIndices.size()) &&
			(mCurrentIndex != (uint32_t)-1))
		{
			return mNodeIndices[mCurrentIndex];
		}
	}

	return TREE::INVALID_INDEX;
}

///////////////////////////////////////////////////////////////////////

template <class TREE>
typename IteratorBinaryTree<TREE>::ValueType* IteratorBinaryTree<TREE>::GetCurrentNode() const
{
	const auto index = GetCurrentIndex();
	if (index != TREE::INVALID_INDEX)
	{
		return &(mpTree->get(index));
	}

	return nullptr;
}

///////////////////////////////////////////////////////////////////////

}
}
}

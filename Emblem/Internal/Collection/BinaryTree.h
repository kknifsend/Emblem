/**
* \file BinaryTree.h

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

#include <cstdint>
#include <vector>

#include <stack>
#include <set>

#include "Emblem/Internal/Collection/Iterator/IteratorBinaryTree.h"
#include "Emblem/Internal/Collection/Iterator/IteratorPreOrder.h"
#include "Emblem/Internal/Collection/Iterator/IteratorPostOrder.h"
#include "Emblem/Internal/Collection/Iterator/IteratorInOrder.h"

///////////////////////////////////////////////////////////////////////

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////

enum InsertDirection { LEFT, RIGHT};

/**
* \class BinaryTree
* \brief Tree utilizing indices to index nodes in the tree.
*/
template <class T, class INDEX_TYPE = uint32_t, class ALLOCATOR = std::allocator<T>>
class BinaryTree
{
	static const size_t sDefaultCapacity = 64;
	struct Node
	{
		INDEX_TYPE mLeftIndex;
		INDEX_TYPE mRightIndex;
		INDEX_TYPE mParentIndex;

		Node() : mLeftIndex(INVALID_INDEX), mRightIndex(INVALID_INDEX), mParentIndex(INVALID_INDEX) {}

		bool isLeaf() const
		{
			return (mLeftIndex == (INDEX_TYPE)-1)
				&& (mRightIndex == (INDEX_TYPE)-1);
		}
	};
public:
	typedef INDEX_TYPE IndexType;
	typedef T ValueType;

	enum { INVALID_INDEX = -1 };

	BinaryTree();
	INDEX_TYPE head() const { return mHeadIndex; }
	INDEX_TYPE left(INDEX_TYPE index) const;
	INDEX_TYPE right(INDEX_TYPE index) const;
	INDEX_TYPE parent(INDEX_TYPE index) const;

	bool isLeaf(INDEX_TYPE) const;

	void clear();
	void remove(INDEX_TYPE index);

	/**
	* \brief Inserts into node's child in the supplied direction.
	*/
	template <InsertDirection DIR = LEFT>
	INDEX_TYPE insert(INDEX_TYPE index, const T& rValue);

	/**
	* \brief Inserts into node's parent, shifting node into the supplied
	*		child of the new parent
	*/
	template <InsertDirection SHIFT_DIR = LEFT>
	INDEX_TYPE insertToHead(const T& rValue);

	/**
	* @copydoc insert()
	*/
	template <InsertDirection DIR = LEFT>
	INDEX_TYPE insert(INDEX_TYPE index, const BinaryTree& rTree);

	T& get(INDEX_TYPE index) { return mData[index]; }
	const T& get(INDEX_TYPE index) const { return mData[index]; }


	Iterator::IteratorBinaryTree<BinaryTree> beginPre() { return Iterator::IteratorPreOrder<BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginPre() const { return Iterator::IteratorPreOrder<const BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<BinaryTree> beginPre(INDEX_TYPE start) { return Iterator::IteratorPreOrder<BinaryTree>(*this, start); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginPre(INDEX_TYPE start) const { return Iterator::IteratorPreOrder<const BinaryTree>(*this, start); }


	Iterator::IteratorBinaryTree<BinaryTree> beginPost() { return Iterator::IteratorPostOrder<BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginPost() const { return Iterator::IteratorPostOrder<const BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<BinaryTree> beginPost(INDEX_TYPE start) { return Iterator::IteratorPostOrder<BinaryTree>(*this, start); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginPost(INDEX_TYPE start) const { return Iterator::IteratorPostOrder<const BinaryTree>(*this, start); }

	Iterator::IteratorBinaryTree<BinaryTree> beginIn() { return Iterator::IteratorInOrder<BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginIn() const { return Iterator::IteratorInOrder<const BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<BinaryTree> beginIn(INDEX_TYPE start) { return Iterator::IteratorInOrder<BinaryTree>(*this, start); }
	Iterator::IteratorBinaryTree<const BinaryTree> beginIn(INDEX_TYPE start) const { return Iterator::IteratorInOrder<const BinaryTree>(*this, start); }

	Iterator::IteratorBinaryTree<BinaryTree> end() { return Iterator::IteratorBinaryTree<BinaryTree>(*this); }
	Iterator::IteratorBinaryTree<const BinaryTree> end() const { return Iterator::IteratorBinaryTree<const BinaryTree>(*this); }

private:
	INDEX_TYPE createNode();
	void deleteTree(INDEX_TYPE index);

	INDEX_TYPE insertTree(const BinaryTree& rTree);

	static bool IsValid(INDEX_TYPE index);

	template <InsertDirection DIR = LEFT>
	static INDEX_TYPE& GetAdjacent(Node& rNode)
	{
		return rNode.mLeftIndex;
	}

	template <>
	static INDEX_TYPE& GetAdjacent<RIGHT>(Node& rNode)
	{
		return rNode.mRightIndex;
	}

	INDEX_TYPE mHeadIndex;
	std::vector<Node> mNodes;
	std::vector<T, ALLOCATOR> mData;
};

template <class T, class INDEX_TYPE, class ALLOCATOR>
BinaryTree<T, INDEX_TYPE, ALLOCATOR>::BinaryTree()
	: mHeadIndex(-1)
{
	mNodes.reserve(sDefaultCapacity);
	mData.reserve(sDefaultCapacity);
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::left(INDEX_TYPE index) const
{
	if (index != INVALID_INDEX)
	{
		const Node& rNode = mNodes[index];
		return rNode.mLeftIndex;
	}
	return INVALID_INDEX;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::right(INDEX_TYPE index) const
{
	if (index != INVALID_INDEX)
	{
		const Node& rNode = mNodes[index];
		return rNode.mRightIndex;
	}
	return INVALID_INDEX;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::parent(INDEX_TYPE index) const
{
	if (index != INVALID_INDEX)
	{
		const Node& rNode = mNodes[index];
		return rNode.mParentIndex;
	}
	return INVALID_INDEX;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
bool BinaryTree<T, INDEX_TYPE, ALLOCATOR>::isLeaf(INDEX_TYPE index) const
{
	if (index != INVALID_INDEX)
	{
		const Node& rNode = mNodes[index];
		return rNode.isLeaf();
	}
	return false;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
template <InsertDirection DIR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::insert(INDEX_TYPE index, const T& rValue)
{
	const INDEX_TYPE newIndex = createNode();
	mData[newIndex] = rValue;
	Node& newNode = mNodes[newIndex];

	if (!BinaryTree::IsValid(mHeadIndex))
	{
		// If head is not valid, then insert at head
		mHeadIndex = newIndex;
	}
	else
	{
		Node& rInsertPoint = mNodes[index];

		const INDEX_TYPE adjacentIndex = BinaryTree::GetAdjacent<DIR>(rInsertPoint);
		BinaryTree::GetAdjacent<DIR>(newNode) = adjacentIndex;
		BinaryTree::GetAdjacent<DIR>(rInsertPoint) = newIndex;
		newNode.mParentIndex = index;
	}

	return newIndex;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
template <InsertDirection SHIFT_DIR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::insertToHead(const T& rValue)
{
	const INDEX_TYPE newIndex = createNode();
	mData[newIndex] = rValue;
	Node& newNode = mNodes[newIndex];

	if (!BinaryTree::IsValid(mHeadIndex))
	{
		// If head is not valid, then insert at head
		mHeadIndex = newIndex;
	}
	else
	{
		// Set new parent for current head
		Node& rCurHead = mNodes[mHeadIndex];
		rCurHead.mParentIndex = newIndex;

		// Move current head into child of the new node
		BinaryTree::GetAdjacent<SHIFT_DIR>(newNode) = mHeadIndex;
		mHeadIndex = newIndex; // Set the current head to new node
	}
	return newIndex;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
template <InsertDirection DIR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::insert(INDEX_TYPE index,
	const BinaryTree& rTree)
{
	if (index != INVALID_INDEX)
	{
		const INDEX_TYPE newIndex = insertTree(rTree);
		Node& rInsertPoint = mNodes[index];
		BinaryTree::GetAdjacent<DIR>(rInsertPoint) = newIndex;
		mNodes[newIndex].mParentIndex = index;

		return newIndex;
	}
	return INVALID_INDEX;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
void BinaryTree<T, INDEX_TYPE, ALLOCATOR>::clear()
{
	mHeadIndex = 0;
	mData.clear();
	mNodes.clear();
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
void BinaryTree<T, INDEX_TYPE, ALLOCATOR>::remove(INDEX_TYPE index)
{
	deleteTree(index);
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::createNode()
{
	const INDEX_TYPE newIndex = (INDEX_TYPE)mNodes.size();
	mNodes.emplace_back();
	mData.emplace_back();
	return newIndex;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
void BinaryTree<T, INDEX_TYPE, ALLOCATOR>::deleteTree(INDEX_TYPE index)
{
	if (!BinaryTree::IsValid(index))
	{
		return;
	}

	std::stack<INDEX_TYPE> indicesToRemove;
	indicesToRemove.push(index);
	
	std::set<INDEX_TYPE> removedIndices;
	while (!indicesToRemove.empty())
	{
		const INDEX_TYPE removeOffset = indicesToRemove.top();
		indicesToRemove.pop();
		mNodes.erase(mNodes.begin() + removeOffset);
		mData.erase(mData.begin() + removeOffset);

		removedIndices.insert(removeOffset);
	}

	// adjust indices
	for (const auto removedIndex : removedIndices)
	{
		for (auto& rNode : mNodes)
		{
			if (rNode.mLeftIndex > removedIndex)
			{
				--rNode.mLeftIndex;
			}

			if (rNode.mRightIndex > removedIndex)
			{
				--rNode.mRightIndex;
			}

			if (rNode.mParentIndex > removedIndex)
			{
				--rNode.mParentIndex;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
INDEX_TYPE BinaryTree<T, INDEX_TYPE, ALLOCATOR>::insertTree(const BinaryTree& rTree)
{
	const INDEX_TYPE insertOffset = (INDEX_TYPE)mNodes.size();
	const size_t numOfNodesToAdd = rTree.mNodes.size();

	const size_t numOfNodes = insertOffset + numOfNodesToAdd;
	mNodes.resize(numOfNodes);
	mData.resize(numOfNodes);

	for (size_t i = 0; i < numOfNodesToAdd; ++i)
	{
		mNodes[insertOffset + i] = rTree.mNodes[i];
		mData[insertOffset + i] = rTree.mData[i];

		if (mNodes[insertOffset + i].mLeftIndex != INVALID_INDEX)
		{
			mNodes[insertOffset + i].mLeftIndex += insertOffset;
		}

		if (mNodes[insertOffset + i].mRightIndex != INVALID_INDEX)
		{
			mNodes[insertOffset + i].mRightIndex += insertOffset;
		}
		
		if (mNodes[insertOffset + i].mParentIndex != INVALID_INDEX)
		{
			mNodes[insertOffset + i].mParentIndex += insertOffset;
		}
	}

	return rTree.mHeadIndex + insertOffset;
}

///////////////////////////////////////////////////////////////////////

template <class T, class INDEX_TYPE, class ALLOCATOR>
bool BinaryTree<T, INDEX_TYPE, ALLOCATOR>::IsValid(INDEX_TYPE index)
{
	return (index != (INDEX_TYPE)INVALID_INDEX);
}

///////////////////////////////////////////////////////////////////////

}
}

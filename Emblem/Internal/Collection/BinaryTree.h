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
#include <memory>
#include <iterator>

///////////////////////////////////////////////////////////////////////

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////
template <class NodeType>
class Node
{
public:
    NodeType* mpLeftNode;
    NodeType* mpRightNode;

    Node()
        : mpLeftNode(nullptr), mpRightNode(nullptr) {}

    virtual ~Node() {}

    bool isLeaf() const
    {
        return (mpLeftNode == nullptr)
               && (mpRightNode == nullptr);
    }

};

/**
* \class BinaryTree
* \brief Tree utilizing indices to index nodes in the tree.
*/
template <class NodeType>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree(BinaryTree&&);
    BinaryTree& operator=(const BinaryTree&);
    BinaryTree& operator=(BinaryTree&&);
    virtual ~BinaryTree();

    NodeType* createNode()
    {
        new NodeType;
    }

    /**
    * \brief Inserts and takes ownership of node.
    */
    const NodeType* insertChildLeft(const NodeType* pParentNode, const NodeType* pChildNode);
    const NodeType* insertChildRight(const NodeType* pParentNode, const NodeType* pChildNode);

    void clear();

    const NodeType* head()
    {
        return mpHead;
    }

    const NodeType* const head() const
    {
        return mpHead;
    }

    NodeType* release()
    {
        NodeType* pHead = mpHead;
        mpHead = nullptr;
        return pHead;
    }

    BinaryTree clone() const;

private:
    const NodeType* insertToHead(const NodeType* pNode);

    NodeType* mpHead;
};

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>::BinaryTree()
    : mpHead(nullptr)
{
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>::BinaryTree(const BinaryTree&)
{

}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>::BinaryTree(BinaryTree&&)
{

}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>& BinaryTree<NodeType>::operator=(const BinaryTree&)
{

}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>& BinaryTree<NodeType>::operator=(BinaryTree&&)
{

}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>::~BinaryTree()
{
    clear();
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
void BinaryTree<NodeType>::clear()
{
    if (mpHead == nullptr)
    {
        return;
    }

    std::set<NodeType*> nodes;

    std::stack<NodeType*> nodesToWalk;
    nodesToWalk.push(mpHead);
    mpHead = nullptr;

    while (!nodesToWalk.empty())
    {
        NodeType* pNode = nodesToWalk.top();
        nodesToWalk.pop();
        if (pNode == nullptr)
        {
            continue;
        }

        nodes.insert(pNode);
        nodesToWalk.push(pNode->mpLeftNode);
        nodesToWalk.push(pNode->mpRightNode);
    }

    for (NodeType* pNode : nodes)
    {
        pNode->mpLeftNode = nullptr;
        pNode->mpRightNode = nullptr;

        delete pNode;
    }
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertChildLeft(
    const NodeType* pParentNode, const NodeType* pChildNode)
{
    if ((mpHead == nullptr) || (pParentNode == nullptr))
    {
        return insertToHead(pNewNode);
    }

    if (pParentNode->mpLeftNode != nullptr)
    {
        pChildNode->mpLeftNode = pParentNode->mpLeftNode;
    }
    pParentNode->mpLeftNode = pChildNode;

    return pChildNode;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertChildRight(
    const NodeType* pParentNode, const NodeType* pChildNode)
{
    if ((mpHead == nullptr) || (pParentNode == nullptr))
    {
        return insertToHead(pNewNode);
    }

    if (pParentNode->mpRightNode != nullptr)
    {
        pChildNode->mpRightNode = pParentNode->mpRightNode;
    }
    pParentNode->mpRightNode = pChildNode;

    return pChildNode;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertToHead(const NodeType* pNode)
{
    clear();
    mpHead = pNode;
    return mpHead;
}

///////////////////////////////////////////////////////////////////////

}
}

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

namespace Emblem
{
namespace Internal
{

///////////////////////////////////////////////////////////////////////

template <class NodeType>
class Node
{
public:
    NodeType* mpParentNode;
    NodeType* mpLeftNode;
    NodeType* mpRightNode;

    Node()
        : mpParentNode(nullptr), mpLeftNode(nullptr), mpRightNode(nullptr) {}

    virtual ~Node() {}

    bool isLeaf() const
    {
        return (mpLeftNode == nullptr)
               && (mpRightNode == nullptr);
    }

    virtual NodeType* clone() = 0;

    NodeType* cloneTree()
    {
        NodeType* pClone = clone();
        if (mpLeftNode != nullptr)
        {
            pClone->mpLeftNode = mpLeftNode->cloneTree();
            pClone->mpLeftNode->mpParentNode = pClone;
        }

        if (mpRightNode != nullptr)
        {
            pClone->mpRightNode = mpRightNode->cloneTree();
            pClone->mpRightNode->mpParentNode = pClone;
        }

        return pClone;
    }
};

///////////////////////////////////////////////////////////////////////

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
    const NodeType* insertChildLeft(NodeType* pParentNode, NodeType* pChildNode);
    const NodeType* insertChildRight(NodeType* pParentNode, NodeType* pChildNode);
    const NodeType* insertToHead(NodeType* pNode);

    void replace(NodeType* pNodeToReplace, NodeType* pReplacementNode)
    {
        if ((pNodeToReplace == nullptr) || (pReplacementNode == nullptr))
        {
            return;
        }

        if (pNodeToReplace == mpHead)
        {
            insertToHead(pReplacementNode);
            return;
        }

        NodeType* pParentNode = pNodeToReplace->mpParentNode;
        if (pParentNode->mpLeftNode == pNodeToReplace)
        {
            delete pParentNode->mpLeftNode;
            pParentNode->mpLeftNode = pReplacementNode;
        }
        else
        {
            delete pParentNode->mpRightNode;
            pParentNode->mpRightNode = pReplacementNode;
        }

    }

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

    void swap(BinaryTree<NodeType>& rOther)
    {
        std::swap(mpHead, rOther.mpHead);
    }

    BinaryTree clone() const;

private:

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
BinaryTree<NodeType>::BinaryTree(const BinaryTree& rOther)
    : mpHead(nullptr)
{
    if (rOther.mpHead != nullptr)
    {
        mpHead = rOther.mpHead->cloneTree();
    }
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>::BinaryTree(BinaryTree&& rOther)
    : mpHead(nullptr)
{
    mpHead = rOther.mpHead;
    rOther.mpHead = nullptr;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>& BinaryTree<NodeType>::operator=(const BinaryTree& rOther)
{
    if (this != &rOther)
    {
        clear();
        if (rOther.mpHead != nullptr)
        {
            mpHead = rOther.mpHead->cloneTree();
        }
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType>& BinaryTree<NodeType>::operator=(BinaryTree&& rOther)
{
    clear();
    mpHead = rOther.mpHead;
    rOther.mpHead = nullptr;

    return *this;
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
        pNode->mpParentNode = nullptr;

        delete pNode;
    }
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
BinaryTree<NodeType> BinaryTree<NodeType>::clone() const
{
    BinaryTree tree;
    if (mpHead != nullptr)
    {
        tree.mpHead = mpHead->cloneTree();
    }
    return tree;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertChildLeft(
    NodeType* pParentNode, NodeType* pChildNode)
{
    if ((mpHead == nullptr) || (pParentNode == nullptr))
    {
        return insertToHead(pChildNode);
    }

    if (pParentNode->mpLeftNode != nullptr)
    {
        pChildNode->mpLeftNode = pParentNode->mpLeftNode;
        pChildNode->mpLeftNode->mpParentNode = pChildNode;
    }
    pParentNode->mpLeftNode = pChildNode;
    pChildNode->mpParentNode = pParentNode;

    return pChildNode;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertChildRight(
    NodeType* pParentNode, NodeType* pChildNode)
{
    if ((mpHead == nullptr) || (pParentNode == nullptr))
    {
        return insertToHead(pChildNode);
    }

    if (pParentNode->mpRightNode != nullptr)
    {
        pChildNode->mpRightNode = pParentNode->mpRightNode;
        pChildNode->mpRightNode->mpParentNode = pChildNode;
    }
    pParentNode->mpRightNode = pChildNode;
    pChildNode->mpParentNode = pParentNode;

    return pChildNode;
}

///////////////////////////////////////////////////////////////////////

template <class NodeType>
const NodeType* BinaryTree<NodeType>::insertToHead(NodeType* pNode)
{
    clear();
    mpHead = pNode;
    return mpHead;
}

///////////////////////////////////////////////////////////////////////

} // namespace Internal
} // namespace Emblem
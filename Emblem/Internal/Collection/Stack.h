/**
* \file Stack.h

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

#include "Emblem/Internal/Collection/IfcPack.h"

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////

/**
* \class Stack
*/
template <class T>
class Stack : public IfcPack<T>
{
	std::stack<T> mStack;
public:
	void push(const T& rA);
	bool pop();

	T top() const;

	bool empty() const;

	size_t size() const;
};

///////////////////////////////////////////////////////////////////////

template <class T>
void Stack<T>::push(const T& rA)
{
	mStack.push(rA);
}

///////////////////////////////////////////////////////////////////////

template <class T>
bool Stack<T>::pop()
{
	if (!mStack.empty())
	{
		mStack.pop();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////

template <class T>
T Stack<T>::top() const
{
	return mStack.top();
}

///////////////////////////////////////////////////////////////////////

template <class T>
bool Stack<T>::empty() const
{
	return mStack.empty();
}

///////////////////////////////////////////////////////////////////////

template <class T>
size_t Stack<T>::size() const
{
	return mStack.size();
}

///////////////////////////////////////////////////////////////////////

}
}
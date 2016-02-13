/**
* \file Queue.h

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

#include <queue>

#include "Emblem/Internal/Collection/IfcPack.h"

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////

/**
* \class Queue
*/
template <class T>
class Queue : public IfcPack<T>
{
	std::queue<T> mQueue;
public:
	void push(const T& rA);
	bool pop();

	T top() const;

	bool empty() const;

	size_t size() const;
};

///////////////////////////////////////////////////////////////////////

template <class T>
void Queue<T>::push(const T& rA)
{
	mQueue.push(rA);
}

///////////////////////////////////////////////////////////////////////

template <class T>
bool Queue<T>::pop()
{
	if (!mQueue.empty())
	{
		mQueue.pop();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////

template <class T>
T Queue<T>::top() const
{
	return mQueue.front();
}

///////////////////////////////////////////////////////////////////////

template <class T>
bool Queue<T>::empty() const
{
	return mQueue.empty();
}

///////////////////////////////////////////////////////////////////////

template <class T>
size_t Queue<T>::size() const
{
	return mQueue.size();
}

///////////////////////////////////////////////////////////////////////

}
}
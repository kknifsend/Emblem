/**
* \file IfcPack.h

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

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////

/**
* \class IfcPack
* \brief Base for Stack/Queue implementation.
*/
template <class T>
class IfcPack
{
public:
	virtual void push(const T& rA) = 0;
	virtual bool pop() = 0;

	virtual T top() const = 0;

	virtual bool empty() const = 0;

	virtual size_t size() const = 0;
};

///////////////////////////////////////////////////////////////////////

}
}
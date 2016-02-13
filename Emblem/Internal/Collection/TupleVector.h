/**
* \file TupleVector.h

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

#include <vector>
#include <tuple>
#include <type_traits>

namespace Emblem
{
namespace Collection
{

///////////////////////////////////////////////////////////////////////

/**
* \class SmartType
* \brief Simple template used to pass both type and allocator.
* \tparam T Types of which we should create a vector.
*/

template <class T, class ALLOCATOR = std::allocator<T>>
struct SmartType
{
	typedef T Type;
	typedef ALLOCATOR Allocator;
};

///////////////////////////////////////////////////////////////////////

//! @cond
template <typename T, typename... Ts> struct Index;

template <typename T, typename... Ts>
struct Index<T, T, Ts...> : std::integral_constant<std::size_t, 0> {};

template <typename T, typename Tail, typename... Ts>
struct Index<T, Tail, Ts...> :
	std::integral_constant<std::size_t, 1 + Index<T, Ts...>::value> {};
//! @endcond

///////////////////////////////////////////////////////////////////////

/**
* \class TupleVector
* \brief Creates a vector for each type supplied.
* \tparam T Types of which we should create a vector.
*
* Types should be supplied via a SmartType structure.
* After initialization, functions take inner type of SmartType.
*/
template <class... T>
class TupleVector
{
	typedef std::tuple<std::vector<typename T::Type, typename T::Allocator>...> Tuple;

public:
	TupleVector() {}

	template <class U> U& at(size_t index);
	template <class U> const U& at(size_t index) const;

	template <class U> void push_back(const U& rU);
	template <class U> void resize(size_t s);
	template <class U> void reserve(size_t s);

	template <class U> size_t size() const;
	template <class U> bool empty() const;

	template <class U> void clear();

	template <class U> U* data();
	template <class U> const U* data() const;

	/** \brief Joins the vectors of given type. */
	template <class U> void concatenate(const TupleVector&);

private:
	template <class U>
	inline auto& getVector()
	{
		constexpr size_t index = Index<U, typename T::Type...>::value;
		return std::get<index>(mData);
	}

	template <class U>
	inline auto& getVector() const
	{
		constexpr size_t index = Index<U, typename T::Type...>::value;
		return std::get<index>(mData);
	}

	Tuple mData;
};

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
U& TupleVector<T...>::at(size_t index)
{
	return getVector<U>().at(index);
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U> 
const U& TupleVector<T...>::at(size_t index) const
{
	return getVector<U>().at(index);
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
void TupleVector<T...>::push_back(const U& rU)
{
	getVector<U>().push_back(rU);
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
void TupleVector<T...>::resize(size_t s)
{
	getVector<U>().resize(s);
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
void TupleVector<T...>::reserve(size_t s)
{
	getVector<U>().reserve(s);
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
size_t TupleVector<T...>::size() const
{
	return getVector<U>().size();
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
bool TupleVector<T...>::empty() const
{
	return getVector<U>().empty();
}

///////////////////////////////////////////////////////////////////////
template <class... T>
template <class U>
void TupleVector<T...>::clear()
{
	getVector<U>().clear();
}

///////////////////////////////////////////////////////////////////////
template <class... T>
template <class U> 
U* TupleVector<T...>::data()
{
	return getVector<U>().data();
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U>
const U* TupleVector<T...>::data() const
{
	return getVector<U>().data();
}

///////////////////////////////////////////////////////////////////////

template <class... T>
template <class U> 
void TupleVector<T...>::concatenate(const TupleVector& rVec)
{
	auto& rVector = getVector<U>();
	for (const auto& rData : rVec.getVector<U>())
	{
		rVector.push_back(rData);
	}
}

///////////////////////////////////////////////////////////////////////

}
}
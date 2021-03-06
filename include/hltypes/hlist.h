/// @file
/// @version 4.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Encapsulates std::list and adds high level methods.

#ifndef HLTYPES_LIST_H
#define HLTYPES_LIST_H

#include <list>

#include "hcontainer.h"
#include "hexception.h"
#include "hltypesUtil.h"
#include "hstring.h"

/// @brief Provides a simpler syntax to iterate through a List.
#define foreach_l(type, name, container) for (typename hltypes::List< type >::iterator_t name = (container).begin(), name ## End = (container).end(); name != name ## End; ++name)
/// @brief Provides a simpler syntax to iterate through a List.
#define foreachc_l(type, name, container) for (typename hltypes::List< type >::const_iterator_t name = (container).begin(), name ## End = (container).end(); name != name ## End; ++name)
/// @brief Provides a simpler syntax to reverse iterate through a List.
#define foreach_lr(type, name, container) for (typename hltypes::List< type >::riterator_t name = (container).rbegin(), name ## End = (container).rend(); name != name ## End; ++name)
/// @brief Provides a simpler syntax to reverse iterate through a List.
#define foreachc_lr(type, name, container) for (typename hltypes::List< type >::const_riterator_t name = (container).rbegin(), name ## End = (container).rend(); name != name ## End; ++name)

namespace hltypes
{
	/// @brief Encapsulates std::list and adds high level methods.
	template <typename T>
	class List : public Container<std::list<T>, T>
	{
	public:
		/// @brief Empty constructor.
		inline List() :
			Container<std::list<T>, T>()
		{
		}
		/// @brief Copy constructor.
		/// @param[in] other Container to copy.
		inline List(const Container<std::list<T>, T>& other) :
			Container<std::list<T>, T>(other)
		{
		}
		/// @brief Constructor from single element.
		/// @param[in] element Element to insert.
		/// @note The explicit prevents "var = element" from working.
		inline explicit List(const T& element) :
			Container<std::list<T>, T>(element)
		{
		}
		/// @brief Constructor from single element.
		/// @param[in] element Element to insert.
		/// @param[in] times Number of times to insert element.
		inline List(const T& element, int times) :
			Container<std::list<T>, T>(element, times)
		{
		}
		/// @brief Constructor from another Container.
		/// @param[in] other Container to copy.
		/// @param[in] count Number of elements to copy.
		inline List(const Container<std::list<T>, T>& other, const int count) :
			Container<std::list<T>, T>(other, count)
		{
		}
		/// @brief Constructor from another Container.
		/// @param[in] other Container to copy.
		/// @param[in] start Start index of elements to copy.
		/// @param[in] count Number of elements to copy.
		inline List(const Container<std::list<T>, T>& other, const int start, const int count) :
			Container<std::list<T>, T>(other, start, count)
		{
		}
		/// @brief Constructor from C-type array.
		/// @param[in] other C-type array to copy.
		/// @param[in] count Number of elements to copy.
		inline List(const T other[], const int count) :
			Container<std::list<T>, T>(other, count)
		{
		}
		/// @brief Constructor from C-type array.
		/// @param[in] other C-type array to copy.
		/// @param[in] start Start index of elements to copy.
		/// @param[in] count Number of elements to copy.
		inline List(const T other[], const int start, const int count) :
			Container<std::list<T>, T>(other, start, count)
		{
		}
		/// @brief Gets all indices.
		/// @return All indices.
		inline List<int> indices() const
		{
			return this->template _indices<List<int> >();
		}
		/// @brief Gets all indices of the given element.
		/// @param[in] element Element to search for.
		/// @return All indices of the given element.
		inline List<int> indicesOf(const T& element) const
		{
			return this->template _indicesOf<List<int> >(element);
		}
		/// @brief Removes element at given index.
		/// @param[in] index Index of element to remove.
		/// @return The removed element.
		inline T removeAt(int index)
		{
			return Container<std::list<T>, T>::removeAt(index);
		}
		/// @brief Removes n elements at given index of List.
		/// @param[in] index Start index of elements to remove.
		/// @param[in] count Number of elements to remove.
		/// @return List of all removed elements.
		/// @note Elements in the returned List are in the same order as in the orignal List.
		inline List<T> removeAt(int index, int count)
		{
			return this->template _removeAt<List<T> >(index, count);
		}
		/// @brief Removes first element of List.
		/// @return The removed element.
		inline T removeFirst()
		{
			return Container<std::list<T>, T>::removeFirst();
		}
		/// @brief Removes n elements from the beginning of List.
		/// @param[in] count Number of elements to remove.
		/// @return List of all removed elements.
		/// @note Elements in the returned List are in the same order as in the orignal List.
		inline List<T> removeFirst(const int count)
		{
			return this->template _removeFirst<List<T> >(count);
		}
		/// @brief Removes last element of List.
		/// @return The removed element.
		inline T removeLast()
		{
			return Container<std::list<T>, T>::removeLast();
		}
		/// @brief Removes n elements from the end of List.
		/// @param[in] count Number of elements to remove.
		/// @return List of all removed elements.
		/// @note Elements in the returned List are in the same order as in the orignal List.
		inline List<T> removeLast(const int count)
		{
			return this->template _removeLast<List<T> >(count);
		}
		/// @brief Gets a random element in List and removes it.
		/// @return Random element.
		inline T removeRandom()
		{
			return Container<std::list<T>, T>::removeRandom();
		}
		/// @brief Gets an List of random elements selected from this one and removes them.
		/// @param[in] count Number of random elements.
		/// @return List of random elements selected from this one.
		inline List<T> removeRandom(const int count)
		{
			return this->template _removeRandom<List<T> >(count);
		}
		/// @brief Gets a random element in List.
		/// @return Random element.
		inline T random() const
		{
			return Container<std::list<T>, T>::random();
		}
		/// @brief Gets an List of random elements selected from this one.
		/// @param[in] count Number of random elements.
		/// @param[in] unique Whether to force all random values to be at unique positions.
		/// @return List of random elements selected from this one.
		inline List<T> random(int count, bool unique = true) const
		{
			return this->template _random<List<T> >(count, unique);
		}
		/// @brief Creates new List with reversed order of elements.
		/// @return A new List.
		inline List<T> reversed() const
		{
			return this->template _reversed<List<T> >();
		}
		/// @brief Creates new List without duplicates.
		/// @return A new List.
		inline List<T> removedDuplicates() const
		{
			return this->template _removedDuplicates<List<T> >();
		}
		/// @brief Creates new sorted List.
		/// @return A new List.
		/// @note The sorting order is ascending.
		inline List<T> sorted() const
		{
			return this->template _sorted<List<T> >();
		}
		/// @brief Creates new sorted List.
		/// @param[in] compareFunction Function pointer with comparison function that takes two elements of type T and returns bool.
		/// @return A new List.
		/// @note The sorting order is ascending.
		/// @note compareFunction should return true if first element is less than the second element.
		inline List<T> sorted(bool (*compareFunction)(T const&, T const&)) const
		{
			return this->template _sorted<List<T> >(compareFunction);
		}
		/// @brief Creates a new List with randomized order of elements.
		/// @return A new List.
		inline List<T> randomized() const
		{
			return this->template _randomized<List<T> >();
		}
		/// @brief Creates a new List as union of this List with an element.
		/// @param[in] element Element to unite with.
		/// @return A new List.
		/// @note Removes duplicates.
		inline List<T> united(const T& element) const
		{
			return this->template _united<List<T> >(element);
		}
		/// @brief Creates a new List as union of this List with another one.
		/// @param[in] other List to unite with.
		/// @return A new List.
		/// @note Removes duplicates.
		inline List<T> united(const List<T>& other) const
		{
			return this->template _united<List<T> >(other);
		}
		/// @brief Creates a new List as intersection of this List with another one.
		/// @param[in] other List to intersect with.
		/// @return A new List.
		/// @note Does not remove duplicates.
		inline List<T> intersected(const List<T>& other) const
		{
			return this->template _intersected<List<T> >(other);
		}
		/// @brief Creates a new List as difference of this List with an element.
		/// @param[in] element Element to differentiate with.
		/// @return A new List.
		/// @note Unlike remove, this method ignores if the element is not in this List.
		/// @note Does not remove duplicates.
		inline List<T> differentiated(const T& element) const
		{
			return this->template _differentiated<List<T> >(element);
		}
		/// @brief Creates a new List as difference of this List with another one.
		/// @param[in] other List to differentiate with.
		/// @return A new List.
		/// @note Unlike remove, this method ignore elements of other List that are not in this one.
		/// @note Does not remove duplicates.
		inline List<T> differentiated(const List<T>& other) const
		{
			return this->template _differentiated<List<T> >(other);
		}
		/// @brief Creates new List with new elements obtained from the current List elements.
		/// @param[in] generateFunction Function pointer with generation function for the new elements.
		/// @return A new List with the new elements.
		template <typename S>
		inline List<S> mapped(S (*generateFunction)(T const&)) const
		{
			return this->template _mapped<List<S>, S>(generateFunction);
		}
		/// @brief Finds and returns new List of elements that match the condition.
		/// @param[in] conditionFunction Function pointer with condition function that takes one element of type T and returns bool.
		/// @return New List with all matching elements.
		inline List<T> findAll(bool (*conditionFunction)(T const&)) const
		{
			return this->template _findAll<List<T> >(conditionFunction);
		}
		/// @brief Returns a new List with all elements cast into type S.
		/// @return A new List with all elements cast into type S.
		/// @note Make sure all elements in the List can be cast into type S.
		template <typename S>
		inline List<S> cast() const
		{
			return this->template _cast<List<S>, S>();
		}
		/// @brief Returns a new List with all elements dynamically cast into type S.
		/// @param[in] includeNulls Whether to include NULLs that failed to cast.
		/// @return A new List with all elements cast into type S.
		/// @note Be careful not to use this function with non-pointers and classes that don't have virtual functions.
		template <typename S>
		inline List<S> dynamicCast(bool includeNulls = false) const
		{
			return this->template _dynamicCast<List<S>, S>(includeNulls);
		}
		/// @brief Returns element at specified position.
		/// @param[in] index Index of the element.
		/// @return Element at specified position.
		/// @note Does not work with bool as T.
		inline T& operator[](int index)
		{
			return this->at(index);
		}
		/// @brief Returns element at specified position.
		/// @param[in] index Index of the element.
		/// @return Element at specified position.
		/// @note Does not work with bool as T.
		inline const T& operator[](int index) const
		{
			return this->at(index);
		}
		/// @brief Returns a sublist.
		/// @param[in] start Start index of the elements to copy.
		/// @param[in] count Number of elements to copy.
		/// @return Sublist created from the current List.
		inline List<T> operator()(int start, const int count) const
		{
			return this->template _sub<List<T> >(start, count);
		}
		/// @brief Same as equals.
		/// @see equals
		inline bool operator==(const List<T>& other) const
		{
			return this->equals(other);
		}
		/// @brief Same as nequals.
		/// @see nequals
		inline bool operator!=(const List<T>& other) const
		{
			return this->nequals(other);
		}
		/// @brief Same as add.
		/// @see add(const T& element)
		inline List<T>& operator<<(const T& element)
		{
			this->add(element);
			return (*this);
		}
		/// @brief Same as add.
		/// @see add(const List<T>& other)
		inline List<T>& operator<<(const List<T>& other)
		{
			this->add(other);
			return (*this);
		}
		/// @brief Same as add.
		/// @see add(const T& element)
		inline List<T>& operator+=(const T& element)
		{
			this->add(element);
			return (*this);
		}
		/// @brief Same as add.
		/// @see add(const List<T>& other)
		inline List<T>& operator+=(const List<T>& other)
		{
			this->add(other);
			return (*this);
		}
		/// @brief Same as remove.
		/// @see remove(T element)
		inline List<T>& operator-=(T element)
		{
			this->remove(element);
			return (*this);
		}
		/// @brief Same as remove.
		/// @see remove(const List<T>& other)
		inline List<T>& operator-=(const List<T>& other)
		{
			this->remove(other);
			return (*this);
		}
		/// @brief Same as unite.
		/// @see unite(const T& element)
		inline List<T>& operator|=(const T& element)
		{
			this->unite(element);
			return (*this);
		}
		/// @brief Same as unite.
		/// @see unite(const List<T>& other)
		inline List<T>& operator|=(const List<T>& other)
		{
			this->unite(other);
			return (*this);
		}
		/// @brief Same as intersect.
		/// @see intersect(const List<T>& other)
		inline List<T>& operator&=(const List<T>& other)
		{
			this->intersect(other);
			return (*this);
		}
		/// @brief Same as differentiate.
		/// @see differentiate(const T& element)
		inline List<T>& operator/=(const T& element)
		{
			this->differentiate(element);
			return (*this);
		}
		/// @brief Same as differentiate.
		/// @see differentiate(const List<T>& other)
		inline List<T>& operator/=(const List<T>& other)
		{
			this->differentiate(other);
			return (*this);
		}
		/// @brief Merges a List with an element.
		/// @param[in] element Element to merge with.
		/// @return New List with element added at the end of List.
		inline List<T> operator+(const T& element) const
		{
			List<T> result(*this);
			result += element;
			return result;
		}
		/// @brief Merges two Lists.
		/// @param[in] other Second List to merge with.
		/// @return New List with elements of second List added at the end of first List.
		inline List<T> operator+(const List<T>& other) const
		{
			List<T> result(*this);
			result += other;
			return result;
		}
		/// @brief Removes element from List.
		/// @param[in] element Element to remove.
		/// @return New List with elements of first List without given element.
		inline List<T> operator-(T element) const
		{
			List<T> result(*this);
			result -= element;
			return result;
		}
		/// @brief Removes second List from first List.
		/// @param[in] other List to remove.
		/// @return New List with elements of first List without the elements of second List.
		inline List<T> operator-(const List<T>& other) const
		{
			List<T> result(*this);
			result -= other;
			return result;
		}
		/// @brief Same as united.
		/// @see united(const T& element)
		inline List<T> operator|(const T& element) const
		{
			return this->united(element);
		}
		/// @brief Same as united.
		/// @see united(const List<T>& other)
		inline List<T> operator|(const List<T>& other) const
		{
			return this->united(other);
		}
		/// @brief Same as intersected.
		/// @see intersected(const List<T>& other)
		inline List<T> operator&(const List<T>& other) const
		{
			return this->intersected(other);
		}
		/// @brief Same as differentiated.
		/// @see differentiated(const T& element)
		inline List<T> operator/(const T& element) const
		{
			return this->differentiated(element);
		}
		/// @brief Same as differentiated.
		/// @see differentiated(const List<T>& other)
		inline List<T> operator/(const List<T>& other) const
		{
			return this->differentiated(other);
		}

	};
	
}

/// @brief Alias for simpler code.
#define hlist hltypes::List

#endif

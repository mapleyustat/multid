#ifndef _IntArray_h
#define _IntArray_h

// Control macros:
//
//	IntArray_SHALLOW	-- see below
//	IntArray_DEBUG		-- turn on debugging
//	IntArray_NO_CHECKING	-- turn off range checking

// The semantics of the copy constructor, of the assignment operator,
// and of the copy() and ref() member functions are as follows:
//
// By default:
//
//	IntArray(const IntArray &int_array):
//		a. If shallow_copy() has been called by int_array,
//		   make "*this" a clone of (i.e., reference to) "int_array".
//		b. Otherwise copy the components of "int_array" into "*this".
//
//	IntArray &operator=(const IntArray &):
//		Detach "*this" from its clones
//		and copy the components of "int_array" into it.
//
//	IntArray &copy(const IntArray &):
//		Copy the components of "int_array" into "*this"
//		(without detaching "*this" from its clones).
//		The sizes of "*this" and "int_array" must match.
//
//	IntArray &ref(IntArray &):
//		Detach "*this" from its clones
//		and make it a clone of "int_array".
//
// When the return value of a function has type "IntArray" (as opposed
// to "IntArray &"), it is prudent to return a IntArray that has called
// shallow_copy().  This way, the copy constructors called while
// returning by value make clones rather than copy components.
//
// If "IntArray_SHALLOW" is defined:
//
//	IntArray(const IntArray &):			copy by reference
//	IntArray &operator=(const IntArray &):	delete; copy by reference
//	IntArray &copy(const IntArray &):		delete; copy by value
//	IntArray &ref(IntArray &):			delete; copy by reference

#include <iostream>
#include <cstring>

class ActualIntArray {
public:
	class InvalidSize : public std::exception { };

private:
	ActualIntArray(void);
	ActualIntArray(int size_);
	ActualIntArray(int size_, int *coords_);
	ActualIntArray(const ActualIntArray &actual_int_array);
	~ActualIntArray(void);
	ActualIntArray &operator=(const ActualIntArray &actual_int_array);
	void copy_coords(const ActualIntArray &actual_int_array);
	void zero(void);

	int size;
	int *coords;
	int count;

	friend class IntArray;
};

class IntArray {
public:
	IntArray(void);
	IntArray(int size_);
	IntArray(int size_, int *coords_);
	IntArray(const IntArray &int_array);
	virtual ~IntArray(void);
	IntArray &operator=(const IntArray &int_array);
	IntArray &copy(const IntArray &int_array);
	IntArray &ref(IntArray &int_array);
	void resize(int size_);
	IntArray &zero(void);

	int size(void) const;
	void range_check(int comp) const;
	IntArray &shallow_copy(void);

	int &operator()(int comp);
	int operator()(int comp) const;
	int &component(int comp);
	int component(int comp) const;

	class RangeViolation : public std::exception { };
	class SizeMismatch : public std::exception { };

protected:
	ActualIntArray *actual;
	int *coords;
	bool shallow;

	IntArray &copy_by_reference(const IntArray &int_array);
	IntArray &copy_by_value(const IntArray &int_array);
};

std::ostream &operator<<(std::ostream &os, const IntArray &int_array);
std::istream &operator>>(std::istream &is, IntArray &int_array);

inline void
ActualIntArray::copy_coords(const ActualIntArray &actual_int_array)
{
#if HAVE_STRING_H
	memcpy(coords, actual_int_array.coords, size*sizeof(int));
#else
	int *p = coords;
	int *end = coords + size;
	int *q = actual_int_array.coords;
	while (p < end)
		*p++ = *q++;
#endif
}

inline
ActualIntArray::ActualIntArray(void)
	: size(0),
	  coords(0),
	  count(1)
{
}

inline
ActualIntArray::ActualIntArray(int size_)
	: size(0),
	  coords(0),
	  count(1)
{
#ifndef IntArray_NO_CHECKING
	if (size_ < 0)
		throw InvalidSize();
#endif
	size = size_;
	coords = new int[size];
	count = 1;
}

inline
ActualIntArray::ActualIntArray(int size_, int *coords_)
	: size(size_),
	  coords(coords_),
	  count(2)
{
}

inline
ActualIntArray::ActualIntArray(const ActualIntArray &actual_int_array)
	: size(actual_int_array.size),
	  coords(new int[size]),
	  count(1)
{
	copy_coords(actual_int_array);
}

inline
ActualIntArray::~ActualIntArray(void)
{
	delete [] coords;
}

inline void
ActualIntArray::zero(void)
{
#if HAVE_STRING_H
	memset(coords, 0, size*sizeof(int));
#else
	int *p = coords;
	int *end = coords + size;
	while (p < end)
		*p++ = 0;
#endif
}

inline int
IntArray::size(void) const
{
	return actual->size;
}

inline IntArray &
IntArray::copy_by_reference(const IntArray &int_array)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::copy_by_reference(const IntArray &) called\n";
#endif
	int_array.actual->count++;	// done first in case lhs == rhs
	if (--actual->count == 0)
		delete actual;
	actual = int_array.actual;
	coords = int_array.coords;
	shallow = false;
	return *this;
}

inline IntArray &
IntArray::copy_by_value(const IntArray &int_array)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::copy_by_value(const IntArray &) called\n";
#endif
	if (&int_array != this) {
		if (--actual->count == 0)
			delete actual;
		actual = new ActualIntArray(*int_array.actual);
		coords = actual->coords;
		shallow = false;
	}
	return *this;
}

inline
IntArray::IntArray(void)
	: actual(new ActualIntArray),
	  coords(0),
	  shallow(false)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::IntArray(void) called\n";
#endif
}

inline
IntArray::IntArray(int size_)
	: actual(new ActualIntArray(size_)),
	  coords(actual->coords),
	  shallow(false)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::IntArray(int) called\n";
#endif
}

inline
IntArray::IntArray(int size_, int *coords_)
	: actual(new ActualIntArray(size_, coords_)),
	  coords(coords_),
	  shallow(false)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::IntArray(int, int *) called\n";
#endif
}

#ifdef IntArray_SHALLOW

inline
IntArray::IntArray(const IntArray &int_array)
	: actual(int_array.actual),
	  coords(int_array.coords),
	  shallow(false)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::IntArray(IntArray &) called\n";
#endif
	actual->count++;
}

#else /* ! IntArray_SHALLOW */

inline
IntArray::IntArray(const IntArray &int_array)
	: actual(int_array.shallow ? int_array.actual
		: new ActualIntArray(*int_array.actual)),
	  coords(int_array.shallow ? int_array.coords : actual->coords),
	  shallow(false)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::IntArray(IntArray &) called\n";
#endif
	if (int_array.shallow) {
		actual->count++;
#ifdef IntArray_DEBUG
		std::cerr << "IntArray::IntArray(IntArray &): shallow copy\n";
#endif
	}
#ifdef IntArray_DEBUG
	else
		std::cerr << "IntArray::IntArray(IntArray &): deep copy\n";
#endif
}

#endif /* IntArray_SHALLOW */

inline IntArray &
IntArray::operator=(const IntArray &int_array)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::operator=(const IntArray &) called\n";
#endif
#ifdef IntArray_SHALLOW
	return copy_by_reference(int_array);
#else
	return copy_by_value(int_array);
#endif
}

inline IntArray &
IntArray::copy(const IntArray &int_array)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::copy(const IntArray &) called\n";
#endif
#ifdef IntArray_SHALLOW
	return copy_by_value(int_array);
#else
#ifndef IntArray_NO_CHECKING
	if (int_array.size() != size())
		throw SizeMismatch();
#endif
	actual->copy_coords(*int_array.actual);
	return *this;
#endif
}

inline IntArray &
IntArray::ref(IntArray &int_array)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::ref(IntArray &) called\n";
#endif
	return copy_by_reference(int_array);
}

inline void
IntArray::resize(int size_)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::resize(int) called\n";
#endif
	if ( size_ == size() )
		return;
	if (--actual->count == 0)
		delete actual;
	actual = new ActualIntArray(size_);
	coords = actual->coords;
}

inline IntArray &
IntArray::zero(void)
{
	actual->zero();
	return *this;
}

#ifndef IntArray_NO_CHECKING

inline void
IntArray::range_check(int comp) const
{
	if (comp < 0 || comp >= size())
		throw RangeViolation();
}

#else /* ! IntArray_NO_CHECKING */

inline void
IntArray::range_check(int /* comp */) const
{
}

#endif /* IntArray_NO_CHECKING */

inline IntArray &
IntArray::shallow_copy(void)
{
	shallow = true;
	return *this;
}

inline int &
IntArray::operator()(int comp)
{
	range_check(comp);
	return coords[comp];
}

inline int
IntArray::operator()(int comp) const
{
	range_check(comp);
	return coords[comp];
}

inline int &
IntArray::component(int comp)
{
	range_check(comp);
	return coords[comp];
}

inline int
IntArray::component(int comp) const
{
	range_check(comp);
	return coords[comp];
}

#endif /* _IntArray_h */

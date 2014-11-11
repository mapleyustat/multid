#ifndef _Vector_h
#define _Vector_h

// Control macros:
//
//	Vector_SHALLOW		-- see below
//	Vector_DEBUG		-- turn on debugging
//	Vector_NO_CHECKING	-- turn off range checking

// The semantics of the copy constructor, of the assignment operator,
// and of the copy() and ref() member functions are as follows:
//
// By default:
//
//	Vector(const Vector &vector):
//		a. If shallow_copy() has been called by vector,
//		   make "*this" a clone of (i.e., reference to) "vector".
//		b. Otherwise copy the components of "vector" into "*this".
//
//	Vector &operator=(const Vector &):
//		Detach "*this" from its clones
//		and copy the components of "vector" into it.
//
//	Vector &copy(const Vector &):
//		Copy the components of "vector" into "*this"
//		(without detaching "*this" from its clones).
//		The sizes of "*this" and "vector" must match.
//
//	Vector &ref(Vector &):
//		Detach "*this" from its clones
//		and make it a clone of "vector".
//
// When the return value of a function has type "Vector" (as opposed
// to "Vector &"), it is prudent to return a Vector that has called
// shallow_copy().  This way, the copy constructors called while
// returning by value make clones rather than copy components.
//
// If "Vector_SHALLOW" is defined:
//
//	Vector(const Vector &):			copy by reference
//	Vector &operator=(const Vector &):	delete; copy by reference
//	Vector &copy(const Vector &):		delete; copy by value
//	Vector &ref(Vector &):			delete; copy by reference

#include <iostream>
#include <cstring>

class ActualVector {
public:
	class InvalidSize : public std::exception { };

private:
	ActualVector(void);
	ActualVector(int size_);
	ActualVector(int size_, double *coords_);
	ActualVector(const ActualVector &actual_vector);
	~ActualVector(void);
	ActualVector &operator=(const ActualVector &actual_vector); // do not define
	void copy_coords(const ActualVector &actual_vector);
	void zero(void);

	int size;
	double *coords;
	int count;

	friend class Vector;
};

class Vector {
public:
	Vector(void);
	Vector(int size_);
	Vector(int size_, double *coords_);
	Vector(const Vector &vector);
	virtual ~Vector(void);
	Vector &operator=(const Vector &vector);
	Vector &copy(const Vector &vector);
	Vector &ref(Vector &vector);
	void resize(int size_);
	Vector &zero(void);

	int size(void) const;
	void range_check(int comp) const;
	Vector &shallow_copy(void);

	double &operator()(int comp);
	double operator()(int comp) const;
	double &component(int comp);
	double component(int comp) const;

	Vector &operator*=(double s);
	Vector &operator+=(const Vector &b);
	Vector &operator-=(const Vector &b);

	class RangeViolation : public std::exception { };
	class SizeMismatch : public std::exception { };

protected:
	ActualVector *actual;
	double *coords;
	bool shallow;

	Vector &copy_by_reference(const Vector &vector);
	Vector &copy_by_value(const Vector &vector);
};

inline Vector operator*(double s, const Vector &a);
inline Vector operator+(const Vector &a, const Vector &b);
inline Vector operator-(const Vector &a, const Vector &b);

std::ostream &operator<<(std::ostream &os, const Vector &vector);
std::istream &operator>>(std::istream &is, Vector &vector);

inline void
ActualVector::copy_coords(const ActualVector &actual_vector)
{
#if HAVE_STRING_H
	memcpy(coords, actual_vector.coords, size*sizeof(double));
#else
	double *p = coords;
	double *end = coords + size;
	double *q = actual_vector.coords;
	while (p < end)
		*p++ = *q++;
#endif
}

inline
ActualVector::ActualVector(void)
	: size(0),
	  coords(0),
	  count(1)
{
}

inline
ActualVector::ActualVector(int size_)
	: size(0),
	  coords(0),
	  count(1)
{
#ifndef Vector_NO_CHECKING
	if (size_ < 0)
		throw InvalidSize();
#endif
	size = size_;
	coords = new double[size];
}

inline
ActualVector::ActualVector(int size_, double *coords_)
	: size(size_),
	  coords(coords_),
	  count(2)
{
}

inline
ActualVector::ActualVector(const ActualVector &actual_vector)
	: size(actual_vector.size),
	  coords(new double[size]),
	  count(1)
{
	copy_coords(actual_vector);
}

inline
ActualVector::~ActualVector(void)
{
	delete [] coords;
}

inline void
ActualVector::zero(void)
{
#if HAVE_STRING_H
	memset(coords, 0, size*sizeof(double));
#else
	double *p = coords;
	double *end = coords + size;
	while (p < end)
		*p++ = 0.;
#endif
}

inline int
Vector::size(void) const
{
	return actual->size;
}

inline Vector &
Vector::copy_by_reference(const Vector &vector)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::copy_by_reference(const Vector &) called\n";
#endif
	vector.actual->count++;	// done first in case lhs == rhs
	if (--actual->count == 0)
		delete actual;
	actual = vector.actual;
	coords = vector.coords;
	shallow = false;
	return *this;
}

inline Vector &
Vector::copy_by_value(const Vector &vector)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::copy_by_value(const Vector &) called\n";
#endif
	if (&vector != this) {
		if (--actual->count == 0)
			delete actual;
		actual = new ActualVector(*vector.actual);
		coords = actual->coords;
		shallow = false;
	}
	return *this;
}

#ifdef Vector_SHALLOW

inline
Vector::Vector(const Vector &vector)
	: actual(vector.actual),
	  coords(vector.coords),
	  shallow(false)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::Vector(Vector &) called\n";
#endif
	actual->count++;
}

#else /* ! Vector_SHALLOW */

inline
Vector::Vector(const Vector &vector)
	: actual(vector.shallow ? vector.actual : new ActualVector(*vector.actual)),
	  coords(vector.shallow ? vector.coords : actual->coords),
	  shallow(false)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::Vector(Vector &) called\n";
#endif
	if (vector.shallow) {
		actual->count++;
#ifdef Vector_DEBUG
		std::cerr << "Vector::Vector(Vector &): shallow copy\n";
#endif
	}
#ifdef Vector_DEBUG
	else
		std::cerr << "Vector::Vector(Vector &): deep copy\n";
#endif
}

#endif /* Vector_SHALLOW */

inline Vector &
Vector::operator=(const Vector &vector)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::operator=(const Vector &) called\n";
#endif
#ifdef Vector_SHALLOW
	return copy_by_reference(vector);
#else
	return copy_by_value(vector);
#endif
}

inline Vector &
Vector::copy(const Vector &vector)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::copy(const Vector &) called\n";
#endif
#ifdef Vector_SHALLOW
	return copy_by_value(vector);
#else
#ifndef Vector_NO_CHECKING
	if (vector.size() != size())
		throw Vector::SizeMismatch();
#endif
	actual->copy_coords(*vector.actual);
	return *this;
#endif
}

inline Vector &
Vector::ref(Vector &vector)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::ref(Vector &) called\n";
#endif
	return copy_by_reference(vector);
}

inline void
Vector::resize(int size_)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::resize(int) called\n";
#endif
	if ( size_ == size() )
		return;
	if (--actual->count == 0)
		delete actual;
	actual = new ActualVector(size_);
	coords = actual->coords;
}

inline Vector &
Vector::zero(void)
{
	actual->zero();
	return *this;
}

#ifndef Vector_NO_CHECKING

inline void
Vector::range_check(int comp) const
{
	if (comp < 0 || comp >= size())
		throw RangeViolation();
}

#else /* ! Vector_NO_CHECKING */

inline void
Vector::range_check(int /* comp */) const
{
}

#endif /* Vector_NO_CHECKING */

inline Vector &
Vector::shallow_copy(void)
{
	shallow = true;
	return *this;
}

#ifdef Vector_SHALLOW

inline Vector
operator*(double s, const Vector &a)
{
	Vector vector;
	vector.copy(a);
	vector *= s;
	return vector.shallow_copy();
}

inline Vector
operator+(const Vector &a, const Vector &b)
{
	Vector vector;
	vector.copy(a);
	vector += b;
	return vector.shallow_copy();
}

inline Vector
operator-(const Vector &a, const Vector &b)
{
	Vector vector;
	vector.copy(a);
	vector -= b;
	return vector.shallow_copy();
}

#else /* ! Vector_SHALLOW */

inline Vector
operator*(double s, const Vector &a)
{
	Vector vector(a);
	vector *= s;
	return vector.shallow_copy();
}

inline Vector
operator+(const Vector &a, const Vector &b)
{
	Vector vector(a);
	vector += b;
	return vector.shallow_copy();
}

inline Vector
operator-(const Vector &a, const Vector &b)
{
	Vector vector(a);
	vector -= b;
	return vector.shallow_copy();
}

#endif /* Vector_SHALLOW */

#endif /* _Vector_h */

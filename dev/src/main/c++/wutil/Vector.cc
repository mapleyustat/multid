#include <iostream>
#include "Vector.h"

Vector::~Vector(void)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::~Vector(void) called\n";
#endif
	if (--actual->count == 0)
		delete actual;
}

double &
Vector::operator()(int comp)
{
	range_check(comp);
	return coords[comp];
}

double
Vector::operator()(int comp) const
{
	range_check(comp);
	return coords[comp];
}

double &
Vector::component(int comp)
{
	range_check(comp);
	return coords[comp];
}

double
Vector::component(int comp) const
{
	range_check(comp);
	return coords[comp];
}

Vector::Vector(void)
	: actual(new ActualVector),
	  coords(0),
	  shallow(false)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::Vector(void) called\n";
#endif
}

Vector::Vector(int size_)
	: actual(new ActualVector(size_)),
	  coords(actual->coords),
	  shallow(false)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::Vector(int) called\n";
#endif
}

Vector::Vector(int size_, double *coords_)
	: actual(new ActualVector(size_, coords_)),
	  coords(coords_),
	  shallow(false)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::Vector(int, double *) called\n";
#endif
}

Vector &
Vector::operator*=(double s)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::operator*=(double) called\n";
#endif
	double *p = coords;
	double *end = coords + size();
	while (p < end)
		*p++ *= s;
	return *this;
}

Vector &
Vector::operator+=(const Vector &b)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::operator+=(const Vector &) called\n";
#endif
#ifndef Vector_NO_CHECKING
	if (b.size() != size())
		throw SizeMismatch();
#endif
	double *p = coords;
	double *end = coords + size();
	double *r = b.coords;
	while (p < end)
		*p++ += *r++;
	return *this;
}

Vector &
Vector::operator-=(const Vector &b)
{
#ifdef Vector_DEBUG
	std::cerr << "Vector::operator-=(const Vector &) called\n";
#endif
#ifndef Vector_NO_CHECKING
	if (b.size() != size())
		throw SizeMismatch();
#endif
	double *p = coords;
	double *end = coords + size();
	double *r = b.coords;
	while (p < end)
		*p++ -= *r++;
	return *this;
}

std::istream &
operator>>(std::istream &is, Vector &vector)
{
	for (int i = 0; i < vector.size(); i++)
		is >> vector(i);
	return is;
}

std::ostream &
operator<<(std::ostream &os, const Vector &vector)
{
	if (vector.size() == 0) {
		os << "zero-length Vector\n";
	}
	else {
		os << vector(0);
		for (int i = 1; i < vector.size(); i++)
			os << " " << vector(i);
	}
	return os;
}

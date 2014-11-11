VectorNArray::~VectorNArray(void)
{
}

VectorNArray &
VectorNArray::operator*=(const ScalarArray &s)
{
#ifndef VectorNArray_NO_CHECKING
	if (s.size() != size())
		throw SizeMismatch();
#endif
	for (int i = 0; i < size(); i++)
		(*this)(i) *= s(i);
	return *this;
}

std::istream &
operator>>(std::istream &is, VectorNArray &vector_array)
{
	for (int i = 0; i < vector_array.size(); i++)
		is >> vector_array(i);
	return is;
}

std::ostream &
operator<<(std::ostream &os, const VectorNArray &vector_array)
{
	for (int i = 0; i < vector_array.size(); i++)
		os << vector_array(i) << "\n";
	return os;
}

MatrixNArray::~MatrixNArray(void)
{
}

MatrixNArray &
MatrixNArray::operator*=(const ScalarArray &s)
{
#ifndef VectorNArray_NO_CHECKING
	if (s.size() != size())
		throw SizeMismatch();
#endif
	for (int i = 0; i < size(); i++)
		(*this)(i) *= s(i);
	return *this;
}

MatrixNArray &
MatrixNArray::equals_multiple_of_identity(double s)
{
	for (int i = 0; i < size(); i++)
		(*this)(i).equals_multiple_of_identity(s);
	return *this;
}

MatrixNArray &
MatrixNArray::add_multiple_of_identity(double s)
{
	for (int i = 0; i < size(); i++)
		(*this)(i).add_multiple_of_identity(s);
	return *this;
}

MatrixNDerivativeArray &
MatrixNDerivativeArray::equals_multiple_of_identity(double s)
{
	for (int i = 0; i < size(); i++)
		(*this)(i).equals_multiple_of_identity(s);
	return *this;
}

MatrixNDerivativeArray &
MatrixNDerivativeArray::add_multiple_of_identity(double s)
{
	for (int i = 0; i < size(); i++)
		(*this)(i).add_multiple_of_identity(s);
	return *this;
}

std::ostream &
operator<<(std::ostream &os, const MatrixNArray &matrix_array)
{
	for (int i = 0; i < matrix_array.size(); i++)
		os << matrix_array(i);
	return os;
}

std::ostream &
operator<<(std::ostream &os, const MatrixNDerivative &matrix_array)
{
	for (int i = 0; i < matrix_array.size(); i++)
		os << matrix_array(i);
	return os;
}

std::ostream &
operator<<(std::ostream &os, const MatrixNDerivativeArray &matrix_array)
{
	for (int i = 0; i < matrix_array.size(); i++)
		os << matrix_array(i);
	return os;
}

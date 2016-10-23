#include "LongNum.h"

longnum::longnum()
{
	number = new int[1];
	real_size = length = 1;
	number[0] = 0;
}
//template <typename T>
longnum::longnum(unsigned long long par)
{
	unsigned long long temp = par;
	size_t number_of_ints = 0;
	while (temp)
	{
		++number_of_ints;
		temp /= 10;
	}
	number = new int[number_of_ints + 1];
	int i = 0;// *temp_mas = new int[number_of_ints - 1];
	while (par)
	{
		number[i] = par % 10;
		++i;
		par /= 10;
	}
	/*for (int i = 0; i < number_of_ints; ++i)
	{
		number[i] = temp_mas[number_of_ints - 1 - i];
	}*/
	length = number_of_ints;
	real_size = number_of_ints + 1;
}
longnum::~longnum()
{
	delete[] number;
	real_size = length = 0;
}
longnum::longnum(const longnum & par_longnum)
{
	number = new int[par_longnum.real_size];
	length = par_longnum.length;
	real_size = par_longnum.real_size;
	for (size_t i = 0; i < length; ++i)
		number[i] = par_longnum.number[i];
}
std::ostream& operator << (std::ostream& ot, const longnum& X)
{
	for (size_t i = 0; i < X.length; ++i)
		ot << X.number[X.length - 1 - i];
	return ot;
}
void longnum::swap(longnum &arg)
{
	std::swap(number, arg.number);
	std::swap(length, arg.length);
	std::swap(real_size, arg.real_size);
}
longnum& longnum::operator = (longnum const &td)
{
	if (this == &td)
	{
		return *this;
	}
	longnum(td).swap(*this);
//	this->swap(td);
	return *this;
}
const bool operator > (const longnum & left, const longnum & right)
{
	if (left.length > right.length)
		return true;
	if (left.length < right.length)
		return false;
	for (size_t i = 0; i < left.length; ++i)
	{
		if (left.number[i] > right.number[i])
			return true;
		if (left.number[i] < right.number[i])
			return false;
	}
	return false;
}
const bool operator < (const longnum & left, const longnum & right)
{
	if (left.length > right.length)
		return false;
	if (left.length < right.length)
		return true;
	for (size_t i = 0; i < left.length; ++i)
	{
		if (left.number[i] > right.number[i])
			return false;
		if (left.number[i] < right.number[i])
			return true;
	}
	return false;
}
const bool operator == (const longnum & left, const longnum & right)
{
	if (!(left > right) && !(left < right))
		return true;
	return false;
}
void longnum::resize(size_t new_size)
{
	int *temp = new int[new_size];
	for (size_t i = 0; i < new_size; ++i)
	{
		if (i < this->length)
			temp[new_size - 1 - i] = this->number[this->length - 1 - i];
		else
			temp[new_size - 1 - i] = 0;
	}
	this->number = temp;
	this->real_size = new_size;
	delete[] temp;
}
size_t longnum::get_real_size()
{
	return /*this->*/real_size;
}
/*const longnum operator+(const longnum &left, const longnum &right)
{
	longnum temp(left > right ? left : right);

}*/
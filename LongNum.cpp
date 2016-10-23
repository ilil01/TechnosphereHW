#include "LongNum.h"

longnum::longnum():real_size(1), length(1), number(new int[1])
{
	number[0] = 0;
}
longnum::longnum(unsigned long long par)
{
	if (par == 0)
	{
		longnum a;
		*this = a;
		return;
	}
	unsigned long long temp = par;
	size_t number_of_ints = 0;
	while (temp)
	{
		++number_of_ints;
		temp /= 10;
	}
	number = new int[number_of_ints];
	size_t i = 0;
	int *temp_mas = new int[number_of_ints];
	while (par)
	{
		temp_mas[i] = par % 10;
		++i;
		par /= 10;
	}
	for (i = 0; i < number_of_ints; ++i)
	{
		number[i] = temp_mas[number_of_ints - 1 - i];
	}
	real_size = length = number_of_ints;
}
longnum::~longnum()
{
//	std::cout << '~' << *this << ' ';
	delete[] number;
	number = nullptr;
	real_size = length = 0;
}
longnum::longnum(const longnum & par_longnum)
	/*:number(new int[par_longnum.real_size])
	/*,length(par_longnum.length)
	,real_size(par_longnum.real_size)*/
{
	number = new int[par_longnum.real_size];
	length = par_longnum.length;
	real_size = par_longnum.real_size;
	for (size_t i = 0; i < real_size; ++i)
		number[i] = par_longnum.number[i];
}
std::ostream& operator << (std::ostream& ot, const longnum& X)
{
	for (size_t i = X.real_size - X.length; i < X.real_size; ++i)
		ot << X.number[i];
	return ot;
}
std::istream& operator >> (std::istream& it, longnum& X)
{
	std::string s;
//	char c;
	it >> s;
	X.length = X.real_size = s.size();
	X.number = new int[X.length];
	for (size_t i = 0; i < X.length; ++i)
		X.number[i] = s[i] - '0';
	return it;
}
void longnum::swap(longnum &arg)
{
	std::swap(number, arg.number);
	std::swap(length, arg.length);
	std::swap(real_size, arg.real_size);
}
longnum& longnum::operator = (longnum const &td)
{
	if (this != &td)
	{
		longnum(td).swap(*this);
	}
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
	return right > left;
}
const bool operator == (const longnum & left, const longnum & right)
{
	if (!(left > right) && !(left < right))
		return true;
	return false;
}
const bool operator != (const longnum & left, const longnum & right)
{
	return !(left == right);
}
const bool operator >= (const longnum & left, const longnum & right)
{
	return !(left < right);
}
const bool operator <= (const longnum & left, const longnum & right)
{
	return !(left > right);
}
size_t longnum::get_real_size()
{
	return this->real_size;
}
void longnum::resize(size_t new_size)
{
	int *temp = new int[new_size];
	for (size_t i = 0; i < new_size; ++i)
	{
		if (i < this->length)
			temp[new_size - 1 - i] = this->number[this->real_size - 1 - i];
		else
			temp[new_size - 1 - i] = 0;
	}
	delete[] this->number;
	this->number = temp;
	this->real_size = new_size;
	if (this->length > this->real_size)
		this->length = this->real_size;
}
const longnum operator+(const longnum &left, const longnum &right)
{
	longnum temp1, temp2;
	if (left > right)
	{
		temp1 = left;
		temp2 = right;
	}
	else
	{
		temp1 = right;
		temp2 = left;
	}
	temp1.resize(temp1.real_size + 1);
	size_t l1 = temp1.real_size, l2 = temp2.real_size;
	for (size_t i = 0; i < l2; ++i)
	{
		temp1.number[l1 - 1 - i] += temp2.number[l2 - 1 - i];
		if (temp1.number[l1 - 1 - i] / 10 != 0)
		{
			temp1.number[l1 - 2 - i] += temp1.number[l1 - 1 - i] / 10;
			temp1.number[l1 - 1 - i] %= 10;
		}
	}
	if (temp1.number[0])
		temp1.length = temp1.real_size;
	else
	{
		temp1.length = temp1.real_size - 1;
//		temp1.resize(temp1.real_size - 1);
	}
	temp1.shrink_to_fit();
	return temp1;
}
longnum& longnum::operator += (const longnum & td)
{
	*this = *this + td;
	return *this;
}
const longnum operator * (const longnum & left, const longnum & right)
{
	longnum temp;
	if (left == temp || right == temp)
		return temp;
	temp.resize(left.length + right.length);
	longnum templ(left), tempr(right);
	templ.shrink_to_fit();
	tempr.shrink_to_fit();
	for (size_t i = 0; i < templ.length; ++i)
		for (size_t j = 0; j < tempr.length; ++j)
			temp.number[i + j] += templ.number[i] * tempr.number[j];
	temp.check();
	for (int i = temp.real_size - 1; i > 0; --i)
	{
		temp.number[i] = temp.number[i - 1];
	}
	temp.check();
	temp.number[0] = 0;
	for (int i = temp.real_size - 1; i > 0; --i)
	{
		temp.number[i - 1] += temp.number[i] / 10;
		temp.number[i] %= 10;
	}
	temp.check();
	if (!temp.number[0])
	{
		temp.length = temp.real_size - 1;
		temp.resize(temp.real_size - 1);
	}
	else
		temp.length = temp.real_size;
	return temp;
}
void longnum::shrink_to_fit()
{
	this->resize(this->length);
	this->real_size = this->length;
}
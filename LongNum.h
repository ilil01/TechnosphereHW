#pragma once
#include <iostream>
class longnum
{
	int *number;
	size_t length;
	size_t real_size;
public:
	longnum();
	//template <typename T>
	longnum(unsigned long long par);
	longnum(const longnum & par_longnum);
	~longnum();
	friend std::ostream& operator << (std::ostream& cout, const longnum& X);
	void swap(longnum &arg);
	longnum& operator = (const longnum & td);
	void resize(size_t new_size);
	size_t get_real_size();
	friend const longnum operator + (const longnum & left, const longnum & right);
	friend const bool operator > (const longnum & left, const longnum & right);
	friend const bool operator < (const longnum & left, const longnum & right);
	friend const bool operator == (const longnum & left, const longnum & right);
};

/*longnum::longnum()
{
	number = new int[1];
	length = 1;
	number[0] = 0;
}
template <typename T>
longnum::longnum(T par)
{
	T temp = par;
	int number_of_ints = 1;
	while (temp)
	{
		++number_of_ints;
		temp /= 10;
	}
	number = new int[number_of_ints];
	int i = 0;
	while (par)
	{
		number[i] = par % 10;
		++i;
		par /= 10;
	}
	length = number_of_ints;
}
longnum::~longnum()
{
	delete[] number;
	length = 0;
}
longnum::longnum(const longnum & par_longnum)
{
	number = new int[par_longnum.length];
	length = par_longnum.length;
	for (int i = 0; i < length; ++i)
		number[i] = par_longnum.number[i];
}
std::ostream& operator<<(std::ostream& ot, const longnum& X)
{
	for (int i = X.length; i >= 0; --i)
		ot << X.number[i];
	return ot;
}*/
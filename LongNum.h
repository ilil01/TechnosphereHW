#pragma once
#include <iostream>
#include <string>
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
	friend std::ostream& operator << (std::ostream& ot, const longnum& X);
	friend std::istream& operator >> (std::istream& it, longnum& X);
	void swap(longnum &arg);
	longnum& operator = (const longnum & td);
	void resize(size_t new_size);
	size_t get_real_size();
	friend const longnum operator + (const longnum & left, const longnum & right);
	longnum& operator += (const longnum & td);
	friend const bool operator > (const longnum & left, const longnum & right);
	friend const bool operator < (const longnum & left, const longnum & right);
	friend const bool operator == (const longnum & left, const longnum & right);
	friend const bool operator != (const longnum & left, const longnum & right);
	friend const bool operator >= (const longnum & left, const longnum & right);
	friend const bool operator <= (const longnum & left, const longnum & right);
	friend const longnum operator * (const longnum & left, const longnum & right);
	void shrink_to_fit();
	void check()
	{
		for (size_t i = 0; i < real_size; ++i)
			std::cout << number[i];
		std::cout << '\n';
	}
};
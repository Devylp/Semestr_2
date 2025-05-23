/*
#include <iostream>
#include <sstream>

std::string ReverseNumber(long int);

template<typename T> std::string to_string(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

int main() {
	long int num;
	std::cin >> num;

	std::cout << ReverseNumber(num);
}

std::string ReverseNumber(long int Number) {
	std::string ResultNumber;

	if (Number > 0)
		ResultNumber = to_string(Number % 10) + to_string(ReverseNumber(Number / 10));
	
	return ResultNumber;
}
*/

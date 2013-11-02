#pragma once

#include <string>
#include <iostream>

template <typename T>
T prompt(std::string x) {
	T out;
	std::cout << x << ": ";
	std::cin >> out;
	return out;
}

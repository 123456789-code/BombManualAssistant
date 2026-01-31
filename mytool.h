#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

namespace mytool {
	template <typename T, typename ... others>
	constexpr void print(const T& t, const others& ... o) {
		std::cout << t;
		if constexpr (sizeof...(o) != 0) { print(o...); }
	}

	template <typename S1, typename S2, typename T, typename ... others>
	constexpr void prints(const S1& sep, const S2& end, const T& t, const others& ... o) {
		if constexpr (sizeof...(o) == 0) { std::cout << t << end; }
		else {
			std::cout << t << sep;
			prints(sep, end, o...);
		}
	}

	template <typename T, typename ... others>
	constexpr void printw(const T& t, const others& ... o) {
		std::wcout << t;
		if constexpr (sizeof...(o) != 0) { printw(o...); }
	}

	template <typename ... others>
	constexpr void printa(const others& ... o) {
		if constexpr (sizeof...(o) == 0) { std::cout << std::endl; }
		else { prints(" ", "\n", o...); }
		std::cout.flush();
	}

#ifdef _DEBUG
	void pass() { }
#endif
}
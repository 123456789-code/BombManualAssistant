#include <iostream>
#include <vector>
#include <string>
#include <array>

using std::string, std::vector, std::pair, std::array, std::to_string;

template<int size>
class Maze {
private:
	array<array<bool, size>, size - 1> rwall;
	array<array<bool, size - 1>, size> cwall;

public:
	constexpr Maze() noexcept : rwall{}, cwall{} {}
	constexpr Maze(
		const array<array<bool, size>, size - 1>& r,
		const array<array<bool, size - 1>, size>& c
	) noexcept : rwall(r), cwall(c) {  }
	constexpr Maze(
		array<array<bool, size>, size - 1>&& r,
		array<array<bool, size - 1>, size>&& c
	) noexcept : rwall(r), cwall(c) {  }
	constexpr ~Maze() noexcept = default;


	// 是否是墙
	constexpr const bool is_wall(int r, int c, int direction) const {
		// direction: 0=上, 1=右, 2=下, 3=左
		switch (direction) {
		case 0:
			return r == 0 || rwall[r - 1][c];
		case 1:
			return c == size || cwall[r][c];
		case 2:
			return r == size - 1 || rwall[r][c];
		case 3:
			return c == 0 || cwall[r][c - 1];
		}
		return true;
	}
};

using Maze6x6 = Maze<6>;
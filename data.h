#pragma once
#include <iostream>
#include <string>
#include <array>
#include <unordered_map>
#include <iomanip>
#include <cassert>
#include <functional>
#include <bitset>
#include "mytool.h"
#include "maze.h"

using std::cin, std::cout, std::endl, std::string, std::array, std::unordered_map, std::left, std::setw, std::function, std::memset, std::bitset;
using mytool::print, mytool::printa;

// 模块1
constexpr static const int left1 = 28;
constexpr static const int right1 = 23;
static const void output1(const unsigned& counts, const bool& odd) {
	cout << "╔════════════════════════════════════════════════════════╗" << endl;
	cout << "║                    线路模块操作指南                    ║" << endl;
	cout << "╠══════════════════════════════╦═════════════════════════╣" << endl;
	cout << "║ 条件                         ║ 剪断                    ║" << endl;
	cout << "╠══════════════════════════════╬═════════════════════════╣" << endl;
	switch (counts) {
	case 3:
		cout << "║ " << left << setw(left1) << "红线 == 0" << " ║ " << setw(right1) << "2" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "last == 白线" << " ║ " << setw(right1) << "3" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "蓝线 > 1" << " ║ " << setw(right1) << "最后一根蓝线" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "其他" << " ║ " << setw(right1) << "3" << " ║" << endl;
		break;
	case 4:
		if (odd) {
			cout << "║ " << left << setw(left1) << "红线 > 1" << " ║ " << setw(right1) << "最后一根红线" << " ║" << endl;
		}
		cout << "║ " << left << setw(left1) << "红线 == 0 && last == 黄线" << " ║ " << setw(right1) << "1" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "蓝线 == 1" << " ║ " << setw(right1) << "1" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "黄线 > 1" << " ║ " << setw(right1) << "4" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "其他" << " ║ " << setw(right1) << "2" << " ║" << endl;
		break;
	case 5:
		if (odd) {
			cout << "║ " << left << setw(left1) << "last == 黑线" << " ║ " << setw(right1) << "4" << " ║" << endl;
		}
		cout << "║ " << left << setw(left1) << "红线 == 1 && 黄线 > 1" << " ║ " << setw(right1) << "1" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "黑线 == 0" << " ║ " << setw(right1) << "2" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "其他" << " ║ " << setw(right1) << "1" << " ║" << endl;
		break;
	case 6:
		if (odd) {
			cout << "║ " << left << setw(left1) << "黄线 == 0" << " ║ " << setw(right1) << "3" << " ║" << endl;
		}
		cout << "║ " << left << setw(left1) << "黄线 == 1" << " ║ " << setw(right1) << "4" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "红线 == 0" << " ║ " << setw(right1) << "6" << " ║" << endl;
		cout << "║ " << left << setw(left1) << "其他" << " ║ " << setw(right1) << "4" << " ║" << endl;
		break;
	}
	cout << "╚══════════════════════════════╩═════════════════════════╝" << endl;
}
// 模块2
constexpr static const int left2 = 24;
constexpr static const int right2 = 11;
static const void output2(const unsigned& battery) {
	cout << "╔════════════════════════════════════════╗" << endl;
	cout << "║            按钮模块操作指南            ║" << endl;
	cout << "╠══════════════════════════╦═════════════╣" << endl;
	cout << "║ 情况                     ║ 操作        ║" << endl;
	cout << "╠══════════════════════════╬═════════════╣" << endl;
	cout << "║ " << left << setw(left2) << "蓝色, 中止" << " ║ " << setw(right2) << "按住" << " ║" << endl;
	if (battery > 1) {
		cout << "║ " << left << setw(left2) << "引爆" << " ║ " << setw(right2) << "按下松开" << " ║" << endl;
	}
	cout << "║ " << left << setw(left2) << "白色, CAR" << " ║ " << setw(right2) << "按住" << " ║" << endl;
	if (battery > 2) {
		cout << "║ " << left << setw(left2) << "FRK" << " ║ " << setw(right2) << "按下松开" << " ║" << endl;
	}
	cout << "║ " << left << setw(left2) << "黄色" << " ║ " << setw(right2) << "按住" << " ║" << endl;
	cout << "║ " << left << setw(left2) << "红色, 按住" << " ║ " << setw(right2) << "按下松开" << " ║" << endl;
	cout << "║ " << left << setw(left2) << "否则" << " ║ " << setw(right2) << "按住" << " ║" << endl;
	cout << "╚══════════════════════════╩═════════════╝" << endl;
}
// 模块4
constexpr static const unsigned table4[2][3][4]{
	{ {4,3,2,1}, {1,4,3,2}, {3,2,4,1} },
	{ {4,1,3,2}, {3,2,4,1}, {2,1,3,4} }
};
// 模块6
void input6(string& code, unsigned(&now)[5]) {
	cin >> code;
	bool flag = false;
	while (true) {
		if (code.size() != 5) {
			print("应该输入五个数字，请重新输入: ");
			cin >> code;
			continue;
		}
		flag = false;
		for (int i = 0; i < 5; i++) {
			now[i] = code[i] - '0';
			if (now[i] > 4 || now[i] == 0) {
				print("这五个数字应当在1234之中，请重新输入: ");
				cin >> code;
				flag = true;
				break;
			}
		}
		if (!flag) { break; }
	}
}
// 模块7
static const unordered_map<string, char> morse_to_char{
	{"01", 'a'},      // .-
	{"1000", 'b'},    // -...
	{"1010", 'c'},    // -.-.
	{"100", 'd'},     // -..
	{"0", 'e'},       // .
	{"0010", 'f'},    // ..-.
	{"110", 'g'},     // --.
	{"0000", 'h'},    // ....
	{"00", 'i'},      // ..
	{"0111", 'j'},    // .---
	{"101", 'k'},     // -.-
	{"0100", 'l'},    // .-..
	{"11", 'm'},      // --
	{"10", 'n'},      // -.
	{"111", 'o'},     // ---
	{"0110", 'p'},    // .--.
	{"1101", 'q'},    // --.-
	{"010", 'e'},     // .-.
	{"000", 's'},     // ...
	{"1", 't'},       // -
	{"001", 'u'},     // ..-
	{"0001", 'v'},    // ...-
	{"011", 'w'},     // .--
	{"1001", 'x'},    // -..-
	{"1011", 'y'},    // -.--
	{"1100", 'z'},    // --..
	{"11111", '0'},   // -----
	{"01111", '1'},   // .----
	{"00111", '2'},   // ..---
	{"00011", '3'},   // ...--
	{"00001", '4'},   // ....-
	{"00000", '5'},   // .....
	{"10000", '6'},   // -....
	{"11000", '7'},   // --...
	{"11100", '8'},   // ---..
	{"11110", '9'}    // ----.
};
static const unordered_map<string, unsigned> table7{
	{"shell", 505},
	{"halls", 515},
	{"slick", 522},
	{"trick", 532},
	{"boxes", 535},
	{"leaks", 542},
	{"strobe", 545},
	{"bistro", 552},
	{"flick", 555},
	{"bombs", 565},
	{"break", 572},
	{"brick", 575},
	{"steak", 582},
	{"sting", 592},
	{"vector", 595},
	{"beats", 600}
};
// 模块8
constexpr static const char table8[16]{
	'C', 'D', 'C', 'B',
	'S', 'P', 'D', 'P',
	'S', 'B', 'C', 'B',
	'S', 'S', 'P', 'D'
};
// 模块9
constexpr static const bool table9[3][9][3]{
	{ {0,0,1}, {0,1,0}, {1,0,0}, {1,0,1}, {0,1,0}, {1,0,1}, {1,1,1}, {1,1,0}, {0,1,0} },
	{ {0,1,0}, {1,0,1}, {0,1,0}, {1,0,0}, {0,1,0}, {0,1,1}, {0,0,1}, {1,0,1}, {1,0,0} },
	{ {1,1,1}, {1,0,1}, {0,1,0}, {1,0,1}, {0,1,0}, {0,1,1}, {1,1,0}, {0,0,1}, {0,0,1} }
};
// 模块10
constexpr array <unsigned, 100> make_table10() {
	array <unsigned, 100> table{};
	table[21] = 1;
	table[36] = 1;
	table[25] = 2;
	table[42] = 2;
	table[44] = 3;
	table[46] = 3;
	table[11] = 4;
	table[41] = 4;
	table[35] = 5;
	table[64] = 5;
	table[15] = 6;
	table[53] = 6;
	table[12] = 7;
	table[62] = 7;
	table[14] = 8;
	table[43] = 8;
	table[23] = 9;
	table[51] = 9;
	return table;
}
constexpr static const array <unsigned, 100> table10 = make_table10();
constexpr static const int size = 6;
constexpr array<array<bool, size>, size - 1> buildr10(std::string_view r) {
	assert(r.size() == size * size - 2);
	array<array<bool, size>, size - 1> rwall{};
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size; j++) {
			rwall[i][j] = (r[i * (size + 1) + j] == '1');
		}
	}
	return rwall;
}
constexpr array<array<bool, size - 1>, size> buildc10(std::string_view c) {
	assert(c.size() == size * size - 1);
	array<array<bool, size - 1>, size> cwall{};
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			cwall[i][j] = (c[i * (size - 1 + 1) + j] == '1');
		}
	}
	return cwall;
}
constexpr array <Maze6x6, 9> make_maze10() {
	array <Maze6x6, 9> mazes{};
	mazes[0] = Maze6x6(buildr10("010011 001110 010010 011110 010010"), buildc10("00100 10100 10100 10010 00101 01010"));
	mazes[1] = Maze6x6(buildr10("101001 010110 001010 010100 000010"), buildc10("00100 01010 10100 01011 11101 10100"));
	mazes[2] = Maze6x6(buildr10("010000 100110 000000 000000 011000"), buildc10("00110 11101 01101 11111 10111 00010"));
	mazes[3] = Maze6x6(buildr10("001110 000110 011010 011110 011100"), buildc10("01000 11000 10101 10000 00001 00101"));
	mazes[4] = Maze6x6(buildr10("111100 011011 001100 011010 001110"), buildc10("00000 00001 01010 10011 10001 10000"));
	mazes[5] = Maze6x6(buildr10("000100 000010 011001 100000 011010"), buildc10("10100 11101 01110 01011 01110 00010"));
	mazes[6] = Maze6x6(buildr10("011000 001110 110100 000110 011100"), buildc10("00010 10101 01010 01001 11001 00000"));
	mazes[7] = Maze6x6(buildr10("001000 011110 001100 010111 001111"), buildc10("10010 00101 10001 10100 11000 00000"));
	mazes[8] = Maze6x6(buildr10("001100 000100 011010 000110 000001"), buildc10("10000 11011 00101 11010 11101 01010"));
	return mazes;
}
constexpr static const array <Maze6x6, 9> mazes10 = make_maze10();
vector<pair<int, int>> solve10(const Maze6x6& maze, const pair<int, int>& start, const pair<int, int>& end) {
	vector<pair<int, int>> path;
	auto hash = [](const pair<int, int>& p) {
		return p.first * 10 + p.second;
	};

	// 方向：上、右、下、左
	const vector<pair<int, int>> directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

	// 从终点开始DFS
	vector<vector<bool>> visited(size, vector<bool>(size, false));
	function<bool(int, int)> dfs = [&](int r, int c) {
		if (r == start.first && c == start.second) {
			path.emplace_back(r, c);
			return true;
		}
		visited[r][c] = true;
		for (int dir = 0; dir < 4; dir++) {
			int nr = r + directions[dir].first;
			int nc = c + directions[dir].second;
			if (nr >= 0 && nr < size && nc >= 0 && nc < size && !maze.is_wall(r, c, dir) && !visited[nr][nc]) {
				if (dfs(nr, nc)) {
					path.emplace_back(r, c);
					return true;
				}
			}
		}
		return false;
		};
	dfs(end.first, end.second);
	return path;
}
constexpr string output_path10(const vector<pair<int, int>>& path) {
	string result = "路径为: ";
	for (int i = 0; i < path.size() - 1; i++) {
		result += "(" + to_string(path[i].first + 1) + ", " + to_string(path[i].second + 1) + ") -> ";
	}
	result += "(" + to_string(path.back().first + 1) + ", " + to_string(path.back().second + 1) + ")\n";
	return result;
}
constexpr array<array<bool, 4 * size + 1>, 4 * size + 1> form_maze(unsigned type) {
	array<array<bool, 4 * size + 1>, 4 * size + 1> wall;
	// 初始全部设为空格
	for (int i = 0; i < 4 * size + 1; i++) {
		for (int j = 0; j < 4 * size + 1; j++) {
			wall[i][j] = 0;
		}
	}
	// 初始化迷宫边界
	for (int i = 0; i < 4 * size + 1; i++) {
		wall[0][i] = true;
		wall[4 * size][i] = true;
		wall[i][0] = true;
		wall[i][4 * size] = true;
	}
	// 设置格点
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			wall[4 * i][4 * j] = true;
		}
	}
	const Maze6x6& maze = mazes10[type];
	// 设置横墙
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size; j++) {
			if (maze.is_wall(i, j, 2)) {
				for (int k = 0; k < 4; k++) {
					wall[4 * (i + 1)][4 * j + 1 + k] = true;
				}
			}
		}
	}
	// 设置竖墙
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (maze.is_wall(i, j, 1)) {
				for (int k = 0; k < 4; k++) {
					wall[4 * i + 1 + k][4 * (j + 1)] = true;
				}
			}
		}
	}
	return wall;
}
constexpr string draw_maze10(unsigned type) { // 打印迷宫本身
	array<array<bool, 4 * size + 1>, 4 * size + 1> wall = form_maze(type);
	string maze_str;
	for (int i = 0; i < 4 * size + 1; i++) {
		for (int j = 0; j < 4 * size + 1; j++) {
			maze_str += wall[i][j] ? "██" : "  ";
		}
		maze_str += '\n';
	}
	return maze_str;
}
constexpr string draw_maze10(unsigned type, vector<pair<int, int>> path) { // 打印带路径的迷宫
	array<array<bool, 4 * size + 1>, 4 * size + 1> wall = form_maze(type);
	array<array<bool, 4 * size + 1>, 4 * size + 1> star;
	// 初始star
	for (int i = 0; i < 4 * size + 1; i++) {
		for (int j = 0; j < 4 * size + 1; j++) {
			star[i][j] = false;
		}
	}
	// 标记路径
	for (int i = 0; i < path.size(); i++) {
		int r = path[i].first;
		int c = path[i].second;
		star[4 * r + 2][4 * c + 2] = true;
		if (i < path.size() - 1) {
			int nr = path[i + 1].first;
			int nc = path[i + 1].second;
			if (nr == r - 1 && nc == c) { // 上
				star[4 * r + 1][4 * c + 2] = true;
				star[4 * r][4 * c + 2] = true;
				star[4 * r - 1][4 * c + 2] = true;
			}
			else if (nr == r + 1 && nc == c) { // 下
				star[4 * r + 3][4 * c + 2] = true;
				star[4 * r + 4][4 * c + 2] = true;
				star[4 * r + 5][4 * c + 2] = true;
			}
			else if (nr == r && nc == c - 1) { // 左
				star[4 * r + 2][4 * c + 1] = true;
				star[4 * r + 2][4 * c] = true;
				star[4 * r + 2][4 * c - 1] = true;
			}
			else if (nr == r && nc == c + 1) { // 右
				star[4 * r + 2][4 * c + 3] = true;
				star[4 * r + 2][4 * c + 4] = true;
				star[4 * r + 2][4 * c + 5] = true;
			}
		}
	}
	string maze_str;
	for (int i = 0; i < 4 * size + 1; i++) {
		for (int j = 0; j < 4 * size + 1; j++) {
			maze_str += wall[i][j] ? "██" : (star[i][j] ? "▓▓" : "  ");
		}
		maze_str += '\n';
	}
	return maze_str;
}
// 模块11
static const array<string, 35> table11{
	"about", "after", "again", "below", "could",
	"every", "first", "found", "great", "house",
	"large", "learn", "never", "other", "place",
	"plant", "point", "right", "small", "sound",
	"spell", "still", "study", "their", "there",
	"these", "thing", "think", "three", "water",
	"where", "which", "world", "would", "write"
};
// 模块12
constexpr array <uint8_t, 4096> make_table12() {
	array <uint8_t, 4096> table{};
	table[0x2FD] = 1;
	table[0xA9B] = 1;
	table[0x67D] = 2;
	table[0xA91] = 2;
	table[0x0A7] = 3;
	table[0x086] = 3;
	table[0xBFA] = 4;
	table[0xB3A] = 4;
	return table;
}
constexpr static const array <uint8_t, 4096> table12 = make_table12();
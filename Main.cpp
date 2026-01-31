/*
 *  oooooo   oooooo     oooo                                    .o    .oooo.     oooooooo   oooooooo   .o    .oooo.
 *   `888.    `888.     .8'                                   o888  .dP""Y88b   dP"""""""  dP""""""" o888   d8P'`Y8b
 *    `888.   .8888.   .8'    .oooo.   ooo. .oo.    .oooooooo  888        ]8P' d88888b.   d88888b.    888  888    888
 *     `888  .8'`888. .8'    `P  )88b  `888P"Y88b  888' `88b   888      .d8P'      `Y88b      `Y88b   888  888    888
 *      `888.8'  `888.8'      .oP"888   888   888  888   888   888    .dP'           ]88        ]88   888  888    888
 *       `888'    `888'      d8(  888   888   888  `88bod8P'   888  .oP     .o o.   .88P  o.   .88P   888  `88b  d88'
 *        `8'      `8'       `Y888""8o o888o o888o `8oooooo.  o888o 8888888888 `8bd88P'   `8bd88P'   o888o  `Y8bd8P'
 *                                                 d"     YD
 *                                                 "Y88888P'
 */
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include "mytool.h"
#include "data.h"

#ifdef _WIN32
#include <windows.h>
#include "win.h"
#include "ImageDisplayWrapper.h"
#include "resource.h"
#endif

using std::cin, std::cout, std::endl, std::string, std::fill, std::bitset, std::pair, std::unordered_map, std::vector, std::remove_if, std::left, std::setw, std::string_view;
using mytool::print, mytool::printa, mytool::prints;

#ifdef _DEBUG
	using mytool::pass;
#endif // DEBUG

constexpr inline string_view verson = "1.3.4";

int main() {
#ifdef _WIN32 // Win相关设置
	// 设置标题
	SetConsoleTitle(TEXT("Bomb Manual Assistant"));

	if (!IsRunAsAdmin()) {
		// 启动提示
		prints('\n', '\n',
			"此程序仅用于辅助拆弹助手，带有一定作弊性质，请谨慎使用！",
			"建议第一次使用时先将各个模块的编码方式完整阅读",
			"祝你好运 ^_^",
			"Made by Wang125510"
		);
		bool ontop = false;
		print("是否需要将窗口置顶(0表示否，1表示是): ");
		cin >> ontop;
		if (ontop) { // 请求以管理员权限重新启动
			if (RestartAsAdmin()) {
				return 0; // 当前进程退出
			}
			else {
				// 用户拒绝了权限请求
				return 1;
			}
		}
	}
	else {
		// 设置置顶
		if (HWND hwnd = GetConsoleWindow()) {
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		}
	}
#endif

	bool odd = 0, aeiou = 0, parallel = 0;
	unsigned battery = 0, module = 0;

restart:
	system("cls");

	// 预输入炸弹参数
	printa("请告诉我你的炸弹的型号");
	print("序列号的末伪是奇数还是偶数(0表示偶数，1表示奇数): ");
	cin >> odd;
	print("序列号是否包含元音: ");
	cin >> aeiou;
	print("电池数量: ");
	cin >> battery;
	print("是否有Parallel端口: ");
	cin >> parallel;

	// 主逻辑
	while (true){
		// 选择模块
		system("cls");
		prints('\n', '\n',
			"请输入当前的模块",
			"1.线路模块",
			"2.按钮模块",
			"3.键盘模块",
			"4.四色方块",
			"5.汉字模块",
			"6.记忆模块",
			"7.摩斯电码",
			"8.复杂线路",
			"9.顺序线路",
			"10.迷宫模块",
			"11.密码模块",
			"12.旋钮模块",
			"13.重新开始"
		);
		print("请选择模块: ");
		cin >> module;
		switch (module) {
			case 1: {
				unsigned counts = 0;
				print("请输入线的数量: ");
				cin >> counts;
				while (counts < 3 || counts > 6) {
					print("线的数量应该在3到6之间，请重新输入: ");
					cin >> counts;
				}
				output1(counts, odd);
				break;
			}
			case 2: { // 按钮模块
				output2(battery);
				break;
			}
			case 3: { // 键盘模块
#ifdef _WIN32
				printa("请输入当前键盘上的字符，编码为下表对应数字，顺序请按照正常文字阅读顺序");
				show_image(IDB_BITMAP1);
				array<unsigned, 4> code;
				print("请输入左上角的字符: ");
				cin >> code[0];
				print("请输入右上角的字符: ");
				cin >> code[1];
				print("请输入左下角的字符: ");
				cin >> code[2];
				print("请输入右下角的字符: ");
				cin >> code[3];
				array<unsigned, 4> order = sort3(code);
				output3(order);
				close_image();
#else
				printa("这个模块的代码依赖Windows");
#endif
				break;
			}
			case 4: { // 四色方块
				unsigned times = 0, temp = 0;
				print("目前失误了几次: ");
				cin >> times;
				while (times > 2) {
					print("失误应当最多两次，请重新输入: ");
					cin >> times;
				}
				printa("接下来输入本次新增的颜色，红绿黄蓝对应1234，输入0表示退出");
				while (true) {
					print("请输入本次的颜色: ");
					cin >> temp;
					while (temp > 4) {
						print("编码应当在1234中取，请重新输入: ");
						cin >> temp;
					}
					if (temp == 0) { break; }
					printa(static_cast<int>(table4[!aeiou][times][temp - 1]));
				}
				break;
			}
			case 5: { // 汉字模块  未完成
				printa("由于汉字输入过于麻烦，这个还是自己来更快，加油！");
				break;
			}
			case 6: { // 记忆模块
				string code = "";
				array<unsigned, 5> now;
				unsigned ans = 0;
				array<pair<unsigned, unsigned>, 4> history;
				printa("编码格式为{屏幕数字}{下方四位数字}，请放心，程序会帮你记住的^_^");

				// 第一次
				print("请输入第一次的情况: ");
				input6(code, now);
				switch (now[0]) {
				case 1:
					ans = 2;
					break;
				case 2:
					[[fallthrough]];
				case 3:
					[[fallthrough]];
				case 4:
					ans = now[0];
					break;
				}
				print("按下第", ans, "个位置的按钮\n");
				history[0] = { ans, now[ans] };

				// 第二次
				print("请输入第二次的情况: ");
				input6(code, now);
				for (int i = 0; i < 5; i++) { now[i] = code[i] - '0'; }
				switch (now[0]) {
				case 1:
					for (int i = 1; i < 5; i++) { if (now[i] == 4) { ans = i; break; } }
					break;
				case 3:
					ans = 1;
					break;
				case 2:
					[[fallthrough]];
				case 4:
					ans = history[0].first;
					break;
				}
				print("按下第", ans, "个位置的按钮\n");
				history[1] = { ans, now[ans] };

				// 第三次
				print("请输入第三次的情况: ");
				input6(code, now);
				for (int i = 0; i < 5; i++) { now[i] = code[i] - '0'; }
				switch (now[0]) {
				case 1:
					for (int i = 1; i < 5; i++) { if (now[i] == history[1].second) { ans = i; break; } }
					break;
				case 2:
					for (int i = 1; i < 5; i++) { if (now[i] == history[0].second) { ans = i; break; } }
					break;
				case 3:
					ans = 3;
					break;
				case 4:
					for (int i = 1; i < 5; i++) { if (now[i] == 4) { ans = i; break; } }
					break;
				}
				print("按下第", ans, "个位置的按钮\n");
				history[2] = { ans, now[ans] };

				// 第四次
				print("请输入第四次的情况: ");
				input6(code, now);
				for (int i = 0; i < 5; i++) { now[i] = code[i] - '0'; }
				switch (now[0]) {
				case 1:
					ans = history[0].first;
					break;
				case 2:
					ans = 1;
					break;
				case 3:
					[[fallthrough]];
				case 4:
					ans = history[1].first;
					break;
				}
				print("按下第", ans, "个位置的按钮\n");
				history[3] = { ans, now[ans] };

				// 第五次
				print("请输入第五次的情况: ");
				input6(code, now);
				for (int i = 0; i < 5; i++) { now[i] = code[i] - '0'; }
				switch (now[0]) {
				case 1:
					for (int i = 1; i < 5; i++) { if (now[i] == history[0].second) { ans = i; break; } }
					break;
				case 2:
					for (int i = 1; i < 5; i++) { if (now[i] == history[1].second) { ans = i; break; } }
					break;
				case 3:
					for (int i = 1; i < 5; i++) { if (now[i] == history[3].second) { ans = i; break; } }
					break;
				case 4:
					for (int i = 1; i < 5; i++) { if (now[i] == history[2].second) { ans = i; break; } }
					break;
				}
				print("按下第", ans, "个位置的按钮\n");

				break;
			}
			case 7: { // 摩斯电码
				string code = "", ans = "";
				printa("请输入摩斯密码，0代表短，1代表长，每次输入一个字母，全部输入完后输入任意非数字完成单词输入: ");
				while (true) {
					print("输入: ");
					cin >> code;
					if (!std::all_of(code.begin(), code.end(), ::isdigit)) {
						break;
					}
					auto temp = morse_to_char.find(code);
					if (temp == morse_to_char.end()) {
						printa("没有这个摩斯电码");
						continue;
					}
					print("本次输入的是: ", temp->second, '\n');
					ans += temp->second;
					print("当前得到的是: ", ans, '\n');
				}
				print("你的密码是: ", ans, '\n');
				auto temp = table7.find(ans);
				if (temp == table7.end()) [[unlikely]] { printa("库里没这个单词"); }
				else [[likely]] { print("对应的数字是: ", temp->second, '\n'); }
				break;
			}
			case 8: { // 复杂线路
				string code = "";
				printa("编码格式为{红色}{蓝色}{符号}{LED}，存在为1，不存在为0，不规范输入表示该模块完成");
				while (true) {
					print("请输入编码: ");
					cin >> code;
					if (code.length() != 4) { break; }
					// 直接查表
					bitset<4> bits(code);
					switch (table8[static_cast<uint8_t>(bits.to_ulong())]) {
					case 'C': // 剪断线路
						printa("剪!");
						break;
					case 'D': // 不要剪断线路
						printa("不剪!");
						break;
					case 'S': // 如果炸弹序列号末位为偶数则剪断线路
						if (!odd) { printa("剪!"); }
						else { printa("不剪!"); }
						break;
					case 'P': // 如果炸弹有Parallel端口则剪断线路
						if (parallel) { printa("剪!"); }
						else { printa("不剪!"); }
						break;
					case 'B': // 如果炸弹上有两个或更多电池则剪断线路
						if (battery >= 2) { printa("剪!"); }
						else { printa("不剪!"); }
						break;
					}
				}
				break;
			}
			case 9: { // 顺序线路
				array<unsigned, 3> active = {0, 0, 0};
				unsigned choice = 0;
				string code = "";
				bool flag = false;
				while (true) {
					print("请选择线路(123对应红蓝黑，0表示退出): ");
					cin >> choice;
					while (choice > 3) {
						print("线路应当是123之中一个，请重新输入: ");
						cin >> choice;
					}
					if (choice == 0) { break; }
					printa("请按照左侧从上倒下的顺序输入当前颜色对应的字母(使用123代替ABC): ");
					cin >> code;
					for (const char& c : code) {
						if (unsigned(c - '1') > 3) {
							printa("字母应当在123中取，请你重新开始本模块");
							flag = true;
							break;
						}
						print(table9[choice - 1][active[choice - 1]][c - '1'] ? "剪!" : "不剪!", " ");
						active[choice - 1]++;
					}
					if (flag) { break; }
					printa("");
				}
				break;
			}
			case 10: { // 迷宫模块
				unsigned temp;
				unsigned type = 0;
				printa("其实，任意一个圈的坐标都足以确定迷宫结构");
				printa("接下来的坐标格式均为{行}{列}，以左上角为11");
				print("请输入一个圈的坐标: ");
				cin >> temp;
				while (true) {
					if (temp / 10 >= 7 || temp / 10 < 1 || temp % 10 > 6 || temp % 10 == 0) {
						print("行列均应在1到6之间，请重新输入: ");
						cin >> temp;
						continue;
					}
					type = table10[temp];
					if (type == 0) {
						print("未找到对应的迷宫，请重新输入: ");
						cin >> temp;
						continue;
					}
					break;
				}
				print("该迷宫的类型是: ", type, "，接下来将输出对应的迷宫\n");
				printa(draw_maze10(type - 1));
				print("请输入起点坐标: ");
				cin >> temp;
				while (temp / 10 >= 7 || temp / 10 < 1 || temp % 10 > 6 || temp % 10 == 0) {
					print("行列均应在1到6之间，请重新输入: ");
					cin >> temp;
				}
				pair<int, int> start = { static_cast<int>(temp / 10) - 1, static_cast<int>(temp % 10) - 1 };
				print("请输入终点坐标: ");
				cin >> temp;
				while (temp / 10 >= 7 || temp / 10 < 1 || temp % 10 > 6 || temp % 10 == 0) {
					print("行列均应在1到6之间，请重新输入: ");
					cin >> temp;
				}
				pair<int, int> end = { static_cast<int>(temp / 10) - 1, static_cast<int>(temp % 10) - 1 };
				printa("计算得到的路径为");
				printa(draw_maze10(type - 1, solve10(mazes10[type - 1], start, end)));
#ifdef _DEBUG
				printa(output_path10(solve10(mazes10[type - 1], start, end)));
#endif
				break;
			}
			case 11: { // 密码模块
				string ch;
				vector<string> table_temp(35);
				std::copy(table11.begin(), table11.end(), table_temp.begin());
				bool flag = false;
				for (int i = 0; i < 5; i++) {
					print("请按第", i + 1, "个位置的可能字母（6个小写字母，中间无空格）: ");
					cin >> ch;
					while (ch.size() != 6) {
						print("应当是6个字母，请重新输入: ");
						cin >> ch;
					}
					for (string& word : table_temp) {
						table_temp.erase(
							remove_if(
								table_temp.begin(),
								table_temp.end(),
								[&ch, i](const string& w) { return ch.find(w[i]) == string::npos; }
							),
							table_temp.end()
						);
						if (table_temp.size() == 1) [[likely]] {
							print("正确答案是: ", table_temp[0], '\n');
							flag = true;
							break;
						}
						else if (table_temp.empty()) [[unlikely]] {
							printa("没有符合条件的单词，请检查输入是否正确");
							flag = true;
							break;
						}
					}
					if (flag) { break; }
				}
				break;
			}
			case 12: { // 旋钮模块
				// 读取并编码
				string code = "";
				printa("请输入灯泡亮起的模式，按从左到右，先第一行后第二行，亮起为1进行编码:");
				cin >> code;
				if (code.length() != 12) {
					printa("非法输入");
					break;
				}
				// 直接查表
				bitset<12> bits(code);
				switch (table12[static_cast<uint16_t>(bits.to_ulong())]) {
				case 1:
					printa("上");
					break;
				case 2:
					printa("下");
					break;
				case 3:
					printa("左");
					break;
				case 4:
					printa("右");
					break;
				default:
					printa("没有这个排列");
					break;
				}
				break;
			}
			case 13:
				[[unlikely]];
				goto restart;
			default: {
				printa("你输入了错误指令");
				break;
			}
		}
		system("pause");
	}
}
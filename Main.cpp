/*Made by Wang125510*/

#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include <unordered_map>

#ifdef _WIN32
#include <thread>
#include <windows.h>
#endif

#include "mytool.h"

using std::cin, std::string, std::array, std::fill, std::bitset, std::pair, std::unordered_map, std::thread;
using mytool::print, mytool::printa, mytool::prints;

#ifdef _DEBUG
	using mytool::pass;
#endif // DEBUG

#ifdef _WIN32
	// 检查当前是否以管理员权限运行
	BOOL IsRunAsAdmin() {
		BOOL isAdmin = FALSE;
		PSID adminGroup = NULL;

		// 创建管理员组的 SID
		SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		if (AllocateAndInitializeSid(&NtAuthority, 2,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0,
			&adminGroup)) {

			if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
				isAdmin = FALSE;
			}

			FreeSid(adminGroup);
		}

		return isAdmin;
	}

	// 请求以管理员权限重新启动程序
	BOOL RestartAsAdmin() {
		WCHAR szPath[MAX_PATH];
		if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
			SHELLEXECUTEINFO sei = { sizeof(sei) };

			sei.lpVerb = L"runas";  // 请求提升权限的关键
			sei.lpFile = szPath;
			sei.hwnd = NULL;
			sei.nShow = SW_NORMAL;

			if (ShellExecuteEx(&sei)) {
				return TRUE;
			}
			else {
				DWORD dwError = GetLastError();
				if (dwError == ERROR_CANCELLED) {
					// 用户拒绝了 UAC 提示
					MessageBox(NULL, L"需要管理员权限才能继续操作", L"权限不足", MB_ICONWARNING);
				}
				return FALSE;
			}
		}
		return FALSE;
	}
#endif



// 模块4
const unsigned table4[2][3][4] = {
	{ {4,3,2,1}, {1,4,3,2}, {3,2,4,1} },
	{ {4,1,3,2}, {3,2,4,1}, {2,1,3,4} }
};
// 模块7
const unordered_map<string, char> morse_to_char = {
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
const unordered_map<string, unsigned> table7 = {
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
const char table8[16] = {
	'C', 'D', 'C', 'B',
	'S', 'P', 'D', 'P',
	'S', 'B', 'C', 'B',
	'S', 'S', 'P', 'D'
};
// 模块9
const bool table9[3][9][3] = {
	{ {0,0,1}, {0,1,0}, {1,0,0}, {1,0,1}, {0,1,0}, {1,0,1}, {1,1,1}, {1,1,0}, {0,1,0} },
	{ {0,1,0}, {1,0,1}, {0,1,0}, {1,0,0}, {0,1,0}, {0,1,1}, {0,0,1}, {1,0,1}, {1,0,0} },
	{ {1,1,1}, {1,0,1}, {0,1,0}, {1,0,1}, {0,1,0}, {0,1,1}, {1,1,0}, {0,0,1}, {0,0,1} }
};
// 模块11
const array<string, 35> table11 = {
	"about", "after", "again", "below", "could",
	"every", "first", "found", "great", "house",
	"large", "learn", "never", "other", "place",
	"plant", "point", "right", "small", "sound",
	"spell", "still", "study", "their", "there",
	"these", "thing", "think", "three", "water",
	"where", "which", "world", "would", "write"
};
// 模块12
constexpr array <uint8_t, 4096> make_table12 () {
	array <uint8_t, 4096> table12;
	fill(table12.begin(), table12.end(), 0);
	table12[0x2FD] = 1;
	table12[0xA9B] = 1;
	table12[0x67D] = 2;
	table12[0xA91] = 2;
	table12[0x0A7] = 3;
	table12[0x086] = 3;
	table12[0xBFA] = 4;
	table12[0xB3A] = 4;
	return table12;
}
constexpr const array <uint8_t, 4096> table12 = make_table12();


int main() {
#ifdef _WIN32 // Win相关设置
	// 设置标题
	SetConsoleTitle(TEXT("Bomb Manual Assistant"));
	// 要求用户启用管理员权限
	if (!IsRunAsAdmin()) {
		// 请求以管理员权限重新启动
		if (RestartAsAdmin()) {
			return 0; // 当前进程退出
		}
		else {
			// 用户拒绝了权限请求
			return 1;
		}
	}
	// 设置置顶
	if (HWND hwnd = GetConsoleWindow()) {
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
#endif

	bool odd = 0, aeiou = 0, parallel = 0;
	unsigned battery = 0, module = 0;
	unsigned ;

	// 开始提示
	prints('\n', '\n',
		"此程序仅用于辅助拆弹助手，带有一定作弊性质，请谨慎使用！",
		"建议第一次使用时先将各个模块的编码方式完整阅读，部分模块直接对照手册会更快。",
		"祝你好运 ^_^",
		"Made by Wang125510"
	);

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
		cin >> module;
		switch (module) {
			case 1: {
				unsigned counts = 0;
				print("请输入线的数量: ");
				cin >> counts;
				switch (counts) {
				case 3:
					prints('\n', '\n',
						"如果没有红线，则剪断第二根线",
						"否则，当最后一根线为白线时，剪断最后一根线",
						"否则，当有不止一根蓝线的时候，剪断最后一根蓝线",
						"否则，剪断最后一根线"
					);
					break;
				case 4:
					prints('\n', '\n',
						"如果有不止一根红线且序列号末位为奇数，则剪断最后一根红线",
						"否则，当没有红线且最后一根线是黄线时，剪断第一根线",
						"否则，当有且仅有一根蓝线时，剪断第一根线",
						"则，当有不止一根黄线时，剪断最后一根线",
						"则，剪断第二根线"
					);
					break;
				case 5:
					prints('\n', '\n',
						"如果最后一根线是黑线且序列号末位为奇数，则剪断第四根线",
						"否则，当有且仅有一根红线，且黄线不止一根时，剪断第一根线",
						"否则，当没有黑线时，剪断第二根线",
						"否则，剪断第一根线"
					);
					break;
				case 6:
					prints('\n', '\n',
						"如果没有黄线且序列号末位为奇数，则剪断第三根线",
						"否则，当有且仅有一根黄线，且白线不止一根时，剪断第四根线",
						"否则，当没有红线时，剪断最后一根线",
						"否则，剪断第四根线"
					);
					break;
				}
				break;
			}
			case 2: { // 按钮模块
				prints('\n', '\n',
					"如果是写有“中止”的蓝色按钮，按住按钮",
					"如果炸弹上有不止1个电池，同时按钮上写着“引爆”，按下按钮并立即松开",
					"如果按钮是白色的，同时炸弹上有个写着CAR的指示灯亮，按住按钮",
					"如果炸弹上有不止2个电池，也有写着FRK的指示灯亮，按下按钮并立即松开",
					"如果按钮是黄色的，按住按钮",
					"如果是写有“按住”的红色按钮，按下按钮并立即松开",
					"如果不满足上述任一情况，按住按钮",
					"",
					"以下是光条对应的操作:"
					"蓝色： 在计时器任意数位显示4时松开",
					"白色： 在计时器任意数位显示1时松开",
					"黄色： 在计时器任意数位显示5时松开",
					"其他： 在计时器任意数位显示1时松开"
				);
				break;
			}
			case 3: { // 键盘模块
				printa("由于背诵符号编码很抽象，这个还是自己来更快，加油！");
				break;
			}
			case 4: { // 四色方块
				unsigned times = 0, temp = 0;
				print("目前失误了几次: ");
				cin >> times;
				printa("接下来输入本次新增的颜色，红绿黄蓝对应1234，输入超过4表示退出");
				while (true) {
					print("请输入本次的颜色: ");
					cin >> temp;
					if (temp > 4) { break; }
					printa(table4[aeiou][times][temp - 1]);
				}
				break;
			}
			case 5: { // 汉字模块
				printa("由于汉字输入过于麻烦，这个还是自己来更快，加油！");
				break;
			}
			case 6: { // 记忆模块
				string code = "";
				unsigned now[5];
				unsigned ans = 0;
				pair<unsigned, unsigned> history[4];
				printa("编码格式为{屏幕数字}{下方四位数字}，请放心，程序会帮你记住的^_^");

				// 第一次
				print("请输入第一次的情况: ");
				cin >> code;
				for (int i = 0; i < 5; i++) { now[i] = code[i] - '0'; }
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
				cin >> code;
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
				cin >> code;
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
				cin >> code;
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
				cin >> code;
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
					cin >> code;
					if (!std::all_of(code.begin(), code.end(), ::isdigit)) { break; }
					ans += morse_to_char.find(code)->second;
				}
				print("你的密码是: ", ans, '\n');
				auto it = table7.find(ans);
				if (it == table7.end()) { printa("库里没这个单词"); }
				else { print("对应的数字是: ", it->second, '\n'); }
				break;
			}
			case 8: { // 复杂线路
				string code = "";
				printa("编码格式为{红色}{蓝色}{符号}{LED}，存在为1，不存在为0，输入'0'表示该模块完成");
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
				printa("请输入");
				unsigned active[3] = {0, 0, 0};
				unsigned choice = 0;
				string code = "";
				while (true) {
					print("请选择线路(123对应红蓝黑，0表示退出): ");
					cin >> choice;
					if (choice == 0) { break; }
					printa("请按照左侧从上倒下的顺序输入当前颜色对应的字母(使用123代替ABC): ");
					cin >> code;
					for (char& c : code) {
						print(table9[choice - 1][active[choice - 1]][c - '1'] ? "剪!" : "不剪!", " ");
						active[choice - 1]++;
					}
					printa("");
				}
				break;
			}
			case 10: { // 迷宫模块
				printa("由于图片分析+操作编码太麻烦，这个还是自己来更快，加油！");
				break;
			}
			case 11: { // 密码模块
				string pos1, pos2, pos3, pos4, pos5;
				printa("请按顺序输入五个位置的可能字母（每个位置6个字母，中间无空格）:");
				cin >> pos1 >> pos2 >> pos3 >> pos4 >> pos5 ;
				for (const string& word : table11) {
					if (pos1.find(word[0]) != string::npos
						&& pos2.find(word[1]) != string::npos
						&& pos3.find(word[2]) != string::npos
						&& pos4.find(word[3]) != string::npos
						&& pos5.find(word[4]) != string::npos
					) {
						print("正确答案是", word, '\n');
						break;
					}
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
					printa("非法输入");
					break;
				}
				break;
			}
			case 13:
				goto restart;
			default: {
				printa("你输入了错误指令");
				break;
			}
		}
		system("pause");
	}

	return 0;
}
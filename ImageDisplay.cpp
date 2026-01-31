// 由deepseek生成
#include "ImageDisplay.h"
#include <thread>
#include <chrono>
#include <iostream>

// 静态成员初始化
HWND ImageDisplay::s_hwnd = nullptr;
HBITMAP ImageDisplay::s_hBitmap = nullptr;
HWND ImageDisplay::s_staticControl = nullptr;
int ImageDisplay::s_timeoutMs = 0;
UINT_PTR ImageDisplay::s_timerId = 0;

bool ImageDisplay::show_image(int resourceId, const std::string& title, int timeoutMs) {
	// 如果已有窗口，先关闭
	if (s_hwnd != nullptr) {
		close_image();
		// 短暂等待确保窗口完全关闭
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// 在新线程中创建窗口，避免阻塞调用者
	std::thread([resourceId, title, timeoutMs]() {
		CreateWindowInstance(resourceId, title, timeoutMs);
		}).detach();

	return true;
}

bool ImageDisplay::show_image(const char* resourceName, const std::string& title, int timeoutMs) {
	if (s_hwnd != nullptr) {
		close_image();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::thread([resourceName, title, timeoutMs]() {
		CreateWindowInstance(resourceName, title, timeoutMs);
		}).detach();

	return true;
}

void ImageDisplay::CreateWindowInstance(int resourceId, const std::string& title, int timeoutMs) {
	s_timeoutMs = timeoutMs;

	HINSTANCE hInstance = GetModuleHandle(nullptr);

	// 注册窗口类
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ImageDisplayClass";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wc);

	// 加载位图资源
	s_hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(resourceId));
	if (!s_hBitmap) {
		std::cerr << "Failed to load bitmap resource ID: " << resourceId << std::endl;
		return;
	}

	// 获取位图尺寸
	BITMAP bmp;
	GetObject(s_hBitmap, sizeof(BITMAP), &bmp);

	// 添加缩放比例计算（假设我们希望最大显示为800x600）
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int maxWidth = min(800, screenWidth * 0.8);  // 最大宽度的80%
	int maxHeight = min(600, screenHeight * 0.8); // 最大高度的80%

	double scaleX = (double)maxWidth / bmp.bmWidth;
	double scaleY = (double)maxHeight / bmp.bmHeight;
	double scale = min(min(scaleX, scaleY), 1.0); // 保持比例，不超过原图大小

	int displayWidth = (int)(bmp.bmWidth * scale);
	int displayHeight = (int)(bmp.bmHeight * scale);

	// 创建窗口时使用缩放后的尺寸
	s_hwnd = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
		L"ImageDisplayClass",
		std::wstring(title.begin(), title.end()).c_str(),
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		displayWidth + 16,
		displayHeight + 40,
		nullptr, nullptr, hInstance, nullptr
	);

	// 创建静态控件时使用SS_REALSIZECONTROL
	s_staticControl = CreateWindow(
		L"STATIC", nullptr,
		WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_REALSIZECONTROL,
		8, 8, displayWidth, displayHeight,
		s_hwnd, nullptr, hInstance, nullptr
	);

	// 创建静态控件显示位图
	s_staticControl = CreateWindow(
		L"STATIC", nullptr,
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		8, 8, bmp.bmWidth, bmp.bmHeight,
		s_hwnd, nullptr, hInstance, nullptr
	);

	// 在创建静态控件和设置位图之后，手动触发一次初始缩放
	SendMessage(s_staticControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)s_hBitmap);

	// 立即发送一个WM_SIZE消息，让位图进行初始缩放
	PostMessage(s_hwnd, WM_SIZE, 0,
		MAKELPARAM(displayWidth + 16, displayHeight + 40));

	// 居中显示
	RECT screenRect;
	GetClientRect(GetDesktopWindow(), &screenRect);
	RECT windowRect;
	GetWindowRect(s_hwnd, &windowRect);
	int x = (screenRect.right - (windowRect.right - windowRect.left)) / 2;
	int y = (screenRect.bottom - (windowRect.bottom - windowRect.top)) / 2;
	SetWindowPos(s_hwnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// 设置自动关闭定时器
	if (timeoutMs > 0) {
		s_timerId = SetTimer(s_hwnd, 1, timeoutMs, nullptr);
	}

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void ImageDisplay::CreateWindowInstance(const char* resourceName, const std::string& title, int timeoutMs) {
	s_timeoutMs = timeoutMs;

	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ImageDisplayClass";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wc);

	// 按名称加载位图
	s_hBitmap = LoadBitmap(hInstance, std::wstring(resourceName, resourceName + strlen(resourceName)).c_str());
	if (!s_hBitmap) {
		std::cerr << "Failed to load bitmap resource: " << resourceName << std::endl;
		return;
	}

	BITMAP bmp;
	GetObject(s_hBitmap, sizeof(BITMAP), &bmp);

	s_hwnd = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
		L"ImageDisplayClass",
		std::wstring(title.begin(), title.end()).c_str(),
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		bmp.bmWidth + 16,
		bmp.bmHeight + 40,
		nullptr, nullptr, hInstance, nullptr
	);

	if (!s_hwnd) {
		DeleteObject(s_hBitmap);
		s_hBitmap = nullptr;
		return;
	}

	HINSTANCE hInst = GetModuleHandle(nullptr);
	s_staticControl = CreateWindow(
		L"STATIC", nullptr,
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		8, 8, bmp.bmWidth, bmp.bmHeight,
		s_hwnd, nullptr, hInst, nullptr
	);

	SendMessage(s_staticControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)s_hBitmap);

	RECT screenRect;
	GetClientRect(GetDesktopWindow(), &screenRect);
	RECT windowRect;
	GetWindowRect(s_hwnd, &windowRect);
	int x = (screenRect.right - (windowRect.right - windowRect.left)) / 2;
	int y = (screenRect.bottom - (windowRect.bottom - windowRect.top)) / 2;
	SetWindowPos(s_hwnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	if (timeoutMs > 0) {
		s_timerId = SetTimer(s_hwnd, 1, timeoutMs, nullptr);
	}

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT ImageDisplay::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_TIMER:
		if (wParam == 1) {
			KillTimer(hwnd, s_timerId);
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			DestroyWindow(hwnd);
		}
		return 0;

		//case WM_LBUTTONDOWN:
		//    // 点击窗口任意位置可关闭
		//    DestroyWindow(hwnd);
		//    return 0;
	case WM_SIZE: {
		if (s_staticControl && s_hBitmap) {
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);

			int width = clientRect.right - 16;
			int height = clientRect.bottom - 40;

			if (width > 0 && height > 0) {
				// 获取原始位图尺寸
				BITMAP bm;
				GetObject(s_hBitmap, sizeof(bm), &bm);

				// 计算保持比例的缩放尺寸
				float aspectRatio = (float)bm.bmWidth / bm.bmHeight;
				int scaledWidth, scaledHeight, offsetX = 0, offsetY = 0;

				// 基于当前窗口大小计算保持比例的尺寸
				if ((float)width / height > aspectRatio) {
					// 窗口更宽，按高度缩放
					scaledHeight = height;
					scaledWidth = (int)(height * aspectRatio);
					offsetX = (width - scaledWidth) / 2;  // 水平居中
				}
				else {
					// 窗口更高，按宽度缩放
					scaledWidth = width;
					scaledHeight = (int)(width / aspectRatio);
					offsetY = (height - scaledHeight) / 2;  // 垂直居中
				}

				// 创建缩放位图（保持比例）
				HDC hdcScreen = GetDC(nullptr);
				HDC hdcMem = CreateCompatibleDC(hdcScreen);
				HBITMAP hScaledBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
				HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hScaledBitmap);

				// 填充白色背景
				HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
				RECT fillRect = { 0, 0, width, height };
				FillRect(hdcMem, &fillRect, hWhiteBrush);
				DeleteObject(hWhiteBrush);

				// 创建源位图DC
				HDC hdcSrc = CreateCompatibleDC(nullptr);
				HBITMAP hOldSrc = (HBITMAP)SelectObject(hdcSrc, s_hBitmap);

				// 居中绘制保持比例的图片
				SetStretchBltMode(hdcMem, COLORONCOLOR);
				StretchBlt(hdcMem, offsetX, offsetY, scaledWidth, scaledHeight,
					hdcSrc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

				// 清理资源
				SelectObject(hdcSrc, hOldSrc);
				DeleteDC(hdcSrc);
				SelectObject(hdcMem, hOldBmp);
				DeleteDC(hdcMem);
				ReleaseDC(nullptr, hdcScreen);

				// 设置新的缩放位图
				HBITMAP hOldBitmap = (HBITMAP)SendMessage(s_staticControl, STM_GETIMAGE,
					IMAGE_BITMAP, 0);
				SendMessage(s_staticControl, STM_SETIMAGE,
					IMAGE_BITMAP, (LPARAM)hScaledBitmap);

				// 删除旧的缩放位图
				if (hOldBitmap && hOldBitmap != s_hBitmap) {
					DeleteObject(hOldBitmap);
				}

				// 控件占满整个客户区（白边在图片内部）
				SetWindowPos(s_staticControl, nullptr,
					8, 8, width, height,
					SWP_NOZORDER | SWP_NOACTIVATE);
			}
		}
		return 0;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void ImageDisplay::close_image() {
	if (s_hwnd != nullptr) {
		// 发送关闭消息到窗口线程
		PostMessage(s_hwnd, WM_CLOSE, 0, 0);

		// 等待一小段时间确保窗口关闭
		for (int i = 0; i < 10 && s_hwnd != nullptr; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

bool ImageDisplay::is_showing() {
	return s_hwnd != nullptr && IsWindow(s_hwnd);
}

void ImageDisplay::Cleanup() {
	if (s_hBitmap) {
		DeleteObject(s_hBitmap);
		s_hBitmap = nullptr;
	}

	if (s_timerId != 0) {
		s_timerId = 0;
	}

	s_hwnd = nullptr;
	s_staticControl = nullptr;
	s_timeoutMs = 0;
}
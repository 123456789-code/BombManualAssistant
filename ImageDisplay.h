// 由deepseek生成
#pragma once
#include <windows.h>
#include <string>

class ImageDisplay {
public:
    // 显示位图图像
    // @param resourceId: RC文件中的位图资源ID
    // @param title: 窗口标题
    // @param timeoutMs: 自动关闭时间（毫秒），0表示不自动关闭
    // @return: 成功返回true，失败返回false
    static bool show_image(int resourceId, const std::string& title = "Image Display", int timeoutMs = 0);

    // 显示位图图像（通过资源名称）
    static bool show_image(const char* resourceName, const std::string& title = "Image Display", int timeoutMs = 0);

    // 关闭图像窗口
    static void close_image();

    // 检查窗口是否正在显示
    static bool is_showing();

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static void CreateWindowInstance(int resourceId, const std::string& title, int timeoutMs);
    static void CreateWindowInstance(const char* resourceName, const std::string& title, int timeoutMs);
    static void Cleanup();

    static HWND s_hwnd;
    static HBITMAP s_hBitmap;
    static HWND s_staticControl;
    static int s_timeoutMs;
    static UINT_PTR s_timerId;
};
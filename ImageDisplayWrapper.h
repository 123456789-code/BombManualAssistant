// 由deepseek生成
#pragma once
#include "ImageDisplay.h"

// 简单包装函数，符合您的要求
inline bool show_image(int resourceId, const char* title = "Image Display", int timeoutMs = 0) {
    return ImageDisplay::show_image(resourceId, title, timeoutMs);
}

inline bool show_image(const char* resourceName, const char* title = "Image Display", int timeoutMs = 0) {
    return ImageDisplay::show_image(resourceName, title, timeoutMs);
}

inline void close_image() {
    ImageDisplay::close_image();
}

inline bool is_image_showing() {
    return ImageDisplay::is_showing();
}
#include "Console.h"

#include <Windows.h>

#include <iostream>

using namespace miniant::Windows;

Console::Console(std::function<void()> onShow):
    m_onShow(std::move(onShow)) {}

void Console::Open() {
    ::AllocConsole();

    FILE* dummy;
    freopen_s(&dummy, "conout$", "w", stdout);
    std::cout.clear();

    if (m_onShow)
        m_onShow();
}

void Console::Close() {
    ::SendMessage(::GetConsoleWindow(), WM_CLOSE, 0, 0);
    ::FreeConsole();
}
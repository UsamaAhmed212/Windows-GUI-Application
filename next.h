#ifndef NEXT_H
#define NEXT_H

#include <windows.h>

// Function declarations
int showKeyboardLayout(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif

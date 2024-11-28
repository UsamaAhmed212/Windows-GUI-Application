#include "next.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Call the function from next.c
    return showKeyboardLayout(hInstance, nShowCmd);
}

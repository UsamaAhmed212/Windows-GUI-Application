#include <stdio.h>
#include <windows.h>
#include "resource.h" // Include your resource header
#include <wchar.h>

// Function prototype for window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Define a struct to hold the character and its corresponding key
struct KeyValue {
    wchar_t banglaChar[20];  // Bangla character
    char key[20];         // Corresponding keyboard key
};

// Define an array of consonants (ব্যঞ্জনবর্ণ) for the keyboard layout
struct KeyValue keyboardLayoutConsonants[] = {
    {L"ক", "k"},
    {L"খ", "K"},
    {L"গ", "g"},
    {L"ঘ", "G"},
    {L"ঙ", "NG"},
    {L"চ", "c"},
    {L"ছ", "C"},
    {L"জ", "j"},
    {L"ঝ", "J"},
    {L"ঞ", "NIO"},
    {L"ট", "t"},
    {L"ঠ", "T"},
    {L"ড", "d"},
    {L"ঢ", "D"},
    {L"ণ", "N"},
    {L"ত", "T"},
    {L"থ", "th"},
    {L"দ", "d"},
    {L"ধ", "Dh"},
    {L"ন", "n"},
    {L"প", "p"},
    {L"ফ", "P"},
    {L"ব", "b"},
    {L"ভ", "B"},
    {L"ম", "m"},
    {L"য", "z"},
    {L"র", "r"},
    {L"ল", "l"},
    {L"শ", "S"},
    {L"ষ", "M"},
    {L"স", "s"},
    {L"হ", "h"},
    {L"ড়", "RR"},
    {L"ঢ়", "RRh"},
    {L"য়", "Y"},
    {L"ৎ", "q"},
    {L"ং", "ng"},
    {L"ঃ", ":"},
    {L"ঁ", "^"}
};

// Main function to draw the text and handle the keyboard layout
void drawKeyboardLayout(HWND hwnd, HDC hdc) {
    // Create a font that supports Bangla
    HFONT hFont = CreateFontW(
        30,                     // Height of font
        0,                      // Width of font
        0,                      // Angle of escapement
        0,                      // Orientation angle
        FW_BOLD,                // Font weight (bold)
        FALSE,                  // Italic
        FALSE,                  // Underline
        FALSE,                  // Strikeout
        DEFAULT_CHARSET,        // Character set identifier
        OUT_OUTLINE_PRECIS,     // Output precision
        CLIP_DEFAULT_PRECIS,    // Clipping precision
        CLEARTYPE_QUALITY,      // Output quality
        DEFAULT_PITCH,          // Pitch and family
        L"Nirmala UI"           // Font name (Nirmala UI supports Bangla)
    );
    // Select the font into the DC
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);


    RECT rect = {10, 30, 45, 65};  // Define initial rectangle
    
    // Set up the brush and pen for drawing the rounded rectangles
    HBRUSH hBrush = CreateSolidBrush(RGB(235, 171, 0)); // Background color: #EBAB00
    HPEN hPenTransparent = CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // Transparent pen (no border)
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPenTransparent);

    // Loop for drawing the characters in the layout
    for (int i = 0; i < sizeof(keyboardLayoutConsonants) / sizeof(keyboardLayoutConsonants[0]); ++i) {
        // Draw the rounded rectangle
        RoundRect(
            hdc,                  // Handle to the device context
            rect.left,            // x-coordinate of the upper-left corner
            rect.top,             // y-coordinate of the upper-left corner
            rect.right,           // x-coordinate of the lower-right corner
            rect.bottom,          // y-coordinate of the lower-right corner
            15,                   // Width of the ellipse used to round the corners
            15                    // Height of the ellipse used to round the corners
        );

        // Draw the Bangla text inside the rectangle
        SetBkMode(hdc, TRANSPARENT); // Enable transparent background
        DrawTextW(hdc, keyboardLayoutConsonants[i].banglaChar, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

        // Adjust the rectangle to draw the corresponding Latin character to the right of the Bangla text
        RECT khRect = {rect.right + 5, rect.top, rect.right + 50, rect.bottom}; // Shifted to the right
        DrawText(hdc, keyboardLayoutConsonants[i].key, -1, &khRect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);

        // Move the rectangle down by 37 pixels
        rect.top += 37;
        rect.bottom += 37;

        // After every 10 rectangles, move to the next column
        if ((i + 1) % 10 == 0) {
            rect.top = 30;  // Reset top position
            rect.bottom = 65;  // Reset bottom position
            rect.left += 100;  // Shift to the right by 100 pixels (accounting for added Latin characters)
            rect.right += 100;  // Shift to the right by 100 pixels
        }
    }
    
    // Clean up font
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    
    // Clean up GDI objects
    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPenTransparent);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Define the window class
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = {0}; // Initialize to zero
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(235, 196, 82)); // background color #EBC452 in RGB
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // Load the icon (optional)
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON)); // Set window icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set default cursor

    // Register the window class
    RegisterClass(&wc);

    // Define window dimensions
    const int width = 900;  // Window width
    const int height = 440; // Window height

    // Calculate center position
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - width) / 2; // Center X
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - height) / 2; // Center Y

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                          // Optional window styles
        CLASS_NAME,                 // Window class
        "Windows GUI Application",  // Window text
        WS_OVERLAPPEDWINDOW,        // Window style
        xPos, yPos, width, height,  // Size and position
        NULL,                       // Parent window
        NULL,                       // Menu
        hInstance,                  // Instance handle
        NULL                        // Additional application data
    );

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            DeleteObject((HBRUSH)GetClassLongPtr(hwnd, GCLP_HBRBACKGROUND));
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Get client area dimensions
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            // Original top border (50px)
            HPEN hPen = CreatePen(PS_SOLID, 45, RGB(240, 240, 240));
            HGDIOBJ oldPen = SelectObject(hdc, hPen);
            MoveToEx(hdc, clientRect.left, clientRect.top + 1, NULL);
            LineTo(hdc, clientRect.right, clientRect.top + 1);
            
            // Create 5px pen for left and right borders
            HPEN hPen5px = CreatePen(PS_SOLID, 5, RGB(240, 240, 240));
            SelectObject(hdc, hPen5px);
            
            // Draw left border
            MoveToEx(hdc, clientRect.left + 2, clientRect.top, NULL);
            LineTo(hdc, clientRect.left + 2, clientRect.bottom);
            
            // Draw right border
            // MoveToEx(hdc, clientRect.right - 2, clientRect.top, NULL);
            // LineTo(hdc, clientRect.right - 2, clientRect.bottom);
            
            // Create 2px pen for bottom border
            HPEN hPen2px = CreatePen(PS_SOLID, 2, RGB(240, 240, 240));
            SelectObject(hdc, hPen2px);
            
            // Draw bottom border
            MoveToEx(hdc, clientRect.left, clientRect.bottom - 1, NULL);
            LineTo(hdc, clientRect.right, clientRect.bottom - 1);

            // Clean up
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            DeleteObject(hPen5px);
            DeleteObject(hPen2px);

            // Call the drawKeyboardLayout function to render the keyboard layout on the window
            drawKeyboardLayout(hwnd, hdc);

            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#include <windows.h>
#include "resource.h" // Include your resource header
#include <stdio.h>

// Function prototype for window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Define the window class
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = {0}; // Initialize to zero
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(235, 196, 82)); // #EBC452 in RGB
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // Load the icon (optional)
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON)); // Set window icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set default cursor

    // Register the window class
    RegisterClass(&wc);

    // Define window dimensions
    const int width = 900;  // Window width
    const int height = 400; // Window height

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

            // Define starting position for text
            int startX = 150;
            int startY = 120;
            int lineHeight = 30; // Space between lines

            // Set text background color to #EBAB00
            SetBkColor(hdc, RGB(235, 171, 0));  // #EBAB00
            SetBkMode(hdc, OPAQUE);             // Ensure background is painted

            // Draw each spike on a new line
            TextOut(hdc, startX, startY, "spike a", 7);
            TextOut(hdc, startX, startY + lineHeight, "spike b", 7);
            TextOut(hdc, startX, startY + (lineHeight * 2), "spike c", 7);
            TextOut(hdc, startX, startY + (lineHeight * 3), "spike d", 7);


            // Set text background color to #EBAB00
            SetBkColor(hdc, RGB(235, 171, 0));  // #EBAB00
            SetBkMode(hdc, OPAQUE);             // Ensure background is painted

            // RECT rect = {15, 15, 200, 100};
            // DrawText(hdc, "Hello, World!", -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
            

            // Create a font that supports Bangla
            HFONT hFont = CreateFontW(
                30,                     // Height of font
                0,                      // Width of font
                0,                      // Angle of escapement
                0,                      // Orientation angle
                FW_NORMAL,              // Font weight
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

            // Set up the rectangle for drawing
            RECT rect = {15, 15, 200, 100};

            // Draw Text in the window using Unicode
            const wchar_t *text = L"ক";  // Bangla character "ক"

            // Draw the character with background color #EBAB00
            SetBkColor(hdc, RGB(235, 171, 0));  // Set background color
            SetBkMode(hdc, OPAQUE);             // Enable opaque background
            DrawTextW(hdc, text, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);

            // Calculate width of the text for offset
            SIZE textSize;
            GetTextExtentPoint32W(hdc, text, wcslen(text), &textSize);
            rect.left += textSize.cx;  // Move position after drawing

            SetBkMode(hdc, TRANSPARENT);  // Enable transparent background

            // Draw a space
            text = L" "; // Set text to a space
            GetTextExtentPoint32W(hdc, text, wcslen(text), &textSize);
            rect.left += textSize.cx;  // Move position after space

            // Draw the space
            DrawTextW(hdc, text, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);

            // Now draw the text "kh"
            text = L"kh";  // Set text to "kh"
            SetBkMode(hdc, TRANSPARENT);  // Enable transparent background
            DrawTextW(hdc, text, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);

            // Reset background mode if needed for other drawing operations
            SetBkMode(hdc, TRANSPARENT);

            
            EndPaint(hwnd, &ps);
            return 0;
        }


        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

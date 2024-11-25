#include <stdio.h>
#include <windows.h>
#include "resource.h" // Include your resource header
#include <wchar.h>

// Function prototype for window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to convert hex color string to RGB and return the RGB value
COLORREF HexToRGB(const char* hexColor) {
    int red, green, blue;
    
    // Convert the hexadecimal color string to RGB components
    sscanf(hexColor + 1, "%2x%2x%2x", &red, &green, &blue);
    
    // Return the color in RGB format (COLORREF)
    return RGB(red, green, blue);
}

// Define a structure to hold a Bangla character, its corresponding keyboard key, and its color
struct KeyboardLayout {
    wchar_t banglaChar[20];  // Wide-character array for Bangla characters
    char key[20];            // Corresponding keyboard key.Store the text value (single character + null terminator)
    char color[8];           // Store the color (HEX code as a string)
};

// Define an array of consonants (ব্যঞ্জনবর্ণ) for the keyboard layout
struct KeyboardLayout keyboardLayoutConsonants[] = {
    {L"ক", "k", "#b726bf"},
    {L"খ", "K", "#b726bf"},
    {L"গ", "g", "#b726bf"},
    {L"ঘ", "G", "#b726bf"},
    {L"ঙ", "umo", "#fc620b"},
    {L"চ", "c", "#b726bf"},
    {L"ছ", "C", "#b726bf"},
    {L"জ", "j", "#b726bf"},
    {L"ঝ", "J", "#b726bf"},
    {L"ঞ", "nio", "#fc620b"},
    {L"ট", "T", "#b726bf"},
    {L"ঠ", "TT", "#b726bf"},
    {L"ড", "D", "#b726bf"},
    {L"ঢ", "DD", "#b726bf"},
    {L"ণ", "N", "#b726bf"},
    {L"ত", "t", "#b726bf"},
    {L"থ", "tt", "#b726bf"},
    {L"দ", "d", "#b726bf"},
    {L"ধ", "dd", "#b726bf"},
    {L"ন", "n", "#b726bf"},
    {L"প", "p", "#b726bf"},
    {L"ফ", "P", "#b726bf"},
    {L"ব", "b,V", "#b726bf"},
    {L"ভ", "B,v", "#b726bf"},
    {L"ম", "m", "#b726bf"},
    {L"য", "z", "#b726bf"},
    {L"র", "r", "#b726bf"},
    {L"ল", "l", "#b726bf"},
    {L"শ", "S", "#b726bf"},
    {L"ষ", "M", "#b726bf"},
    {L"স", "s", "#b726bf"},
    {L"হ", "h", "#fc620b"},
    {L"ড়", "R", "#b726bf"},
    {L"ঢ়", "RR", "#b726bf"},
    {L"য়", "y", "#fc620b"},
    {L"ৎ", "q", "#b726bf"},
    {L"ং", "Q", "#b726bf"},
    {L"ঃ", ":", "#fc620b"},
    {L"ঁ", "^", "#fc620b"},
    {L"ল", "L", "#b726bf"},
};

// Define an array of vowels (স্বরবর্ণ) for the keyboard layout
struct KeyboardLayout keyboardLayoutVowels[] = {
    {L"অ    ", "a", "#b726bf"},
    {L"আ    া", "A", "#b726bf"},
    {L"ই    ি", "i", "#b726bf"},
    {L"ঈ    ী", "I", "#b726bf"},
    {L"উ   ◌ুু", "u", "#b726bf"},
    {L"ঊ   ◌ূ", "U", "#b726bf"},
    {L"ঋ   ◌ৃ", "rie", "#fc620b"},
    {L"এ    ে", "e", "#b726bf"},
    {L"ঐ    ৈ", "E", "#b726bf"},
    {L"ও    ো", "o", "#b726bf"},
    {L"ঔ    ৌ", "O", "#b726bf"},
};

// Define an array of Bangla Character Signs for the keyboard layout
struct KeyboardLayout keyboardLayoutBanglaCharacterSigns[] = {
    {L"ব ফলা", "bb,VV", "#b726bf"},
    {L"য ফলা", "Z", "#b726bf"},
    {L"র ফলা", "rr", "#b726bf"},
    {L"রেফ", "X", "#b726bf"},
    {L"হসন্ত", "x", "#b726bf"},
    {L"। - দাড়ি", ".", "#fc620b"},
    {L"৳ - টাকা", "$", "#fc620b"},
    {L". - ডট", ".(NP)", "#fc620b"},
    {L"ঃ কোলন", ":", "#fc620b"},
};

// Define an array of Bangla Numeral Letters (সংখ্যা) for the keyboard layout
struct KeyboardLayout keyboardLayoutBanglaNumeralLetters[] = {
    {L"০", "0", "#fc620b"},
    {L"১", "1", "#fc620b"},
    {L"২", "2", "#fc620b"},
    {L"৩", "3", "#fc620b"},
    {L"৪", "4", "#fc620b"},
    {L"৫", "5", "#fc620b"},
    {L"৬", "6", "#fc620b"},
    {L"৭", "7", "#fc620b"},
    {L"৮", "8", "#fc620b"},
    {L"৯", "9", "#fc620b"},
};


// Main function to draw the text and handle the keyboard layout
void drawKeyboardLayoutConsonants(HWND hwnd, HDC hdc) {
    COLORREF primaryTextColor = HexToRGB("#070564"); // Convert Hex to RGB color

    // Load Custom Font
    LPCWSTR customBanglaFont = L"./Geetanjali Academic/Geetanjali Academic.otf";
    AddFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    
    // Create a font that supports Bangla
    HFONT hFont = CreateFontW(
        40,                     // Height of font
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
        L"Geetanjali Academic"  // Font name
    );
    // Select the font into the DC
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);


    RECT rect = {10, 30, 45, 65};  // Define initial rectangle
    
    // Set up the brush and pen for drawing the rounded rectangles
    HBRUSH hBrush = CreateSolidBrush( HexToRGB("#ebab00") ); // Box Background color: #EBAB00 in RGB
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

        SetBkMode(hdc, TRANSPARENT); // Set Bangla text background to transparent

        SetTextColor(hdc, primaryTextColor ); // Set the Text color
        // Draw the Bangla character in the rectangle with word wrapping and centered vertically and horizontally
        DrawTextW(hdc, keyboardLayoutConsonants[i].banglaChar, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

        // Extract the HEX color code from the struct and Convert Hex to RGB color for the corresponding key
        SetTextColor(hdc, HexToRGB(keyboardLayoutConsonants[i].color) ); // Set the text color
        // Adjust the rectangle to draw the corresponding Latin character to the right of the Bangla text
        RECT khRect = {rect.right + 5, rect.top, rect.right + 70, rect.bottom}; // Shifted to the right
        DrawText(hdc, keyboardLayoutConsonants[i].key, -1, &khRect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
        
        // SetTextColor(hdc, primaryTextColor ); // Restore the original PrimaryTextColor And Set the Text color


        // Move the rectangle down by 37 pixels
        rect.top += 37;
        rect.bottom += 37;

        // After every 10 rectangles, move to the next column
        if ((i + 1) % 10 == 0) {
            rect.top = 30;     // Reset top position
            rect.bottom = 65;  // Reset bottom position
            rect.left += 100;  // Shift to the right by 100 pixels (accounting for added Latin characters)
            rect.right += 100; // Shift to the right by 100 pixels
        }
    }
    
    // Cleanup: Free memory and remove the font
    RemoveFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    
    // Clean up GDI objects
    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPenTransparent);
}

// Main function to draw the text and handle the keyboard layout
void drawKeyboardLayoutVowels(HWND hwnd, HDC hdc) {
    COLORREF primaryTextColor = HexToRGB("#070564"); // Convert Hex to RGB color

    // Load Custom Font
    LPCWSTR customBanglaFont = L"./Geetanjali Academic/Geetanjali Academic.otf";
    
    AddFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    
    // Create a font that supports Bangla
    HFONT hFont = CreateFontW(
        40,                     // Height of font
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
        L"Geetanjali Academic"  // Font name
    );
    // Select the font into the DC
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);


    RECT rect = {10, 30, 100, 65};  // Define initial rectangle
    
    // Move the rectangle 400 units to the right
    int offset = 400;
    rect.left += offset;
    rect.right += offset;


    // Set up the brush and pen for drawing the rounded rectangles
    HBRUSH hBrush = CreateSolidBrush( HexToRGB("#f5dd92") ); // Box Background color: #F5DD92 in RGB
    HPEN hPenTransparent = CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // Transparent pen (no border)
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPenTransparent);

    // Loop for drawing the characters in the layout
    for (int i = 0; i < sizeof(keyboardLayoutVowels) / sizeof(keyboardLayoutVowels[0]); ++i) {
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

        SetBkMode(hdc, TRANSPARENT); // Set Bangla text background to transparent

        SetTextColor(hdc, primaryTextColor ); // Set the Text color
        // Draw the Bangla character in the rectangle with word wrapping and centered vertically and horizontally
        DrawTextW(hdc, keyboardLayoutVowels[i].banglaChar, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

        // Extract the HEX color code from the struct and Convert Hex to RGB color for the corresponding key
        SetTextColor(hdc, HexToRGB(keyboardLayoutVowels[i].color) ); // Set the text color
        // Adjust the rectangle to draw the corresponding Latin character to the right of the Bangla text
        RECT khRect = {rect.right + 5, rect.top, rect.right + 70, rect.bottom}; // Shifted to the right
        DrawText(hdc, keyboardLayoutVowels[i].key, -1, &khRect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
        
        // SetTextColor(hdc, primaryTextColor ); // Restore the original PrimaryTextColor And Set the Text color


        // Move the rectangle down by 37 pixels
        rect.top += 37;
        rect.bottom += 37;

        // After every 10 rectangles, move to the next column
        if ((i + 1) % 10 == 0) {
            rect.top = 30;     // Reset top position
            rect.bottom = 65;  // Reset bottom position
            rect.left += 140;  // Shift to the right by 140 pixels (accounting for added Latin characters)
            rect.right += 140; // Shift to the right by 140 pixels
        }
    }
    
    // Cleanup: Free memory and remove the font
    RemoveFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);

    // Clean up GDI objects
    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPenTransparent);
}

// Main function to draw the text and handle the keyboard layout
void drawKeyboardLayoutBanglaCharacterSigns(HWND hwnd, HDC hdc) {
    COLORREF primaryTextColor = HexToRGB("#070564"); // Convert Hex to RGB color

    // Load Custom Font
    LPCWSTR customBanglaFont = L"./Geetanjali Academic/Geetanjali Academic.otf";
    
    AddFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    
    // Create a font that supports Bangla
    HFONT hFont = CreateFontW(
        35,                     // Height of font
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
        L"Geetanjali Academic"  // Font name
    );
    // Select the font into the DC
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);


    RECT rect = {10, 30, 100, 65};  // Define initial rectangle
    
    // Move the rectangle units to the right and top
    int offsetY = 37;
    int offsetX = 540;
    rect.top += offsetY;
    rect.bottom += offsetY;
    rect.left += offsetX;
    rect.right += offsetX;


    // Set up the brush and pen for drawing the rounded rectangles
    HBRUSH hBrush = CreateSolidBrush( HexToRGB("#ebab00") ); // Box Background color: #F5DD92 in RGB
    HPEN hPenTransparent = CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // Transparent pen (no border)
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPenTransparent);

    // Loop for drawing the characters in the layout
    for (int i = 0; i < sizeof(keyboardLayoutBanglaCharacterSigns) / sizeof(keyboardLayoutBanglaCharacterSigns[0]); ++i) {
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

        SetBkMode(hdc, TRANSPARENT); // Set Bangla text background to transparent

        SetTextColor(hdc, primaryTextColor ); // Set the Text color
        // Draw the Bangla character in the rectangle with word wrapping and centered vertically and horizontally
        DrawTextW(hdc, keyboardLayoutBanglaCharacterSigns[i].banglaChar, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

        // Extract the HEX color code from the struct and Convert Hex to RGB color for the corresponding key
        SetTextColor(hdc, HexToRGB(keyboardLayoutBanglaCharacterSigns[i].color) ); // Set the text color
        // Adjust the rectangle to draw the corresponding Latin character to the right of the Bangla text
        RECT khRect = {rect.right + 5, rect.top, rect.right + 70, rect.bottom}; // Shifted to the right
        DrawText(hdc, keyboardLayoutBanglaCharacterSigns[i].key, -1, &khRect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
        
        // SetTextColor(hdc, primaryTextColor ); // Restore the original PrimaryTextColor And Set the Text color


        // Move the rectangle down by 37 pixels
        rect.top += 37;
        rect.bottom += 37;

        // After every 10 rectangles, move to the next column
        if ((i + 1) % 10 == 0) {
            rect.top = 30;     // Reset top position
            rect.bottom = 65;  // Reset bottom position
            rect.left += 140;  // Shift to the right by 140 pixels (accounting for added Latin characters)
            rect.right += 140; // Shift to the right by 140 pixels
        }
    }
    
    // Cleanup: Free memory and remove the font
    RemoveFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);

    // Clean up GDI objects
    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPenTransparent);
}


// Main function to draw the text and handle the keyboard layout
void drawKeyboardLayoutBanglaNumeralLetters(HWND hwnd, HDC hdc) {
    COLORREF primaryTextColor = HexToRGB("#070564"); // Convert Hex to RGB color

    // Load Custom Font
    LPCWSTR customBanglaFont = L"./Geetanjali Academic/Geetanjali Academic.otf";
    
    AddFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
    
    // Create a font that supports Bangla
    HFONT hFont = CreateFontW(
        40,                     // Height of font
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
        L"Geetanjali Academic"  // Font name
    );
    // Select the font into the DC
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);


    RECT rect = {10, 30, 45, 65};  // Define initial rectangle
    
    // Move the rectangle 710 units to the right
    int offset = 710;
    rect.left += offset;
    rect.right += offset;


    // Set up the brush and pen for drawing the rounded rectangles
    HBRUSH hBrush = CreateSolidBrush( HexToRGB("#f5dd92") ); // Box Background color: #F5DD92 in RGB
    HPEN hPenTransparent = CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // Transparent pen (no border)
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPenTransparent);

    // Loop for drawing the characters in the layout
    for (int i = 0; i < sizeof(keyboardLayoutBanglaNumeralLetters) / sizeof(keyboardLayoutBanglaNumeralLetters[0]); ++i) {
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

        SetBkMode(hdc, TRANSPARENT); // Set Bangla text background to transparent

        SetTextColor(hdc, primaryTextColor ); // Set the Text color
        // Draw the Bangla character in the rectangle with word wrapping and centered vertically and horizontally
        DrawTextW(hdc, keyboardLayoutBanglaNumeralLetters[i].banglaChar, -1, &rect, DT_WORDBREAK | DT_VCENTER | DT_CENTER | DT_SINGLELINE);

        // Extract the HEX color code from the struct and Convert Hex to RGB color for the corresponding key
        SetTextColor(hdc, HexToRGB(keyboardLayoutBanglaNumeralLetters[i].color) ); // Set the text color
        // Adjust the rectangle to draw the corresponding Latin character to the right of the Bangla text
        RECT khRect = {rect.right + 5, rect.top, rect.right + 70, rect.bottom}; // Shifted to the right
        DrawText(hdc, keyboardLayoutBanglaNumeralLetters[i].key, -1, &khRect, DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
        
        // SetTextColor(hdc, primaryTextColor ); // Restore the original PrimaryTextColor And Set the Text color


        // Move the rectangle down by 37 pixels
        rect.top += 37;
        rect.bottom += 37;

        // After every 10 rectangles, move to the next column
        if ((i + 1) % 10 == 0) {
            rect.top = 30;     // Reset top position
            rect.bottom = 65;  // Reset bottom position
            rect.left += 140;  // Shift to the right by 140 pixels (accounting for added Latin characters)
            rect.right += 140; // Shift to the right by 140 pixels
        }
    }
    
    // Cleanup: Free memory and remove the font
    RemoveFontResourceExW(customBanglaFont, FR_PRIVATE, 0);
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
    wc.hbrBackground = CreateSolidBrush( HexToRGB("#ebc452") ); // background color #EBC452 in RGB
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // Load the icon (optional)
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON)); // Set window icon
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set default cursor

    // Register the window class
    RegisterClass(&wc);

    // Define window dimensions
    const int width = 980;  // Window width
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
            HPEN hPen = CreatePen(PS_SOLID, 45, HexToRGB("#f0f0f0") );
            HGDIOBJ oldPen = SelectObject(hdc, hPen);
            MoveToEx(hdc, clientRect.left, clientRect.top + 1, NULL);
            LineTo(hdc, clientRect.right, clientRect.top + 1);
            
            // Create 5px pen for left and right borders
            HPEN hPen5px = CreatePen(PS_SOLID, 5, HexToRGB("#f0f0f0") );
            SelectObject(hdc, hPen5px);
            
            // Draw left border
            MoveToEx(hdc, clientRect.left + 2, clientRect.top, NULL);
            LineTo(hdc, clientRect.left + 2, clientRect.bottom);
            
            // Draw right border
            // MoveToEx(hdc, clientRect.right - 2, clientRect.top, NULL);
            // LineTo(hdc, clientRect.right - 2, clientRect.bottom);
            
            // Create 2px pen for bottom border
            HPEN hPen2px = CreatePen(PS_SOLID, 2, HexToRGB("#f0f0f0") );
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
            drawKeyboardLayoutConsonants(hwnd, hdc);  // Consonants (ব্যঞ্জনবর্ণ)
            drawKeyboardLayoutVowels(hwnd, hdc);  // Vowels (স্বরবর্ণ)
            drawKeyboardLayoutBanglaCharacterSigns(hwnd, hdc);  // Bangla Character Signs
            drawKeyboardLayoutBanglaNumeralLetters(hwnd, hdc);  // Bangla Numeral Letters (সংখ্যা)

            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

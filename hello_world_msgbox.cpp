#include <windows.h>
#include <iostream>

// 1. Define a function pointer type that matches the MessageBox signature.
// MessageBoxW (Unicode) signature: int WINAPI MessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT)
typedef int (WINAPI* PfnMessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT);

void CallMessageBoxDynamic() {
    // 2. Load the library containing the function
    HMODULE hUser32 = LoadLibraryA("user32.dll");

    if (hUser32 != NULL) {
        // 3. Get the address of the function
        // Note: We use "MessageBoxW" for wide-character strings
        PfnMessageBoxW pMessageBoxW = (PfnMessageBoxW)GetProcAddress(hUser32, "MessageBoxW");

        if (pMessageBoxW != NULL) {
            // 4. Call the function via the pointer
            pMessageBoxW(NULL, L"Hello from GetProcAddress!", L"Dynamic Call", MB_OK | MB_ICONINFORMATION);
        } else {
            std::cerr << "Could not find MessageBoxW in user32.dll" << std::endl;
        }

        // 5. Free the library when done
        FreeLibrary(hUser32);
    } else {
        std::cerr << "Could not load user32.dll" << std::endl;
    }
}

int main() {
    CallMessageBoxDynamic();
    return 0;
}
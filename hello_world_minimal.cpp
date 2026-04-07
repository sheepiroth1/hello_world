#include <windows.h>

// Forced global pointer - this MUST be relocated by the linker
const char* msg = "Hello from injected PE!";
const char* cap = "TTP Success";

extern "C" __attribute__((used, force_align_arg_pointer))
void MyCustomStart() {
    HMODULE hUser32 = GetModuleHandleA("user32.dll");
    if (!hUser32){
        hUser32 = LoadLibraryA("user32.dll");
    }
    if (hUser32) {
        typedef int (WINAPI *PMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
        PMessageBoxA pMsgBox = (PMessageBoxA)GetProcAddress(hUser32, "MessageBoxA");
        
        if (pMsgBox) {
            // Using the global pointers forces a relocation entry
            pMsgBox(NULL, msg, cap, MB_OK);
        }
    }
    ExitProcess(0);
}
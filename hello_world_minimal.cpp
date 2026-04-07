#include <windows.h>

// This is our Custom Entry Point. 
// No CRT, no argc/argv, just raw execution.
void __stdcall MyCustomStart() {
    // 1. Stack is already set up by the OS when the thread starts.
    // 2. We perform our logic immediately.
    
    // We use the Dynamic Linking method we discussed to stay Position Independent.
    HMODULE hUser32 = GetModuleHandleA("user32.dll");
    if (hUser32) {
        typedef int (WINAPI *PMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
        PMessageBoxA pMsgBox = (PMessageBoxA)GetProcAddress(hUser32, "MessageBoxA");
        
        if (pMsgBox) {
            pMsgBox(NULL, "Hello from Custom Entry!", "TTP Research", MB_OK);
        }
    }

    // 3. CRITICAL: We must call ExitProcess. 
    // Since there is no 'return' path to a CRT caller, 
    // falling off the end of the function would crash the process.
    ExitProcess(0);
}
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// This function runs on its own thread to safely execute commands outside the loader lock
DWORD WINAPI LaunchPayload(LPVOID lpParam) {
    // Spawn Calculator
    WinExec("calc.exe", SW_SHOWNORMAL); 
    
    // Spawn Paint
    WinExec("mspaint.exe", SW_SHOWNORMAL);
    
    return 0;
}

extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            // Create a thread to spawn calc and paint when the DLL is first loaded
            CreateThread(NULL, 0, LaunchPayload, NULL, 0, NULL);
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            // Ignored to avoid spawning hundreds of processes for individual application threads
            break;

        case DLL_PROCESS_DETACH:
            // Create a thread to spawn calc and paint when the DLL is being unloaded/process exits
            CreateThread(NULL, 0, LaunchPayload, NULL, 0, NULL);
            break;
    }
    return TRUE;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <sddl.h> // For ConvertSidToStringSidA

std::string GetCurrentUserAndSID() {
    HANDLE hToken = NULL;
    DWORD dwLength = 0;
    PTOKEN_USER pTokenUser = NULL;
    char userName[256];
    DWORD userNameSize = sizeof(userName);
    std::string result = "Unknown User | SID: Unknown";

    // 1. Get the username
    if (GetUserNameA(userName, &userNameSize)) {
        result = std::string(userName);
    }

    // 2. Open the access token associated with the current process
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        // Get the size required for the token information
        GetTokenInformation(hToken, TokenUser, NULL, 0, &dwLength);
        pTokenUser = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), 0, dwLength);

        if (pTokenUser && GetTokenInformation(hToken, TokenUser, pTokenUser, dwLength, &dwLength)) {
            LPSTR sidString = NULL;
            // 3. Convert the binary SID to a readable string format
            if (ConvertSidToStringSidA(pTokenUser->User.Sid, &sidString)) {
                result += " | SID: " + std::string(sidString);
                LocalFree(sidString);
            }
        }
        if (pTokenUser) HeapAlloc(GetProcessHeap(), 0, (SIZE_T)pTokenUser);
        CloseHandle(hToken);
    }
    return result;
}

int main(int argc, char* argv[]) {

    std::string out_file = "C:\\programdata\\hello_world_default_txt.txt";
    std::ofstream outFile(out_file.c_str(), std::ios::app);
    if (!outFile) {
        std::cerr << "Error: Could not open file: " << out_file << std::endl;
        return 1;
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Write log entry
    // Format: [Wed Mar 11 16:01:48 2026] User: Name | SID: S-1-5-... hello_world
    outFile << "[" << std::put_time(std::localtime(&now_c), "%a %b %d %H:%M:%S %Y") << "] ";
    outFile << "User: " << GetCurrentUserAndSID() << " | ";
    outFile << "hello_world" << std::endl;
    std::cout << "Log written to " << out_file.c_str() << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

int main(int argc, char* argv[]) {
    // 1. Check if the file path argument exists
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <output_file_path>" << std::endl;
        return 1;
    }

    // 2. Open the file in append mode
    std::ofstream outFile(argv[1], std::ios::app);
    if (!outFile) {
        std::cerr << "Error: Could not open or create file: " << argv[1] << std::endl;
        return 1;
    }

    // 3. Get the current system time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 4. Format the time and write to file
    // Use std::put_time for easy formatting (e.g., HH:MM:SS)
    outFile << "[" << std::put_time(std::localtime(&now_c), "%H:%M:%S") << "] ";
    outFile << "hello_world" << std::endl;

    std::cout << "Log written to " << argv[1] << std::endl;

    return 0;
}
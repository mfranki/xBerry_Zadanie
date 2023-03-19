#pragma once

#include <string>
#include <mutex>

/**
 * @brief Loggs messages to the console in thread safe way
 */
class logger {
public:
    /**
     * @brief Loggs messages to the console in thread safe way
     * 
     * @param message 
     */
    static void Log(std::string message);

private:
    static std::mutex loggerMutex;
    static std::chrono::time_point<std::chrono::high_resolution_clock>  programStartTime;
};
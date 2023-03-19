#include "logger.h"
#include <iostream>
#include <chrono>

std::mutex logger::loggerMutex;
std::chrono::time_point<std::chrono::high_resolution_clock>  logger::programStartTime = std::chrono::high_resolution_clock::now();

void logger::Log(std::string message)
{
    std::lock_guard<std::mutex> lock(loggerMutex);

    auto t = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t-programStartTime);
    std::cout<<int_ms.count()<<"ms: "<<message<<std::endl;
}
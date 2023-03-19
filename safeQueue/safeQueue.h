#pragma once

#include <mutex>
#include <stdint.h>
#include <vector>


/**
 * @brief Thread safe queue for communication between threads/processes
 * 
 * @tparam T - type of queued data
 */
template <typename T>
class safeQueue {
public:

    /**
     * @brief Pushes data into the queue
     * 
     * @param [in] message 
     */
    void Push(T message)
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        queueData.push_back(message);
    }

    /**
     * @brief Pops oldest data from the queue
     * 
     * @return T - popped data
     */
    T Pop()
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        T message = queueData.at(0);
        queueData.erase(queueData.begin());
        return message;
    }   

    /**
     * @brief Queue state
     * 
     * @return true if queue is empty
     * @return false if queue is not empty
     */
    bool IsEmpty()
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        return queueData.size() == 0;
    }

private:

    std::mutex queueMutex;
    std::vector<T> queueData;
};
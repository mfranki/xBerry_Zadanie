#pragma once
#include "../sensor/sensor.h"
#include <string>

/**
 * @brief Simulates data consumer thread that subscribes to data produced by some sensor
 */
class subscriber {
public:
    /**
     * @brief Construct a new subscriber object
     * 
     * @param [in] id - subscriber id
     */
    subscriber(uint32_t id);

    /**
     * @brief Get the Queue pointer
     * 
     * @return safeQueue<sensorMessage>* queue for data reception
     */
    safeQueue<sensorMessage>* GetQueue();

private:
    safeQueue<sensorMessage> queue;
    uint32_t id;

    /**
     * @brief Checks if any data arrived through queue and prints it
     */
    void Task();
};
#pragma once

#include "../safeQueue/safeQueue.h"
#include <stdint.h>
#include <chrono>

struct sensorMessage {
    uint32_t sensorId;
    uint64_t messageId;
    std::string value;
};

/**
 * @brief Simulates working sensor that reports some data to the queue
 */
class sensor {
public:
    /**
     * @brief Construct a new sensor object
     * 
     * @param [in] period - sensor data measurement period in [ms]
     * @param [in] sensorId 
     */
    sensor(std::chrono::milliseconds period, uint32_t sensorId);

    /**
     * @brief Get the Queue object pointer
     * 
     * @return safeQueue<sensorMessage>* 
     */
    safeQueue<sensorMessage>* GetQueue();

    /**
     * @brief Get sensor Id
     * 
     * @return uint32_t 
     */
    uint32_t GetId();

protected:
    uint32_t sensorId;
    safeQueue<sensorMessage> queue;

    /**
     * @brief Reads data from sensor, packs it into @ref sensorMessage and pushes it into the queue
     */
    virtual void ReadData() = 0;

private:

    std::chrono::milliseconds period;
    
    /**
     * @brief performs sensor read every @ref period ms
     * 
     */
    void Process();
};
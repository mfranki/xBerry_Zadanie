#pragma once

#include <vector>
#include <array>
#include <stdint.h>
#include <chrono>
#include <map>
#include "../sensor/sensor.h"

#define MAIN_NODE_CYCLIC_BUFFER_SIZE (100U)

/**
 * @brief Cyclic buffer
 * 
 * @tparam T - type of data stored in buffer
 * @tparam bufferSize - max number of elements in buffer
 */
template <typename T, uint32_t bufferSize>
class cyclicBuffer {
public:
    /**
     * @brief Construct a new cyclic Buffer object
     */
    cyclicBuffer() 
        : buffer({0}), readIndex(0), writeIndex(0), empty(true)
    {}

    /**
     * @brief Pushes data into the buffer
     * 
     * @param [in] element 
     */
    void Push(T element)
    {
        buffer.at(writeIndex) = element;
        if((readIndex == writeIndex) && !empty) {
            readIndex = (readIndex+1)%bufferSize;
        }
        writeIndex = (writeIndex+1)%bufferSize;
        empty = false;
    }

    /**
     * @brief Pops oldest data from the buffer
     * 
     * @return T - Oldest data from the buffer
     */
    T Pop()
    {
        if(!empty) {
            T element = buffer.at(readIndex);
            readIndex = (readIndex+1)%bufferSize;
            if(readIndex == writeIndex) {
                empty = true;
            }
            return element;
        }
        T element;
        return element;
    }

    /**
     * @brief Buffer state
     * 
     * @return true if buffer is empty
     * @return false if buffer is not empty
     */
    bool Empty()
    {
        return empty;
    }

private:
    std::array<T, bufferSize> buffer; 
    uint32_t readIndex;
    uint32_t writeIndex;
    bool empty;
};


/**
 * @brief Data broker node, collects data from sensors through the queues and sends data to the subscribers throught queues
 */
class mainNode {
public:
    /**
     * @brief Get the Instance of mainNode object (singleton)
     * 
     * @return mainNode& reference to mainNode object
     */
    static mainNode& GetInstance();

    /**
     * @brief Reads data from the queues and sends it to subscribers every @ref reportPeriodMs ms
     */
    void Process();

    /**
     * @brief Connects sensor queue to mainNode
     * 
     * @param [in] sens - sensor object reference
     */
    void AddSensor(sensor& sens);

    /**
     * @brief connects data consumer queue to mainNode and subscribes it to given sensor
     * 
     * @param [in] queue 
     * @param [in] sensorId 
     */
    void Subscribe(safeQueue<sensorMessage>* queue, uint32_t sensorId);

private:

    static const double reportPeriodMs;

    std::chrono::high_resolution_clock::time_point lastSubscriberReport;
    std::vector<safeQueue<sensorMessage>*> inputQueues;
    cyclicBuffer<sensorMessage,MAIN_NODE_CYCLIC_BUFFER_SIZE> cycBuf;  
    std::map<uint32_t, std::vector<safeQueue<sensorMessage>*>> subscriberMap;
  
    /**
     * @brief Construct a new main Node object, private due to singleton pattern
     * 
     */
    mainNode();
};
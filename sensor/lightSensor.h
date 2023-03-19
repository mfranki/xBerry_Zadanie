#pragma once

#include "sensor.h"
#include <utility>



class lightSensor : public sensor {
public:
    /**
     * @brief Construct a new light Sensor object
     * 
     * @param period - sensor data measurement period in [ms]
     * @param sensorId 
     */
    lightSensor(std::chrono::milliseconds period, uint32_t sensorId)
        : sensor(period,sensorId) 
    {
        messageCount = 0;
    }
    
protected:
    /**
     * @brief Reads data from sensor, packs it into @ref sensorMessage and pushes it into the queue
     */
    void ReadData()
    {
        sensorMessage msg;
        msg.sensorId = this->sensorId;
        msg.value = "Light sensor data";
        msg.messageId = this->messageCount++;

        this->queue.Push(msg);
    }

private:
    uint64_t messageCount;

};
#include "sensor.h"
#include <thread>
#include <iostream>

#define MIN_PERIOD ((std::chrono::milliseconds)10U)
#define MAX_PERIOD ((std::chrono::milliseconds)10000U)

sensor::sensor(std::chrono::milliseconds period, uint32_t sensorId)
{
    if(period < MIN_PERIOD) {
        this->period = MIN_PERIOD;    
    } else if(period > MAX_PERIOD) {
        this->period = MAX_PERIOD;
    } else {
        this->period = period;
    }
    this->sensorId = sensorId;

    std::thread sensorThread(&sensor::Process, this);
    sensorThread.detach();
}

safeQueue<sensorMessage>* sensor::GetQueue()
{
    return &queue;
}

uint32_t sensor::GetId()
{
    return sensorId;
}

void sensor::Process()
{
    while(1) {
        ReadData();
        std::this_thread::sleep_for(this->period);
    }
}
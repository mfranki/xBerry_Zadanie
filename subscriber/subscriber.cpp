#include "subscriber.h"
#include "../logger/logger.h"
#include <iostream>
#include <thread>
#include <sstream>

#define SUBSCRIBER_REFRESH_PERIOD_MS (200U)

subscriber::subscriber(uint32_t id)
{
    this->id = id;
    std::thread sensorThread(&subscriber::Task, this);
    sensorThread.detach();
}

safeQueue<sensorMessage>* subscriber::GetQueue()
{
    return &queue;
}

void subscriber::Task()
{
    while(1) {
        while(!queue.IsEmpty()) {
            sensorMessage msg = queue.Pop();
            std::stringstream ss;
            ss <<"Subscriber("<<id<<") received message "<<msg.messageId<<": " << msg.value << " from sensor(" << msg.sensorId << ")";
            logger::Log(ss.str());
        }
        std::this_thread::sleep_for((std::chrono::milliseconds)SUBSCRIBER_REFRESH_PERIOD_MS);
    }
}

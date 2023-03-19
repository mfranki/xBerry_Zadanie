#include "mainNode.h"
#include <iostream>

const double mainNode::reportPeriodMs = 1000.0;

mainNode::mainNode()
{
    lastSubscriberReport = std::chrono::high_resolution_clock::now();
}

mainNode& mainNode::GetInstance()
{
    static mainNode instance;
    return instance;
}

void mainNode::Process()
{
    for(uint32_t i=0; i<inputQueues.size(); i++) {
        while(!inputQueues.at(i)->IsEmpty()) {
            cycBuf.Push(inputQueues.at(i)->Pop());
        }
    }

    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    double timeElapsedMs = std::chrono::duration<double, std::milli>(now-lastSubscriberReport).count();
    if(timeElapsedMs > mainNode::reportPeriodMs) {
        lastSubscriberReport = std::chrono::high_resolution_clock::now();
        
        while(!cycBuf.Empty()) {
            sensorMessage msg = cycBuf.Pop();
            for(uint32_t i=0; i<subscriberMap.at(msg.sensorId).size(); i++) {
                subscriberMap.at(msg.sensorId).at(i)->Push(msg);
            }
        }
    } 
}

void mainNode::AddSensor(sensor& sens)
{
    inputQueues.push_back(sens.GetQueue());
    std::vector<safeQueue<sensorMessage>*> subscriberQueues;
    subscriberMap.insert({sens.GetId(),subscriberQueues});
}

void mainNode::Subscribe(safeQueue<sensorMessage>* queue, uint32_t sensorId)
{
    subscriberMap.at(sensorId).push_back(queue);
}

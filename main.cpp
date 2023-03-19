#include <iostream>
#include <stdint.h>
#include "sensor/lightSensor.h"
#include "subscriber/subscriber.h"
#include "mainNode/mainNode.h"

int main()
{
    lightSensor s1 = lightSensor((std::chrono::milliseconds)1000,1);
    lightSensor s2 = lightSensor((std::chrono::milliseconds)2000,2);
    lightSensor s3 = lightSensor((std::chrono::milliseconds)500,3);
    lightSensor s4 = lightSensor((std::chrono::milliseconds)5000,4);

    subscriber sub1 = subscriber(1);
    subscriber sub2 = subscriber(2);
    subscriber sub3 = subscriber(3);

    mainNode& broker = mainNode::GetInstance();

    broker.AddSensor(s1);
    broker.AddSensor(s2);
    broker.AddSensor(s3);
    broker.AddSensor(s4);

    broker.Subscribe(sub1.GetQueue(),3);
    broker.Subscribe(sub1.GetQueue(),1);
    broker.Subscribe(sub2.GetQueue(),2);
    broker.Subscribe(sub2.GetQueue(),3);

    while(1)
    {
        broker.Process();
    }

    return 0;
}
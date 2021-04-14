#include "dds/dds.hpp"
#include "HelloWorld.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    dds::domain::DomainParticipant participant(org::eclipse::cyclonedds::domain::default_id());

    dds::topic::Topic<HelloWorld::Msg> topic(participant, "HelloWorld");
    dds::sub::Subscriber subscriber(participant);
    dds::sub::DataReader<HelloWorld::Msg> reader(subscriber, topic);

    while(true)
    {
        const auto samples = reader.take();
        if(samples.length() > 0)
        {
            for(auto& sample : samples)
            {
                const auto msg = sample.data();
                const auto info = sample.info();

                if(info.valid())
                {
                    std::cout << msg.message() << std::endl;
                    break;
                }
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    return 0;
}


#include "dds/dds.hpp"
#include "HelloWorld.hpp"
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    dds::domain::DomainParticipant participant(org::eclipse::cyclonedds::domain::default_id());

    dds::topic::Topic<HelloWorld::Msg> topic(participant, "HelloWorld");

    dds::pub::Publisher publisher(participant);

    dds::pub::DataWriter<HelloWorld::Msg> writer(publisher, topic);

    HelloWorld::Msg msg("Hello");

    while (writer.publication_matched_status().current_count() == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    writer.write(msg);

    return 0;
}


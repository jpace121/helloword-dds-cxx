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

    dds::core::cond::StatusCondition statusCondition(writer);
    statusCondition.enabled_statuses(dds::core::status::StatusMask::publication_matched());
    statusCondition.handler([&writer](const dds::core::cond::StatusCondition&)
                            {
                                HelloWorld::Msg msg("Hello");
                                writer.write(msg);
                            });

    dds::core::cond::WaitSet waitSet;
    waitSet.attach_condition(statusCondition);

    waitSet.dispatch();


    return 0;
}


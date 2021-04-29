#include "dds/dds.hpp"
#include "HelloWorld.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    dds::domain::DomainParticipant participant(org::eclipse::cyclonedds::domain::default_id());

    dds::topic::Topic<HelloWorld::Msg> topic(participant, "HelloWorld");

    dds::pub::qos::PublisherQos pubQos = participant.default_publisher_qos()
                                        << dds::core::policy::Partition("jpace121");
    dds::pub::Publisher publisher(participant, pubQos);


    dds::pub::qos::DataWriterQos writerQos = publisher.default_datawriter_qos()
        << dds::core::policy::Reliability::Reliable(dds::core::Duration::from_secs(0.5));
    dds::pub::DataWriter<HelloWorld::Msg> writer(publisher, topic, writerQos);

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

#include "dds/dds.hpp"
#include "HelloWorld.hpp"
#include <iostream>
#include <thread>
#include <chrono>

class Subscriber : public dds::sub::DataReaderListener<HelloWorld::Msg>
{
    void on_data_available(dds::sub::DataReader<HelloWorld::Msg>& reader) override
    {
        const auto samples = reader.take();
        //std::cout << samples.length() << std::endl;
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
    }

    // Pass on all of these.
    void on_requested_deadline_missed(dds::sub::DataReader<HelloWorld::Msg>&,
                                      const dds::core::status::RequestedDeadlineMissedStatus& ) override
    {
    }
    void on_requested_incompatible_qos(dds::sub::DataReader<HelloWorld::Msg>& reader,
                                       const dds::core::status::RequestedIncompatibleQosStatus & status) override
    {
    }
    void on_sample_rejected(dds::sub::DataReader<HelloWorld::Msg>& reader,
                            const dds::core::status::SampleRejectedStatus & status) override
    {
    }
    void on_liveliness_changed(dds::sub::DataReader<HelloWorld::Msg>& reader,
                               const dds::core::status::LivelinessChangedStatus & status) override
    {
    }
    void on_subscription_matched(dds::sub::DataReader<HelloWorld::Msg>& reader,
                                 const dds::core::status::SubscriptionMatchedStatus & status) override
    {
    }
    void on_sample_lost(dds::sub::DataReader<HelloWorld::Msg>& reader,
                        const dds::core::status::SampleLostStatus & status) override
    {
    }
};

int main(int argc, char *argv[])
{
    dds::domain::DomainParticipant participant(org::eclipse::cyclonedds::domain::default_id());

    dds::topic::Topic<HelloWorld::Msg> topic(participant, "HelloWorld");
    dds::sub::Subscriber subscriber(participant);
    dds::sub::DataReader<HelloWorld::Msg> reader(subscriber, topic);

    reader.listener(new Subscriber, dds::core::status::StatusMask::data_available());

    while(true){}

    return 0;
}


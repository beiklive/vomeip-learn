#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <iomanip>
#include <condition_variable>
#include <thread>
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")

static vsomeip::service_t service_id = 0x1234;
static vsomeip::instance_t service_instance_id = 0x9999;
static vsomeip::instance_t service_method_id = 0x1145;

#define SOMEIP_EVENT_ID_1             0x0333
#define SOMEIP_EVENT_ID_2             0x0334
#define SOMEIP_EVENT_ID_3             0x0335
#define SOMEIP_EVENT_ID_4             0x0336
#define SOMEIP_EVENTGROUP_ID_1        0x01
#define SOMEIP_EVENTGROUP_ID_2        0x02
#define SOMEIP_EVENTGROUP_ID_3        0x03
 

std::shared_ptr<vsomeip::application> app;
std::mutex mutex;
std::condition_variable condition;


void on_state_cbk(vsomeip::state_type_e _state)
{
    if (_state == vsomeip::state_type_e::ST_REGISTERED)
    {
        app->request_service(service_id, service_instance_id);
    }
}

void on_availability_cbk(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    std::cout << "[DJ] Service ["
        << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
        << "] is " << (_is_available ? "available." : "NOT available.")  << std::endl;
    if(_is_available){
        condition.notify_one();
    }
}

void on_message_cbk(const std::shared_ptr<vsomeip::message>& _response)
{
    std::stringstream its_message;
    its_message << ">>>>> CLIENT: received a notification for event ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_service() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_instance() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_method() << "] to Client/Session ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_client() << "/"
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_session()
            << "] = ";
    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    its_message << "(" << std::dec << its_payload->get_length() << ") ";
    for (uint32_t i = 0; i < its_payload->get_length(); ++i)
        its_message << std::hex << std::setw(2) << std::setfill('0')
            << (int) its_payload->get_data()[i] << " ";
    std::cout << its_message.str() << std::endl;
}

void msg_send(){
    std::unique_lock<std::mutex> its_lock(mutex);
    condition.wait(its_lock);
    app->request_event(service_id, service_instance_id, SOMEIP_EVENT_ID_1, {SOMEIP_EVENTGROUP_ID_1}, vsomeip::event_type_e::ET_FIELD);
    app->subscribe(service_id, service_instance_id, SOMEIP_EVENTGROUP_ID_1);
    
}



int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application();
    app->init();
    app->register_availability_handler(service_id, service_instance_id, on_availability_cbk);
    app->request_service(service_id, service_instance_id);
    app->register_message_handler(service_id, service_instance_id, vsomeip::ANY_METHOD, on_message_cbk);

    std::thread sender(msg_send);
    app->start();
    return 0;
}
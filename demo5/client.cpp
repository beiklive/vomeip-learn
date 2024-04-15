#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <iomanip>

#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")

static vsomeip::service_t service_id = 0x1234;
static vsomeip::instance_t service_instance_id = 0x9999;



std::shared_ptr<vsomeip::application> app;


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
    if (service_id == _service && service_instance_id == _instance
        && _is_available)
    {
        
    }
}

void on_message_cbk(const std::shared_ptr<vsomeip::message>& _response)
{
    if (service_id == _response->get_service()
        && service_instance_id == _response->get_instance()
        && vsomeip::message_type_e::MT_RESPONSE
        == _response->get_message_type()
        && vsomeip::return_code_e::E_OK == _response->get_return_code())
    {
        // Get the payload and print it
        std::shared_ptr<vsomeip::payload> pl = _response->get_payload();
        std::string resp = std::string(
            reinterpret_cast<const char*>(pl->get_data()), 0,
            pl->get_length());
        LOG_INF("Received: %s", resp.c_str());
    }
}



int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application();
    app->init();
   app->register_availability_handler(service_id, service_instance_id, on_availability_cbk);

    app->request_service(service_id, service_instance_id);

    app->start();
    return 0;
}
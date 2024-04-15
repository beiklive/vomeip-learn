#include <iostream>
#include <iomanip>
#include <vsomeip/vsomeip.hpp>
 
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")

std::shared_ptr<vsomeip::application> app;
 
static vsomeip::service_t service_id = 0x1234;
static vsomeip::instance_t service_instance_id = 0x9999;

// 定义消息处理函数
void on_message_cbk(const std::shared_ptr<vsomeip::message> &_request) {
    // 获取从客户端拿到的payload
    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    // 获取 payload 内容
    auto str = reinterpret_cast<const char*>(its_payload->get_data());
    std::cout << "[message Received][Client/Session:"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_session()
        << "] " << str << std::endl;
}

void on_state_cbk(vsomeip::state_type_e _state)
{
    LOG_INF("[DJ] cur state: %s",std::to_string(int(_state)).c_str());
    if(_state == vsomeip::state_type_e::ST_REGISTERED)
    {        // we are registered at the runtime and can offer our service
        LOG_INF("[DJ] OFFER service");
    }
}

int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application();
    app->init();

    app->register_message_handler(service_id, service_instance_id, vsomeip::ANY_METHOD, on_message_cbk);
    app->register_state_handler(on_state_cbk);
    app->offer_service(service_id, service_instance_id);

    app->start();
    return 0;
}
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vsomeip/vsomeip.hpp>
 
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")

std::shared_ptr<vsomeip::application> app;
 
static vsomeip::service_t service_id = 0x1234;
static vsomeip::instance_t service_instance_id = 0x9999;
static vsomeip::instance_t service_method_id = 0x1145;

// 将字符串转换为大写
std::string toUpper(std::string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            // 如果字符是小写字母，则转换为大写字母
            str[i] = str[i] - 'a' + 'A';
        }
    }
    return str;
}


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
        // 根据请求创建一个响应，内部会将请求中的各种ID以及其他通信数据设置到响应中
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    // 创建一个payload
    std::shared_ptr<vsomeip::payload> rsp_payload = vsomeip::runtime::get()->create_payload();
 
    std::stringstream  rsp_ss;
    rsp_ss << "[toUpper][" << toUpper(str) << "]" << " ";
    std::string rsp_str(rsp_ss.str());
    // 创建 payload data并设置内容
    std::vector<vsomeip::byte_t> rsp_payload_data(std::begin(rsp_str), std::end(rsp_str));
    // 填充数据
    rsp_payload->set_data(rsp_payload_data);
    its_response->set_payload(rsp_payload);
    // 发送响应
    app->send(its_response);
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
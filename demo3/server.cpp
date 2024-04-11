#include <iostream>
#include <iomanip>
#include <sstream>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID  0x1234
#define SOMEIP_INSTANCE_ID 0x9999
#define SOMEIP_UPPER_METHOD_ID   0x1145
 
std::shared_ptr<vsomeip::application> app;
 
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
 
void on_message_cbk(const std::shared_ptr<vsomeip::message> &_request)
{
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
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstApp");
    app->init();
    app->offer_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);
    // 注册消息处理回调函数
    app->register_message_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_UPPER_METHOD_ID, on_message_cbk);
    app->start();
    return 0;
}
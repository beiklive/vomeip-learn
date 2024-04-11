#include <iomanip>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID  0x1234
#define SOMEIP_INSTANCE_ID 0x9999
#define SOMEIP_UPPER_METHOD_ID   0x1145
 
 
std::shared_ptr<vsomeip::application> app;
std::mutex mutex;
std::condition_variable condition;
 
 
void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout << "Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is " << (_is_available ? "available." : "NOT available.")  << std::endl;
    // 检测到服务可用后，通知子线程发送消息
    if(_is_available){
        condition.notify_one();
    }
}
 
// 处理接收到的消息
void on_message_cbk(const std::shared_ptr<vsomeip::message> &_response)
{
    // 获取从客户端拿到的payload
    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    // 获取 payload 内容
    auto str = reinterpret_cast<const char*>(its_payload->get_data());
 
    std::cout << "[message Received][Client/Session:"
    << std::setw(4) << std::setfill('0') << std::hex << _response->get_client() << "/"
    << std::setw(4) << std::setfill('0') << std::hex << _response->get_session()
    << "] " << str << std::endl;
}
 
 
void msg_send(){
    std::unique_lock<std::mutex> its_lock(mutex);
    // 阻塞此函数，等待服务可用
    condition.wait(its_lock);
 
    // 创建请求，需要指定请求的服务以及需要远程调用的方法
    std::shared_ptr< vsomeip::message > request = vsomeip::runtime::get()->create_request();
    request->set_service(SOMEIP_SERVICE_ID);
    request->set_instance(SOMEIP_INSTANCE_ID);
    request->set_method(SOMEIP_UPPER_METHOD_ID);
 
    // 创建 payload 以及payload data
    std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
    std::string str("this is Client");
    std::vector<vsomeip::byte_t> payload_data(std::begin(str), std::end(str));
    its_payload->set_data(payload_data);
    request->set_payload(its_payload);
    // 发送请求
    app->send(request);
}
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstClient");
    app->init();
    app->register_availability_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, on_availability);
    app->request_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);
    // 注册消息处理回调函数，客户端的 method id必须与请求的远端method id一致
    app->register_message_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_UPPER_METHOD_ID, on_message_cbk);
     
    // 在子线程中运行消息发送函数， 因为发送消息需要 start 内部的事件循环，而 start 函数时阻塞性质的，必须在子线程中等待事件循环
    std::thread sender(msg_send);
    app->start();
 
    return 0;
}
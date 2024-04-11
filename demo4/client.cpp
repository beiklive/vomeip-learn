#include <iomanip>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID           0x1234
#define SOMEIP_INSTANCE_ID          0x9999
#define SOMEIP_UPPER_METHOD_ID      0x1145
 
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
void on_event_cbk(const std::shared_ptr<vsomeip::message> &_response)
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
    // 需要确认服务可用之后才能订阅服务，所以还是需要阻塞一下等待可用性
    condition.wait(its_lock);
    // 绑定事件组和事件，向服务端发送订阅特定事件的请求
    // 这里只请求了事件1，没有请求事件2
    app->request_event(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_1, {SOMEIP_EVENTGROUP_ID_1}, vsomeip::event_type_e::ET_FIELD);
    // 告知服务端，已经准备好开始接收特定事件组的事件通知
    app->subscribe(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENTGROUP_ID_1);
}
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstClient");
    app->init();

    app->register_availability_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, on_availability);
    app->request_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);

    // 注册消息处理回调函数，客户端的 method id必须与请求的远端method id一致
    app->register_message_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, vsomeip::ANY_METHOD, on_event_cbk);
     
    // 在子线程中运行消息发送函数， 因为发送消息需要 start 内部的事件循环，而 start 函数时阻塞性质的，必须在子线程中等待事件循环
    std::thread sender(msg_send);
    app->start();
 
    return 0;
}
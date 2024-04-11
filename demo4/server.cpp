#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID           0x1234
#define SOMEIP_INSTANCE_ID          0x9999
#define SOMEIP_UPPER_METHOD_ID      0x1145
 
#define SOMEIP_EVENT_ID_1             0x0333
#define SOMEIP_EVENT_ID_2             0x0334
#define SOMEIP_EVENT_ID_3             0x0335
#define SOMEIP_EVENTGROUP_ID_1        0x01
#define SOMEIP_EVENTGROUP_ID_2        0x02

std::shared_ptr<vsomeip::application> app;

// 用来更新数据通知客户端
void event_publish(const int &data){
    // 创建事件payload对象并设置数据
    std::shared_ptr<vsomeip::payload> its_payload = vsomeip::runtime::get()->create_payload();
    
    // 向订阅了事件的客户端发送通知
    // 这里我广播了三组事件，前两组事件属于同一个事件组，第三个事件属于另一个事件组
    const vsomeip::byte_t its_data1[] = { data };
    const vsomeip::byte_t its_data2[] = { 0xf - data };
    its_payload->set_data(its_data1, sizeof(its_data1));
    app->notify(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_1, its_payload);
    its_payload->set_data(its_data2, sizeof(its_data2));
    app->notify(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_2, its_payload);
    app->notify(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_3, its_payload);
}

// 自动更新并发送数据
void auto_publish()
{
    std::cout << ">>> sleep 10s wait for client startup" << std::endl;
    // 向事件组中绑定事件ID，并广播自己提供的事件服务，这里我提供了三个事件服务， 第三个服务属于另一个事件组
    app->offer_event(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_1, {SOMEIP_EVENTGROUP_ID_1}, vsomeip::event_type_e::ET_FIELD);
    app->offer_event(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_2, {SOMEIP_EVENTGROUP_ID_1}, vsomeip::event_type_e::ET_FIELD);
    app->offer_event(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_EVENT_ID_3, {SOMEIP_EVENTGROUP_ID_2}, vsomeip::event_type_e::ET_FIELD);
    
    std::this_thread::sleep_for(std::chrono::seconds(10));// 等待客户端启动和订阅上面的事件(这里偷懒没用条件变量和锁)

    // 每隔一秒对订阅了事件的客户端进行广播
    std::cout << ">>> start send" << std::endl;
    for(int i = 0; i<=4;i++)
    {
        event_publish(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "==== send [" << std::hex << i << "]" << std::endl;
    }   
    std::cout << ">>> finish send" << std::endl;
}
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstApp");
    app->init();
    app->offer_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);
    
    // 与demo2的客户端同理，需要在start之后进行广播操作，所以需要子线程
    std::thread auuuto(auto_publish);
    app->start();
    return 0;
}
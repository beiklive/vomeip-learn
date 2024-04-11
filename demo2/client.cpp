
#include <iomanip>
#include <iostream>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID  0x1234
#define SOMEIP_INSTANCE_ID 0x9999
 
std::shared_ptr<vsomeip::application> app;
 
void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout << "Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is " << (_is_available ? "available." : "NOT available.")  << std::endl;
}
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstClient");
    app->init();
    // 该函数会注册一个可用性处理器，在指定服务的可用性状态变化时会调用 on_availability 函数
   app->register_availability_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, on_availability);
    app->request_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);
    app->start();
 
    return 0;
}
#include <iostream>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID  0x1234                   // 指定服务标识，每个服务都应该有一个唯一的标识ID，
#define SOMEIP_INSTANCE_ID 0x9999                   // 服务的实例标识，区分同一个服务的不同实例
 
std::shared_ptr<vsomeip::application> app;
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstApp");
    app->init();
    app->offer_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);   // 使用 offer_service 函数会触发应用程序提供服务实例
   app->start();
    return 0;
}
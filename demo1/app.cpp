#include <iostream>
#include <vsomeip/vsomeip.hpp>
 
std::shared_ptr<vsomeip::application> app;
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstApp");
    app->init();
    app->start();
    return 0;
}
#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <iomanip>
#include <condition_variable>
#include <thread>
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")

static vsomeip::service_t service_id = 0x1234;
static vsomeip::instance_t service_instance_id = 0x9999;
static vsomeip::instance_t service_method_id = 0x1145;



std::shared_ptr<vsomeip::application> app;
std::mutex mutex;
std::condition_variable condition;


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
    if(_is_available){
        condition.notify_one();
    }
}

void on_message_cbk(const std::shared_ptr<vsomeip::message>& _response)
{
// 获取从客户端拿到的payload
    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    // 获取 payload 内容
    std::string str;
    str.append(reinterpret_cast<const char*>(_response->get_payload()->get_data()),0, _response->get_payload()->get_length());
 
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
    request->set_service(service_id);
    request->set_instance(service_instance_id);
    request->set_method(service_method_id);
 
    // 创建 payload 以及payload data
    std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
    std::string str("this is Client");
    std::vector<vsomeip::byte_t> payload_data(std::begin(str), std::end(str));
    its_payload->set_data(payload_data);
    request->set_payload(its_payload);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // 发送请求
        app->send(request);
    }
    
}



int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application();
    app->init();
   app->register_availability_handler(service_id, service_instance_id, on_availability_cbk);
    app->request_service(service_id, service_instance_id);
    app->register_message_handler(service_id, service_instance_id, service_method_id, on_message_cbk);

    std::thread sender(msg_send);
    app->start();
    return 0;
}
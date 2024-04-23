#include <thread>
#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "v1/commonapi/examples/HelloworldStubDefault.hpp"

class HelloWorldStubImpl : public v1::commonapi::examples::HelloworldStubDefault{
public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();
    virtual void incCounter();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);
private:
    int cnt;

};
HelloWorldStubImpl::HelloWorldStubImpl() {cnt = 0;}
HelloWorldStubImpl::~HelloWorldStubImpl() {}
void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) {

    std::stringstream messageStream;

    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};
void HelloWorldStubImpl::incCounter() {
    cnt++;
    setXAttribute((int32_t)cnt);
    std::cout <<  "Set X value = " << cnt << std::endl;
    std::string s_string = getA1Attribute().getS();
    std::cout<<" Rev S val = " << s_string << std::endl;
}

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "E01S");
    CommonAPI::Runtime::setProperty("LogApplication", "E01S");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Helloworld";
    std::string connection = "service-sample";

    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService, connection);

    while (!successfullyRegistered) {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService, connection);
    }

    std::cout << "Successfully Registered Service!" << std::endl;

    v1::commonapi::examples::CommonTypes::a1Struct valueStruct;
    valueStruct.setS("abc");
    v1::commonapi::examples::CommonTypes::a2Struct a2Struct = valueStruct.getA2();
    a2Struct.setA(123);
    a2Struct.setB(true);
    a2Struct.setD(1234);
    valueStruct.setA2(a2Struct);

    int i = 0;
    while (true) 
    {
        i++;
        myService->incCounter();

        if(i==2)
        {
            myService->setA1Attribute(valueStruct);
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
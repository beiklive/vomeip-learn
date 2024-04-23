// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>
#include <thread>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <CommonAPI/CommonAPI.hpp>
#include <CommonAPI/AttributeCacheExtension.hpp>
#include "v1/commonapi/examples/HelloworldProxy.hpp"

using namespace v1::commonapi::examples;

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "E01C");
    CommonAPI::Runtime::setProperty("LogApplication", "E01C");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.Helloworld";
    std::string connection = "client-sample";

    // auto myProxy = runtime->buildProxyWithDefaultAttributeExtension<HelloworldProxy, CommonAPI::Extensions::AttributeCacheExtension>(domain, instance, connection);
    std::shared_ptr<HelloworldProxy<>> myProxy = runtime->buildProxy < HelloworldProxy > (domain, instance, connection);
    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
    {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
        

    std::cout << "Available..." << std::endl;
    std::cout << "start value test ..." << std::endl;

    // Subscribe for receiving values
    myProxy->getXAttribute().getChangedEvent().subscribe([&](const int32_t& val)
    {
        std::cout << "Received change message: " << val << std::endl;
    });


    myProxy->getA1Attribute().getChangedEvent().subscribe([&](const CommonTypes::a1Struct& val)
    {
        std::cout << "Received change message for A1" << std::endl;

        std::cout << "a1Struct.s = " << val.getS()<<std::endl;

        std::cout << "a1Struct.a1.a2.a = " << val.getA2().getA()<<std::endl;
        std::cout << "a1Struct.a1.a2.b = " << val.getA2().getB()<<std::endl;
        std::cout << "a1Struct.a1.a2.d = " << val.getA2().getD()<<std::endl;
    });


    std::cout << "start Method test ..." << std::endl;


    const std::string name = "World";
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    CommonTypes::a1Struct valueStruct;


    myProxy->sayHello(name, callStatus, returnMessage, &info);
    if (callStatus != CommonAPI::CallStatus::SUCCESS) {
        std::cerr << "Remote call failed!\n";
        return -1;
    }
    info.timeout_ = info.timeout_ + 1000;

    std::cout << "Got message: '" << returnMessage << "'\n";
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1000000));
    }

    return 0;
}

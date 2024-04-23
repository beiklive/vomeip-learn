此 demo 参考 
https://github.com/COVESA/capicxx-core-tools/wiki

https://blog.csdn.net/qq_42695024/article/details/135304699

## 什么是CommonAPI
CommonAPI 是一种用于实现分布式服务的通用框架，旨在促使不同模块或组件之间的通信更加容易。它是一种跨平台的通信框架，适用于嵌入式系统、汽车电子等领域。

我们可以将 CommonAPI 视为一种接口规范，CommonAPI 实际上包括两个层面的概念：

1、CommonAPI 接口规范（IDL）： CommonAPI 提供了一种接口定义语言（IDL），用于描述服务接口的结构，包括服务的方法、属性、事件等。这种 IDL 类似于 FIDL（Franca Interface Definition Language），用于规范化描述接口。

2、CommonAPI 运行时环境： CommonAPI 还提供了一个运行时环境，负责实际的服务注册、发现、通信等功能。这个运行时环境是 CommonAPI 框架的核心部分，确保不同的组件可以协同工作，实现松耦合的通信。

## SomeIP/CommonAPI

我们可以这样理解：
CommonAPI是一套接口规范，通.fidl文件定义接口，使用CommonAPI Core Runtime代码生成工具来解析fidl文件获得接口文件即(.cpp和.hpp)

someIP是一个利用Socket（套接字）机制的协议库。

我们通过解析fidl文件获得接口文件

，并没有IPC通讯功能，为了实现其IPC通讯，引入了fdepl部署文件。

fdepl根据.fidl中的接口，设置每个接口的网络服务ID、网络地址、端口号、通信协议等。然后通过CommonAPI SomeIP Runtime代码生成工具解析fdepl文件，生成可以通过someIP协议通信的接口文件(.cpp和.hpp)。

即：

fidl接口配置文件 ---》commonapi ---》   接口 hpp

 fdepl someip配置文件 + fidl接口配置文件 ---》 commonapi ---》 通信接口 cpp

## 关于  fidl 和 fdepl
Franca IDL
CommonAPI其使用的接口语言为：Franca IDL 语言规范。

Franca 是一个用于定义和转换软件接口的框架。它用于集成来自不同供应商的基于各种运行时框架、平台和IPC（进程间通信）机制构建的软件组件。

fidl 文件和 fdepl 文件是在 CommonAPI 框架中使用的两种文件类型，用于描述服务接口和部署规范。

FIDL 文件（通常以 ".fidl" 后缀结尾）：
* FIDL 文件定义了服务接口的结构和行为。
* 它包含接口的方法、属性、数据结构等的定义。
* FIDL 文件描述了服务接口的功能和使用方式，以及与之相关的数据类型。
* 开发人员可以根据 FIDL 文件生成特定编程语言的接口代码，用于实现服务和客户端。

FDEPL 文件（通常以 ".fdepl" 后缀结尾）：
* FDEPL 文件定义了服务接口在特定部署环境中的部署规范。
* 它包含了服务接口的部署信息，例如服务ID、方法ID、属性ID等。
* FDEPL 文件描述了服务接口在特定网络协议或通讯协议下的部署细节，以便于服务的注册、发现和通信。
* FDEPL 文件通常用于在特定的服务平台或框架中配置和部署服务接口，以确保服务能够在网络中正确地运行和交互。

## 环境安装
在 demo 中已经安装过 boost库、vsomeip库， 接下来要安装的是 commonapi 相关的库
### dlt-daemon
```bash
git clone https://github.com/COVESA/dlt-daemon.git
cd dlt-daemon
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

### CommonAPI Core Runtime
```bash
git clone https://github.com/COVESA/capicxx-core-runtime.git
cd capicxx-core-runtime
mkdir build
cd build
cmake ..
make -j32
make install
```

### CommonAPI SomeIP Runtime
```bash
git clone https://github.com/COVESA/capicxx-someip-runtime.git
cd capicxx-someip-runtime
mkdir build
cd build
cmake -DUSE_INSTALLED_COMMONAPI=ON ..
make -j32
sudo make install
```

### Runtime代码生成工具
`CommonAPI Core Runtime代码生成工具`和 `CommonAPI SomeIP Runtime代码生成工具`已经被我下载到了 `gen` 目录下, 可以直接使用

## fidl配置文件
文件位于 `config` 目录下

`HelloWorld.fidl`

```rust
package commonapi.examples
 
interface Helloworld {
    version { major 1 minor 0 }
 
    attribute Int32 x
    attribute CommonTypes.a1Struct a1
    method sayHello {
        in {
            String name
        }
        out {
            String message
        }
    }
}
 
typeCollection CommonTypes {
    version { major 1 minor 0 }
     
    struct a1Struct {
        String s
        a2Struct a2
    }
 
    struct a2Struct {
        Int32 a
        Boolean b
        Double d
    }
}
```

fidl 文件用于定义服务接口的结构和行为

这段代码是一个简单的示例，展示了一个名为"commonapi"的包中的接口和类型集合的定义。让我逐一解释一下：

1. **接口 Helloworld**:

   - **version**: 这个接口的版本号，由主版本号（major）和次版本号（minor）组成，用来标识接口的版本信息。

   - **attribute Int32 x**: 这是一个整数属性，命名为 "x"，用来存储一个 32 位的整数值。

   - **attribute CommonTypes.a1Struct a1**: 这是一个复杂类型的属性，命名为 "a1"，它的类型是 CommonTypes.a1Struct，即结构体 a1Struct。

   - method sayHello

     : 这是一个方法，名为 "sayHello"，用来执行打招呼的操作。

     - **in**: 这是方法的输入参数部分，其中包含一个名为 "name" 的字符串参数，表示要向谁打招呼。
     - **out**: 这是方法的输出参数部分，其中包含一个名为 "message" 的字符串参数，表示打招呼的消息内容。

2. **类型集合 CommonTypes**:

   - **version**: 这个类型集合的版本号，由主版本号（major）和次版本号（minor）组成，用来标识类型集合的版本信息。

   - struct a1Struct

     : 这是一个结构体，名为 "a1Struct"，包含两个字段：

     - **String s**: 一个字符串类型的字段，用来存储字符串值。
     - **a2Struct a2**: 一个嵌套的结构体类型的字段，名为 "a2"，类型为 a2Struct。

   - struct a2Struct

     : 这是另一个结构体，名为 "a2Struct"，包含三个字段：

     - **Int32 a**: 一个整数类型的字段，用来存储整数值。
     - **Boolean b**: 一个布尔类型的字段，用来存储布尔值。
     - **Double d**: 一个双精度浮点数类型的字段，用来存储双精度浮点数值。

`HelloWorld-someip.fdepl`

```bash
import "platform:/plugin/org.genivi.commonapi.someip/deployment/CommonAPI-4-SOMEIP_deployment_spec.fdepl"
import "HelloWorld.fidl"
 
define org.genivi.commonapi.someip.deployment for interface commonapi.examples.Helloworld {
    SomeIpServiceID = 4660
 
    attribute x {
        SomeIpGetterID = 3000
        SomeIpSetterID = 3001
        SomeIpNotifierID = 33010
        SomeIpNotifierEventGroups = { 33010 }
 
        SomeIpAttributeReliable = true
    }
 
    attribute a1 {
        SomeIpGetterID = 3002
        SomeIpSetterID = 3003
        SomeIpNotifierID = 33011
        SomeIpNotifierEventGroups = { 33011 }
 
        SomeIpAttributeReliable = true
    }
 
    method sayHello {
        SomeIpMethodID = 3004
        SomeIpReliable = true
 
        in {
            name {
                SomeIpStringEncoding = utf16le
            }
        }
    }
}
 
define org.genivi.commonapi.someip.deployment for typeCollection commonapi.examples.CommonTypes {
    struct a1Struct {
    }
 
    struct a2Struct {
    }
 
}
 
define org.genivi.commonapi.someip.deployment for provider as Service {
    instance commonapi.examples.Helloworld {
        InstanceId = "commonapi.examples.Helloworld"
 
        SomeIpInstanceID = 22136
 
        SomeIpUnicastAddress = "192.168.0.2"
        SomeIpReliableUnicastPort = 30499
        SomeIpUnreliableUnicastPort = 30500
    }
}
```

fdepl 文件通常是 CommonAPI 的部署描述文件，用于配置和定义 CommonAPI 服务的运行时参数以及服务的部署信息。这个文件通常包含了与服务的实际运行有关的配置信息，例如服务的ID、网络地址、端口号、通信协议等



1. **导入部署规范和 FIDL 文件**：

   - `import "platform:/plugin/org.genivi.commonapi.someip/deployment/CommonAPI-4-SOMEIP_deployment_spec.fdepl"`：这行代码导入了 CommonAPI-4-SOMEIP 框架的部署规范文件，该文件定义了在 SOME/IP 网络中部署服务的规则和标准。
   - `import "HelloWorld.fidl"`：这行代码导入了名为 "HelloWorld" 的 FIDL 文件，该文件定义了服务接口 "Helloworld" 的结构和行为。

2. **定义服务接口部署**：
   - 使用 `define` 关键字为服务接口 "commonapi.examples.Helloworld" 配置部署信息。
   - 设置了服务的 SomeIpServiceID 为 4660，这是在 SOME/IP 网络中唯一标识服务的 ID。
   - 对于每个属性（"x" 和 "a1"）和方法（"sayHello"），指定了其在网络中的各种标识，如 Getter、Setter、Notifier 和 Method 的 ID。
   - 设置了属性的通信是否可靠（SomeIpAttributeReliable）为 true，这表示属性通信将使用可靠的传输方式。
   - 对于`sayHello`方法，定义了其在网络中的标识和行为。
     - 设置了方法的 SomeIpMethodID 为 3004，用于在网络中唯一标识该方法。
     - 设置了方法的可靠性（SomeIpReliable）为 true，表示该方法调用将使用可靠的传输方式。
     - 在方法的`in`部分中，定义了方法的输入参数。具体来说，该方法接收一个名为`name`
的字符串参数，以表示要向谁打招呼。
       - 设置了 `name` 参数的编码格式为 UTF-16 Little Endian，以确保在网络中正确传输字符串数据。

3. **定义类型集合部署**：
   - 使用 `define` 关键字为类型集合 "commonapi.examples.CommonTypes" 配置部署信息。
   - 定义了两个结构体 "a1Struct" 和 "a2Struct"，但暂时没有为它们指定具体的部署细节。
4. **定义服务提供者部署**：
   - 使用 `define` 关键字为服务提供者配置部署信息。
   - 指定了实现 "commonapi.examples.Helloworld" 接口的服务实例的部署细节，包括实例 ID、SOME/IP 实例 ID，以及单播通信地址和端口等信息。


5. **内部变量的解释**

|            属性             |               含义                |
| :-------------------------: | :-------------------------------: |
|       SomeIpServiceID       | 在SOME/IP网络中识别服务的唯一ID。 |
|       SomeIpGetterID        |    获取属性值时使用的唯一ID。     |
|       SomeIpSetterID        |    设置属性值时使用的唯一ID。     |
|      SomeIpNotifierID       |  属性变化通知的唯一ID (事件ID)。  |
|  SomeIpNotifierEventGroups  |         相关事件组的ID。          |
|   SomeIpAttributeReliable   |        属性通信是否可靠。         |
|       SomeIpMethodID        |          方法的唯一ID。           |
|       SomeIpReliable        | 方法调用是否使用可靠的传输方式。  |
|    SomeIpStringEncoding     |      字符串参数的编码格式。       |
|         InstanceId          |      服务实例的唯一标识符。       |
|      SomeIpInstanceID       | 服务实例在SOME/IP网络中的唯一ID。 |
|    SomeIpUnicastAddress     |     服务实例的单播通信地址。      |
|  SomeIpReliableUnicastPort  |   服务实例的可靠单播通信端口。    |
| SomeIpUnreliableUnicastPort |  服务实例的不可靠单播通信端口。   |

## 使用配置文件生成代码

在当前目录执行以下命令

### 生成框架代码
```bash
./gen/commonapi_core_generator/commonapi-core-generator-linux-x86 -d src-gen/core -sk ./config/HelloWorld.fidl
```
生成文件如下
```bash
byeaxj:~/wkspaces/SOMEIP/Demo$ tree src-gen/core/
src-gen/core/
└── v1
    └── commonapi
        └── examples
            ├── CommonTypes.hpp
            ├── Helloworld.hpp
            ├── HelloworldProxyBase.hpp
            ├── HelloworldProxy.hpp
            ├── HelloworldStubDefault.hpp
            └── HelloworldStub.hpp
 
3 directories, 6 files
```

### 生成someip服务代码
```bash
./gen/commonapi_someip_generator/commonapi-someip-generator-linux-x86 -d src-gen/someip ./config/HelloWorld-someip.fdepl
```
生成文件如下
```bash
byeaxj:~/wkspaces/SOMEIP/Demo$ tree src-gen/someip/
src-gen/someip/
└── v1
    └── commonapi
        └── examples
            ├── CommonTypesSomeIPDeployment.cpp
            ├── CommonTypesSomeIPDeployment.hpp
            ├── HelloworldSomeIPCatalog.json
            ├── HelloworldSomeIPDeployment.cpp
            ├── HelloworldSomeIPDeployment.hpp
            ├── HelloworldSomeIPProxy.cpp
            ├── HelloworldSomeIPProxy.hpp
            ├── HelloworldSomeIPStubAdapter.cpp
            └── HelloworldSomeIPStubAdapter.hpp
 
3 directories, 9 files
```
someip 文件夹下的代码包含了fdepl 文件中的所有配置，初始化了someip相关的事件订阅注册等内容，不需要改动，直接参与编译生成库文件即可，如果需要改动必须修改fdepl 文件然后重新生成代码

core目录下的文件功能:
```bash
src-gen/core/
└── v1
    └── commonapi
        └── examples
# 类型集合接口类，配置了服务里用到的数据类型
            ├── CommonTypes.hpp 
 
 
# 用于客户端开发：代理是一个提供方法调用的类，
# 该方法调用将导致对服务的远程方法调用，以及服务可以广播的事件的注册方法。
            ├── Helloworld.hpp
            ├── HelloworldProxyBase.hpp
            ├── HelloworldProxy.hpp
 
# 服务器开发：存根是服务的一部分，当来自客户端的远程方法调用到达时，
# 存根将被调用，它还包含将事件（广播）激发到几个或所有客户端的方法。
            ├── HelloworldStubDefault.hpp
            └── HelloworldStub.hpp
```

## Server代码
```C++
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
    CommonAPI::Runtime::setProperty("LogContext", "demoS");
    CommonAPI::Runtime::setProperty("LogApplication", "demoS");
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
```

### 解释

```C++
class HelloWorldStubImpl : public v1::commonapi::examples::HelloworldStubDefault
```

此处继承了前面生成的 HelloworldStubDefault 的类，对 sayHello 虚函数进行了具体的实现，同时也封装了一个 incCounter 函数来更改属性 X 的数值



```C++
CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");
```

此处是设置使用的要使用哪个库，名称需要于fidl文件的名称一致



```C++
std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
```

获取运行环境



```C++
    std::string domain = "local";
    std::string instance = "commonapi.examples.Helloworld";
    std::string connection = "service-sample";
 
    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
```

这里是注册 service 需要的信息，

- domain 指定的是本地，如果运行时使用了配置文件，此处会被覆盖
- instance 是服务实例的名字， 也就是 fidl 文件开头的 package名字 commonapi.examples 和 interface名字 Helloworld, 此处填错会导致服务无法被发现



```C++
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
```

从此开始的部分可以自由发挥，这里我实现的是服务端主动修改数据，每十秒设置一次


## Client
```C++
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
    CommonAPI::Runtime::setProperty("LogContext", "demoC");
    CommonAPI::Runtime::setProperty("LogApplication", "demoC");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");
 
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
 
    std::string domain = "local";
    std::string instance = "commonapi.examples.Helloworld";
    std::string connection = "client-sample";
 
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

```

### 解释
```C++

CommonAPI::Runtime::setProperty("LogContext", "demoC");
CommonAPI::Runtime::setProperty("LogApplication", "demoC");
CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");
 
std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
 
std::string domain = "local";
std::string instance = "commonapi.examples.Helloworld";
std::string connection = "client-sample";
 
std::shared_ptr<HelloworldProxy<>> myProxy = runtime->buildProxy < HelloworldProxy > (domain, instance, connection);
std::cout << "Checking availability!" << std::endl;
while (!myProxy->isAvailable())
{
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}
```
以上流程都与 server 端代码基本一致， 服务端是注册服务，这里是等待服务


```C++
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
```
以上代码对 变量 X 和结构体 A1 进行了订阅，并设置了回调函数，订阅后，如果服务端广播了数据变化的消息，客户端的回调函数会进行打印

```C++
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
```

这里的代码是为了测试 远程调用的功能， 直接再 客户端调用服务端提供 的sayHello 函数并打印

## 构建编译
以上都完成后目录结构应该是这样的
```bash
.
├── CMakeLists.txt
├── commonapi4someip.ini
├── config
│   ├── HelloWorld.fidl
│   └── HelloWorld-someip.fdepl
├── gen
│   ├── commonapi_core_generator
│   └── commonapi_someip_generator
├── mylog.log
├── src
│   ├── Client.cpp
│   └── Server.cpp
└── src-gen
    ├── core
    └── someip
```

确认无误后，在当前目录下执行以下命令
```bash
cmake -Bbuild -DCMAKE_PREFIX_PATH=$(realpath ../install_folder) -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON .
cmake --build build
```

## 代码运行
开启两个终端分别执行以下命令


Server启动命令
```bash
VSOMEIP_CONFIGURATION= COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/ build/Server
```

Client 启动命令
```bash
VSOMEIP_CONFIGURATION= COMMONAPI_CONFIG=commonapi4someip.ini LD_LIBRARY_PATH=../install_folder/lib:$PWD/build/ build/Client
```

`VSOMEIP_CONFIGURATION=` 这里我把vsomeip的环境变量设置为了空，防止之前的demo运行时设置的环境变量对这里的程序造成影响

> 两端输出如下

Server 输出
```bash
024-04-22 03:14:42.953908 [info] REGISTERED_ACK(0101)
2024-04-22 03:14:42.981538 [info] REGISTER EVENT(0101): [1234.5678.80f2:eventtype=2:is_provided=false:reliable=1]
2024-04-22 03:14:42.981736 [info] REGISTER EVENT(0101): [1234.5678.80f3:eventtype=2:is_provided=false:reliable=1]
2024-04-22 03:14:42.087751 [info] REQUEST(0101): [1234.5678:1.4294967295]
2024-04-22 03:14:42.130598 [info] SUBSCRIBE(0101): [1234.5678.80f2:80f2:1]
2024-04-22 03:14:42.130910 [info] SUBSCRIBE(0101): [1234.5678.80f3:80f3:1]
sayHello('World'): 'Hello World!'
Set X value = 2
 Rev S val =
Set X value = 3
 Rev S val = abc
2024-04-22 03:14:50.340196 [info] vSomeIP 3.4.10 | (default)
Set X value = 4
 Rev S val = abc
2024-04-22 03:15:00.353773 [info] vSomeIP 3.4.10 | (default)
Set X value = 5
 Rev S val = abc
Set X value = 6
 Rev S val = abc
2024-04-22 03:15:10.360538 [info] vSomeIP 3.4.10 | (default)
Set X value = 7
 Rev S val = abc
Set X value = 8
 Rev S val = abc
2024-04-22 03:15:20.361992 [info] vSomeIP 3.4.10 | (default)
Set X value = 9
 Rev S val = abc
Set X value = 10
 Rev S val = abc
2024-04-22 03:15:25.551906 [info] Application/Client 0101 is deregistering.
2024-04-22 03:15:25.656507 [info] Client [100] is closing connection to [101]
2024-04-22 03:15:25.656781 [info] local_uds_client_endpoint_impl::receive_cbk Error: Operation canceled
^C2024-04-22 03:15:26.722447 [info] Stopping vsomeip application "service-sample" (0100).
2024-04-22 03:15:26.729891 [info] Exiting vsomeip application...
[ 5782.126916]~DLT~18520~WARNING  ~Lost log messages in user buffer when exiting: 8
[ 5782.127697]~DLT~18520~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...

```

Client输出
```bash
2024-04-22 03:14:42.090640 [info] ON_AVAILABLE(0101): [1234.5678:1.0]
Available...
start value test ...
2024-04-22 03:14:42.128638 [info] Client [101] is connecting to [100] at /tmp/vsomeip-100
start Method test ...
[CAPI][2024-04-22 03:14:42.131062 [info] SUBSCRIBE ACK(0100): [1234.5678.80f2.80f2]
2024-04-22 03:14:42.133788 [info] SUBSCRIBE ACK(0100): [1234.5678.80f3.80f3]
DEBUG] Message sent: SenderID: 1234 - ClientID: 257, SessionID: 1
Received change message: 1
Received change message for A1
a1Struct.s =
a1Struct.a1.a2.a = 0
a1Struct.a1.a2.b = 0
a1Struct.a1.a2.d = 0
Got message: 'Hello World!'
Received change message: 2
Received change message for A1
a1Struct.s = abc
a1Struct.a1.a2.a = 123
a1Struct.a1.a2.b = 1
a1Struct.a1.a2.d = 1234
Received change message: 3
Received change message: 4
Received change message: 5
Received change message: 6
Received change message: 7
Received change message: 8
Received change message: 9
Received change message: 10
^C2024-04-22 03:15:25.545565 [info] Stopping vsomeip application "client-sample" (0101).
2024-04-22 03:15:25.555963 [info] Application/Client 101 (client-sample) is deregistered.
2024-04-22 03:15:25.560281 [info] Client [101] is closing connection to [100]
2024-04-22 03:15:25.561267 [info] local_uds_client_endpoint_impl::receive_cbk Error: Operation canceled
2024-04-22 03:15:25.562436 [info] local_uds_client_endpoint_impl::receive_cbk Error: Operation canceled
2024-04-22 03:15:25.566396 [info] Exiting vsomeip application...
[ 5781.386719]~DLT~18549~WARNING  ~Lost log messages in user buffer when exiting: 7
[ 5781.387519]~DLT~18549~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...

```

# vsomeip 开源库学习
## 前期准备

Ubuntu18.04

gcc

cmake/xmake

boost库


### 编译环境准备
```bash
sudo apt-get install libboost-system-dev libboost-thread-dev libboost-log-dev
sudo apt-get install asciidoc source-highlight doxygen graphviz
sudo apt-get install gcc g++ make
```



### 拉取代码并编译安装
```bash
git clone https://github.com/COVESA/vsomeip.git
cd vsomeip
cmake -Bbuild
cd build
make
sudo make install
```

## demo使用

demo1 到 demo6 都是 someip 的代码，使用以下方法编译即可

CommonApiDemo 的内容参考其目录下的 README

### 编译
可使用 cmake 或者 xmake 编译

编译完成后可执行文件会在各demo的build目录下
#### cmake
```bash
cmake -Bbuild
cd build
make
```
#### xmake
```bash
xmake
```

### 编译后目录结构
```bash
.
├── build
├── CMakeLists.txt
├── demo1
│   ├── app.cpp
│   └── build
│       └── AppDemo1
├── demo2
│   ├── build
│   │   ├── ClientDemo2
│   │   └── ServerDemo2
│   ├── client.cpp
│   └── server.cpp
├── demo3
│   ├── build
│   │   ├── ClientDemo3
│   │   └── ServerDemo3
│   ├── client.cpp
│   └── server.cpp
├── demo4
│   ├── build
│   │   ├── ClientDemo4
│   │   └── ServerDemo4
│   ├── client.cpp
│   └── server.cpp
├── demo5
│   ├── build
│   │   ├── ClientDemo5
│   │   └── ServerDemo5
│   ├── client.cpp
│   ├── client.json
│   ├── server.cpp
│   └── server.json
├── demo6
│   ├── build
│   │   ├── ClientDemo6
│   │   └── ServerDemo6
│   ├── client.cpp
│   ├── client.json
│   ├── server.cpp
│   └── server.json
├── README.md
└── xmake.lua
```

## 详细介绍
### Demo1 – 简单的application

以下代码演示了最简单的一个 app 的创建过程，全部使用默认配置，未添加个性化设置

> `demo_main.cpp`
```CPP 
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
```

运行结果如下, 添加了对应解读
```bash
byeaxj@DL8DCD2J3:~/space/MyCode/vSomeIpDemo/cmakebuild$ ./ServerDemo
2024-04-10 10:55:39.302189 [info] Parsed vsomeip configuration in 0ms                                                       
// 在0毫秒内解析了vsomeip的配置。
2024-04-10 10:55:39.302647 [info] Configuration module loaded.                                                              
// 配置模块已加载。
2024-04-10 10:55:39.302694 [info] Security disabled!                                                                        
// 安全性已禁用。
2024-04-10 10:55:39.302714 [info] Initializing vsomeip (3.4.10) application "FirstApp".                                     
// 初始化了vsomeip应用程序 "FirstApp"，版本为3.4.10。
2024-04-10 10:55:39.302844 [info] Instantiating routing manager [Host].                                                     
// 实例化路由管理器 [Host]。
2024-04-10 10:55:39.303780 [info] create_routing_root: Routing root @ /tmp/vsomeip-0                                        
// 创建了路由根目录。
2024-04-10 10:55:39.304274 [info] Service Discovery enabled. Trying to load module.                                         
// 启用了服务发现，尝试加载模块。
2024-04-10 10:55:39.305795 [info] Service Discovery module loaded.                                                          
// 服务发现模块已加载。
2024-04-10 10:55:39.306246 [info] Application(FirstApp, 0100) is initialized (11, 100).                                     
// 应用程序 "FirstApp" 初始化完成，标识为(11, 100)。 11表示vsomeip使用的最大调度程序数量为11， 100表示回调阻塞时长最多100 毫秒
2024-04-10 10:55:39.306426 [info] Starting vsomeip application "FirstApp" (0100) using 2 threads I/O nice 255               
// 启动了vsomeip应用程序 "FirstApp"，使用2个I/O线程，优先级为255。
2024-04-10 10:55:39.307121 [info] Client [0100] routes unicast:127.0.0.1, netmask:255.255.255.0                             
// 客户端 [0100] 路由单播地址为127.0.0.1，子网掩码为255.255.255.0。
2024-04-10 10:55:39.307184 [info] shutdown thread id from application: 0100 (FirstApp) is: 7fcba2e8a700 TID: 2682           
// 应用程序 "FirstApp" 的关闭线程标识为7fcba2e8a700，线程ID为2682。
2024-04-10 10:55:39.307840 [info] Watchdog is disabled!                                                                     
// 看门狗已禁用。
2024-04-10 10:55:39.307452 [info] main dispatch thread id from application: 0100 (FirstApp) is: 7fcba368b700 TID: 2681      
// 应用程序 "FirstApp" 的主分发线程标识为7fcba368b700，线程ID为2681。
2024-04-10 10:55:39.308354 [info] io thread id from application: 0100 (FirstApp) is: 7fcba1e88700 TID: 2684                 
// 应用程序 "FirstApp" 的I/O线程标识为7fcba1e88700，线程ID为2684。
2024-04-10 10:55:39.308385 [info] io thread id from application: 0100 (FirstApp) is: 7fcba3f9b000 TID: 2679                 
// 应用程序 "FirstApp" 的I/O线程标识为7fcba3f9b000，线程ID为2679。   开启两个IO线程，用来并行处理vsomeip长消息
2024-04-10 10:55:39.309469 [info] vSomeIP 3.4.10 | (default)                                                                
// vsomeip版本为3.4.10。
2024-04-10 10:55:39.309804 [info] Network interface "lo" state changed: up                                                  
// 网络接口 "lo" 的状态已更改为上线。
```
****
### Demo2 – 服务发现
以上程序由于没有添加多余的配置，没有服务端和客户端的区别，下面尝试编写一个提供服务的实例，和检查服务可用的客户端

> `ServerDemo.cpp`
```CPP
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
```

> `ClientDemo.cpp`
```CPP
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
```

输出结果如下

> `Server Output`
```bash
2024-04-10 13:32:54.891031 [info] Application/Client 0101 is registering.
// 与客户端建立连接
2024-04-10 13:32:54.892487 [info] Client [100] is connecting to [101] at /tmp/vsomeip-101

// 客户端注册服务
2024-04-10 13:32:54.897426 [info] REGISTERED_ACK(0101)

// 连接成功
// 接收到 客户端的 request service
2024-04-10 13:32:54.987995 [info] REQUEST(0101): [1234.9999:255.4294967295]

// 关闭server
// 重新打开server, 重新连接注册
2024-04-10 13:33:02.986989 [info] Application/Client 0101 is registering.
2024-04-10 13:33:02.987798 [info] Client [100] is connecting to [101] at /tmp/vsomeip-101
2024-04-10 13:33:02.993103 [info] REGISTERED_ACK(0101)
2024-04-10 13:33:02.993679 [info] REQUEST(0101): [1234.9999:255.4294967295]
// 关闭server
```
> `Client Output`
```bash
2024-04-10 13:32:54.890332 [info] Registering to routing manager @ vsomeip-0
// 与服务端建立连接
2024-04-10 13:32:54.895987 [info] Application/Client 101 (FirstClient) is registered.
// 服务注册完成前不可用
Service [1234.9999] is NOT available.
 
// 注册成功，服务可用
2024-04-10 13:32:54.989571 [info] ON_AVAILABLE(0101): [1234.9999:0.0]
Service [1234.9999] is available.
 
2024-04-10 13:32:57.956926 [info] local_uds_client_endpoint_impl::receive_cbk Error: End of file
2024-04-10 13:32:57.957650 [info] Application/Client 101: Reconnecting to routing manager.
// server关闭导致服务不可用
Service [1234.9999] is NOT available.
 
2024-04-10 13:33:02.985323 [info] Reusing local server endpoint@0
2024-04-10 13:33:02.985755 [info] Client 101 (FirstClient) successfully connected to routing  ~> registering..
2024-04-10 13:33:02.985928 [info] Registering to routing manager @ vsomeip-0
2024-04-10 13:33:02.991756 [info] Application/Client 101 (FirstClient) is registered.
// 注册成功，服务可用
2024-04-10 13:33:02.995114 [info] ON_AVAILABLE(0101): [1234.9999:0.0]
Service [1234.9999] is available.
2024-04-10 13:33:05.588583 [info] local_uds_client_endpoint_impl::receive_cbk Error: End of file
2024-04-10 13:33:05.589179 [info] Application/Client 101: Reconnecting to routing manager.
// server关闭导致服务不可用
Service [1234.9999] is NOT available.
```

#### 流程说明
在上面这个例子中，我在 `FirstApp` 这个应用程序中，使用 `offer_service` 接口注册了一个服务ID为 `0x1234`, 服务实例ID为 `0x9999` 的服务。

在 `FirstClient` 这个应用程序中使用 `register_availability_handler` 接口注册了0x1234.9999 服务实例的可用性检测函数，随后使用 `request_service` 接口将服务请求加入到事件队列中，在执行 `start` 接口启用事件循环之后，向其他应用程序请求这个服务，同时也会调用可用性回调函数 

关于服务发现
上面的例子在执行时，我对server进行了关闭重启的操作，可以看到server重新提供服务之后， client 会知道服务上线，这就是someip的服务发现 （service discovery）的能力。

#### 服务发现 （service discovery）

在VSOMEIP中，服务发现是指客户端在网络中发现和识别可用的服务实例的过程。当服务重新上线时，它会向网络发送注册消息，通知其他参与者它重新可用了。客户端会收到这些注册消息，并根据收到的消息自动注册或更新服务信息。

这种自动注册的机制可以确保服务提供者重新上线后，客户端可以及时地发现并使用它提供的服务，而无需手动重新配置客户端。这也是VSOMEIP作为一种面向服务的中间件所提供的便利之一。

****

### Demo3 – 请求 / 响应 &（ 远程过程调用RPC）
在上面的例子里面，已经实现了 一个提供服务的服务端和一个请求服务的客户端。接下来要实现的就是在服务端实现功能，由客户端远程调用。

因此，服务端需要 有接收消息的能力，需要注册消息处理函数。
代码如下
> `ServerDemo.cpp`
```CPP
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vsomeip/vsomeip.hpp>
 
#define SOMEIP_SERVICE_ID  0x1234
#define SOMEIP_INSTANCE_ID 0x9999
#define SOMEIP_UPPER_METHOD_ID   0x1145
 
std::shared_ptr<vsomeip::application> app;
 
// 将字符串转换为大写
std::string toUpper(std::string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            // 如果字符是小写字母，则转换为大写字母
            str[i] = str[i] - 'a' + 'A';
        }
    }
    return str;
}
 
void on_message_cbk(const std::shared_ptr<vsomeip::message> &_request)
{
    // 获取从客户端拿到的payload
    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    // 获取 payload 内容
    auto str = reinterpret_cast<const char*>(its_payload->get_data());
    std::cout << "[message Received][Client/Session:"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_session()
        << "] " << str << std::endl;
    // 根据请求创建一个响应，内部会将请求中的各种ID以及其他通信数据设置到响应中
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    // 创建一个payload
    std::shared_ptr<vsomeip::payload> rsp_payload = vsomeip::runtime::get()->create_payload();
 
    std::stringstream  rsp_ss;
    rsp_ss << "[toUpper][" << toUpper(str) << "]" << " ";
    std::string rsp_str(rsp_ss.str());
    // 创建 payload data并设置内容
    std::vector<vsomeip::byte_t> rsp_payload_data(std::begin(rsp_str), std::end(rsp_str));
    // 填充数据
    rsp_payload->set_data(rsp_payload_data);
    its_response->set_payload(rsp_payload);
    // 发送响应
    app->send(its_response);
 
}
 
int main(int argc, char** argv)
{
    app = vsomeip::runtime::get()->create_application("FirstApp");
    app->init();
    app->offer_service(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID);
    // 注册消息处理回调函数
    app->register_message_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, SOMEIP_UPPER_METHOD_ID, on_message_cbk);
    app->start();
    return 0;
}
```

同理， 客户端需要有发送能力，也要有接收返回的消息的能力
> `ClientDemo.cpp`
```CPP
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
```
命令行输出如下
> `Server Output`
```bash
2024-04-10 15:41:40.205218 [info] Application/Client 0101 is registering.
2024-04-10 15:41:40.206623 [info] Client [100] is connecting to [101] at /tmp/vsomeip-101
2024-04-10 15:41:40.209459 [info] REGISTERED_ACK(0101)
2024-04-10 15:41:40.294332 [info] REQUEST(0101): [1234.9999:255.4294967295]
[message Received][Client/Session:0101/0001] this is Client
```
> `Client Output`
```bash
2024-04-10 15:41:40.295490 [info] ON_AVAILABLE(0101): [1234.9999:0.0]
Service [1234.9999] is available.
2024-04-10 15:41:40.297410 [info] Client [101] is connecting to [100] at /tmp/vsomeip-100
[message Received][Client/Session:0101/0001] [toUpper][THIS IS CLIENT]
```
#### 流程说明
上面例子中，服务端提供的服务是将发过来的字符串转为大写， 使用register_message_handler 接口，将 on_message_cbk 函数绑定了 Method id， 并注册为了消息处理回调函数

这样在其他app请求服务时，可以获取到请求中携带的payload并进行处理。

在客户端中

同样需要消息处理函数，注册流程与服务端相同。

但是客户端比服务端多出一个主动发送的操作，由于app→start() 接口在其内部才开启事件循环，处理网络通信，而它又是阻塞的，所以发送程序的代码不能写在start()之后，否则无法调用，写在start()之前，网络通信未建立，消息也发送不出去。

所以需要使用线程，在线程中等待网络通信正常运行，然后再执行发送消息的操作。因此用到了线程锁和条件变量，等待服务可用后通知继续运行消息发送函数。



#### 关于远程过程调用
在以上代码中

服务端通过注册消息处理回调函数来处理客户端发送的请求，并在收到请求后执行相应的业务逻辑（将字符串转换为大写），然后将结果作为响应发送回客户端。

客户端在检测到服务可用后，发送远程调用请求到服务端，并等待服务端的响应。一旦收到响应，客户端处理响应并输出结果。

这种交互模式就是RPC的基本原理：客户端发起调用请求，服务端执行相应的操作并返回结果给客户端
****

### Demo4 – 事件订阅/通知
上面的例子都是需要客户端主动向服务端请求，然后服务端才会做出响应。

所以这个例子里会展示，如何在客户端不请求的情况下，服务端主动发送消息，也就是订阅和通知机制

以下是示例代码

> `ServerDemo.cpp`
```CPP
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
```

> `ClientDemo.cpp`
```CPP
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
#define SOMEIP_EVENTGROUP_ID_1        0x01
#define SOMEIP_EVENTGROUP_ID_2        0x02
  
  
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
 
    // 注册消息处理回调函数，这里是测试订阅和广播的功能，所以对method不做限制使用 ANY_METHOD
    app->register_message_handler(SOMEIP_SERVICE_ID, SOMEIP_INSTANCE_ID, vsomeip::ANY_METHOD, on_event_cbk);
      
    // 在子线程中运行消息发送函数， 因为发送消息需要 start 内部的事件循环，而 start 函数时阻塞性质的，必须在子线程中等待事件循环
    std::thread sender(msg_send);
    app->start();
  
    return 0;
}
```

以下只展示 请求订阅相关功能的输出

> `Server Output`
```CPP
2024-04-11 14:51:18.803393 [info] Application/Client 0101 is registering.
2024-04-11 14:51:18.804935 [info] Client [100] is connecting to [101] at /tmp/vsomeip-101
2024-04-11 14:51:18.808418 [info] REGISTERED_ACK(0101)
2024-04-11 14:51:18.899506 [info] REQUEST(0101): [1234.9999:255.4294967295]
 
// 接收到客户端注册事件的请求，
// 101 是客户端id, 0333是事件id，eventtype表示事件类型，这里是2，对应的是字段事件 (ET_FIELD)
// is_provided表示该事件是否已被提供，这里是 false，表示该事件目前还没有被服务端提供。
// reliable：表示事件的可靠性，这里是 255，表示可靠性未知
2024-04-11 14:51:18.905816 [info] REGISTER EVENT(0101): [1234.9999.0333:eventtype=2:is_provided=false:reliable=255]
 
// 这是是接收到客户端的订阅请求， 0001 是事件组id
2024-04-11 14:51:18.905898 [info] SUBSCRIBE(0101): [1234.9999.0001:ffff:0]
 
// 这是提示的是 事件333和事件334没有设置初始状态，所以客户端不会收到数据，不影响
// 因为客户端订阅了事件组1，而事件1和事件2都在事件组1中，所以事件1 2 会在这里被提示，而事件组2中的事件3不会被提示
2024-04-11 14:51:18.908134 [info] notify_one_unlocked: Initial value for [1234.9999.333] not yet set by the service/client. Client 101 will not receive any initial notification!
2024-04-11 14:51:18.908301 [info] notify_one_unlocked: Initial value for [1234.9999.334] not yet set by the service/client. Client 101 will not receive any initial notification!
 
// 以下开始是事件1 事件2 事件3 的通知，每一秒发送一次
>>> start send
==== send [0]
==== send [1]
==== send [2]
==== send [3]
==== send [4]
>>> finish send
```

> `Client Output`
```CPP
// 客户端检测到服务端服务可用
Service [1234.9999] is available.
2024-04-11 14:51:18.904255 [info] Client [101] is connecting to [100] at /tmp/vsomeip-100
 
// 发送事件注册请求和订阅请求，获取到服务端的响应
2024-04-11 14:51:18.909549 [info] SUBSCRIBE ACK(0100): [1234.9999.0001.ffff]
 
// 此处是客户端接收到服务端广播的事件组1的消息，由于事件组2没有在客户端中订阅，所以这里不会提示事件3的消息
// 因为没有定于事件2， 所以事件2在此处被 block， 而事件1可以正常调用消息回调
2024-04-11 14:51:26.481237 [info] application_impl::on_message [1234.9999.0334]: blocked as the subscription is already inactive.
>>>>> CLIENT: received a notification for event [1234.9999.0333] to Client/Session [0000/0001] = (1) 00
>>>>> CLIENT: received a notification for event [1234.9999.0333] to Client/Session [0000/0004] = (1) 01
2024-04-11 14:51:27.487151 [info] application_impl::on_message [1234.9999.0334]: blocked as the subscription is already inactive.
2024-04-11 14:51:28.487061 [info] application_impl::on_message [1234.9999.0334]: blocked as the subscription is already inactive.
>>>>> CLIENT: received a notification for event [1234.9999.0333] to Client/Session [0000/0007] = (1) 02
>>>>> CLIENT: received a notification for event [1234.9999.0333] to Client/Session [0000/000a] = (1) 03
2024-04-11 14:51:29.492233 [info] application_impl::on_message [1234.9999.0334]: blocked as the subscription is already inactive.
>>>>> CLIENT: received a notification for event [1234.9999.0333] to Client/Session [0000/000d] = (1) 04
2024-04-11 14:51:30.492329 [info] application_impl::on_message [1234.9999.0334]: blocked as the subscription is already inactive.

```

#### 流程说明
服务端

* 使用 offer_event 广播出自己提供的事件服务
* 使用 notify 通知所有订阅了对应事件组的客户端
* 需要在子线程中 等待start的事件循环开启后才能 notify



客户端

* 使用 register_message_handler 注册消息回调函数
* 必须在子线程中等待服务端的服务可用
* 使用 request_event 通知服务端自己的事件请求
* 使用 subscribe 通知 服务端自己订阅了这个事件组


 关于事件的订阅和广播，需要遵守以上顺序进行配置。

上面的代码实现的是

服务端提供两个事件组， 第一个事件组有有个事件，第二个事件组只提供一个事件。客户端只订阅第一个事件组中的第一个事件。

服务端会在客户端订阅后，每隔1秒事件1 的数据会进行更新，服务端会发送对应的通知。不需要客户端主动去请求获取 数据。



#### 请求/响应
SOMEIP的订阅和通知是一种允许客户端监听并接收服务端特定事件更新的机制。在这个过程中，客户端订阅服务端的一个或多个特定事件，当这些事件发生变化时，服务端会通知所有订阅了该事件的客户端。这是一种典型的发布/订阅模式，用于实现分布式系统中的事件驱动通信。
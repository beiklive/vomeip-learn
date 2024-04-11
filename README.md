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
├── README.md
└── xmake.lua
```
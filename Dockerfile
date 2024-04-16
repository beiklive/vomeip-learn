FROM ubuntu:20.04

# 设置环境变量，防止在安装过程中出现时区等交互式选择
ENV DEBIAN_FRONTEND=noninteractive

# 修改软件源为阿里云镜像源
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 设置工作目录
WORKDIR /app

RUN apt-get update
RUN apt-get install -y curl
RUN apt-get install -y libboost-system-dev libboost-thread-dev libboost-log-dev build-essential


RUN apt-get install -y net-tools

# 安装 VSOMEIP 和其他必要的包
RUN apt-get install -y \
    git \
    iputils-ping \
    asciidoc source-highlight doxygen graphviz \
    make 


WORKDIR /cmake
RUN curl -LO "https://cmake.org/files/v3.22/cmake-3.22.1-linux-x86_64.tar.gz" \
    && tar -xzvf cmake-3.22.1-linux-x86_64.tar.gz --strip-components=1 -C /usr/local \
    && rm cmake-3.22.1-linux-x86_64.tar.gz

RUN cmake --version
RUN gcc --version 
RUN g++ --version

WORKDIR /vsomeip
RUN pwd && git clone --depth 1 https://github.com/COVESA/vsomeip.git

RUN ls && pwd && cd vsomeip \
    && cmake -Bbuild . \
    && cd build \
    && make \
    && make install

WORKDIR /vsomeip-learn
RUN git clone --depth 1 https://github.com/beiklive/vsomeip-learn.git
RUN pwd && ls

RUN cd vsomeip-learn \
    && cmake -Bbuild \
    && cd build \
    && make


RUN apt-get clean

WORKDIR /cmake
RUN rm -rf *

WORKDIR /vsomeip
RUN rm -rf *
RUN rm -rf /var/lib/apt/lists/*

# 容器启动时运行你的 VSOMEIP 应用程序
CMD ["sh", "-c", "pwd && ls && ls /usr/local/lib/"]

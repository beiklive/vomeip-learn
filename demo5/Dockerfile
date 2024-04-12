FROM ubuntu:18.04

# 设置环境变量，防止在安装过程中出现时区等交互式选择
ENV DEBIAN_FRONTEND=noninteractive

# 安装 VSOMEIP 和其他必要的包
RUN apt-get update && apt-get install -y \
    build-essential \
    iputils-ping \
    && rm -rf /var/lib/apt/lists/*

# 复制你的 VSOMEIP 应用程序到容器中
COPY ./build /app
COPY ./client.json /app/client.json
COPY ./server.json /app/server.json

# 设置工作目录
WORKDIR /app/build

# 编译你的 VSOMEIP 应用程序
# RUN g++ -o my-vsomeip-app your-vsomeip-app.cpp -lvsomeip -lvsomeip_sd

# 容器启动时运行你的 VSOMEIP 应用程序
CMD ["VSOMEIP_CONFIGURATION=../server.json VSOMEIP_APPLICATION_NAME=World ./ServerDemo5"]

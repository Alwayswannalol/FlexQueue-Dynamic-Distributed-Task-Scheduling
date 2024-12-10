# Базовый образ
FROM ubuntu:20.04

# Установка необходимых пакетов без интерактивного ввода
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    unzip \
    tzdata \
    libopencv-dev\
    ca-certificates \
    && ln -fs /usr/share/zoneinfo/UTC /etc/localtime && \
    dpkg-reconfigure --frontend noninteractive tzdata && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Установка gRPC из исходников
ENV MY_INSTALL_DIR=/usr/local
RUN git clone --recurse-submodules -b v1.54.2 --depth 1 --shallow-submodules https://github.com/grpc/grpc.git /usr/local/src/grpc && \
    cd /usr/local/src/grpc && \
    mkdir -p cmake/build && cd cmake/build && \
    cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
          ../.. && \
    make -j 4 && \
    make install

# Копируем содержимое проекта в контейнер
WORKDIR /app

COPY . .

# Сборка проекта
RUN rm -rf build && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Debug .. && make

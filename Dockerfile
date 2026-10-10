
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV VCPKG_ROOT=/opt/vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    ca-certificates \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    libsqlite3-dev \
    libpq-dev \
    libsodium-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT" \
    && "$VCPKG_ROOT/bootstrap-vcpkg.sh" -disableMetrics

WORKDIR /app

COPY . .

RUN mkdir -p db/migrations uploads/products

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DVCPKG_MANIFEST_MODE=ON

RUN cmake --build build --parallel 2

EXPOSE 10000

CMD ["sh", "-c", "mkdir -p db uploads/products && exec ./build/DharaniMart"]

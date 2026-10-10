
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    libsqlite3-dev \
    libpq-dev \
    libsodium-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p db/migrations uploads/products

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --parallel 2

EXPOSE 10000

CMD ["sh", "-c", "mkdir -p db uploads/products && exec ./build/DharaniMart"]

# docker build -t veriyapilari .
# docker run --rm -it veriapp
# Docker containerlarında GUI ile uygulama çalıştırmak için:
# Windows => X Server kurulu olmalı (VcXsrv)
# macOS => XQuartz
# Linux => X11 native olarak destekleniyor

# Docker imajı Github Releases içerisine yüklenmiştir.
# Eğer Docker imajı doğrudan çekilmek istenirse:
# docker pull rkaankaraman/veriyapilari
# docker run -it rkaankaraman/veriyapilari

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    qt6-base-dev qt6-tools-dev qt6-tools-dev-tools \
    qt6-base-dev-tools libqt6sql6-sqlite \
    libgl1-mesa-dev libopengl0 libxkbcommon-dev \
    && apt-get clean

ENV QT_SELECT=qt6

WORKDIR /app

COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --config Release

CMD ["./build/VeriYapilari"]
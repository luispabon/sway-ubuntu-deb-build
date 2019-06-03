FROM ubuntu:disco

RUN apt-get update; \
    apt-get -y install \
        build-essential \
        checkinstall \
        clang-tidy\
        cmake \
        debhelper \
        devscripts \
        dh-make \
        meson \
        ninja-build \
        pkg-config \
        wayland-protocols \
        libcap-dev \
        libdrm-dev \
        libegl1-mesa-dev \
        libgbm-dev \
        libgles2-mesa-dev \
        libinput-dev \
        libpixman-1-dev \
        libsystemd-dev \
        libwayland-dev \
        libxcb-composite0-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-render0-dev \
        libxcb-xfixes0-dev \
        libxkbcommon-dev; \
    apt-get clean

RUN apt-get update;     \
    apt-get install -y \
        dh-exec

RUN apt-get install -y \
    libpango1.0-dev \
    libcairo2-dev \
    libgdk-pixbuf2.0-dev \
    libpam0g-dev \
    libdbus-1-dev \
    libjs-jquery

RUN apt-get install -y \
        scdoc \
        tree

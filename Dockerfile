FROM ubuntu:disco

RUN yes | unminimize; \
    apt-get update; \
    apt-get -y install \
        build-essential \
        checkinstall \
        clang-tidy\
        cmake \
        debhelper \
        devscripts \
        dh-exec \
        dh-make \
        libcairo2-dev \
        libcap-dev \
        libdbus-1-dev \
        libdbusmenu-gtk3-dev \
        libdrm-dev \
        libegl1-mesa-dev \
        libfmt-dev \
        libgbm-dev \
        libgdk-pixbuf2.0-dev \
        libgles2-mesa-dev \
        libgtkmm-3.0-dev \
        libinput-dev \
        libjs-jquery \
        libjsoncpp-dev \
        libmpdclient-dev \
        libnl-3-dev \
        libnl-genl-3-dev \
        libpam0g-dev \
        libpango1.0-dev \
        libpixman-1-dev \
        libpulse-dev \
        libspdlog-dev  \
        libsystemd-dev \
        libwayland-dev \
        libxcb-composite0-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-render0-dev \
        libxcb-xfixes0-dev \
        libxkbcommon-dev \
        meson \
        ninja-build \
        pkg-config \
        scdoc \
        tree \
        wayland-protocols; \
    apt-get clean

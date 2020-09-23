FROM ubuntu:focal AS meson-builder

ENV DEBIAN_FRONTEND=noninteractive

RUN yes | unminimize; \
    apt-get update; \
    apt-get -y install \
        curl \
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
        libjpeg-dev \
        libjs-jquery \
        libjson-c-dev \
        libjsoncpp-dev \
        libmpdclient-dev \
        libnl-3-dev \
        libnl-genl-3-dev \
        libgtk-layer-shell-dev \
        libpam0g-dev \
        libpango1.0-dev \
        libpixman-1-dev \
        libpulse-dev \
        libspdlog-dev  \
        libsystemd-dev \
        libwayland-client++0 \
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
        wayland-protocols \
        wayland-scanner++ \
        libglib2.0-dev \
        libgtk-3-dev \
        libjson-glib-dev \
        libgudev-1.0-dev \
        libdazzle-1.0-dev \
        libgnome-desktop-3-dev \
        valac \
        libasound2-dev \
        gobject-introspection \
        libxml2-dev \
        libglm-dev \
        fakeroot \
        gdb \
        libappindicator3-dev \
        libnm-dev \
        libmm-glib-dev \
        libgudev-1.0-dev \
        libjansson-dev \
        libgcr-3-dev \
        libgck-1-dev \
        libgirepository1.0-dev \
        gobject-introspection \
        gtk-doc-tools \
        libgtk-3-doc \
        dh-translations \
        mobile-broadband-provider-info \
        libsecret-1-dev \
        libnotify-dev \
        network-manager-dev \
        gnome-common \
        libglib2.0-doc \
        libavutil-dev \
        libavcodec-dev \
        libavformat-dev \
        libswscale-dev \
        libavdevice-dev \
        libpipewire-0.2-dev \
        libxcb-xinput-dev \
        libx11-xcb-dev \
        jq; \
    apt-get clean


# Enable source repositories
#RUN sed -i '/deb-src/s/^# //' /etc/apt/sources.list && apt update

# Sway 1.5 and wlroots 0.11 require a newer meson than that's available in Ubuntu. Debian testing's will do the trick
RUN curl -o meson.deb http://http.us.debian.org/debian/pool/main/m/meson/meson_0.55.3-1_all.deb; \
    dpkg -i meson.deb; \
    apt-get -f install; \
    apt-get install -y --no-install-recommends \
        bison \
        flex \
        libstartup-notification0-dev \
        libxkbcommon-x11-dev \
        libxcb-xkb-dev \
        libxcb-xinerama0-dev \
        libxcb-ewmh-dev \
        libxcb-randr0-dev \
        libxcb-util0-dev \
        librsvg2-dev \
        libxcb-xrm-dev \
        nvidia-opencl-dev; \
    rm meson.deb

# Rust apps builder

FROM ubuntu:eoan AS rust-builder

RUN export DEBIAN_FRONTEND=noninteractive;  \
    yes | unminimize; \
    apt-get update; \
    apt-get -y install --no-install-recommends \
        ca-certificates \
        rustc \
        cargo \
        libasound2-dev \
        librust-libdbus-sys-dev \
        libpulse0

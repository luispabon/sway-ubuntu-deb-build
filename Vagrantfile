# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/disco64"

  config.vm.box_check_update = false
  config.vm.synced_folder "/home/luis/.gnupg", "/vagrant/.gnupg"
  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = "2048"
  end
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update && \
      apt-get install -y \
        build-essential \
        checkinstall \
        clang-tidy\
        cmake \
        debhelper \
        devscripts \
        dh-make \
        fish \
        freerdp2-dev \
        git \
        libavcodec-dev \
        libavformat-dev \
        libavutil-dev \
        libcap-dev \
        libdbusmenu-gtk3-dev \
        libegl1-mesa-dev \
        libgbm-dev \
        libgles2-mesa-dev \
        libgtkmm-3.0-dev \
        libinput-dev \
        libinput10 \
        libjson-c-dev \
        libjsoncpp-dev \
        libmpdclient-dev \
        libmpdclient-dev \
        libnl-genl-3-dev \
        libpixman-1-dev \
        libpulse-dev \
        libsystemd-dev \
        libudev-dev \
        libwayland-client0 \
        libwayland-cursor0 \
        libwayland-dev \
        libwinpr2-dev \
        libxcb-composite0-dev \
        libxcb-icccm4-dev \
        libxcb-xinput-dev \
        libxcb1-dev \
        libxkbcommon-dev \
        meson \
        ninja-build \
        pkg-config \
        wayland-protocols \
        virtualbox-guest-utils-hwe \
        virtualbox-guest-dkms

      chsh vagrant -s /usr/bin/fish
      ln -s /vagrant /home/vagrant/code
  SHELL
end

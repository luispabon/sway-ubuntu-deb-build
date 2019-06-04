build-everything: build-image json-c-build scdoc-build wlroots-build-deb sway-build-deb swaylock-build-deb swayidle-build-dev swaybg-build-dev xdg-desktop-portal-wlr-build-deb kanshi-build kanshi-install waybar-image waybar-build waybar-install

build-image:
	docker build -t sway_build .

json-c-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd json-c; debuild -b -uc -us"
	make fix-permissions

scdoc-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd scdoc; debuild -b -uc -us"
	make fix-permissions

wlroots-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd wlroots; debuild -b -uc -us"
	make fix-permissions

sway-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c 'dpkg -i scdoc_1*deb; dpkg -i libwlroots0_*deb; dpkg -i libwlroots-dev*.deb;dpkg -i libjson-c*.deb; apt-get -f install; cd sway; debuild -b -uc -us'
	make fix-permissions

swaylock-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "dpkg -i scdoc_1*deb; dpkg -i libwlroots0_*deb; dpkg -i libwlroots-dev*.deb; cd swaylock; debuild -b -uc -us"
	make fix-permissions

swayidle-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "dpkg -i scdoc_1*deb; dpkg -i libwlroots0_*deb; dpkg -i libwlroots-dev*.deb; cd swayidle; debuild -b -uc -us"
	make fix-permissions

swaybg-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "dpkg -i scdoc_1*deb; dpkg -i libwlroots0_*deb; dpkg -i libwlroots-dev*.deb; cd swaybg; debuild -b -uc -us"
	make fix-permissions

mako-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd mako; debuild -b -uc -us"
	make fix-permissions

xdg-desktop-portal-wlr-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd xdg-desktop-portal-wlr; debuild -b -uc -us"
	make fix-permissions

kanshi-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd kanshi; debuild -b -uc -us"
	make fix-permissions

waybar-image:
	docker build -t waybar_build ./Waybar

waybar-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" waybar_build sh -c "cd Waybar; meson build; ninja -C build"
	make fix-permissions

waybar-install:
	ln -s $(PWD)/Waybar/build/waybar ~/bin/

fix-permissions:
	sudo chown $(shell id -u):$(shell id -g) . -Rf

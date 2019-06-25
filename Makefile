build-everything: build-image json-c-build scdoc-build wlroots-build-deb sway-build-deb swaylock-build-deb swayidle-build-deb swaybg-build-deb xdg-desktop-portal-wlr-build-deb mako-build-deb kanshi-build-deb waybar-build-deb grim-build-deb slurp-build-deb

build-image:
	docker build -t sway_build .

install-all-debs:
	ls -1  | tr '\n' '\0' | xargs -0 -n 1 basename | grep deb | grep -v ddeb | grep -v dev | grep -v skele | grep -v udeb | xargs sudo dpkg -i

yolo: build-everything install-all-debs
	echo "YOLO"

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

slurp-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd slurp; debuild -b -uc -us"
	make fix-permissions

grim-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd grim; debuild -b -uc -us"
	make fix-permissions

waybar-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd Waybar; debuild -b -uc -us"
	make fix-permissions

wl-clipboard-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd wl-clipboard; debuild -b -uc -us"
	make fix-permissions

nm-applet-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd network-manager-applet; debuild -b -uc -us"
	make fix-permissions

clipman-install:
	cd clipman; go install; ln -s ~/go/bin/clipman ~/bin/

fix-permissions:
	sudo chown $(shell id -u):$(shell id -g) . -Rf

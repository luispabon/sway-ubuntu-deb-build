build-image:
	docker build -t sway_build .

json-c-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd json-c; debuild -b -uc -us"
	make fix-permissions

scdoc-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd scdoc; debuild -b -uc -us"
	make fix-permissions

wlroots-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c "cd wlroots; meson build; ninja -C build; debuild -b -uc -us"
	make fix-permissions

sway-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build sh -c 'dpkg -i scdoc_1*deb; dpkg -i libwlroots0_*deb; dpkg -i libwlroots-dev*.deb;dpkg -i libjson-c*.deb; apt-get -f install; cd sway; meson build; ninja -C build; debuild -b -uc -us'
	make fix-permissions

fix-permissions:
	sudo chown $(shell id -u):$(shell id -g) . -Rf

build-everything: build-meson-image build-rust-image scdoc-build wlroots-build-deb sway-build-deb swaylock-build-deb swayidle-build-deb swaybg-build-deb xdg-desktop-portal-wlr-build-deb mako-build-deb kanshi-build-deb waybar-build-deb grim-build-deb slurp-build-deb clipman-install wldash-install gtk-layer-shell-build-deb wfconfig-build-deb wfshell-build-deb wayfire-build-deb

build-meson-image:
	docker build --target meson-builder -t sway_build_meson .

build-rust-image:
	docker build --target rust-builder -t sway_build_rust .

install-all-debs:
	cd debs/; ls -1 | tr '\n' '\0' | xargs -0 -n 1 basename | grep deb | grep -v ddeb | grep -v dev | grep -v skele | grep -v udeb | xargs sudo dpkg -i

yolo: build-everything install-all-debs
	echo "YOLO"

wlroots-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd wlroots; debuild -b -uc -us"
	make fix-permissions tidy

sway-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb; apt-get -f install; cd sway; debuild -b -uc -us'
	make fix-permissions tidy

swaylock-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb; cd swaylock; debuild -b -uc -us"
	make fix-permissions tidy

swayidle-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb; cd swayidle; debuild -b -uc -us"
	make fix-permissions tidy

swaybg-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb; cd swaybg; debuild -b -uc -us"
	make fix-permissions tidy

mako-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd mako; debuild -b -uc -us"
	make fix-permissions tidy

xdg-desktop-portal-wlr-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd xdg-desktop-portal-wlr; debuild -b -uc -us"
	make fix-permissions tidy

kanshi-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd kanshi; debuild -b -uc -us"
	make fix-permissions tidy

slurp-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd slurp; debuild -b -uc -us"
	make fix-permissions tidy

grim-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd grim; debuild -b -uc -us"
	make fix-permissions tidy

waybar-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd Waybar; debuild -b -uc -us"
	make fix-permissions tidy

wl-clipboard-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd wl-clipboard; debuild -b -uc -us"
	make fix-permissions tidy

nm-applet-build:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd network-manager-applet; debuild -b -uc -us"
	make fix-permissions tidy

wofi-build-install:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c "cd wofi/Release; make clean wofi"
	make fix-permissions tidy
	ln -sf $(shell pwd)/wofi/Release/wofi ~/bin/

clipman-install:
	cd clipman; go install; ln -sf ~/go/bin/clipman ~/bin/

wldash-install:
	docker run -t --rm -v $(shell pwd)/wldash:/workdir -w "/workdir" sway_build_rust sh -c "cargo build --release"
	make fix-permissions tidy
	ln -sf $(shell pwd)/wldash/target/release/wldash ~/bin

gtk-layer-shell-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'cd gtk-layer-shell; debuild -b -uc -us'
	make fix-permissions tidy

wfconfig-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb; apt-get -f install; cd wf-config; debuild -b -uc -us'
	make fix-permissions tidy

wcm-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/*wf-config*.deb debs/wayfire*.deb; apt-get -f install; cd wcm; debuild -b -uc -us'
	make fix-permissions tidy

wfshell-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb debs/libwf-config*.deb debs/libgtk-layer-shell*.deb; apt-get -f install; cd wf-shell; debuild -b -uc -us'
	make fix-permissions tidy

wayfire-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb debs/libwf-config*.deb; apt-get -f install; cd wayfire; debuild -b -uc -us'
	make fix-permissions tidy

carbonshell-build-deb:
	docker run -t --rm -v $(shell pwd):/workdir -w "/workdir" sway_build_meson sh -c 'dpkg -i debs/libwlroots0_*deb debs/libwlroots-dev*.deb debs/libwf-config*.deb debs/wayfire*.deb debs/libgtk-layer-shell*.deb; apt-get -f install; cd carbonshell; debuild -b -uc -us'
	make fix-permissions tidy

tidy:
	mkdir -p debs
	mkdir -p ddebs
	find . -maxdepth 1 -name '*.deb' -type f -print0 | xargs -0r mv -t debs/
	find . -maxdepth 1 -name '*.ddeb' -type f -print0 | xargs -0r mv -t ddebs/
	rm -f *build *buildinfo *changes *udeb

fix-permissions:
	sudo chown $(shell id -u):$(shell id -g) . -Rf

wlroots-clean:
	rm wlroots/build -Rf

wlroots-build:
	cd wlroots; meson build; ninja -C build

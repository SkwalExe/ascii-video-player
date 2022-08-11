all: build

build:
	mkdir -p build; \
	cd build; \
	cmake ..; \
	make;

install:
	[ -f build/ascii-video-player ] || (echo Please build first; exit 1)
	sudo cp build/ascii-video-player /usr/local/bin/

uninstall:
	sudo rm -f /usr/local/bin/ascii-video-player
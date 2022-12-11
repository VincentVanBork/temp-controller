
init: clean
	mkdir -p build
	cd ./build make && cmake ..

build-uf2:
	cd ./build && make main

clean:
	rm -rf ./build

flash:
	cp ./build/main.uf2 /media/${USER}/RPI-RP2/main.uf2
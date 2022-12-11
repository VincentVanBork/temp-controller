
init: clean
	mkdir -p build
	cd ./build make && cmake ..

build-uf2:
	cd ./build && make main

clean:
	rm -rf ./build

flash:
	cp ./build/main.uf2 /media/${USER}/RPI-RP2/main.uf2

monitor:
	sudo minicom -b 115200 -o -D /dev/ttyACM0

run: build-uf2 flash 
	sleep 2
	sudo minicom -b 115200 -o -D /dev/ttyACM0


all: release

clean:
	rm -fR build
	mkdir build

release: clean
	cd build ; cmake .. -DCMAKE_BUILD_TYPE=Release

debug: clean
	cd build ; cmake .. -DCMAKE_BUILD_TYPE=Debug

	

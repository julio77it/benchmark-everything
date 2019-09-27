

all: release

clean:
	rm -fR build/*

release: clean
	cd build ; cmake .. -DCMAKE_BUILD_TYPE=Release ; make

debug: clean
	cd build ; cmake .. -DCMAKE_BUILD_TYPE=Debug ; make

	

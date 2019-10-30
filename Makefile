CXX=arm-linux-gnueabihf-g++
ARCH=-march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard
FLAGS=$(ARCH) -Ofast -Wall -pthread -I/usr/local/include/RF24/.. -L/usr/local/lib -lrf24
PROG=pirf24

sources=$(wildcard *.cpp)

run:$(PROG)
	sudo ./$(PROG)

all: $(PROG)

$(PROG): main.cpp
	$(CXX) $(FLAGS) main.cpp tea.cpp -o $(PROG)
clean:
	rm -rf pirf24

#arm-linux-gnueabihf-g++ -march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Ofast -Wall -pthread -I/usr/local/include/RF24/.. -I.. -L/usr/local/lib receiver.cpp -lrf24 -o receiver

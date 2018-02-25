#------------------------------------------------------------------------------
SOURCE=lidar_test.cpp
PROGRAM=lidar_test
LIBRARIESPATH=/home/pi/Downloads/lidar_sdk/sdk/output/Linux/Release
LIBRARIES= lrplidar_sdk
CC=g++
#------------------------------------------------------------------------------
all: $(PROGRAM)

$(PROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -L $(LIBRARIESPATH) -$(LIBRARIES) -pthread -o$(PROGRAM)

clean:

	rm -f $(PROGRAM)

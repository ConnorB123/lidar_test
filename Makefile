#------------------------------------------------------------------------------

SOURCE=lidar_test.cpp
PROGRAM=lidar_test
INCLUDES=/home/pi/Downloads/lidar_sdk/sdk/sdk/include/*.h
LIBRARIESPATH=/home/pi/Downloads/lidar_sdk/sdk/output/Linux/Release
LIBRARIES= lrplidar_sdk
CC=g++

#------------------------------------------------------------------------------
all: $(PROGRAM)

$(PROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -I $(INCLUDES) -L $(LIBRARIESPATH) -$(LIBRARIES) -pthread -o$(PROGRAM)

clean:

	rm -f $(PROGRAM)

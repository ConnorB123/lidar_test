#------------------------------------------------------------------------------

SOURCE=lidar_test.cpp
PROGRAM=lidar_test
INCLUDES=/home/pi/Downloads/lidar_sdk/sdk/sdk/include/*.h
LIBRARIES=/home/pi/Downloads/lidar_sdk/sdk/output/Linux/Release/*.a
CC=g++

#------------------------------------------------------------------------------
all: $(PROGRAM)

$(PROGRAM): $(SOURCE)

	$(CC) -I$(INCLUDES) $(SOURCE) -o$(PROGRAM) -l$(LIBRARIES)

clean:

	rm -f $(PROGRAM)

#------------------------------------------------------------------------------

SOURCE=lidar_test.cpp
PROGRAM=lidar_test
INCLUDESPATH=/home/pi/Downloads/lidar_sdk/sdk/sdk/include
INCLUDES=-rplidar.h -rplidar_driver.h -rplidar_protocol.h -rptypes.h -rplidar_cmd.h
LIBRARIESPATH=/home/pi/Downloads/lidar_sdk/sdk/output/Linux/Release
LIBRARIES= lrplidar_sdk
CC=g++

#------------------------------------------------------------------------------
all: $(PROGRAM)

$(PROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -I $(INCLUDESPATH) $(INCLUDES) -L $(LIBRARIESPATH) -$(LIBRARIES) -pthread -o$(PROGRAM)

clean:

	rm -f $(PROGRAM)

#include <stdio.h>
#include <stdlib.h>

#include "rplidar.h"

using namespace rp::standalone::rplidar;

int main(int argc, char const *argv[]) {

  const char * opt_com_baudrate = 115200;
  RPlidarDriver * drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);

  do {
      // try to connect
      if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) {
          fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
              , opt_com_path);
          break;
      }
      drv->startMotor();

      // take only one 360 deg scan and display the result as a histogram
      ////////////////////////////////////////////////////////////////////////////////
      if (IS_FAIL(drv->startScan( /* true */ ))) // you can force rplidar to perform scan operation regardless whether the motor is rotating
      {
          fprintf(stderr, "Error, cannot start the scan operation.\n");
          break;
      }

      if (IS_FAIL(capture_and_display(drv))) {
          fprintf(stderr, "Error, cannot grab scan data.\n");
          break;

      }

  } while(0);

  drv->stop();
  drv->stopMotor();

  RPlidarDriver::DisposeDriver(drv);
  return 0;
}

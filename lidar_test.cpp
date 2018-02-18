#include <stdio.h>
#include <stdlib.h>

#include "rplidar.h"

using namespace rp::standalone::rplidar;

int main(int argc, char const *argv[]) {
  RPlidarDriver * drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);

  if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) {
      fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
          , opt_com_path);
      break;
  }

  op_result = drv->getDeviceInfo(devinfo);

  if (IS_FAIL(op_result)) {
      if (op_result == RESULT_OPERATION_TIMEOUT) {
          // you can check the detailed failure reason
          fprintf(stderr, "Error, operation time out.\n");
      } else {
          fprintf(stderr, "Error, unexpected error, code: %x\n", op_result);
          // other unexpected result
      }
      break;
  }

  drv->startMotor();

  if (IS_FAIL(drv->startScan( /* true */ ))) // you can force rplidar to perform scan operation regardless whether the motor is rotating
  {
      fprintf(stderr, "Error, cannot start the scan operation.\n");
      break;
  }

  if (IS_FAIL(capture_and_display(drv))) {
      fprintf(stderr, "Error, cannot grab scan data.\n");
      break;

  }

  drv->stop();
  drv->stopMotor();

  RPlidarDriver::DisposeDriver(drv);

  return 0;
}

#include <cstdio>
#include <cstdlib>
#include "rplidar.h"
#include <cstddef>


using namespace rp::standalone::rplidar;
using namespace std;

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

u_result capture_and_display(RPlidarDriver * drv)
{
    u_result ans;

    rplidar_response_measurement_node_t nodes[360*2];
    size_t count = _countof(nodes);

    printf("waiting for data...\n");

    // fetech extactly one 0-360 degrees' scan
    ans = drv->grabScanData(nodes, count);
    if (IS_OK(ans) || ans == RESULT_OPERATION_TIMEOUT) {
        drv->ascendScanData(nodes, count);
        //plot_histogram(nodes, count);

        printf("Do you want to see all the data? (y/n) ");
        int key = getchar();
        if (key == 'Y' || key == 'y') {
            for (int pos = 0; pos < (int)count ; ++pos) {
                printf("%s theta: %03.2f Dist: %08.2f \n",
                    (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ",
                    (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
                    nodes[pos].distance_q2/4.0f);
            }
        }
    } else {
        printf("error code: %x\n", ans);
    }

    return ans;
}

int main(int argc, char const *argv[]) {

  int opt_com_baudrate = 115200;
  const char * opt_com_path = "/dev/ttyUSB0";
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

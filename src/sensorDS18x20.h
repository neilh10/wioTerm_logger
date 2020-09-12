
#ifndef SRC_SENSOR_DS18X20_H_
#define SRC_SENSOR_DS18X20_H_
#include "Arduino.h"


//https://www.seeedstudio.com/DS18B20-Temperature-Sensor-Waterproof-Probe-p-4283.html
//https://github.com/milesburton/Arduino-Temperature-Control-Library
class sensorDS18x20 {
public:
int begin();
void doMeasurement(void);
float getMeasurement(int sensor_num);

private :


};

#endif // SRC_SENSOR_DS18X20_H_

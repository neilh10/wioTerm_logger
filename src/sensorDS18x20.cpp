/**
 * @file sensorDS18x20.cpp
 * @copyright 2020 Neil Hancock
 * Used for Wio Terminal testing,  mostly mashup 
 * @author neil hancock <neilh20@wllw.net>
 *
 * @brief UI Help
 */

// Included Dependencies
#include "sensorDS18x20.h"


//sensorDS18x20::sensorDS18x20() {}
//sensorDS18x20::~sensorDS18x20() {}

//sensorDS18x20:: {}


// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
#define insideThermometer 0
#define outsideThermometer 1
#define TotalThermometers 2
DeviceAddress sensorPhy[TotalThermometers];//insideThermometer, outsideThermometer;

// Assign address manually. The addresses below will need to be changed
// to valid device addresses on your bus. Device address can be retrieved
// by using either oneWire.search(deviceAddress) or individually via
// sensors.getAddress(deviceAddress, index)
// DeviceAddress sensorPhy[insideThermometer] = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
// DeviceAddress sensorPhy[outsideThermometer]   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}



// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

int sensorDS18x20::begin(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then
  // use those addresses and manually assign them (see above) once you know
  // the devices on your bus (and assuming they don't change).
  //
  // method 1: by index
  uint8_t   sensorsFound_Num=0;
  if (!sensors.getAddress(sensorPhy[insideThermometer], 0)) 
    {Serial.println("Unable to find any temperature Device 0");}
     else {
         sensorsFound_Num++;
        if (!sensors.getAddress(sensorPhy[outsideThermometer], 1)) 
        {Serial.println("Unable to find address for Device 1");}
        else {sensorsFound_Num++;}
     }
  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices,
  // or you have already retrieved all of them. It might be a good idea to
  // check the CRC to make sure you didn't get garbage. The order is
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(sensorPhy[insideThermometer])) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(sensorPhy[outsideThermometer])) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(sensorPhy[insideThermometer]);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(sensorPhy[outsideThermometer]);
  Serial.println();

  // set the resolution to 9 bit per device
  sensors.setResolution(sensorPhy[insideThermometer], TEMPERATURE_PRECISION);
  sensors.setResolution(sensorPhy[outsideThermometer], TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(sensorPhy[insideThermometer]), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(sensorPhy[outsideThermometer]), DEC);
  Serial.println();
}



/*
   Main function, calls the temperatures in a loop.
*/

void sensorDS18x20::doMeasurement(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  // print the device information
  printData(sensorPhy[insideThermometer]);
  printData(sensorPhy[outsideThermometer]);
}

// function to print the temperature for a device
float getTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
  }
 return tempC;
}
float sensorDS18x20::getMeasurement(int sensor_num)
{
  // print the device information
  return getTemperature(sensorPhy[sensor_num]);
  
}







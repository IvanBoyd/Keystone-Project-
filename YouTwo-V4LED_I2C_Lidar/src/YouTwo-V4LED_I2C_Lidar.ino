/*
 * Project YouTwo-V4LED_I2C_Lidar.ino
 * Description: Basic Test of the Garmin Lidar Distance Sensor returning distance
 *                values in centimetres
 *                1 cm = 0.39370079 inch, 1 meter = 39.3700787 inches & 1.0936133 yards, 1 mile = 1609.344 meters
 * Author:      Ivan Boyd
 * Date:        11/29/21
 */

/*------------------------------------------------------------------------------
  SDA, pin 0  Yellow wire   LIDAR-Lite I2C SDA 
  SCL, pin 1  Green wire    LIDAR-Lite I2C SCL 

  Optional connections to utilize GPIO triggering:
  D5, pin 5   White wire    LIDAR-Lite GPIOA   (pin 5) to Arduino Digital 2
  D6, pin 6   Blue wire     LIDAR-Lite GPIOB   (pin 6) to Arduino Digital 3
------------------------------------------------------------------------------*/
#include "Wire.h"
#include "LIDARLite_v4LED.h"

LIDARLite_v4LED myLidarLite;
uint8_t  newDistance;
uint16_t distance;
#define FAST_I2C

#define MonitorPin    SDA        
#define TriggerPin    SCL         

SYSTEM_MODE(SEMI_AUTOMATIC); //Using BLE and not Wifi

void setup()
{
    Serial.begin(9600);
    Wire.begin();            // Initialize  I2C (for communication to LidarLite)
}

void loop()       {
  newDistance = distanceSingle(&distance);
  if (newDistance) {
    Serial.println(distance);
  }
  delay(500);
}


//---------------------------------------------------------------------
// Read Single Distance Measurement
//
// This is the simplest form of taking a measurement. This is a
// blocking function as it will not return until a range has been
// taken and a new distance measurement can be read.
//---------------------------------------------------------------------
uint8_t distanceSingle(uint16_t *distance)  {
    myLidarLite.takeRange();                      // 1. Trigger range measurement.
    myLidarLite.waitForBusy();                    // 2. Wait for busyFlag to indicate device is idle.
    *distance = myLidarLite.readDistance();       // 3. Read new distance data from device registers
    return 1;
}

#include <IS_Sensors.h>
#include <IS_Bluetooth.h>

Sensor light_sensor;

void setup() {
  // Инициализируем работу I2C
  Wire.begin();
  // Инициализируем работу UART
  Serial.begin(115200, SERIAL_8E1);
}

void loop() {
  char msg = Serial.read();
  if (msg == 'b') {
    enter_bootloader();
  }

  uint8_t data_array[2];

  light_sensor.I2Cread(0x50, 0, 2, data_array);
  int16_t light1 = data_array[1] << 8 | data_array[0];
  light_sensor.I2Cread(0x51, 0, 2, data_array);
  int16_t light2 = data_array[1] << 8 | data_array[0];
  light_sensor.I2Cread(0x52, 0, 2, data_array);
  int16_t light3 = data_array[1] << 8 | data_array[0];
  light_sensor.I2Cread(0x53, 0, 2, data_array);
  int16_t light4 = data_array[1] << 8 | data_array[0];

  Serial.println("Light data");
  Serial.print (light1, DEC);
  Serial.print ("\t");
  Serial.print (light2, DEC);
  Serial.print ("\t");
  Serial.print (light3, DEC);
  Serial.print ("\t");
  Serial.print (light4, DEC);
  Serial.println("");

  delay(1000);

}

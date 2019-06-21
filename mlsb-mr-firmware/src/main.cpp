#include <Arduino.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#include "lib/wscomm/WsComm.h"
#include "lib/i2cscan/I2CScan.h"
#include "MlsbMrConfig.h"

const int WIRING_I2C_SDA = D3;
const int WIRING_I2C_SCL = D4;
const uint8_t I2C_ADDRESSING_MPU6050_ANTERIOR = 0x68;

WsComm remoteComm;
MPU6050 mpu(I2C_ADDRESSING_MPU6050_ANTERIOR);

void setup()
{
	delay(3500);

	Serial.begin(115200);
	Serial.println("serial_init_done");

	Wire.begin(WIRING_I2C_SDA, WIRING_I2C_SCL);
	I2CScan::scanI2CDevices();
	delay(500);
	Serial.println("i2c_init_done");

	mpu.initialize();
	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
	Serial.println("mpu_init_done");

	remoteComm.connect();
}

int16_t ax = 0, ay = 0, az = 0;
int16_t gx = 0, gy = 0, gz = 0;
bool mpuConn = false;
uint8_t i = 0;
char msgbuf[60];

void loop()
{
	mpuConn = mpu.testConnection();
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	delay(1); // esp8266 needs thread yielding for proper functioning of the network stack

	sprintf(msgbuf, "<%d> mpuConn=%d a[x=%d y=%d z=%d] g[x=%d y=%d z=%d]", i++, mpuConn, ax, ay, az, gx, gy, gz);
	Serial.println(msgbuf);
	remoteComm.send(msgbuf);
	delay(250);
}

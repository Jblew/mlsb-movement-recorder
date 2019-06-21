#include <Arduino.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#include "lib/wscomm/WsComm.h"
#include "lib/i2cscan/I2CScan.h"
#include "MlsbMrConfig.h"



#define WIRING_I2C_SDA D3
#define WIRING_I2C_SCL D4
#define I2C_ADDRESSING_MPU6050_ANTERIOR 0x68
#define FPS 10




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

	if (mpuConn) {
		sprintf(msgbuf, 
			"{\"i\":%d,\"ax\":%d,\"ay\":%d,\"az\":%d,\"gx\":%d,\"gy\":%d,\"gz\":%d}", 
			i++, ax, ay, az, gx, gy, gz);
	}
	else sprintf(msgbuf, "{\"error\":\"accelerometer_not_connected\"}");
	
	Serial.println(msgbuf);
	remoteComm.send(msgbuf);
	delay(250);
}

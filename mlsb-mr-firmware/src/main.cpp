#include <Arduino.h>
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#include "lib/wscomm/WsComm.h"
#include "lib/i2cscan/I2CScan.h"
#include "MlsbMrConfig.h"

//
//
#define WIRING_I2C_SDA D3
#define WIRING_I2C_SCL D4
#define I2C_ADDRESSING_MPU6050_ANTERIOR 0x68
#define FPS 25

const unsigned long loopIntervalMc = 1000 * 1000 / FPS;

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
	mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
	mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
	Serial.println("mpu_init_done");

	remoteComm.connect();
}

int16_t ax = 0, ay = 0, az = 0;
int16_t gx = 0, gy = 0, gz = 0;
bool mpuConn = false;
int loopI = 0;
char msgbuf[200];

unsigned long loopStime = 0;
unsigned long loopTookMc = 0;
void loop()
{
	loopStime = micros();
	mpuConn = mpu.testConnection();
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	delay(1); // esp8266 needs thread yielding for proper functioning of the network stack

	if (mpuConn)
	{
		sprintf(msgbuf,
				"{\"i\":%d,\"t\":%lu,\"ax\":%d,\"ay\":%d,\"az\":%d,\"gx\":%d,\"gy\":%d,\"gz\":%d,\"asc\":2,\"gsc\":250}",
				loopI, millis(), ax, ay, az, gx, gy, gz);
	}
	else
		sprintf(msgbuf, "{\"i\":%d,\"error\":\"accelerometer_not_connected\",\"ax\":%d}", loopI, ax);

	Serial.println(msgbuf);
	delay(1);
	remoteComm.send(msgbuf);
	delay(1);

	loopTookMc = micros() - loopStime;
	if (loopTookMc < loopIntervalMc)
	{
		delayMicroseconds(loopIntervalMc - loopTookMc);
	}
	else
	{
		sprintf(msgbuf, "{\"i\":%d,\"error\":\"cannot_keep_fps\"}", loopI);
		Serial.println(msgbuf);
	}
	loopI++;
}

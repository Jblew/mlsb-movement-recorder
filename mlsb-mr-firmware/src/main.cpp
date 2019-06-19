#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "MlsbMrConfig.h"
#include "lib/wscomm/WsComm.h"


WsComm remoteComm;

void setup() {
	Serial.begin(115200);
	remoteComm.connect();
}



uint8_t i = 0;
char msgbuf[50];

void loop() {
	sprintf(msgbuf, "Msg to remote %d", i++);
	Serial.println(msgbuf);
	remoteComm.send(msgbuf);
	delay(500);
}
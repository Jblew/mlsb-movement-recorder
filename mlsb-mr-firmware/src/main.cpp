#include <Arduino.h>
#include "WebSocketClient.h"
#include "ESP8266WiFi.h"

WebSocketClient ws(false);

const char wifiSSID[] = "UPCF18384A";
const char wifiPassword[] = "";
const char websocketHost[] = "192.168.0.11";
const int websocketPort = 4114;


void setup() {
	Serial.begin(115200);
	WiFi.begin(wifiSSID, wifiPassword);

	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
}


uint8_t i = 0;

char msgbuf[40];

void loop() {
	if (!ws.isConnected()) {
		Serial.println("ws_conn_pend");
		ws.connect(websocketHost, "/", websocketPort);
	} else {
		Serial.println("ws_send");
    	sprintf(msgbuf, "Hello %d", i++);
		ws.send(msgbuf);
		Serial.println("ws_send_done");
	}
	delay(500);
}
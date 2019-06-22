#include "ESP8266WiFi.h"
#include "../websocketclient/WebSocketClient.h"
#include "../../MlsbMrConfig.h"

#include "WsComm.h"

// #define DEBUG 1

#ifdef DEBUG
#define DEBUG_WSC(MSG) Serial.println(MSG)
#else
#define DEBUG_WSC(MSG)
#endif

WsComm::WsComm()
{
	this->ws = new WebSocketClient(false);
}

void WsComm::connect()
{
	WiFi.begin(MlsbMrConfig::wifiSSID, MlsbMrConfig::wifiPassword);

	Serial.print("Wifi Connecting");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.print("Wifi connected");
}

void WsComm::send(const char *msg)
{
	DEBUG_WSC("wscomm_send");
	if (!this->ws->isConnected())
	{
		DEBUG_WSC("ws_conn_pend");
		this->ws->connect(MlsbMrConfig::websocketHost, "/", MlsbMrConfig::websocketPort);
	}
	else
	{
		DEBUG_WSC("ws_send");
		this->ws->send(msg);
		DEBUG_WSC("ws_send_done");
	}
}
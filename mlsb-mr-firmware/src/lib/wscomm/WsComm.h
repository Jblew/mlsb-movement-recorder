
#include "../websocketclient/WebSocketClient.h"

#ifndef WSCOMM_H
#define WSCOMM_H


class WsComm {
public:
    WsComm();
    void connect();
    void send(const char *str);
private:
    WebSocketClient *ws;
};

#endif //WSCOMM_H
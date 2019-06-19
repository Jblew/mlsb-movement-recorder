
#ifndef MLSBMRCONFIG_H
#define MLSBMRCONFIG_H

class MlsbMrConfig {
public:
    MlsbMrConfig ();

    static const char *wifiSSID;
    static const char *wifiPassword;
    static const char *websocketHost;
    static const int   websocketPort;
};

#endif // MLSBMRCONFIG_H

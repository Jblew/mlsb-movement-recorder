// tslint:disable no-console

import * as WebSocket from "ws";

import { config } from "./config";
//

const wss = new WebSocket.Server({ port: config.port });

wss.on("connection", function connection(ws) {
    ws.on("message", function incoming(message) {
        console.log("<WS>%s ", message);
    });
});

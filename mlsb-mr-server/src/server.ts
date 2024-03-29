// tslint:disable no-console

import * as WebSocket from "ws";

import { config } from "./config";
//

const wss = new WebSocket.Server({ port: config.port, path: "/" });

wss.on("connection", function connection(ws) {
    ws.on("message", function incoming(message) {
        console.log("<WS>%s ", message);
    });
});

wss.on("error", function connection(error) {
    console.error(error);
});

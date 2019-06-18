// tslint:disable no-console

import * as BluebirdPromise from "bluebird";
import * as WebSocket from "ws";

import { config } from "./config";
//

const ws = new WebSocket(`ws://${config.host}:${config.port}`);

ws.on("open", function() {
    (async () => {
        let i: number = 0;
        while (true) {
            ws.send(`Msg ${i++}`);
            await BluebirdPromise.delay(500);
        }
    })();
});

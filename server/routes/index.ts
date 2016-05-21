/// <reference path="../alarm-clock.d.ts" />
import * as express from "express-serve-static-core";

export default function(app: express.Application) {
  app.get('/', function(req: express.Request, res: express.Response, next: express.NextFunction) {
    res.send('Hello World');
  });
}
